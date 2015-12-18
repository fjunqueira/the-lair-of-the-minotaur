//
// Created by fabio on 12/17/15.
//

#ifndef THE_LAIR_OF_THE_MINOTAUR_ANIMATION_STATE_H
#define THE_LAIR_OF_THE_MINOTAUR_ANIMATION_STATE_H

#include "../math/vector2.h"
#include <vector>

namespace animation
{
    class AnimationState
    {
    public:
        virtual int get_type() const = 0;

        virtual bool MoveToNextFrame(const int& direction, const float& delta) = 0;

        virtual std::vector<math::Vector2<float>> GetCurrentFrameCoords() const = 0;

        virtual void Reset() = 0;
    };

    namespace states
    {
        const int IDLE = 0;
        const int RUNNING = 1;
        const int ATTACKING = 2;
        const int DYING = 3;
    };
};

#endif //THE_LAIR_OF_THE_MINOTAUR_ANIMATION_STATE_H
