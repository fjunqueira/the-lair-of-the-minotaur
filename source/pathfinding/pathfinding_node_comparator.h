//
// Created by fabio on 12/12/15.
//

#ifndef THE_LAIR_OF_THE_MINOTAUR_PATHFINDING_NODE_COMPARATOR_H
#define THE_LAIR_OF_THE_MINOTAUR_PATHFINDING_NODE_COMPARATOR_H

#include "pathfinding_node.h"
#include "comparator.h"

namespace pathfinding
{
    class PathfindingNodeComparator : public Comparator<PathfindingNode*>
    {
        const int Compare(PathfindingNode* const& obj1, PathfindingNode* const& obj2) const;
    };
}


#endif //THE_LAIR_OF_THE_MINOTAUR_PATHFINDING_NODE_COMPARATOR_H
