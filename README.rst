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

- Any ghost that isn't dead, becomes vulnerable for 6 seconds when pacman eats
  an energizer.  Even when they are in the ghost pen. This can be seen in `this
  video`__ part of the original spec.

__ http://www.youtube.com/watch?feature=player_embedded&v=VbzW6iNDx9U

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

  - Players may not reverse:
    
    - they may not go where they directly came from
      
    - and the new destination may not be a neighbour of where we just came from
    
    - except after pacman has eaten an energizer, or ghosts become invulnerable
      again

    - except as pacman, after having eaten a fruit or a ghost

  - Players may not stand still (except for ghosts who aren't allowed to leave
    the ghost pen yet)

- Pacman gets only 1 life.

- The first level is the only level.

- Cornering near (2, 23), (25, 23), (2, 26) and (25, 26) happens under a
  slightly different angle so that pacman exits/enters its cornering in the
  center of those tiles.


Additions compatible with the original rules:

- Fruit spawns in both tiles tiles underneath the center of the ghost pen

- Pacman size = 0.8 * 2 * tile_size

- When cornering, pacman will briefly move through the wall tile neighbouring
  the intersection. While doing so, pacman's tile pos is that of the
  intersection tile, not that of the wall. 
  
  Note: This works for lvl1 speeds. Player's pixel pos will enter the
  wall tile, even at highest speed. The distance spent in the wall tile is
  about 0.42 * tile_size.

- Dead ghost speed = 2 * normal pacman speed. This was unspecified in the
  original spec. Dead ghosts are unaffected by any other rules about speed;
  they always move at dead ghost speed.

- Allowed speed inaccuracy: When crossing tile bounds, it is allowed to
  maintain the speed of the origin tile (and this implementation does exactly
  that). E.g. during the tick when a ghost exits a tunnel, it may move at
  tunnel speed for that entire tick, even though that means it moves at tunnel
  speed for a short distance outside the tunnel.


Analysis
========

Maze details
------------

Distances are expressed in tiles.

corner point = a point where pacman starts to corner

Distance travelled by pacman from begin to end of cornering = sqrt(2) * 1.3

Distance from pacman spawn to nearest corner point = 0.2 = distance of
corner point to nearest tile edge

While cornering, pacman's center will enter a wall tile. The distance travelled
in the wall tile = 3 * sqrt(2) / 10. The distance between the corner point
and the wall edge = sqrt(2) / 2

Distances of cornering near (2, 23) and (25, 23):

- normal corner point to wall = sqrt(269) / 20

- wall to wall = 4 * sqrt(269) / 65 - sqrt(269) / 20

- exceptional corner point to wall = sqrt(269) / 10 - 4 * sqrt(269) / 65

Development
===========

Development view
----------------

+-----------------------------------+
| Tests | (interactive) | Generator |
+-----------------------------------+
|         Run       |      GUI      |
+-----------------------------------+
|              Model                |
+-----------------------------------+
|           Specification           |
+-----------------------------------+

Each layer depends on the layer(s) below.

Tests may only depend on constants specified by the specification, not anything
implementation specific.

Changing anything in Specification implies changing the specification, so
that's normally not what you want to do.

Model: GameState, implementation constants (e.g. tile size, screen size), ...

Specification: constants, ... as specified and used by the specification.

Run: helper classes to run the game. Ties together GUI and Model.

GUI: classes for providing input and rendering output


Test coverage
-------------

How tests cover the game specification: (tests are in bold font)

- Map: 240 (small) dots and 4 energizers (big dot). Spawn positions detailed in
  source code.

  - **Check start_foods for dot/energizer count**
  - **Check whether ghosts spawn at their spawn positions, nicely centered**

