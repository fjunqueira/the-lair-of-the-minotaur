//
// Created by fabio on 12/12/15.
//

#include "pathfinding_node.h"

pathfinding::PathfindingNode::PathfindingNode(const math::Vector2<int>& index) : index(index), runid()
{

}

float pathfinding::PathfindingNode::F() const
{
    return this->G + this->H;
}

void pathfinding::PathfindingNode::ResetInfo(const unsigned char* runid)
{
    uuid_copy(this->runid, runid);
    this->H = 0;
    this->G = 0;
    this->parent_node = nullptr;
    this->is_on_open_list = false;
}
