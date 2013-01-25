/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <memory>

namespace PACMAN {
    namespace TEST {

        class TreeNode;

        // tests of our implementation of minimax
        class MinimaxTests {
        public:
            static void test_1();

        private:
            static std::shared_ptr<TreeNode> build_tree();
        };

    }
}
