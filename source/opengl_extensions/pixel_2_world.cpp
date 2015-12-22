//
// Created by fabio on 12/17/15.
//

#include "pixel_2_world.h"

math::Vector2<float> opengl_extensions::Pixel2World(const int& x, const int& y)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat win_x = 0, win_y = 0, win_z = 0;
    GLdouble pos_x = 0, pos_y = 0, pos_z = 0;

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    win_x = (float) x;
    win_y = (float) viewport[3] - (float) y;

    glReadPixels(x, int(win_y), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &win_z);
    gluUnProject(win_x, win_y, win_z, modelview, projection, viewport, &pos_x, &pos_y, &pos_z);

    return math::Vector2<float>((float) pos_x, (float) pos_y);
}
