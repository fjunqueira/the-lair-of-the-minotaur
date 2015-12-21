//
// Created by fabio on 12/17/15.
//

#include "running.h"

animation::Running::Running(const Image* spritesheet, const int& num_of_frames, const int& direction) :
        frame_width_((float) (spritesheet->width / (num_of_frames / 8)) / spritesheet->width),
        frame_height_((float) (spritesheet->height / 8) / spritesheet->height)
{
    this->MoveToNextFrame(direction, 0);
}

int animation::Running::get_type() const
{
    return animation::states::RUNNING;
}

bool animation::Running::MoveToNextFrame(const int& direction, const float& delta)
{
    total_elapsed_time_ += delta;

    if (this->current_frame_ > 12)
        this->current_frame_ = 5;

    this->current_frame_coords_ = std::vector<math::Vector2<float>>
            {
                    math::Vector2<float>(frame_width_ * (current_frame_ - 1), frame_height_ * direction),
                    math::Vector2<float>(frame_width_ * current_frame_, frame_height_ * direction),
                    math::Vector2<float>(frame_width_ * current_frame_, frame_height_ * (direction - 1)),
                    math::Vector2<float>(frame_width_ * (current_frame_ - 1), frame_height_ * (direction - 1)),
            };

    if (total_elapsed_time_ > 100 || delta == 0)
    {
        total_elapsed_time_ = 0;
        this->current_frame_++;
    }

    //can be aborted at any time
    return true;
}

std::vector<math::Vector2<float>> animation::Running::GetCurrentFrameCoords() const
{
    return this->current_frame_coords_;
}

void animation::Running::Reset()
{
    this->current_frame_ = 5;
    this->total_elapsed_time_ = 0;
}
