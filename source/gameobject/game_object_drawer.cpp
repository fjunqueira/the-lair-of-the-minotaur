//
// Created by fabio on 12/17/15.
//

#include "game_object_drawer.h"

void ::gameobject::DrawGameObjects(GameObject** const& game_object, const int& size)
{
    for (int i = 0; i < size; ++i)
    {
        gameobject::DrawGameObject(*game_object[i]);
    }
}

void ::gameobject::DrawGameObject(const GameObject& game_object)
{
    auto obj_position = game_object.position();

    auto obj_dimensions = game_object.dimensions();

    glBindTexture(GL_TEXTURE_2D, (GLuint) game_object.textureid());

    glBegin(GL_POLYGON);

    auto coords = game_object.GetTextureCoords();

    glTexCoord2f(coords[0].x, coords[0].y);
    glVertex2d(obj_position.x - obj_dimensions.x / 2, obj_position.y - obj_dimensions.y / 2);

    glTexCoord2f(coords[1].x, coords[1].y);
    glVertex2d(obj_position.x + obj_dimensions.x / 2, obj_position.y - obj_dimensions.y / 2);

    glTexCoord2f(coords[2].x, coords[2].y);
    glVertex2d(obj_position.x + obj_dimensions.x / 2, obj_position.y + obj_dimensions.y / 2);

    glTexCoord2f(coords[3].x, coords[3].y);
    glVertex2d(obj_position.x - obj_dimensions.x / 2, obj_position.y + obj_dimensions.y / 2);

    glEnd();
}