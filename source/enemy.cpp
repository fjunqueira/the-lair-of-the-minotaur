//
// Created by fabio on 12/17/15.
//

#include "enemy.h"

Enemy::Enemy(TileMap* const& map,
             pathfinding::PathfindingGraph* const& graph,
             const animation::Running& running,
             const animation::Dying& dying,
             const math::Vector2<float>& position,
             const math::Vector2<float>& dimensions,
             const unsigned int& textureid) :
        map_(map), graph_(graph), running_(running), dying_(dying),
        GameObject(position, dimensions, textureid)
{
    this->animation_ = &this->running_;
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
    auto current_node = this->path_[this->current_node_];

    auto next_node = this->path_[this->current_node_ + 1];

    if (this->is_dying_)
    {
        this->time_dying_ += delta;
        return;
    }

    if (this->animation_->type() == animation::states::DYING)
    {
        this->is_dying_ = this->animation_->MoveToNextFrame(directions::GetCardinalDirection(current_node, next_node),
                                                            delta);
    }
    else if (this->current_node_ < this->path_.size() - 1)
    {
        auto current_node_pos = this->map_->GetTilePositionByIndex(current_node->index);

        auto next_node_pos = this->map_->GetTilePositionByIndex(next_node->index);

        this->position_ = this->position_ + (next_node_pos - current_node_pos) * 0.001f * delta;

        this->animation_->MoveToNextFrame(directions::GetCardinalDirection(current_node, next_node), delta);

        if ((this->position_ - next_node_pos).magnitude() < 5)
            this->current_node_++;
    }
}

void Enemy::die()
{
    this->animation_ = &this->dying_;
}

const bool Enemy::dead() const
{
    return this->is_dying_ && this->time_dying_ > 2000;
}

const std::vector<math::Vector2<float>> Enemy::GetTextureCoords() const
{
    return this->animation_->GetCurrentFrameCoords();
}

const bool& Enemy::dying() const
{
    return this->is_dying_;
}
