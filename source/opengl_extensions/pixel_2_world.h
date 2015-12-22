//
// Created by fabio on 12/17/15.
//

#ifndef THE_LAIR_OF_THE_MINOTAUR_PIXELTOWORLD_H
#define THE_LAIR_OF_THE_MINOTAUR_PIXELTOWORLD_H


#include "../math/vector2.h"
#include <string>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut_std.h>

namespace opengl_extensions
{
    math::Vector2<float> Pixel2World(const int& x, const int& y);

    void DisplayText(float x, float y, int r, int g, int b, std::string text);
};


#endif //THE_LAIR_OF_THE_MINOTAUR_PIXELTOWORLD_H
