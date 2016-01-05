//
// Created by fabio on 12/17/15.
//

#ifndef THE_LAIR_OF_THE_MINOTAUR_ENEMY_H
#define THE_LAIR_OF_THE_MINOTAUR_ENEMY_H


#include "gameobject/game_object.h"
#include "tile_map.h"
#include "pathfinding/pathfinding_graph.h"
#include "animation/running.h"
#include "directions.h"
#include "animation/dying.h"

class Enemy : public gameobject::GameObject
{
private:

    TileMap* map_;

    pathfinding::PathfindingGraph* graph_;

    int current_node_ = 0;

    float time_dying_ = 0;

    bool is_dying_ = false;

    std::vector<pathfinding::PathfindingNode*> path_;

    animation::AnimationState* animation_ = nullptr;

    animation::Running running_;

    animation::Dying dying_;

public:
    Enemy(TileMap* const& map, pathfinding::PathfindingGraph* const& graph,
          const animation::Running& running,
          const animation::Dying& dying,
          const math::Vector2<float>& position,
          const math::Vector2<float>& dimensions,
          const unsigned int& textureid);

    pathfinding::PathfindingNode const* GetCurrentNode() const;

    void ChangePath(const std::vector<pathfinding::PathfindingNode*>& path);

    void Update(const float& delta);

    void die();

    const bool dead() const;

    const bool& dying() const;

    const std::vector<math::Vector2<float>> GetTextureCoords() const;
};


#endif //THE_LAIR_OF_THE_MINOTAUR_ENEMY_H
