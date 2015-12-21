//
// Created by fabio on 12/17/15.
//

#include "enemy.h"
#include "directions.h"

Enemy::Enemy(TileMap* const& map, pathfinding::PathfindingGraph* const& graph, const animation::Running& running,
             const math::Vector2<float>& position, const math::Vector2<float>& dimensions,
             const unsigned int& textureId) :
        map_(map), graph_(graph), animation_(running), GameObject(position, dimensions, textureId)
{

}

pathfinding::PathfindingNode const* Enemy::GetCurrentNode() const
{
    return this->path_[this->current_node_];
}

void Enemy::ChangePath(const std::vector<pathfinding::PathfindingNode*>& path)
{
    this->current_node_ = 0;
    this->path_ = path;
}

void Enemy::Update(const float& delta)
{
    if (this->current_node_ < this->path_.size() - 1)
    {
        auto current_node = this->path_[this->current_node_];

        auto nextNode = this->path_[this->current_node_ + 1];

        auto current_node_pos = this->map_->GetTilePositionByIndex(current_node->index);

        auto next_node_pos = this->map_->GetTilePositionByIndex(nextNode->index);

        this->position_ = this->position_ + (next_node_pos - current_node_pos) * 0.001f * delta;

        this->animation_.MoveToNextFrame(directions::GetCardinalDirection(current_node, nextNode), delta);

        if ((this->position_ - next_node_pos).magnitude() < 5)
            this->current_node_++;
    }
}

void Enemy::die()
{
    this->dead_ = true;
}

const bool& Enemy::dead() const
{
    return this->dead_;
}

const std::vector<math::Vector2<float>> Enemy::GetTextureCoords() const
{
    return this->animation_.GetCurrentFrameCoords();
}
