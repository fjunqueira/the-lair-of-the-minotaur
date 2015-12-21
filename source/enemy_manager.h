//
// Created by fabio on 12/20/15.
//

#ifndef THE_LAIR_OF_THE_MINOTAUR_ENEMY_MANAGER_H
#define THE_LAIR_OF_THE_MINOTAUR_ENEMY_MANAGER_H


#include "asset_manager.h"
#include "enemy.h"
#include <float.h>
#include "directions.h"

namespace enemy_manager
{
    void AddEnemy(TileMap& map, const AssetManager& asset_manager, pathfinding::PathfindingGraph& pathfinding_graph,
                  std::vector<Enemy>& enemies);

    Enemy* GetNearestEnemy(std::vector<Enemy>* enemies, const math::Vector2<float>& point);
};


#endif //THE_LAIR_OF_THE_MINOTAUR_ENEMY_MANAGER_H
