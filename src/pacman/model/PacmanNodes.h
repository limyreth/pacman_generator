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

namespace PACMAN {
    namespace MODEL {

        // these are choice nodes for pacman/ghosts
        class PacmanNodes : public Nodes
        {
        public:
            PacmanNodes();
            ~PacmanNodes();

            const Node& get_spawn() const;

            const Node* get(int id) const;
            int get_id(const Node*) const;

            void draw(std::shared_ptr<SDL_Surface> buffer) const;

        private:
            Node* spawn;
        };

        extern const PacmanNodes PACMAN_NODES;

    }
}
