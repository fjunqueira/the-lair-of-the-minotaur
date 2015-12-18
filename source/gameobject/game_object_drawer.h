//
// Created by fabio on 12/17/15.
//

#ifndef THE_LAIR_OF_THE_MINOTAUR_GAME_OBJECT_DRAWER_H
#define THE_LAIR_OF_THE_MINOTAUR_GAME_OBJECT_DRAWER_H

#include "game_object.h"
#include <GL/gl.h>

namespace gameobject
{
    void DrawGameObject(const GameObject& game_object);

    void DrawGameObjects(GameObject** const& game_object, const int& size);
};


#endif //THE_LAIR_OF_THE_MINOTAUR_GAME_OBJECT_DRAWER_H
