//
// Created by fabio on 12/13/15.
//

#ifndef THE_LAIR_OF_THE_MINOTAUR_TILE_MAP_H
#define THE_LAIR_OF_THE_MINOTAUR_TILE_MAP_H


#include "math/vector2.h"
#include "gameobject/simple_game_object.h"
#include <cmath>

class TileMap
{
public:
    TileMap(const math::Vector2<float>& tile_dimensions, const math::Vector2<int>& map_dimensions,
            const unsigned int& textureid);

    const math::Vector2<float> GetTilePositionByIndex(const math::Vector2<int>& index) const;

    const math::Vector2<int> GetTileIndexByPosition(const math::Vector2<float>& position) const;

    const math::Vector2<int>& GetMapDimensions() const;

    gameobject::SimpleGameObject** const& GetTiles() const;

    const int& size() const;

    bool IndexInBounds(const math::Vector2<int>& index) const;

    ~TileMap();

private:
    gameobject::SimpleGameObject** map_;

    int map_width_, size_;

    math::Vector2<int> map_dimensions_;

    math::Vector2<float> tile_dimensions_;
};


#endif //THE_LAIR_OF_THE_MINOTAUR_TILE_MAP_H
