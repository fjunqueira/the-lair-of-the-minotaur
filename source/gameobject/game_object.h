//
// Created by fabio on 12/13/15.
//

#ifndef THE_LAIR_OF_THE_MINOTAUR_GAME_OBJECT_H
#define THE_LAIR_OF_THE_MINOTAUR_GAME_OBJECT_H

#include "../math/vector2.h"
#include <vector>

namespace gameobject
{
    class GameObject
    {
    public:
        GameObject(const math::Vector2<float>& position, const math::Vector2<float>& dimensions,
                   const unsigned int& textureid);

        void SetPosition(const math::Vector2<float>& position);

        const math::Vector2<float>& position() const;

        const math::Vector2<float>& dimensions() const;

        const unsigned int& textureid() const;

        virtual const std::vector<math::Vector2<float>> GetTextureCoords() const = 0;

        virtual void Update(const float& delta) = 0;

        virtual ~GameObject();

    protected:
        math::Vector2<float> dimensions_;

        math::Vector2<float> position_;

        unsigned int textureid_;
    };
}

#endif //THE_LAIR_OF_THE_MINOTAUR_GAME_OBJECT_H
