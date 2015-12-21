//
// Created by fabio on 12/12/15.
//

#ifndef THE_LAIR_OF_THE_MINOTAUR_PATHFINDING_GRAPH_H
#define THE_LAIR_OF_THE_MINOTAUR_PATHFINDING_GRAPH_H

#include "../math/vector2.h"
#include "pathfinding_node.h"
#include "comparator.h"
#include "pathfinding_node_comparator.h"
#include <vector>
#include "binary_heap.h"
#include <algorithm>

namespace pathfinding
{
    class PathfindingGraph
    {

    public:

        PathfindingGraph(const math::Vector2<int>& graph_dimensions);

        const int& size() const;

        PathfindingNode* GetNodeByIndex(const math::Vector2<int>& index) const;

        std::vector<pathfinding::PathfindingNode*> FindPath(PathfindingNode& starting_node, PathfindingNode& destination_node);

        ~PathfindingGraph();

    private :

        int size_;

        unsigned char runid_[16];

        math::Vector2<int> graph_dimensions_;

        PathfindingNode** nodes_;

        PathfindingNodeComparator node_comparator_;

        std::vector<pathfinding::PathfindingNode*> GetAdjacentNodes(const math::Vector2<int>& index) const;

        const int GetHeuristic(const PathfindingNode& from, const PathfindingNode& to) const;

        const int GetPartialPathCost(const PathfindingNode& from, const PathfindingNode& to) const;

        const bool IndexNotInBounds(const math::Vector2<int>& index, const int& array_index) const;

        std::vector<pathfinding::PathfindingNode*> GetPathToNode(PathfindingNode* node) const;
    };
}

#endif //THE_LAIR_OF_THE_MINOTAUR_PATHFINDING_GRAPH_H
