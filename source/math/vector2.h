//
// Created by fabio on 12/12/15.
//

#ifndef THE_LAIR_OF_THE_MINOTAUR_VECTOR2_H
#define THE_LAIR_OF_THE_MINOTAUR_VECTOR2_H

#include <math.h>

namespace math
{
    template<typename T>
    struct Vector2
    {
        T x, y;

        Vector2();

        Vector2(const T& x, const T& y);

        Vector2<T> operator+(const Vector2<T>& other) const;

        Vector2<T> operator-(const Vector2<T>& other) const;

        Vector2<T> operator*(const T& value) const;

        T magnitude() const;
    };
}


#endif //THE_LAIR_OF_THE_MINOTAUR_VECTOR2_H
