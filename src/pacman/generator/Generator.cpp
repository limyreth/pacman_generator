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

using namespace PACMAN::MODEL;
using namespace PACMAN::SPECIFICATION;

using std::vector;
using std::cout;
using std::endl;

namespace PACMAN {
    namespace GENERATOR {

Generator::Generator(ChoiceTree& tree) 
:   choice_tree(tree),
    child_value(-1),
    child_action(-1),
    paths(choice_tree.get_max_depth()+1),
    should_stop(false),
    search_complete(false)
{
    INVARIANTS_ON_EXIT;
    for (int depth=0; depth <= choice_tree.get_max_depth(); ++depth) {
        paths.at(depth).reserve(choice_tree.get_max_depth() - depth);
    }
}

Generator::Generator(std::istream& in, ChoiceTree& tree) 
:   choice_tree(tree),
    paths(choice_tree.get_max_depth()+1)
{
    INVARIANTS_ON_EXIT;
    read(in, child_value);
    read(in, child_action);
    read(in, search_complete);

    for (int depth=0; depth <= choice_tree.get_max_depth(); ++depth) {
        paths.at(depth).reserve(choice_tree.get_max_depth() - depth);
    }

    for (auto& path : paths) {
        vector<Action>::size_type size;
        read(in, size);
        path.resize(size);
        in.read((char*)path.data(), path.size() * sizeof(Action));
    }
}

void Generator::start() {
    INVARIANTS_ON_EXIT;
    REQUIRE(thread.get_id() == std::thread::id()); // Not already running; current thread invalid
    if (!search_complete) {
        thread = std::thread(&Generator::minimax, this);
    }
}

void Generator::stop() {
    should_stop = true;
}

void Generator::join() {
    thread.join();
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
    while (!search_complete && !should_stop) {
        INVARIANTS_ON_EXIT;
        auto& best_path = paths.at(choice_tree.get_depth());
        ASSERT(best_path.capacity() == choice_tree.get_max_depth() - choice_tree.get_depth());  // assert we reserved the right amount

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
            //std::cout << "alpha " << get_alpha() << ", beta " << get_beta() << std::endl;
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

    if (search_complete) {
        cout << endl
            << endl
            << "Search complete!" << endl
            << endl
            << endl;
    }

    ENSURE(!search_complete || choice_tree.get_depth() == 0);
}

void Generator::save(std::ostream& out) const {
    // TODO when saving must sync with end of loop iteration, and end that thread...
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

    for (int i=0; i < paths.size(); ++i) {
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
    // Invariant: the action field of all ancestors is valid and shows the path
    // to the current node
}


}}
