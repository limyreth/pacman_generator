/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#pragma once

#include "Nodes.h"
#include "Action.h"

#include <vector>
#include <map>

namespace PACMAN {
    namespace MODEL {

        // these are choice nodes for pacman/ghosts
        class GhostNodes : public Nodes
        {
        public:
            GhostNodes();
            ~GhostNodes();

            const Node& get_node_towards_spawn(const Node& origin) const;
            const std::vector<Node*> get_respawns() const;
            const std::vector<Node*> get_spawns() const;

            double get_cost(const Node& node) const;

            void draw(shared_ptr<SDL_Surface> buffer) const;
            void draw_respawn_paths(shared_ptr<SDL_Surface> buffer) const;

        private:
            void add_respawn_paths();

        private:
            std::map<const Node*, double> min_costs;  // best cost to reach said node
            std::map<const Node*, const Node*> towards_spawn; // map node to a node closer to Pinky spawn
            std::vector<Node*> respawns;
            std::vector<Node*> spawns;
        };

        extern const GhostNodes GHOST_NODES;

    }
}
