A fork of pacman_sdl. pacman_sdl is a clone of the classic arcade game using
C++ and SDL.

This fork calculates and displays perfect play for perfect pacman and perfect
ghosts.

.. contents::

Project state
=============

Under development; not ready for usage.


License
=======

pacman_sdl (and this fork) is licensed under the terms of the GNU General
Public License version 2 (or any later version).


Game Specification
==================

Except for some exceptions and further details, the game follows `these rules`__.

__ http://home.comcast.net/~jpittman2/pacman/pacmandossier.html

Summary of those rules:

- Map: 240 (small) dots and 4 energizers (big dot). Spawn positions detailed in
  source code.

- Scoring:

  - 10 points for eating a dot

  - 50 points for eating an energizer 

  - eating first ghost 200 points, second 400, third 800, fourth 1600. Is reset
    back to 200 upon eating a new energizer.

  - 100 points for a fruit at level 1. 

- Fixed frame rate of 60 ticks per second.

- Ghosts made vulnerable by energizer for 6 seconds

- A fruit spawns after 70 and 170 dots. They remain for 10sec.

- Monster pen leaving: 

  - Blinky and Pinky leave immediately. 

  - Inky leaves after 30 dots eaten.

  - Clyde leaves after 90 dots total eaten.

  - Or if no dots are eaten for 4 seconds, the next monster leaves the pen (first Inky, then Clyde).

- Ghost respawn: 
  
  - Ghosts respawn at their original spawn location. Except for Blinky, Blinky
    respawns at Pinky's spawn.

  - Ghosts take the shortest path to their respawn.

- Player tile position: is determined by the player's pixel position, which is the player's center.

- Speed: 
  
  - is determined by the tile pos and state of the player.

  - See `this table <http://home.comcast.net/~jpittman2/pacman/pacmandossier.html#LvlSpecs>`_.

  - 100% speed = 9.5 tiles per sec.

- Tunnel movement: when a player's tile pos leaves bounds of the map at a
  tunnel, move that player to the other side of the map at the other tunnel
  edge, with pixel accuracy.

- Cornering: 
  
  - Pacman may corner when his bounds touch an intersection tile's bounds. 
    
  - When cornering, pacman moves along a diagonal path.

- Collisions: collision checking is done by tile pos only; even when bounds
  intersect.

 
Changes to the original rules:

- Ghosts and pacman are free to move however they like, except for:

  - Players may not reverse (i.e. they may not go where they directly came from):
    
    - except after pacman has eaten an energizer or a ghost

    - except as pacman, after having eaten a fruit

  - Players may not stand still (except for ghosts who aren't allowed to leave
    the ghost pen yet)

- Pacman gets only 1 life.

- The first level is the only level.


Additions compatible with the original rules:

- Fruit spawns in both tiles tiles underneath the center of the ghost pen

- Pacman size = 0.8 * 2 * tile_size

- When cornering, pacman will briefly move through the wall tile neighbouring
  the intersection. While doing so, pacman's tile pos is that of the
  intersection tile, not that of the wall. 
  
  Note: This works for lvl1 speeds. Player's pixel pos will enter the
  wall tile, even at highest speed. The distance spent in the wall tile is
  about 0.42 * tile_size.

- Ghosts in the ghost pen do not become vulnerable when pacman eats an
  energizer, regardless of their state. They are considered in the pen when
  their tile pos is one of the ghost pen tiles.


Development
===========

Development view
----------------

+---------------------------------+
|   Tests   |   GUI   | Generator |
+---------------------------------+
|              Model              |
+---------------------------------+
|           Specification         |
+---------------------------------+

Each layer depends on the layer(s) below.

Tests may only depend on constants specified by the specification, not anything
implementation specific.

Changing anything in Specification implies changing the specification, so
that's normally not what you want to do.

Model: GameState, implementation constants (e.g. tile size, screen size), ...

Specification: constants, ... as specified and used by the specification.

Contact / More Information
==========================

Github: http://github.com/timdiels/pacman

Email: tim@timdiels.be


Enjoy!
