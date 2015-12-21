//
// Created by fabio on 12/18/15.
//

#ifndef THE_LAIR_OF_THE_MINOTAUR_DIRECTIONS_H
#define THE_LAIR_OF_THE_MINOTAUR_DIRECTIONS_H


#include "pathfinding/pathfinding_node.h"

namespace directions
{
    const int WEST = 8;
    const int NORTHWEST = 7;
    const int NORTH = 6;
    const int NORTHEAST = 5;
    const int EAST = 4;
    const int SOUTHEAST = 3;
    const int SOUTH = 2;
    const int SOUTHWEST = 1;

    const int GetCardinalDirection(const pathfinding::PathfindingNode* from,
                                   const pathfinding::PathfindingNode* to);
};


#endif //THE_LAIR_OF_THE_MINOTAUR_DIRECTIONS_H
