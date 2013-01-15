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

static const int DEFAULT_MAX_ROUNDS = 100;  // TODO set non-random number; may want to revert back to max choices later, as that's easier to estimate. You could keep count of things in ChoiceTree

GeneratorRun::GeneratorRun() 
:   game_tree(DEFAULT_MAX_ROUNDS),
    choice_tree(game_tree),
    generator(choice_tree)
{
}

GeneratorRun::GeneratorRun(std::istream& in)
:   game_tree(in),
    choice_tree(in, game_tree),
    generator(in, choice_tree)
{
    if (in.fail()) {
        throw_exception("Failed to read generator state");
    }
}

void GeneratorRun::start() {
    generator.start();
}

void GeneratorRun::stop(std::ostream& out) {
    generator.stop();
    generator.join();

    game_tree.save(out);
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
