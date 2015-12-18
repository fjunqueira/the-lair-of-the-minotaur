//
// Created by fabio on 12/12/15.
//

#include "vector2.h"

template<typename T>
math::Vector2<T>::Vector2() : x(0), y(0)
{ }

template<typename T>
math::Vector2<T>::Vector2(const T& x, const T& y) : x(x), y(y) { }

template<typename T>
math::Vector2<T> math::Vector2<T>::operator+(const Vector2<T>& other) const
{
    return Vector2<T>(this->x + other.x, this->y + other.y);
}

template<typename T>
math::Vector2<T> math::Vector2<T>::operator-(const Vector2<T>& other) const
{
    return Vector2<T>(this->x - other.x, this->y - other.y);
}

template<typename T>
math::Vector2<T> math::Vector2<T>::operator*(const T& value) const
{
    return Vector2<T>(this->x * value, this->y * value);
}

template<typename T>
T math::Vector2<T>::magnitude() const
{
    return sqrtf((float) (powf(x, 2) + pow(y, 2)));
}

template struct math::Vector2<int>;

template struct math::Vector2<float>;