/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "GeneratorRun.h"
#include "../Error.h"

namespace PACMAN {
    namespace GENERATOR {

static const int DEFAULT_MAX_CHOICES = 80;  // set to 80 which is hopefully large enough because we only count real choices, and no reversing allowed

GeneratorRun::GeneratorRun() 
:   choice_tree(game_tree, DEFAULT_MAX_CHOICES),
    generator(choice_tree)
{
}

GeneratorRun::GeneratorRun(std::istream& in)
:   choice_tree(in, game_tree),
    generator(in, choice_tree)
{
    if (in.fail()) {
        throw_exception("Failed to read generator state");
    }
}

void GeneratorRun::stop() {
    generator.stop();
}

void GeneratorRun::join(std::ostream& out) {
    generator.run();

    choice_tree.save(out);
    generator.save(out);
    out.flush();
    if (out.fail()) {
        throw_exception("Failed to write generator state");
    }
}

bool GeneratorRun::operator==(const GeneratorRun& o) const {
    return o.game_tree == game_tree &&
        o.choice_tree == choice_tree &&
        o.generator == generator;
}

}}
