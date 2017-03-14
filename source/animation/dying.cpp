//
// Created by fabio on 12/17/15.
//

#include "dying.h"

animation::Dying::Dying(const Image* spritesheet, const int& num_of_frames, const int& direction) :
        frame_width_((float) (spritesheet->width / (num_of_frames / 8)) / spritesheet->width),
        frame_height_((float) (spritesheet->height / 8) / spritesheet->height)
{
    this->MoveToNextFrame(direction, -1);
}

int animation::Dying::type() const
{
    return animation::states::DYING;
}

bool animation::Dying::MoveToNextFrame(const int& direction, const float& delta)
{
    total_elapsed_time_ += delta;

    if (this->current_frame_ > 24)
        this->current_frame_ = 19;

    this->current_frame_coords_ = std::vector<math::Vector2<float>>
            {
                    math::Vector2<float>(frame_width_ * (current_frame_ - 1), frame_height_ * direction),
                    math::Vector2<float>(frame_width_ * current_frame_, frame_height_ * direction),
                    math::Vector2<float>(frame_width_ * current_frame_, frame_height_ * (direction - 1)),
                    math::Vector2<float>(frame_width_ * (current_frame_ - 1), frame_height_ * (direction - 1)),
            };

    if (total_elapsed_time_ > 100 || delta == -1)
    {
        total_elapsed_time_ = 0;
        this->current_frame_++;
    }

    return this->current_frame_ > 24;
}

std::vector<math::Vector2<float>> animation::Dying::GetCurrentFrameCoords() const
{
    return this->current_frame_coords_;
}

void animation::Dying::Reset()
{
    this->current_frame_ = 19;
    this->total_elapsed_time_ = 0;
}
