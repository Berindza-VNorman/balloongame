#include "Tower.hpp"
#include <memory>
#include <cmath>
#include <iostream>
#include "Game.hpp"

Tower::Tower(TowerType type, Game &game, float x, float y)
    : m_type(type), game(game)
{
    setPosition(x, y);
    setType(getType());
    // Set default values
    switch (type)
    {
    case TowerType::RED:
        m_dmg = 20;
        m_radius = 110.0f;
        m_cost = 200;
        towerradius.setRadius(m_radius);
        towerradius.setOutlineColor(sf::Color::Red);
        towerradius.setFillColor(sf::Color(255, 0, 0, 50));
        break;
    case TowerType::BLUE:
        m_dmg = 30;
        m_radius = 120.0f;
        m_cost = 450;
        towerradius.setRadius(m_radius);
        towerradius.setOutlineColor(sf::Color::Blue);
        towerradius.setFillColor(sf::Color(0, 0, 255, 50));
        break;
    case TowerType::PURPLE:
        m_dmg = 50;
        m_radius = 130.0f;
        m_cost = 1000;
        towerradius.setRadius(m_radius);
        towerradius.setOutlineColor(sf::Color(163, 73, 164));
        towerradius.setFillColor(sf::Color(163, 73, 164, 50));
        break;
    default:
        // Unknown tower type, set default values
        m_dmg = 20;
        m_radius = 50.0f;
        m_cost = 100;
        towerradius.setRadius(m_radius);
        towerradius.setFillColor(sf::Color(0, 0, 0, 0));
        break;
    }

    towerradius.setOutlineThickness(2);

    towerradius.setPosition(m_sprite.getPosition().x - m_radius, m_sprite.getPosition().y - m_radius);
}

bool Tower::update(float deltaTime)
{
    auto &allballoons = game.balloons;
    deltaTime = 1.7f; // dmg/sec

    for (const auto &balloon : allballoons)
    {
        const auto pos = balloon->getPosition() - getPosition();
        const auto dist = std::sqrt(std::pow(pos.x, 2) + std::pow(pos.y, 2));

        auto balloonsRadius = balloon->getRadius();
        auto towersRadius = getRadius();
        towersRadius += (m_radius / 2) - 8.0f;

        if (dist <= balloonsRadius + towersRadius && m_timer.getElapsedTime().asSeconds() > deltaTime)
        {

            int balloon_elete = balloon->getm_health();
            balloon->setHealth(balloon_elete - getDmgPerType());

            if (balloon_elete <= 45)
            {
                balloon->setTransparent();
            }
            m_timer.restart();
            return true;
        }
    }

    return false;
}

int Tower::getDmgPerType() const
{

    switch (m_type)
    {
    case TowerType::RED:
        return 20;
    case TowerType::BLUE:
        return 30;
    case TowerType::PURPLE:
        return 50;
    default:
        return 0;
    }
}

int Tower::getCost() const
{
    return m_cost;
}

void Tower::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform(); // setting the position of the tower to the sprite
    target.draw(m_sprite, states);
    target.draw(towerradius, states);
}
void Tower::setType(TowerType type)
{
    m_type = type;
    setTexture(game.getTextureTower(type));
}
sf::Texture &Tower::getTexture()
{
    return m_texture;
}
void Tower::setTexture(const sf::Texture &texture)
{
    m_sprite.setTexture(texture);
    m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
}

float Tower::getRadius() const
{
    return 37.5f; // 75/2 radius
}

sf::FloatRect Tower::getGlobalBounds() const
{
    return getTransform().transformRect(m_sprite.getGlobalBounds());
}