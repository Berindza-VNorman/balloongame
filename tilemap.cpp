#include "TileMap.hpp"
#include "Tile.hpp"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

TileMap::TileMap(std::string filename)
{
    // Betöltjük a textúrákat
    if (!m_grassTexture.loadFromFile("tiles/grass.png"))
    {
        std::cerr << "Could not load grass.png" << std::endl;
    }
    if (!m_roadTexture.loadFromFile("tiles/road.png"))
    {
        std::cerr << "Could not load road.png" << std::endl;
    }
    if (!m_wallTexture.loadFromFile("tiles/wall.png"))
    {
        std::cerr << "Could not load wall.png" << std::endl;
    }
    if (!m_startTexture.loadFromFile("tiles/start.png"))
    {
        std::cerr << "Could not load start.png" << std::endl;
    }
    if (!m_endTexture.loadFromFile("tiles/end.png"))
    {
        std::cerr << "Could not load end.png" << std::endl;
    }

    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Could not open file " << filename << std::endl;
        return;
    }

    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            char c;
            file >> c;
            int tileType = c - '0';

            // Tile kirajzolása a megfelelő textúrával
            switch (tileType)
            {
            case 1:
                m_tiles[y][x] = std::make_unique<Tile>(Tile::Grass, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE);
                m_tiles[y][x]->m_sprite.setTexture(m_grassTexture);
                break;
            case 2:
                m_tiles[y][x] = std::make_unique<Tile>(Tile::Road, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE);
                m_tiles[y][x]->m_sprite.setTexture(m_roadTexture);
                break;
            case 3:
                m_tiles[y][x] = std::make_unique<Tile>(Tile::Start, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE);
                m_tiles[y][x]->m_sprite.setTexture(m_startTexture);
                break;
            case 4:
                m_tiles[y][x] = std::make_unique<Tile>(Tile::End, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE);
                m_tiles[y][x]->m_sprite.setTexture(m_endTexture);
                break;
            case 5:
                m_tiles[y][x] = std::make_unique<Tile>(Tile::Wall, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE);
                m_tiles[y][x]->m_sprite.setTexture(m_wallTexture);
                break;
            default:
                std::cerr << "Invalid tile type: " << tileType << std::endl;
                break;
            }
        }
    }
}

sf::Sprite TileMap::getSprite(int x, int y) const
{
    return m_tiles[y][x]->m_sprite;
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            target.draw(m_tiles[y][x]->m_sprite, states);
        }
    }
}
