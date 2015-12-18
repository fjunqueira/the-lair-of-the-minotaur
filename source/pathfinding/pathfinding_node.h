//
// Created by fabio on 12/12/15.
//

#ifndef THE_LAIR_OF_THE_MINOTAUR_PATHFINDING_NODE_H
#define THE_LAIR_OF_THE_MINOTAUR_PATHFINDING_NODE_H

#include "../math/vector2.h"
#include <uuid/uuid.h>

namespace pathfinding
{
    struct PathfindingNode
    {
        PathfindingNode(const math::Vector2<int>& index);

        math::Vector2<int> index;
        unsigned char runid[16];
        PathfindingNode* parent_node = nullptr;

        float weight = 0;

        bool is_walkable = true;
        bool was_visited = false;
        bool is_on_open_list = false;

        float F() const;
        float G = 0;
        float H = 0;

        void ResetInfo(const unsigned char* runid);
    };
}


#endif //THE_LAIR_OF_THE_MINOTAUR_PATHFINDING_NODE_H