- Scoring:

  - 10 points for eating a dot

  - 50 points for eating an energizer 

  - eating first ghost 200 points, second 400, third 800, fourth 1600. Is reset
    back to 200 upon eating a new energizer.

  - 100 points for a fruit at level 1. 

  - **eat 2 dots**
  - **eat an energizer, no ghosts**
  - **eat a fruit**
  - **eat a ghost**
  - **eat a fruit, then a ghost**
  - **eat 2 ghosts**
  - **eat 3 ghosts**
  - **eat all ghosts**
  - **eat ghost, another energizer, ghost**

- Fixed frame rate of 60 ticks per second.

  - **manually checked: game state transitions 1/60th second each tick**

- Ghosts made vulnerable by energizer for 6 seconds

  - **1 energizer, check for ticks it should remain vulnerable and then the tick
    after that when it no longer should be (6 seconds and 1 tick past that)**

  - **1 energizer, then straight to the next, then time check again of when it
    should still be there, and when it no longer should be**

- A fruit spawns after 70 and 170 dots. They remain for 10sec.

  - **right before and at 70/170 dots, and each remains exactly 10 seconds**

- Monster pen leaving: 

  - Blinky and Pinky leave immediately. 

    - **check for movement after first frame**

  - Inky leaves after 30 dots eaten.

    - **still at spawn before 30 dots**
    - **movement at 30 dots**

  - Clyde leaves after 90 dots total eaten.

    - **still at spawn before 90 dots**
    - **movement at 90 dots**

  - Or if no dots are eaten for 4 seconds, the next monster leaves the pen (first Inky, then Clyde).

    - **same kind of tests for both clyde, inky, as for dot count**

- Ghost respawn: 
  
  - Ghosts respawn at their original spawn location. Except for Blinky, Blinky
    respawns at Pinky's spawn.

  - Ghosts take the shortest path to their respawn.

  - **check for each ghost that they return to their respawn, along the shortest
    path**

  - **kill a ghost near far node, and near the closer node. Make sure it returns
    via the closer node each time**

  - **also ensure that the step count matches the expected dead ghost speed**

- Player tile position: is determined by the player's pixel position, which is the player's center.

  - **check correct step count to switch from tile to other tile**

- Speed: 
  
  - is determined by the tile pos and state of the player.

  - See `this table <http://home.comcast.net/~jpittman2/pacman/pacmandossier.html#LvlSpecs>`_.

  - 100% speed = 9.5 tiles per sec.

  - **check tunnel speed: move ghost through tunnel from right to left,
    once**

  - **check elroy1 and 2 speed + timing**

  - **other speeds are thoroughly in other tick-based tests (Path tests and
    playback tests)**

- Tunnel movement: when a player's tile pos leaves bounds of the map at a
  tunnel, move that player to the other side of the map at the other tunnel
  edge, with pixel accuracy.

  - **do a bounds move from left to right**

- Cornering: 
  
  - Pacman may corner when his bounds touch an intersection tile's bounds. 

  - When cornering, pacman moves along a diagonal path.

  - **manual check visualisation of all ghost/pacman nodes + data of some
    nodes. Then automate by saving current nodes map, ensuring that it won't
    change again.**

- Collisions: collision checking is done by tile pos only; even when bounds
  intersect.

  - **code review**

 
Changes to the original rules:

- Ghosts and pacman are free to move however they like, except for:

  - Players may not reverse (i.e. they may not go where they directly came from):
    
    - except after pacman has eaten an energizer or a ghost

    - except as pacman, after having eaten a fruit

  - Players may not stand still (except for ghosts who aren't allowed to leave
    the ghost pen yet)

- Pacman gets only 1 life.

  - **start with 1 life**

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

  - **eat dot in corner**

- Ghosts in the ghost pen do not become vulnerable when pacman eats an
  energizer, regardless of their state. They are considered in the pen when
  their tile pos is one of the ghost pen tiles.

  - **eat energizer while ghosts are in pen**
  - **eat energizer while ghosts are leaving the pen**


Note: tests generated with record/playback are sensitive to the TILE_SIZE used,
and expect a tile size of 24.


Contact / More Information
==========================

Github: http://github.com/timdiels/pacman

Email: tim@timdiels.be


Enjoy!
