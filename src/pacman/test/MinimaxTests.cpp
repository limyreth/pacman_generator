/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "MinimaxTests.h"
#include "ChoiceTree.h"
#include "GameTree.h"
#include "../generator/Generator.h"
#include "../util/assertion.h"

using std::cout;
using std::endl;
using std::shared_ptr;

namespace PACMAN {
    namespace TEST {

shared_ptr<TreeNode> MinimaxTests::build_tree() {
    // TODO include pic of tree for later reference (taken from ai course)

    // node numbering n{height}{child_index}
    shared_ptr<TreeNode> n1_1(new TreeNode);
    n1_1->score = 0;
    n1_1->player = 0;

    shared_ptr<TreeNode> n2_1(new TreeNode);
    n2_1->score = 0;
    n2_1->player = 1;

    shared_ptr<TreeNode> n2_2(new TreeNode);
    n2_2->score = 0;
    n2_2->player = 1;

    shared_ptr<TreeNode> n3_1(new TreeNode);
    n3_1->score = 0;
    n3_1->player = 0;

    shared_ptr<TreeNode> n3_2(new TreeNode);
    n3_2->score = 0;
    n3_2->player = 0;

    shared_ptr<TreeNode> n3_3(new TreeNode);
    n3_3->score = 0;
    n3_3->player = 0;

    shared_ptr<TreeNode> n3_4(new TreeNode);
    n3_4->score = 0;
    n3_4->player = 1;

    shared_ptr<TreeNode> n4_1(new TreeNode);
    n4_1->score = 0;
    n4_1->player = 1;

    shared_ptr<TreeNode> n4_2(new TreeNode);
    n4_2->score = 0;
    n4_2->player = 1;

    shared_ptr<TreeNode> n4_3(new TreeNode);
    n4_3->score = 0;
    n4_3->player = 1;

    shared_ptr<TreeNode> n4_4(new TreeNode);
    n4_4->score = 0;
    n4_4->player = 1;

    shared_ptr<TreeNode> n4_5(new TreeNode);
    n4_5->score = 0;
    n4_5->player = 1;

    shared_ptr<TreeNode> n4_6(new TreeNode);
    n4_6->score = 0;
    n4_6->player = 1;

    shared_ptr<TreeNode> n5_1(new TreeNode);
    n5_1->score = 0;
    n5_1->player = 0;

    shared_ptr<TreeNode> n5_2(new TreeNode);
    n5_2->score = 0;
    n5_2->player = 0;

    shared_ptr<TreeNode> n5_3(new TreeNode);
    n5_3->score = 0;
    n5_3->player = 0;

    shared_ptr<TreeNode> n5_4(new TreeNode);
    n5_4->score = 0;
    n5_4->player = 0;

    shared_ptr<TreeNode> n5_5(new TreeNode);
    n5_5->score = 0;
    n5_5->player = 0;

    shared_ptr<TreeNode> n5_6(new TreeNode);
    n5_6->score = 0;
    n5_6->player = 0;

    shared_ptr<TreeNode> n5_7(new TreeNode);
    n5_7->score = 0;
    n5_7->player = 0;

    shared_ptr<TreeNode> n5_8(new TreeNode);
    n5_8->score = 0;
    n5_8->player = 0;

    shared_ptr<TreeNode> n6_1(new TreeNode);
    n6_1->score = 0;
    n6_1->player = 1;

    shared_ptr<TreeNode> n6_2(new TreeNode);
    n6_2->score = 0;
    n6_2->player = 1;

    shared_ptr<TreeNode> n6_3(new TreeNode);
    n6_3->score = 0;
    n6_3->player = 1;

    shared_ptr<TreeNode> n6_4(new TreeNode);
    n6_4->score = 0;
    n6_4->player = 1;

    shared_ptr<TreeNode> n6_5(new TreeNode);
    n6_5->score = 0;
    n6_5->player = 1;

    shared_ptr<TreeNode> n6_6(new TreeNode);
    n6_6->score = 0;
    n6_6->player = 1;

    shared_ptr<TreeNode> n6_7(new TreeNode);
    n6_7->score = 0;
    n6_7->player = 1;

    shared_ptr<TreeNode> n6_8(new TreeNode);
    n6_8->score = 0;
    n6_8->player = 1;

    shared_ptr<TreeNode> n6_9(new TreeNode);
    n6_9->score = 0;
    n6_9->player = 1;

    shared_ptr<TreeNode> n6_10(new TreeNode);
    n6_10->score = 0;
    n6_10->player = 1;

    shared_ptr<TreeNode> n6_11(new TreeNode);
    n6_11->score = 0;
    n6_11->player = 1;

    shared_ptr<TreeNode> n6_12(new TreeNode);
    n6_12->score = 0;
    n6_12->player = 1;

    shared_ptr<TreeNode> n6_13(new TreeNode);
    n6_13->score = 0;
    n6_13->player = 1;

    shared_ptr<TreeNode> n7_1(new TreeNode);
    n7_1->score = 10;
    n7_1->player = 0;

    shared_ptr<TreeNode> n7_2(new TreeNode);
    n7_2->score = 15;
    n7_2->player = 0;

    shared_ptr<TreeNode> n7_3(new TreeNode);
    n7_3->score = 7;
    n7_3->player = 0;

    shared_ptr<TreeNode> n7_4(new TreeNode);
    n7_4->score = 13;
    n7_4->player = 0;

    shared_ptr<TreeNode> n7_5(new TreeNode);
    n7_5->score = 13;
    n7_5->player = 0;

    shared_ptr<TreeNode> n7_6(new TreeNode);
    n7_6->score = 7;
    n7_6->player = 0;

    shared_ptr<TreeNode> n7_7(new TreeNode);
    n7_7->score = 10;
    n7_7->player = 0;

    shared_ptr<TreeNode> n7_8(new TreeNode);
    n7_8->score = 12;
    n7_8->player = 0;

    shared_ptr<TreeNode> n7_9(new TreeNode);
    n7_9->score = 8;
    n7_9->player = 0;

    shared_ptr<TreeNode> n7_10(new TreeNode);
    n7_10->score = 13;
    n7_10->player = 0;

    shared_ptr<TreeNode> n7_11(new TreeNode);
    n7_11->score = 15;
    n7_11->player = 0;

    shared_ptr<TreeNode> n7_12(new TreeNode);
    n7_12->score = 12;
    n7_12->player = 0;

    shared_ptr<TreeNode> n7_13(new TreeNode);
    n7_13->score = 15;
    n7_13->player = 0;

    shared_ptr<TreeNode> n7_14(new TreeNode);
    n7_14->score = 5;
    n7_14->player = 0;

    shared_ptr<TreeNode> n7_15(new TreeNode);
    n7_15->score = 10;
    n7_15->player = 0;

    shared_ptr<TreeNode> n7_16(new TreeNode);
    n7_16->score = 11;
    n7_16->player = 0;

    shared_ptr<TreeNode> n7_17(new TreeNode);
    n7_17->score = 15;
    n7_17->player = 0;

    shared_ptr<TreeNode> n7_18(new TreeNode);
    n7_18->score = 11;
    n7_18->player = 0;

    shared_ptr<TreeNode> n7_19(new TreeNode);
    n7_19->score = 7;
    n7_19->player = 0;

    shared_ptr<TreeNode> n7_20(new TreeNode);
    n7_20->score = 10;
    n7_20->player = 0;

    shared_ptr<TreeNode> n7_21(new TreeNode);
    n7_21->score = 5;
    n7_21->player = 0;

    shared_ptr<TreeNode> n7_22(new TreeNode);
    n7_22->score = 15;
    n7_22->player = 0;

    shared_ptr<TreeNode> n7_23(new TreeNode);
    n7_23->score = 7;
    n7_23->player = 0;

    shared_ptr<TreeNode> n7_24(new TreeNode);
    n7_24->score = 13;
    n7_24->player = 0;

    shared_ptr<TreeNode> n7_25(new TreeNode);
    n7_25->score = 12;
    n7_25->player = 0;

    n1_1->children.push_back(n2_1);
    n2_1->parent = n1_1;

    n1_1->children.push_back(n2_2);
    n2_2->parent = n1_1;

    n2_1->children.push_back(n3_1);
    n3_1->parent = n2_1;

    n2_1->children.push_back(n3_2);
    n3_2->parent = n2_1;

    n2_2->children.push_back(n3_3);
    n3_3->parent = n2_2;

    n2_2->children.push_back(n3_4);
    n3_4->parent = n2_2;

    n3_1->children.push_back(n4_1);
    n4_1->parent = n3_1;

    n3_2->children.push_back(n4_2);
    n4_2->parent = n3_2;

    n3_2->children.push_back(n4_3);
    n4_3->parent = n3_2;

    n3_3->children.push_back(n4_4);
    n4_4->parent = n3_3;

    n3_3->children.push_back(n4_5);
    n4_5->parent = n3_3;

    n3_4->children.push_back(n4_6);
    n4_6->parent = n3_4;

    n4_1->children.push_back(n5_1);
    n5_1->parent = n4_1;

    n4_1->children.push_back(n5_2);
    n5_2->parent = n4_1;

    n4_2->children.push_back(n5_3);
    n5_3->parent = n4_2;

    n4_3->children.push_back(n5_4);
    n5_4->parent = n4_3;

    n4_4->children.push_back(n5_5);
    n5_5->parent = n4_4;

    n4_5->children.push_back(n5_6);
    n5_6->parent = n4_5;

    n4_5->children.push_back(n5_7);
    n5_7->parent = n4_5;

    n4_6->children.push_back(n5_8);
    n5_8->parent = n4_6;

    n5_1->children.push_back(n6_1);
    n6_1->parent = n5_1;

    n5_1->children.push_back(n6_2);
    n6_2->parent = n5_1;

    n5_2->children.push_back(n6_3);
    n6_3->parent = n5_2;

    n5_2->children.push_back(n6_4);
    n6_4->parent = n5_2;

    n5_2->children.push_back(n6_5);
    n6_5->parent = n5_2;

    n5_3->children.push_back(n6_6);
    n6_6->parent = n5_3;

    n5_3->children.push_back(n6_7);
    n6_7->parent = n5_3;

    n5_4->children.push_back(n6_8);
    n6_8->parent = n5_4;

    n5_5->children.push_back(n6_9);
    n6_9->parent = n5_5;

    n5_5->children.push_back(n6_10);
    n6_10->parent = n5_5;

    n5_6->children.push_back(n6_11);
    n6_11->parent = n5_6;

    n5_7->children.push_back(n6_12);
    n6_12->parent = n5_7;

    n5_8->children.push_back(n6_13);
    n6_13->parent = n5_8;

    n6_1->children.push_back(n7_1);
    n7_1->parent = n6_1;

    n6_1->children.push_back(n7_2);
    n7_2->parent = n6_1;

    n6_2->children.push_back(n7_3);
    n7_3->parent = n6_2;

    n6_2->children.push_back(n7_4);
    n7_4->parent = n6_2;

    n6_3->children.push_back(n7_5);
    n7_5->parent = n6_3;

    n6_4->children.push_back(n7_6);
    n7_6->parent = n6_4;

    n6_4->children.push_back(n7_7);
    n7_7->parent = n6_4;

    n6_4->children.push_back(n7_8);
    n7_8->parent = n6_4;

    n6_5->children.push_back(n7_9);
    n7_9->parent = n6_5;

    n6_5->children.push_back(n7_10);
    n7_10->parent = n6_5;

    n6_6->children.push_back(n7_11);
    n7_11->parent = n6_6;

    n6_6->children.push_back(n7_12);
    n7_12->parent = n6_6;

    n6_7->children.push_back(n7_13);
    n7_13->parent = n6_7;

    n6_7->children.push_back(n7_14);
    n7_14->parent = n6_7;

    n6_8->children.push_back(n7_15);
    n7_15->parent = n6_8;

    n6_8->children.push_back(n7_16);
    n7_16->parent = n6_8;

    n6_9->children.push_back(n7_17);
    n7_17->parent = n6_9;

    n6_9->children.push_back(n7_18);
    n7_18->parent = n6_9;

    n6_10->children.push_back(n7_19);
    n7_19->parent = n6_10;

    n6_10->children.push_back(n7_20);
    n7_20->parent = n6_10;

    n6_11->children.push_back(n7_21);
    n7_21->parent = n6_11;

    n6_11->children.push_back(n7_22);
    n7_22->parent = n6_11;

    n6_12->children.push_back(n7_23);
    n7_23->parent = n6_12;

    n6_12->children.push_back(n7_24);
    n7_24->parent = n6_12;

    n6_13->children.push_back(n7_25);
    n7_25->parent = n6_13;

    return n1_1;
}

void MinimaxTests::test_1() {
    auto root = build_tree();
    GameTree game_tree(root);
    ChoiceTree choice_tree(game_tree, 6);
    GENERATOR::Generator generator(choice_tree);
    int best_score;
    generator.run();
    ASSERT(generator.get_best_score() == 11);
    ASSERT(game_tree.get_children_visited() == 36);  // if more is pruned, could be nice, but that's suspicious
}

}}
