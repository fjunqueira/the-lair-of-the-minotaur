//
// Created by fabio on 12/13/15.
//

#ifndef THE_LAIR_OF_THE_MINOTAUR_SIMPLE_GAME_OBJECT_H
#define THE_LAIR_OF_THE_MINOTAUR_SIMPLE_GAME_OBJECT_H

#include "game_object.h"

namespace gameobject
{
    class SimpleGameObject : public gameobject::GameObject
    {
    public:
        SimpleGameObject(const math::Vector2<float>& position, const math::Vector2<float>& dimensions,
                         const unsigned int& textureid);

        const std::vector<math::Vector2<float>> GetTextureCoords() const;

        void Update(const float& delta);
    };
}


#endif //THE_LAIR_OF_THE_MINOTAUR_SIMPLE_GAME_OBJECT_H
