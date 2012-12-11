/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "GhostState.h"
#include "Utility.h"
#include "Directions.h"

extern Directions DIRECTIONS;

// TODO dead ghost takes shortest path back to correct pen tile

// TODO size enums to 1 byte
GhostState::GhostState()  // the infamous random garble 'initializer'
: GhostState(SDL_Point()) 
{
}

GhostState::GhostState(SDL_Point spawn_pos)
:   PlayerState(spawn_pos), state(NORMAL)
{
}

bool GhostState::is_in_tunnel() {
    return false; // TODO implement this damn it
}

// Note: this has little meaning other than that when it changes, a new action may be chosen (which is by crossing any grid line with offset half a tile)
SDL_Point GhostState::get_action_pos() const {
    return (pos + SDL_Point(TILE_SIZE, TILE_SIZE)/2) / TILE_SIZE;
}

void GhostState::get_legal_actions(const int* walls, Action action, Actions legal_actions, const PlayerState* old) {
    SDL_Point apos = get_action_pos();

    SDL_Point old_apos;
    if (old) {
        old_apos = ((GhostState*)old)->get_action_pos();
    }
    else {
        // set previous pos to an invalid pos
        old_apos = SDL_Point(-1, -1);
    }

    if (apos == old_apos) {
        // Next action has to be the same as current action
        legal_actions[0] = action;
        for (int i=1; i<ACTION_COUNT; ++i) {
            legal_actions[i] = -1;
        }
    }
    else {
        SDL_Point tpos = get_tile_pos();
        // Any nonobstructed path is fine
        for (int i=0; i<ACTION_COUNT; ++i) {
            auto new_tpos = tpos + DIRECTIONS[i];
            bool is_legal_tpos = walls[at(new_tpos)] == 0 || new_tpos.x < 0 || new_tpos.x == MAP_WIDTH;
            legal_actions[i] = is_legal_tpos ? i : -1;
        }
        // TODO order reverse direction as last (swap its value with that of the last)
    }
}


