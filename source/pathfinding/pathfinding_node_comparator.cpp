//
// Created by fabio on 12/12/15.
//

#include "pathfinding_node_comparator.h"

const int pathfinding::PathfindingNodeComparator::Compare(pathfinding::PathfindingNode* const& obj1,
                                                          pathfinding::PathfindingNode* const& obj2) const
{
    if (obj1 == obj2)
    {
        return 0;
    }

    if (obj1 == nullptr || obj2 == nullptr)
    {
        return 2;
    }

    if (obj1->F() < obj2->F())
    {
        return -1;
    }

    if (obj1->F() > obj2->F())
    {
        return 1;
    }

    return -2;
}
