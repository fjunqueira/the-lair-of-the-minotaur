//
// Created by fabio on 12/15/15.
//

#ifndef THE_LAIR_OF_THE_MINOTAUR_IMAGE_H
#define THE_LAIR_OF_THE_MINOTAUR_IMAGE_H

#include <vector>

struct Image
{
    std::vector<unsigned char> image;

    unsigned int width, height, textureid;
};


#endif //THE_LAIR_OF_THE_MINOTAUR_IMAGE_H
