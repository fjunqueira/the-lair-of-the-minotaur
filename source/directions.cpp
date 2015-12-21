//
// Created by fabio on 12/18/15.
//

#include "directions.h"

const int directions::GetCardinalDirection(const pathfinding::PathfindingNode* from,
                                           const pathfinding::PathfindingNode* to)
{
    if (to->index == from->index + math::Vector2<int>(-1, -1))
        return directions::SOUTHWEST;
    if (to->index == from->index + math::Vector2<int>(0, -1))
        return directions::SOUTH;
    if (to->index == from->index + math::Vector2<int>(1, -1))
        return directions::SOUTHEAST;
    if (to->index == from->index + math::Vector2<int>(-1, 0))
        return directions::WEST;
    if (to->index == from->index + math::Vector2<int>(1, 0))
        return directions::EAST;
    if (to->index == from->index + math::Vector2<int>(-1, 1))
        return directions::NORTHWEST;
    if (to->index == from->index + math::Vector2<int>(0, 1))
        return directions::NORTH;
    if (to->index == from->index + math::Vector2<int>(1, 1))
        return directions::NORTHEAST;

    return -1;
}