/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "Generator.h"

#include "../util/assertion.h"

namespace PACMAN {

    using namespace MODEL;
    using namespace SPECIFICATION;

    namespace GENERATOR {

Generator::Generator(ChoiceTree& tree) 
:   choice_tree(tree)
{
    ASSERT_INVARIANTS();
}

void Generator::run(int& best_score) {
    minimax();
    best_score = choice_tree.get().alpha_beta;
    ASSERT_INVARIANTS();
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

void Generator::push_alpha_beta() {

    ASSERT_INVARIANTS();
}

/*
 * Explore all choices of current choice node
 */
void Generator::minimax() {
    REQUIRE(choice_tree.get_depth() == 0);

    int child_value;
    bool search_complete = false;
    while (!search_complete) {
        if (choice_tree.is_leaf()) {
            // TODO if is better than current best, save current path as best
            child_value = choice_tree.get_score();
            choice_tree.parent();
        }
        else {
            if (choice_tree.is_first_child()) {
                // Start search under a node
                const ChoiceNode node = choice_tree.get();
                choice_tree.set_alpha_beta(node.player == 0 ? get_alpha(choice_tree.get_depth()-1) : get_beta(choice_tree.get_depth()-1));
            }
            else {
                // Process the alpha_beta returned by child
                if (choice_tree.get().player == 0) {
                    if (child_value > get_alpha()) {
                        choice_tree.set_alpha_beta(child_value);
                    }
                }
                else {
                    if (child_value < get_beta()) {
                        choice_tree.set_alpha_beta(child_value);
                    }
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

        ASSERT_INVARIANTS();
    }

    ENSURE(choice_tree.get_depth() == 0);
}

void Generator::invariants() {
    // Invariant: the action field of all ancestors is valid and shows the path
    // to the current node
}


}}
