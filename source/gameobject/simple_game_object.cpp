//
// Created by fabio on 12/13/15.
//

#include "simple_game_object.h"

gameobject::SimpleGameObject::SimpleGameObject(const math::Vector2<float>& position,
                                               const math::Vector2<float>& dimensions, const unsigned int& textureid)
        : GameObject(position, dimensions, textureid)
{

}

const std::vector<math::Vector2<float>> gameobject::SimpleGameObject::GetTextureCoords() const
{
    return std::vector<math::Vector2<float>>
            {
                    math::Vector2<float>(0, 1),
                    math::Vector2<float>(1, 1),
                    math::Vector2<float>(1, 0),
                    math::Vector2<float>(0, 0),
            };
}

void gameobject::SimpleGameObject::Update(const float& delta)
{

}
