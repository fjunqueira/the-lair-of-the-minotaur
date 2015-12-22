//
// Created by fabio on 12/17/15.
//

#include "player.h"
#include "enemy_manager.h"

void Player::ChangeAnimation(animation::AnimationState* state)
{
    if (this->current_->type() != state->type())
    {
        state->Reset();
        this->current_ = state;
    }
}

Player::Player(TileMap* const map,
               pathfinding::PathfindingGraph* const graph,
               std::vector<Enemy>* const enemies,
               const animation::Running& running,
               const animation::Idle& idle,
               const animation::Attacking& attacking,
               const math::Vector2<float>& dimensions,
               const unsigned int& textureid) :
        map_(map), graph_(graph), running_(running), idle_(idle), attacking_(attacking), enemies_(enemies),
        GameObject(math::Vector2<float>(), dimensions, textureid)
{
    this->current_ = &this->idle_;
}

pathfinding::PathfindingNode* Player::current_node() const
{
    return this->path_[this->current_node_];
}

void Player::ChangePath(const std::vector<pathfinding::PathfindingNode*>& path)
{
    this->current_node_ = 0;
    this->path_ = path;
}

void Player::Update(const float& delta)
{
    if (this->current_node_ < this->path_.size() - 1)
    {
        auto current_node = this->path_[this->current_node_];

        auto next_node = this->path_[this->current_node_ + 1];

        auto next_node_position = this->map_->GetTilePositionByIndex(next_node->index);

        this->position_ = this->position_ + (next_node_position - this->position_) * 0.01f * delta;

        ChangeAnimation(&this->running_);

        if ((this->position_ - next_node_position).magnitude() < 5)
            this->current_node_++;

        this->current_->MoveToNextFrame(directions::GetCardinalDirection(current_node, next_node), delta);
    }
    else
    {
        auto previous_node =
                this->path_.size() > 1 ? this->path_[this->current_node_ - 1] : this->path_[this->current_node_];

        auto current_node = this->path_[this->current_node_];

        Enemy* target = nullptr;

        if (this->current_->type() == animation::states::RUNNING)
            target = this->GetNearestEnemy(this->map_->GetTilePositionByIndex(current_node->index));

        if (target != nullptr && (this->position_ - target->position()).magnitude() < 30)
        {
            target->die();
            ChangeAnimation(&this->attacking_);
        }
        else if (this->current_->MoveToNextFrame(directions::GetCardinalDirection(previous_node, current_node), delta))
        {
            ChangeAnimation(&this->idle_);
        }
    }
}

const std::vector<math::Vector2<float>> Player::GetTextureCoords() const
{
    return this->current_->GetCurrentFrameCoords();
}

void Player::MoveToCenter()
{
    auto starting_position = this->map_->GetTilePositionByIndex(math::Vector2<int>(15, 15));

    this->position_ = starting_position;

    this->ChangePath(
            std::vector<pathfinding::PathfindingNode*>() = {this->graph_->GetNodeByIndex(math::Vector2<int>(15, 15))});
}

Enemy* const Player::GetNearestEnemy(const math::Vector2<float>& point) const
{
    Enemy* nearest_enemy = nullptr;
    float nearest_enemy_distance = FLT_MAX;

    std::for_each(this->enemies_->begin(), this->enemies_->end(), [&](Enemy& enemy)
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