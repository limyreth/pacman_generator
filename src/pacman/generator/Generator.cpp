/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Generator.h"

using namespace PACMAN::MODEL;
using namespace PACMAN::SPECIFICATION;

using std::vector;

namespace PACMAN {
    namespace GENERATOR {

Generator::Generator(ChoiceTree& tree) 
:   choice_tree(tree)
{
    INVARIANTS_ON_EXIT;
}

void Generator::run(int& best_score) {
    INVARIANTS_ON_EXIT;
    auto best_path = minimax();
    best_score = choice_tree.get().alpha_beta;
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
vector<Action> Generator::minimax() {
    REQUIRE(choice_tree.get_depth() == 0);

    vector<vector<Action>> paths(choice_tree.get_max_depth()+1);
    for (int depth=0; depth <= choice_tree.get_max_depth(); ++depth) {
        paths.at(depth).reserve(choice_tree.get_max_depth() - depth);
    }

    int child_value;
    bool search_complete = false;
    int child_action = -1; // the action used to get to the child we just examined
    while (!search_complete) {
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

    ENSURE(choice_tree.get_depth() == 0);
    return paths.at(0);
}

void Generator::invariants() const {
    // Invariant: the action field of all ancestors is valid and shows the path
    // to the current node
}


}}
