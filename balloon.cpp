#include "balloon.hpp"
#include <memory>
#include <iostream>
#include <cmath>
#include "game.hpp"

Balloon::Balloon(BalloonType type, Game &game) : m_type(type), m_speed(70.f), m_health(100), m_value(10), game(game)
{

    setPosition(120.f, 100.f);
    setType(getType());

    if (type == BalloonType::RED)
    {
        m_speed = 50.f;
        m_health = 50;
        m_value = 60;
    }
    else if (type == BalloonType::BLUE)
    {
        m_speed = 60.f;
        m_health = 85;
        m_value = 80;
    }
    else if (type == BalloonType::GREEN)
    {
        m_speed = 65.f;
        m_health = 150;
        m_value = 100;
    }
    else if (type == BalloonType::YELLOW)
    {
        m_speed = 70.f;
        m_health = 200;
        m_value = 120;
    }
    else
    {
        m_speed = 70.f;
        m_health = 280;
        m_value = 130;
    }

    // initialize hpbar
    hpbar.setSize(sf::Vector2f(40.f, 10.f));
    hpbar.setFillColor(sf::Color(0, 255, 128, 250));
    hpbar.setOutlineThickness(2);
    hpbar.setOutlineColor(sf::Color::Black);

    hpbar.setPosition(m_sprite.getPosition().x - 20.f, m_sprite.getPosition().y - 25.f);
}
void Balloon::setHealth(float health)
{

    m_health = health;
    float maxhp = getHealth();

    hpbar.setSize(sf::Vector2f((m_health / maxhp) * 40.f, 10.f)); // A hpbar width scaling with hp
    if (m_health <= 0)
    {

        m_health = 0;
        game.addGold(getValue());

        hpbar.setSize(sf::Vector2f(0.f, 0.f));
    }
}
int Balloon::getHealth() const
{
    switch (m_type)
    {
    case BalloonType::RED:
        return 50;
    case BalloonType::BLUE:
        return 85;
    case BalloonType::GREEN:
        return 150;
    case BalloonType::YELLOW:
        return 200;
    case BalloonType::PURPLE:
        return 280;
    default:
        return 0;
    }
}

sf::Texture &Balloon::getTexture()
{
    return m_texture;
}

void Balloon::setTexture(const sf::Texture &texture)
{
    m_sprite.setTexture(texture);
    m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
}
void Balloon::setType(BalloonType type)
{
    m_type = type;
    setTexture(game.getTexture(type));
}
bool Balloon::update(float deltaTime)
{
    if (m_health <= 0)
    {
        return true;
    }

    std::vector<sf::Vector2f> destinations = {
        {120.f, 445.f}, {200.f, 445.f}, {200.f, 610.f}, {120.f, 610.f}, {120.f, 850.f}, {365.f, 850.f}, {365.f, 120.f}, {610.f, 120.f}, {610.f, 285.f}, {530.f, 285.f}, {530.f, 445.f}, {610.f, 445.f}, {610.f, 920.f}};

    sf::Vector2f position = getPosition();
    sf::Vector2f destination = destinations[nextDestinationIndex];
    sf::Vector2f direction = destination - position;

    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance <= m_speed * deltaTime)
    {
        setPosition(destination);
        nextDestinationIndex++;
    }
    else
    {
        sf::Vector2f velocity = direction / distance * m_speed;
        setPosition(position + velocity * deltaTime);
    }

    if (nextDestinationIndex == destinations.size())
    {

        int hp = game.getHp();
        game.setHp(hp - 1);
        if (game.getHp() == 0)
        {
            game.setPauseDisabled(true); // dead no pause available
            game.setisPausedToTrue();
        }

        return true; // balloon reached final destination
    }

    return false; // balloon still moving
}

void Balloon::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_sprite, states);
    target.draw(hpbar, states);
}

float Balloon::getSpeed() const
{
    return m_speed;
}

int Balloon::getValue() const
{
    switch (m_type)
    {
    case BalloonType::RED:
        return 60;
    case BalloonType::BLUE:
        return 80;
    case BalloonType::GREEN:
        return 100;
    case BalloonType::YELLOW:
        return 120;
    default:
        return 130;
    }
}
float Balloon::getRadius() const
{
    return std::sqrt(std::pow(25, 2) + std::pow(32.5, 2));
}

void Balloon::setTransparent()
{
    switch (m_type)
    {
    case BalloonType::RED:
        m_sprite.setColor(sf::Color(255, 0, 0, 150));
        break;
    case BalloonType::BLUE:
        m_sprite.setColor(sf::Color(0, 0, 255, 150));
        break;
    case BalloonType::GREEN:
        m_sprite.setColor(sf::Color(0, 255, 0, 200));
        break;
    case BalloonType::YELLOW:
        m_sprite.setColor(sf::Color(255, 255, 0, 150));
        break;
    default:
        m_sprite.setColor(sf::Color(114, 0, 255, 150));
        break;
    }
}
