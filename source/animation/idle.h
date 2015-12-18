//
// Created by fabio on 12/17/15.
//

#ifndef THE_LAIR_OF_THE_MINOTAUR_IDLE_H
#define THE_LAIR_OF_THE_MINOTAUR_IDLE_H

#include "animation_state.h"
#include "../image.h"

namespace animation
{
    class Idle : public animation::AnimationState
    {
    private:
        int current_frame_ = 1;

        float frame_width_;

        float frame_height_;

        float total_elapsed_time_ = 0;

        std::vector<math::Vector2<float>> current_frame_coords_;

        int frame_increment_direction_ = 1;

    public:
        Idle(const Image* spritesheet, const int& num_of_frames, const int& direction);

        int get_type() const;

        bool MoveToNextFrame(const int& direction, const float& delta);

        std::vector<math::Vector2<float>> GetCurrentFrameCoords() const;

        void Reset();
    };
}


#endif //THE_LAIR_OF_THE_MINOTAUR_IDLE_H
