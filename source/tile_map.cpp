//
// Created by fabio on 12/13/15.
//

#include "tile_map.h"

TileMap::TileMap(const math::Vector2<float>& tile_dimensions, const math::Vector2<int>& map_dimensions,
                 const unsigned int& textureid) : tile_dimensions_(tile_dimensions), map_dimensions_(map_dimensions),
                                                  size_(map_dimensions.x * map_dimensions.y),
                                                  map_width_(map_dimensions.x)
{
    auto size = map_dimensions.x * map_dimensions.y;

    this->map_ = new gameobject::SimpleGameObject* [size]();

    for (int y = 0; y < map_dimensions.y; ++y)
    {
        for (int x = 0; x < map_dimensions.x; ++x)
        {
            auto index = math::Vector2<int>(x, y);

            this->map_[y + x * map_dimensions.x] = new gameobject::SimpleGameObject(this->GetTilePositionByIndex(index),
                                                                                    tile_dimensions, textureid);
        }
    }
}

const math::Vector2<float> TileMap::GetTilePositionByIndex(const math::Vector2<int>& index) const
{
    float x = (float) index.x * tile_dimensions_.x / 2.0f + index.y * tile_dimensions_.y / 2.0f;
    float y = (float) index.x * tile_dimensions_.x / 2.0f - index.y * tile_dimensions_.y / 2.0f;

    return math::Vector2<float>(x, y);
}

const math::Vector2<int> TileMap::GetTileIndexByPosition(const math::Vector2<float>& position) const
{
    float x = (position.x + position.y) / tile_dimensions_.x;
    float y = (position.x - position.y) / tile_dimensions_.y;

    return math::Vector2<int>((int) std::round(x), (int) std::round(y));
}

const math::Vector2<int>& TileMap::GetMapDimensions() const
{
    return this->map_dimensions_;
}

gameobject::SimpleGameObject** const& TileMap::GetTiles() const
{
    return this->map_;
}

const int& TileMap::size() const
{
    return this->size_;
}

bool TileMap::IndexInBounds(const math::Vector2<int>& index) const
{
    return ((index.x >= 0 && index.x < map_dimensions_.x) && (index.y >= 0 && index.y < map_dimensions_.y));
}

TileMap::~TileMap()
{
    for (int i = 0; i < this->size(); ++i)
        delete this->map_[i];

    delete[] this->map_;
}
