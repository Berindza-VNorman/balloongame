#include "Tile.hpp"

Tile::Tile(Type type, int x, int y, int size) : m_type(type)
{

    switch (type)
    {
    case Grass:
        m_texture.loadFromFile("tiles/grass.png");
        break;
    case Road:
        m_texture.loadFromFile("tiles/road.png");
        break;
    case Start:
        m_texture.loadFromFile("tiles/start.png");
        break;
    case End:
        m_texture.loadFromFile("tiles/end.png");
        break;
    case Wall:
        m_texture.loadFromFile("tiles/wall.png");
        break;
    }

    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(x * size, y * size);
}

void Tile::draw(sf::RenderWindow &window)
{
    window.draw(m_sprite);
}

void Tile::setTexture(sf::Texture &texture)
{
    m_texture = texture;
    m_sprite.setTexture(m_texture);
}
void Tile::setType(Type type)
{
    m_type = type;
}
