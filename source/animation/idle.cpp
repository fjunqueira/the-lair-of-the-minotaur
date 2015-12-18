//
// Created by fabio on 12/17/15.
//

#include "idle.h"

animation::Idle::Idle(const Image* spritesheet, const int& num_of_frames, const int& direction) :
        frame_width_((float) (spritesheet->width / (num_of_frames / 8)) / spritesheet->width),
        frame_height_((float) (spritesheet->height / 8) / spritesheet->height)
{
    this->MoveToNextFrame(direction, 0);
}

int animation::Idle::get_type() const
{
    return animation::states::IDLE;
}

bool animation::Idle::MoveToNextFrame(const int& direction, const float& delta)
{
    total_elapsed_time_ += delta;

    this->current_frame_coords_ = std::vector<math::Vector2<float>>
            {
                    math::Vector2<float>(frame_width_ * (current_frame_ - 1), frame_height_ * (direction - 1)),
                    math::Vector2<float>(frame_width_ * current_frame_, frame_height_ * (direction - 1)),
                    math::Vector2<float>(frame_width_ * current_frame_, frame_height_ * direction),
                    math::Vector2<float>(frame_width_ * (current_frame_ - 1), frame_height_ * direction),
            };

    if (this->current_frame_ >= 4)
    {
        frame_increment_direction_ = -1;
    }
    else if (this->current_frame_ <= 1)
    {
        frame_increment_direction_ = 1;
    }

    if (total_elapsed_time_ > 300 || delta == 0)
    {
        total_elapsed_time_ = 0;
        this->current_frame_ += frame_increment_direction_;
    }

    //This animation loops forever
    return false;
}

std::vector<math::Vector2<float>> animation::Idle::GetCurrentFrameCoords() const
{
    return this->current_frame_coords_;
}

void animation::Idle::Reset()
{
    this->current_frame_ = 1;
    this->total_elapsed_time_ = 0;
}
