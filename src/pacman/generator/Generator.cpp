/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Generator.h"
#include "../util/serialization.h"

#include <valgrind/callgrind.h>

using namespace PACMAN::MODEL;
using namespace PACMAN::SPECIFICATION;

using std::vector;
using std::cout;
using std::endl;

namespace PACMAN {
    namespace GENERATOR {

Generator::Generator(ChoiceTree& tree) 
:   is_running(false),
    should_stop(false),
    choice_tree(tree),
    paths(choice_tree.get_max_depth()+1),
    child_value(-1),
    child_action(-1),
    search_complete(false)
{
    INVARIANTS_ON_EXIT;
    //REQUIRE(choice_tree's player 0 is the MAXing player, all other players are MINs)
    for (unsigned int depth=0u; depth <= choice_tree.get_max_depth(); ++depth) {
        paths.at(depth).reserve(choice_tree.get_max_depth() - depth);
    }
}

Generator::Generator(std::istream& in, ChoiceTree& tree) 
:   is_running(false),
    should_stop(false),
    choice_tree(tree),
    paths(choice_tree.get_max_depth()+1)
{
    INVARIANTS_ON_EXIT;
    read(in, child_value);
    read(in, child_action);
    read(in, search_complete);

    for (unsigned int depth=0u; depth <= choice_tree.get_max_depth(); ++depth) {
        paths.at(depth).reserve(choice_tree.get_max_depth() - depth);
    }

    for (auto& path : paths) {
        vector<Action>::size_type size;
        read(in, size);
        path.resize(size);
        in.read((char*)path.data(), path.size() * sizeof(Action));
    }
}

void Generator::run() {
    INVARIANTS_ON_EXIT;
    if (!search_complete) {
        CALLGRIND_START_INSTRUMENTATION;
        minimax();
        CALLGRIND_STOP_INSTRUMENTATION;
        CALLGRIND_DUMP_STATS;
    }
}

void Generator::stop() {
    should_stop = true;
}

int Generator::get_best_score() const {
    REQUIRE(search_complete);
    return choice_tree.get().alpha_beta;
}
const vector<Action>& Generator::get_best_path() const {
    REQUIRE(search_complete);
    return paths.at(0);
}

int Generator::get_alpha() const {
    return get_alpha(choice_tree.get_depth());
}

int Generator::get_alpha(int depth) const {
    for (int i = depth; i >= 0; --i) {
        auto node = choice_tree.get(i);
        if (node.player == 0) {  // is maxing player
            return node.alpha_beta;
        }
    }
    return 0;
}

int Generator::get_beta() const {
    return get_beta(choice_tree.get_depth());
}

int Generator::get_beta(int depth) const {
    for (int i = depth; i >= 0; --i) {
        auto node = choice_tree.get(i);
        if (node.player != 0) {
            return node.alpha_beta;
        }
    }
    return 999999999; // +infinity TODO calculate and set this to MAX_SCORE, have it in Spec constants
}

/*
 * Explore all choices of current choice node
 */
void Generator::minimax() {
    INVARIANTS_ON_EXIT;
    REQUIRE(!is_running);
    is_running = true;
    print_completion();
    while (!search_complete && !should_stop) {
        auto& best_path = paths.at(choice_tree.get_depth());

        if (choice_tree.is_leaf()) {
            child_value = choice_tree.get_score();
            child_action = choice_tree.parent();
            paths.at(choice_tree.get_depth()).clear();
        }
        else {
            if (choice_tree.is_first_child()) {
                // Start search under a node
                const ChoiceNode node = choice_tree.get();
                choice_tree.set_alpha_beta(node.player == 0 ? get_alpha(choice_tree.get_depth()-1) : get_beta(choice_tree.get_depth()-1));
                best_path.clear();
            }
            else {
                auto& child_path = paths.at(choice_tree.get_depth()+1);

                // Process the alpha_beta returned by child
                bool is_better_child = choice_tree.get().player == 0 ?
                        child_value > get_alpha() :
                        child_value < get_beta();

                if (is_better_child) {
                    choice_tree.set_alpha_beta(child_value);
                    best_path.clear();
                    best_path.push_back(child_action);
                    best_path.insert(best_path.end(), child_path.begin(), child_path.end());
                }
            }

            ASSERT(get_alpha() >= 0);
            ASSERT(get_beta() >= 0);
            bool continued_search = get_alpha() < get_beta()  // pruning
                                    && choice_tree.next_child();  // get the next choice

            if (!continued_search) {
                if (choice_tree.get_depth() == 0) {
                    search_complete = true;
                }
                else {
                    child_value = choice_tree.get().alpha_beta;
                    choice_tree.parent();
                }
            }
        }
    }
    print_completion();

    if (search_complete) {
        cout << endl
            << endl
            << "Search complete!" << endl
            << endl
            << endl;
    }

    is_running = false;
    ENSURE(!search_complete || choice_tree.get_depth() == 0);
}

void Generator::print_completion() const {
    double completion = choice_tree.get_completion();

    auto old_precision = cout.precision();
    cout.precision(20);
    cout << "Completion: " << completion << endl;
    cout.precision(old_precision);
}

void Generator::save(std::ostream& out) const {
    REQUIRE(!is_running);

    write(out, child_value);
    write(out, child_action);
    write(out, search_complete);

    for (auto path : paths) {
        write(out, path.size());
        out.write((const char*)path.data(), path.size() * sizeof(Action));
    }
}

bool Generator::operator==(const Generator& other) const {
    if (other.paths.size() != paths.size()) {
        return false;
    }

    for (unsigned int i=0u; i < paths.size(); ++i) {
        auto& path = paths.at(i);
        auto& opath = other.paths.at(i);
        if (opath != path || opath.capacity() != path.capacity()) {
            return false;
        }
    }

    return other.child_value == child_value &&
        other.child_action == child_action &&
        other.search_complete == search_complete;
}

void Generator::invariants() const {
    for (unsigned int depth=0u; depth <= choice_tree.get_max_depth(); ++depth) {
        INVARIANT(paths.at(depth).capacity() == choice_tree.get_max_depth() - depth);
    }
}


}}
