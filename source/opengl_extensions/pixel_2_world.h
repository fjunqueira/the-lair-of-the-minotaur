//
// Created by fabio on 12/17/15.
//

#ifndef THE_LAIR_OF_THE_MINOTAUR_PIXELTOWORLD_H
#define THE_LAIR_OF_THE_MINOTAUR_PIXELTOWORLD_H


#include "../math/vector2.h"
#include <GL/gl.h>
#include <GL/glu.h>

namespace opengl_extensions
{
    math::Vector2<float> Pixel2World(const int& x, const int& y);
};


#endif //THE_LAIR_OF_THE_MINOTAUR_PIXELTOWORLD_H
