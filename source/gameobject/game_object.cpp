//
// Created by fabio on 12/13/15.
//

#include "game_object.h"

gameobject::GameObject::GameObject(const math::Vector2<float>& position, const math::Vector2<float>& dimensions,
                                   const unsigned int& textureid) : position_(position), dimensions_(dimensions),
                                                                    textureid_(textureid)
{

}

void gameobject::GameObject::SetPosition(const math::Vector2<float>& position)
{
    this->position_ = position;
}

const math::Vector2<float>& gameobject::GameObject::position() const
{
    return this->position_;
}

const math::Vector2<float>& gameobject::GameObject::dimensions() const
{
    return this->dimensions_;
}

const unsigned int& gameobject::GameObject::textureid() const
{
    return this->textureid_;
}

gameobject::GameObject::~GameObject()
{

}