///////////////////////////////////////////////
// Path finding that might come in handy
/*
bool Ghost::find() {
    int
            i,
            currentx = xpix / tilesize,
            currenty = ypix / tilesize,
            tmppos;

    //if target is not clear

    if ( collision( xtarget, ytarget) ) return 0;

    // reset arrays

    for (i=0; i<width*height; i++) {
        closed[i]=0;
        parentDir[i]=4;
        closedF[i]=-1;
        Gstore[i]=-1;
    }

    // reset heap

    heap.reset();

    //init loop

    parentDir[ currenty*width + currentx ]= -1;
    Gstore[ y*width + x ] = 0;
    heap.add( currentx , currenty , calcF(currentx,currenty) );

    // loop start

    while ( true ) {

        //set focus coords

        currentx=heap.getX();
        currenty=heap.getY();

        // remember F, set status as closed

        closedF[currenty*width+currentx]=heap.getF();
        closed[currenty*width+currentx]=1;

        // if current tile == target, terminate loop

        if (currentx == xtarget && currenty == ytarget) return 1;

        //remove from open list

        heap.remove();

        // first up: RIGHT NEIGHBOR SQUARE
        // special case : current == width-2

        i=1;
        if ( currentx == width-2 ) {

            //if neighbor tile is clear and not on closed list

            if ( ! collision_ignore_gate(0, currenty) && !closed[currenty*width+0] ) {

                // if not already on openlist

                if ( !(tmppos=heap.find(0, currenty)) ) {

                    Gstore[(currenty)*width+0]=Gstore[currenty*width+currentx] + 1;

                    heap.add(0, currenty, calcF(0, currenty));	//add to openlist

                    parentDir[currenty*width+0]=3;				//set parent square
                }

                // if already on openlist -> this path lower G?

                else {
                    if ( Gstore[currenty*width+0] > Gstore[currenty*width+currentx] + 1 ) {

                        Gstore[currenty*width+0] = Gstore[currenty*width+currentx] + 1;	//update G
                        parentDir[currenty*width+0]=3;							//update parent direction
                        heap.changeF( heap.find(0, currenty), calcF(0,currenty));	//update F stored in openList
                    }
                }
            }
        }

        // usual case: current != width -2

        else {
            if (! collision_ignore_gate(currentx+i, currenty) && !closed[currenty*width+currentx +i] ) {
                if ( !(tmppos=heap.find(currentx+i, currenty)) ) {
                    Gstore[(currenty)*width+currentx + i]=Gstore[currenty*width+currentx] + 1;
                    heap.add(currentx+i, currenty, calcF(currentx+i, currenty));
                    parentDir[currenty*width+currentx+i]=3;
                }
                //if already on openlist
                else {			//if this path has a lower G
                    if ( Gstore[currenty*width+currentx+i] > Gstore[currenty*width+currentx] + 1 ) {
                        Gstore[currenty*width+currentx+i] = Gstore[currenty*width+currentx] + 1;
                        parentDir[currenty*width+currentx+i]=3;
                        heap.changeF( heap.find(currentx+i, currenty), calcF(currentx+i,currenty));
                    }
                }
            }
        }

        // LEFT NEIGHBOR SQUARE
        //special case : currentx == 0

        i = -1;

        if (currentx == 0 ) {
            if (! collision_ignore_gate(width-2, currenty) && !closed[currenty*width+width-2] ) {
                if ( !(tmppos=heap.find(width-2, currenty)) ) {
                    Gstore[(currenty)*width+width-2]=Gstore[currenty*width+currentx] + 1;
                    heap.add(width-2, currenty, calcF(width-2, currenty));
                    parentDir[currenty*width+width-2]=1;
                }
                else {
                    if ( Gstore[currenty*width+width-2] > Gstore[currenty*width+currentx] + 1 ) {
                        Gstore[currenty*width+width-2] = Gstore[currenty*width+currentx] + 1;
                        parentDir[currenty*width+width-2]=1;
                        heap.changeF( heap.find(width-2, currenty), calcF(width-2,currenty));
                    }
                }
            }
        }

        // normal case
        else {
            if (! collision_ignore_gate(currentx+i, currenty) && !closed[currenty*width+currentx+i] ) {
                if ( !(tmppos=heap.find(currentx+i, currenty)) ) {
                    Gstore[(currenty)*width+currentx + i]=Gstore[currenty*width+currentx] + 1;
                    heap.add(currentx+i, currenty, calcF(currentx+i, currenty));
                    parentDir[currenty*width+currentx+i]=1;
                }
                else {
                    if ( Gstore[currenty*width+currentx+i] > Gstore[currenty*width+currentx] + 1 ) {
                        Gstore[currenty*width+currentx+i] = Gstore[currenty*width+currentx] + 1;
                        parentDir[currenty*width+currentx+i]=1;
                        heap.changeF( heap.find(currentx+i, currenty), calcF(currentx+i,currenty));
                    }
                }
            }
        }

        // LOWER NEIGHBOR SQUARE

        i=1;

        // special case

        if ( currenty == height -2 ) {
            if ( ! collision_ignore_gate(currentx, 0) && !closed[0*width+currentx] ) {

                // if not already on openlist

                if ( !(tmppos=heap.find(currentx, 0)) ) {

                    Gstore[(0)*width+currentx]=Gstore[currenty*width+currentx] + 1;

                    heap.add(currentx, 0, calcF(currentx, 0));	//add to openlist

                    parentDir[0*width+currentx]=0;				//set parent square
                }

                // if already on openlist -> this path lower G?

                else {
                    if ( Gstore[0*width+currentx] > Gstore[currenty*width+currentx] + 1 ) {

                        Gstore[0*width+currentx] = Gstore[currenty*width+currentx] + 1;	//update G
                        parentDir[0*width+currentx]=0;							//update parent direction
                        heap.changeF( heap.find(currentx, 0), calcF(currentx, 0));	//update F stored in openList
                    }
                }
            }
        }

        //normal case

        else {

            if (! collision_ignore_gate(currentx, currenty+i) && !closed[(currenty+i)*width+currentx] ) {
                if ( !(tmppos=heap.find(currentx, currenty+i)) ) {
                    Gstore[(currenty+i)*width+currentx]=Gstore[currenty*width+currentx] + 1;
                    heap.add(currentx, currenty+i, calcF(currentx, currenty+i));
                    parentDir[(currenty+i)*width+currentx]=0;
                }
                else {
                    if ( Gstore[(currenty+i)*width+currentx] > Gstore[currenty*width+currentx] + 1 ) {
                        Gstore[(currenty+i)*width+currentx] = Gstore[currenty*width+currentx] + 1;
                        parentDir[(currenty+i)*width+currentx]=0;
                        heap.changeF( heap.find(currentx, currenty+i), calcF(currentx,currenty+i));
                    }
                }
            }
        }

        // UPPER NEIGHBOR SQUARE

        i=-1;

        //special case
        if (currenty == 0 ) {
            if (! collision_ignore_gate(currentx, height-2) && !closed[(height-2)*width+currentx] ) {
                if ( !(tmppos=heap.find(currentx, height-2)) ) {
                    Gstore[(height-2)*width+currentx]=Gstore[currenty*width+currentx] + 1;
                    heap.add(currentx, height-2, calcF(currentx, height-2));
                    parentDir[(height-2)*width+currentx]=2;
                }
                else {
                    if ( Gstore[(height-2)*width+currentx] > Gstore[currenty*width+currentx] + 1 ) {
                        Gstore[(height-2)*width+currentx] = Gstore[currenty*width+currentx] + 1;
                        parentDir[(height-2)*width+currentx]=2;
                        heap.changeF( heap.find(currentx, height-2), calcF(currentx,height-2));
                    }
                }
            }
        }

        //normal case
        else {
            if (! collision_ignore_gate(currentx, currenty+i) && !closed[(currenty+i)*width+currentx] ) {
                if ( !(tmppos=heap.find(currentx, currenty+i)) ) {
                        Gstore[(currenty+i)*width+currentx]=Gstore[currenty*width+currentx] + 1;
                        heap.add(currentx, currenty+i, calcF(currentx, currenty+i));
                        parentDir[(currenty+i)*width+currentx]=2;
                }
                else {
                    if ( Gstore[(currenty+i)*width+currentx] > Gstore[currenty*width+currentx] + 1 ) {
                        Gstore[(currenty+i)*width+currentx] = Gstore[currenty*width+currentx] + 1;
                        parentDir[(currenty+i)*width+currentx]=2;
                        heap.changeF( heap.find(currentx, currenty+i), calcF(currentx,currenty+i));
                    }
                }
            }
        }

        // if open list is empty, terminate

        if ( heap.isEmpty() ) return 0;
    }
}

int Ghost::calcF(int ix, int iy) const {
    int a,b;

    //distance current tile -> start tile

    a= Gstore[(iy)*width+ix] ;

    // x-distance current tile -> target tile

    b= ix > xtarget ? (ix-xtarget) : (xtarget-ix);  //current to target =H

    //special cases: target left edge, baddie right edge

    if ( ( width-1)-ix+xtarget < b ) 	b=(width-2)-ix+xtarget;	//width -1 to get correct F

    //				target right edge, baddie left edge

    if (ix + (width+1) -xtarget < b )	b=ix + (width-2) -xtarget;

    a+=b;

    // y-distance current tile -> target tile

    b= iy > ytarget ? (iy-ytarget) : (ytarget-iy);

    //special case: target upper edge, baddie lower edge

    if ( ( height-1)-iy+ytarget < b ) 	b=(height-2)-iy+ytarget;

    // vice versa

    if (iy + (height+1) -ytarget < b )	b=iy + (height-2) -ytarget;

    a+=b;

    return a;
}

bool Ghost::tracePath() {
    int xtmp, ytmp;

    //reset dirToTar

    dirToTar = -1;

    //set coords

    xtmp= heap.getX();
    ytmp= heap.getY();

    if (ytmp == ytarget && xtmp == xtarget ) {	//error check

        while ( parentDir[ ytmp*width + xtmp ] != -1 ) {

            dirToTar = parentDir[ytmp*width+xtmp];		//not sure about dtotarget -1, maybe without -1

            if (dirToTar == 0) {
                if (ytmp==0) ytmp=height-2;
                else ytmp--;
            }
            else if (dirToTar == 1) {
                if ( xtmp== width-2) xtmp=0;
                else xtmp++;
            }
            else if (dirToTar == 2) {
                if (ytmp == height -2 ) ytmp=0;
                else ytmp++;
            }
            else if (dirToTar == 3) {
                if (xtmp == 0) xtmp= width-2;
                else xtmp--;
            }
        }

        if ( dirToTar == 0 ) dirToTar = 2;
        else if ( dirToTar == 1 ) dirToTar = 3;
        else if ( dirToTar == 2 ) dirToTar = 0;
        else if ( dirToTar == 3 ) dirToTar = 1;

        if (dirToTar < 0 || dirToTar > 3 ) return 1;	//error check

        return 0;
    }

    else return 1;	//error
}

void Ghost::pathCalcDead() {
    bool
            flag = 0;
    int
            newdir = -1,
            cur_opp_dir=-1;	// opposite of current direction

    //translate dx + dy into dir -> 0 = up, 1 = right, 2 = down, 3 = left

    if (dx == 1) cur_opp_dir = 3;
    else if (dx == -1) cur_opp_dir = 1;
    else if (dy == 1) cur_opp_dir = 0;
    else if (dy == -1) cur_opp_dir = 2;

    xtarget= baddie_start_point_x ;
    ytarget= baddie_start_point_y ;

    //find path
    if ( find() ) flag=tracePath();

    //if find and trace successful
    // TRACE PATH

    if (! flag ) {		// pathfinding + trace successful
        if ( dirToTar == 0) {
            nextdx = 0;
            nextdy = -1;
        }
        else if ( dirToTar == 1 ) {
            nextdx = 1;
            nextdy = 0;
        }
        else if ( dirToTar == 2 ) {
            nextdx = 0;
            nextdy = 1;
        }
        else if ( dirToTar == 3 ) {
            nextdx = -1;
            nextdy = 0;
        }
    }

    // ELSE RANDOM PATH	-- only happens of trace not successful
    else {

        //if dead end
        if ( !dirClear[1+dx][1+dy] && !dirClear[1+dy][1+dx] && !dirClear[1-dy][1-dx] && dx != dy ) {
            nextdx = -dx;
            nextdy = -dy;
        }
        //generate random dir != - current dir
        else {
            nextdx = -dx;
            nextdy = -dy;
            while ( nextdx == -dx && nextdy == -dy ) {

                newdir = rand()%4;

                if ( newdir == 0 ) {
                    nextdx = 0;
                    nextdy = -1;
                }
                else if ( newdir == 1 ) {
                    nextdx = 1;
                    nextdy = 0;
                }
                else if ( newdir == 2 ) {
                    nextdx = 0;
                    nextdy = 1;
                }
                else if ( newdir == 3 ) {
                    nextdx = -1;
                    nextdy = 0;
                }
                if ( !dirClear[1+nextdx][1+nextdy] ) {
                    nextdx = -dx;
                    nextdy = -dy;
                }
            }
        }
    }
    dx=nextdx;
    dy=nextdy;
}
*/
