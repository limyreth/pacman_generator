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

static const int MAX_CHOICES = 100;  // the max depth of choices to generate into

Generator::Generator() 
:   choice_tree(MAX_CHOICES)
{
    alpha_betas.reserve(MAX_CHOICES);
    ASSERT_INVARIANTS();
}

void Generator::run() {
    minimax();
    ASSERT_INVARIANTS();
}

int translate(int i) {
    return MAX_CHOICES - i - 1;
}

int Generator::get_alpha() const {
    for (int i = alpha_betas.size() -1; i >= 0; ++i) {
        if (choice_tree.get(translate(i)).player == 0) {
            return alpha_betas.at(i);
        }
        ++i;
    }
    return 0;
}

int Generator::get_beta() const {
    for (int i = alpha_betas.size() -1; i >= 0; ++i) {
        if (choice_tree.get(translate(i)).player != 0) {
            return alpha_betas.at(i);
        }
        ++i;
    }
    return 999999999; // +infinity TODO calculate and set this to MAX_SCORE, have it in Spec constants
}

void Generator::push_alpha_beta() {
    const ChoiceNode node = choice_tree.get();
    int alpha_beta = node.player == 0 ? get_alpha() : get_beta();
    alpha_betas.push_back(alpha_beta);

    ASSERT_INVARIANTS();
}

void Generator::pop_alpha_beta() {
    alpha_betas.pop_back();
    ASSERT_INVARIANTS();
}

/*
 * Explore all choices of current choice node
 */
int Generator::minimax() {
    REQUIRE(!choice_tree.is_leaf());

    choice_tree.first_child();
    push_alpha_beta();

    while (choice_tree.next_sibling() &&
            get_alpha() >= get_beta()) {  // alpha beta pruning
            
        if (choice_tree.is_leaf()) {
            // TODO if is better than current best, save current path as best
            int score = choice_tree.get_score();
            choice_tree.parent();
            pop_alpha_beta();
            ASSERT_INVARIANTS();
            return score;
        }

        // explore choices of child
        int value = minimax();

        // process the alpha_beta value it returned
        if (choice_tree.get().player == 0) {
            if (value > get_alpha()) {
                alpha_betas.back() = value;
            }
        }
        else {
            if (value < get_beta()) {
                alpha_betas.back() = value;
            }
        }

        ASSERT_INVARIANTS();
    }

    choice_tree.parent();
    pop_alpha_beta();
    ASSERT_INVARIANTS();
    return alpha_betas.back();
}

void Generator::invariants() {
    INVARIANT(alpha_betas.capacity() == MAX_CHOICES);

    INVARIANT(get_alpha() >= 0);
    INVARIANT(get_beta() >= 0);

    // Invariant: the action field of all ancestors is valid and shows the path
    // to the current node
}


}}
