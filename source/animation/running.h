//
// Created by fabio on 12/17/15.
//

#ifndef THE_LAIR_OF_THE_MINOTAUR_RUNNING_H
#define THE_LAIR_OF_THE_MINOTAUR_RUNNING_H

#include "animation_state.h"
#include "../image.h"

namespace animation
{
    class Running : public animation::AnimationState
    {
    private:
        int current_frame_ = 5;

        float frame_width_;

        float frame_height_;

        float total_elapsed_time_ = 0;

        std::vector<math::Vector2<float>> current_frame_coords_;

    public:
        Running(const Image* spritesheet, const int& num_of_frames, const int& direction);

        int get_type() const;

        bool MoveToNextFrame(const int& direction, const float& delta);

        std::vector<math::Vector2<float>> GetCurrentFrameCoords() const;

        void Reset();
    };
}


#endif //THE_LAIR_OF_THE_MINOTAUR_RUNNING_H
