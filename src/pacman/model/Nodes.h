/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include <vector>

#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

class SDL_Surface;

namespace PACMAN {
    namespace MODEL {

        class Node;

        // these are choice nodes for pacman/ghosts
        class Nodes
        {
        public:
            Nodes();
            virtual ~Nodes();

            void draw(shared_ptr<SDL_Surface> buffer) const;

            virtual void save(std::ostream& out, const Node* node) const = 0;

        protected:
            std::vector<Node*> nodes;

            void ensure_valid(const std::vector<Node*>& nodes, const std::vector<Node*>& all_nodes) const;
            void ensure_valid(const Node* node, const std::vector<Node*>& all_nodes) const;

            void save(std::ostream& out, const Node* node, const std::vector<Node*>& nodes) const;

            double get_branching_factor(const std::vector<Node*>& nodes) const;
        };

    }
}
