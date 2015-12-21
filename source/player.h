//
// Created by fabio on 12/17/15.
//

#ifndef THE_LAIR_OF_THE_MINOTAUR_PLAYER_H
#define THE_LAIR_OF_THE_MINOTAUR_PLAYER_H


#include "gameobject/game_object.h"
#include "tile_map.h"
#include "pathfinding/pathfinding_graph.h"
#include "enemy.h"
#include "animation/idle.h"
#include "animation/attacking.h"
#include "directions.h"

class Player : public gameobject::GameObject
{
private:
    TileMap* map_;

    pathfinding::PathfindingGraph* graph_;

    int current_node_;

    Enemy* target_ = nullptr;

    std::vector<pathfinding::PathfindingNode*> path_;

    animation::Running running_;
    animation::Idle idle_;
    animation::Attacking attacking_;

    animation::AnimationState* current_;

    void ChangeAnimation(animation::AnimationState* state);

public:
    Player(TileMap* const map,
           pathfinding::PathfindingGraph* const graph,
           const animation::Running& running,
           const animation::Idle& idle,
           const animation::Attacking& attacking,
           const math::Vector2<float>& dimensions,
           const unsigned int& textureid);

    pathfinding::PathfindingNode* current_node() const;

    void ChangePath(const std::vector<pathfinding::PathfindingNode*>& path);

    void Update(const float& delta);

    const std::vector<math::Vector2<float>> GetTextureCoords() const;

    void SetTarget(Enemy* const enemy);

    void MoveToCenter();
};


#endif //THE_LAIR_OF_THE_MINOTAUR_PLAYER_H
