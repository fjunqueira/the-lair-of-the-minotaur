//
// Created by fabio on 12/20/15.
//

#include "enemy_manager.h"

void enemy_manager::AddEnemy(TileMap& map, const AssetManager& asset_manager,
                             pathfinding::PathfindingGraph& pathfinding_graph,
                             std::vector<Enemy>& enemies)
{
    auto map_dimensions = map.GetMapDimensions();

    auto row_to_spawn = rand() % 4 + 1;

    math::Vector2<int> index_to_spawn;

    switch (row_to_spawn)
    {
        case 1:
            index_to_spawn = math::Vector2<int>(0, rand() % map_dimensions.y);
            break;
        case 2:
            index_to_spawn = math::Vector2<int>(rand() % map_dimensions.x, 0);
            break;
        case 3:
            index_to_spawn = math::Vector2<int>(rand() % map_dimensions.x, map_dimensions.y - 1);
            break;
        case 4:
            index_to_spawn = math::Vector2<int>(map_dimensions.x - 1, rand() % map_dimensions.y);
            break;
        default:
            return;
    }

    auto orcSpritesheet = asset_manager.get_asset("orc");

    Enemy enemy(&map, &pathfinding_graph, animation::Running(orcSpritesheet, 256, directions::SOUTH),
                map.GetTilePositionByIndex(index_to_spawn), math::Vector2<float>(40, 80),
                orcSpritesheet->textureid);

    enemy.ChangePath(pathfinding_graph.FindPath(*pathfinding_graph.GetNodeByIndex(index_to_spawn),
                                                *pathfinding_graph.GetNodeByIndex(math::Vector2<int>(16, 13))));

    enemies.push_back(enemy);
}

Enemy* ::enemy_manager::GetNearestEnemy(std::vector<Enemy>* enemies, const math::Vector2<float>& point)
{
    Enemy* nearest_enemy = nullptr;
    float nearest_enemy_distance = FLT_MAX;

    std::for_each(enemies->begin(), enemies->end(), [&](Enemy& enemy)
    {
        auto distance = (point - enemy.position()).magnitude();

        if (distance < nearest_enemy_distance)
        {
            nearest_enemy = &enemy;
            nearest_enemy_distance = distance;
        }
    });

    return nearest_enemy;
}
