//
// Created by fabio on 12/15/15.
//

#ifndef THE_LAIR_OF_THE_MINOTAUR_ASSET_MANAGER_H
#define THE_LAIR_OF_THE_MINOTAUR_ASSET_MANAGER_H


#include "image.h"
#include <string>
#include <map>
#include <algorithm>
#include <GL/gl.h>
#include <iostream>
#include "lodepng.h"

class AssetManager
{
public:

    AssetManager();

    void load_assets();

    const Image* get_asset(const std::string& name) const;

    ~AssetManager();

private:
    std::map<std::string, Image*> assets_;

    Image* load_texture(const unsigned int& textureid, const char* path) const;
};


#endif //THE_LAIR_OF_THE_MINOTAUR_ASSET_MANAGER_H
