#ifndef TOWER_H
#define TOWER_H

#include <SFML/Graphics.hpp>
#include "Balloon.hpp"
#include "Tile.hpp"

class Game;
enum class TowerType
{
    BLUE,
    PURPLE,
    RED
};

class Tower : public sf::Drawable, public sf::Transformable
{
public:
    Tower(TowerType type, Game &game, float x, float y);
    bool update(float deltaTime);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::Texture &getTexture();
    void setTexture(const sf::Texture &texture);

    void setType(TowerType type);
    TowerType getType() const { return m_type; }

    sf::Sprite &getSprite() { return m_sprite; }

    int getCost() const;

    float getRadius() const;

    sf::FloatRect getGlobalBounds() const;

    int getDmgPerType() const;

private:
    TowerType m_type;

    sf::Texture m_texture;
    sf::Sprite m_sprite;

    sf::CircleShape towerradius;

    int m_width;
    int m_height;
    int m_dmg;
    int m_cost;
    float m_radius;

    sf::Clock m_timer;

    Game &game;
};

#endif
