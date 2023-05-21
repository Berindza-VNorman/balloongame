#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "tile.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    TileMap(std::string filename);
    int MAP_HEIGHT = 12;
    int MAP_WIDTH = 12;
    int TILE_SIZE = 9;
    sf::Sprite getSprite(int x, int y) const;
    std::unique_ptr<Tile> m_tiles[12][12];

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    sf::Texture m_grassTexture;
    sf::Texture m_roadTexture;
    sf::Texture m_wallTexture;
    sf::Texture m_startTexture;
    sf::Texture m_endTexture;
};

#endif