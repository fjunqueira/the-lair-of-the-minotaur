//
// Created by fabio on 12/21/15.
//

#include "text.h"

void opengl_extensions::DisplayText(float x, float y, int r, int g, int b, std::string text)
{
    int text_length = (int) text.length();

    glColor3f(r, g, b);
    glRasterPos2f(x, y);

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);

    for (int i = 0; i < text_length; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }

    glEnable(GL_TEXTURE_2D);

    glColor4f(1, 1, 1, 1);
}