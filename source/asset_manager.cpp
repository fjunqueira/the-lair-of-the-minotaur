//
// Created by fabio on 12/15/15.
//

#include <iostream>
#include "asset_manager.h"

AssetManager::AssetManager()
{
    this->load_assets();
}

void AssetManager::load_assets()
{
    GLuint textureids[4];

    glGenTextures(4, textureids);

    this->assets_.insert(std::pair<std::string, Image*>("cave_floor", this->load_texture(textureids[0],
                                                                                         "../assets/tile_cave_1.png")));

    this->assets_.insert(std::pair<std::string, Image*>("minotaur", this->load_texture(textureids[1],
                                                                                       "../assets/minotaur_alpha.png")));

    this->assets_.insert(std::pair<std::string, Image*>("orc", this->load_texture(textureids[2],
                                                                                  "../assets/orc_regular_0.png")));

    this->assets_.insert(std::pair<std::string, Image*>("entrance", this->load_texture(textureids[3],
                                                                                       "../assets/temple_entrance_vines_0.png")));

    std::for_each(this->assets_.begin(), this->assets_.end(), [&](std::pair<const std::string, Image*>& asset)
    {
        glBindTexture(GL_TEXTURE_2D, asset.second->textureid);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, 4, asset.second->width, asset.second->height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, &asset.second->image[0]);
    });
}

const Image* AssetManager::get_asset(const std::string& name) const
{
    return this->assets_.at(name);
}

AssetManager::~AssetManager()
{
    std::for_each(this->assets_.begin(), this->assets_.end(), [&](std::pair<const std::string, Image*>& asset)
    {
        delete asset.second;
    });
}

Image* AssetManager::load_texture(const unsigned int& textureid, const char* path) const
{
    auto image = new Image();

    image->textureid = textureid;

    lodepng::decode(image->image, image->width, image->height, path);

    return image;
}
