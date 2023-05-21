#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>

class Tile
{
public:
    enum Type
    {
        Grass = 1,
        Road = 2,
        Start = 3,
        End = 4,
        Wall = 5
    };

    Tile(Type type, int x, int y, int size);

    void draw(sf::RenderWindow &window);
    void setTexture(sf::Texture &texture);

    Type getType() const { return m_type; }
    void setType(Type type);

    sf::Sprite &getSprite() { return m_sprite; }

    sf::Sprite m_sprite;
    sf::Texture m_texture;

private:
    Type m_type;
};

#endif