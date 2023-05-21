#ifndef BALLOON_HPP
#define BALLOON_HPP

#include <SFML/Graphics.hpp>

class Game;
enum class BalloonType
{
    BLUE,
    GREEN,
    PURPLE,
    RED,
    YELLOW
};

class Balloon : public sf::Drawable, public sf::Transformable
{
public:
    Balloon(BalloonType type, Game &game);
    bool update(float deltaTime);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    sf::Texture &getTexture();
    void setTexture(const sf::Texture &texture);
    void setType(BalloonType type);
    BalloonType getType() const { return m_type; }

    float getRadius() const;

    float getSpeed() const;
    int getValue() const;
    void setHealth(float health);
    int getHealth() const;
    int getm_health() const { return m_health; }

    void setTransparent();

private:
    BalloonType m_type;

    sf::Texture m_texture;
    sf::Sprite m_sprite;
    float m_speed;
    int m_health;
    int m_value;
    int nextDestinationIndex = 0;
    Game &game;
    sf::RectangleShape hpbar;
};

#endif
