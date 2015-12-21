//
// Created by fabio on 12/12/15.
//

#include "pathfinding_graph.h"

pathfinding::PathfindingGraph::PathfindingGraph(const math::Vector2<int>& graph_dimensions) :
        graph_dimensions_(graph_dimensions), size_(graph_dimensions.y * graph_dimensions.x), node_comparator_(),
        runid_()
{
    auto size = graph_dimensions.y * graph_dimensions.x;

    this->nodes_ = new PathfindingNode* [size];

    for (int i = 0; i < graph_dimensions.y; ++i)
    {
        for (int j = 0; j < graph_dimensions.x; ++j)
        {
            this->nodes_[i + j * graph_dimensions.x] = new PathfindingNode(math::Vector2<int>(j, i));
        }
    }
}

const int& pathfinding::PathfindingGraph::size() const
{
    return this->size_;
}

pathfinding::PathfindingNode* pathfinding::PathfindingGraph::GetNodeByIndex(const math::Vector2<int>& index) const
{
    int array_index = index.y + index.x * this->graph_dimensions_.x;

    if (this->IndexNotInBounds(index, array_index))
        return nullptr;

    return this->nodes_[array_index];
}

const bool pathfinding::PathfindingGraph::IndexNotInBounds(const math::Vector2<int>& index,
                                                           const int& array_index) const
{
    int max_index = (this->graph_dimensions_.y - 1) + (this->graph_dimensions_.x - 1) * this->graph_dimensions_.x;

    return index.y < 0 || index.x < 0 || array_index > max_index || index.y >= this->graph_dimensions_.y ||
           index.x >= this->graph_dimensions_.x;
}

std::vector<pathfinding::PathfindingNode*> pathfinding::PathfindingGraph::FindPath(
        pathfinding::PathfindingNode& starting_node,
        pathfinding::PathfindingNode& destination_node)
{
    uuid_generate(this->runid_);

    BinaryHeap<PathfindingNode*> open_list(this->size_, &this->node_comparator_);

    starting_node.ResetInfo(this->runid_);
    destination_node.was_visited = false;

    PathfindingNode* current_node = &starting_node;

    bool destination_reached = false;

    while (!destination_reached)
    {
        current_node->was_visited = true;

        auto adjacent_nodes = this->GetAdjacentNodes(current_node->index);

        for (int i = 0; i < adjacent_nodes.size(); i++)
        {
            PathfindingNode& adjacent_node = *adjacent_nodes[i];

            bool is_dirt = uuid_compare(adjacent_node.runid, this->runid_) != 0;

            if (adjacent_node.is_walkable && (!adjacent_node.was_visited || is_dirt))
            {
                if (!adjacent_node.is_on_open_list || is_dirt)
                {
                    uuid_copy(adjacent_node.runid, runid_);
                    adjacent_node.parent_node = current_node;

                    adjacent_node.G = current_node->G + this->GetPartialPathCost(*current_node, adjacent_node);

                    adjacent_node.H = this->GetHeuristic(adjacent_node, destination_node);

                    open_list.Push(&adjacent_node);
                    adjacent_node.is_on_open_list = true;
                }
                else if (adjacent_node.is_on_open_list && !is_dirt)
                {
                    auto g = current_node->G + this->GetPartialPathCost(*current_node, adjacent_node);

                    if (g < current_node->G)
                    {
                        open_list.Remove(&adjacent_node);

                        adjacent_node.parent_node = current_node;
                        adjacent_node.G = g;

                        open_list.Push(&adjacent_node);
                    }
                }
            }
        }

        if (open_list.is_empty())
        {
            return std::vector<pathfinding::PathfindingNode*>() = {&starting_node};
        }

        PathfindingNode* lowest_cost_node = open_list.Pop();
        lowest_cost_node->is_on_open_list = false;

        destination_reached = destination_node.was_visited && uuid_compare(this->runid_, destination_node.runid) == 0;

        if (!destination_reached)
            current_node = lowest_cost_node;
    }

    return this->GetPathToNode(current_node);
}

std::vector<pathfinding::PathfindingNode*> pathfinding::PathfindingGraph::GetAdjacentNodes(
        const math::Vector2<int>& index) const
{
    std::vector<pathfinding::PathfindingNode*> result =
            {
                    this->GetNodeByIndex(index + math::Vector2<int>(-1, -1)),
                    this->GetNodeByIndex(index + math::Vector2<int>(0, -1)),
                    this->GetNodeByIndex(index + math::Vector2<int>(1, -1)),
                    this->GetNodeByIndex(index + math::Vector2<int>(-1, 0)),
                    this->GetNodeByIndex(index + math::Vector2<int>(1, 0)),
                    this->GetNodeByIndex(index + math::Vector2<int>(-1, 1)),
                    this->GetNodeByIndex(index + math::Vector2<int>(0, 1)),
                    this->GetNodeByIndex(index + math::Vector2<int>(1, 1)),
            };

    result.erase(std::remove(result.begin(), result.end(), nullptr), result.end());

    return result;
}

const int pathfinding::PathfindingGraph::GetHeuristic(const pathfinding::PathfindingNode& from,
                                                      const pathfinding::PathfindingNode& to) const
{
    auto row_movement_weight = abs(to.index.y - from.index.y);
    auto col_movement_weight = abs(to.index.x - from.index.x);

    return (row_movement_weight + col_movement_weight) * 10;
}

const int pathfinding::PathfindingGraph::GetPartialPathCost(const pathfinding::PathfindingNode& from,
                                                            const pathfinding::PathfindingNode& to) const
{
    int movement_weight = 0;

    if (to.index.x < from.index.x && to.index.y < from.index.y ||
        to.index.x > from.index.x && to.index.y < from.index.y ||
        to.index.x > from.index.x && to.index.y > from.index.y ||
        to.index.x < from.index.x && to.index.y > from.index.y)
        movement_weight = 14;
    else
        movement_weight = 10;

    return movement_weight + to.weight;
}

pathfinding::PathfindingGraph::~PathfindingGraph()
{
    for (int i = 0; i < this->size(); ++i)
        delete this->nodes_[i];

    delete[] this->nodes_;
}

std::vector<pathfinding::PathfindingNode*> pathfinding::PathfindingGraph::GetPathToNode(
        pathfinding::PathfindingNode* node) const
{
    auto path = std::vector<pathfinding::PathfindingNode*>();

    auto current_node = node;

    while (current_node != nullptr)
    {
        path.push_back(current_node);
        current_node = current_node->parent_node;
    }

    std::reverse(path.begin(), path.end());

    return path;
}
