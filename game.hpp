#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "tilemap.hpp"
#include "balloon.hpp"
#include "tower.hpp"
#include <memory>

class Game
{
public:
    Game();
    void run();

    int getHp() const { return startinghp; }
    void setHp(int startinghp) { this->startinghp = startinghp; }

    sf::Texture &getTexture(BalloonType type);
    sf::Texture &getTextureTower(TowerType type);

    bool getisPaused() const { return isPaused; }
    void setisPausedToTrue() { isPaused = true; }

    bool getPauseDisabled() const { return isPauseDisabled; }
    void setPauseDisabled(bool value) { isPauseDisabled = value; }

    void BuildBlue();
    void BuildRed();
    void BuildPurple();
    void Sell();

    int getGold() const;
    void addGold(int value);

    std::vector<std::unique_ptr<Balloon>> balloons;
    std::vector<std::unique_ptr<Tower>> towers;

private:
    void handleEvents();
    void update(float deltaTime);
    void render();

    void spamBalloons(float delay);

    int WINDOW_WIDTH = 980;
    int WINDOW_HEIGHT = 980;
    int MAP_SIZE = 12;
    sf::RenderWindow m_window;

    TileMap m_tileMap;
    Tile m_tile;
    Tower m_tower;

    float elapsedTime = 0.f;
    float delayBetweenBalloons = 3.0f;

    sf::Clock goldTime;
    sf::Clock m_clock;

    sf::Clock spawnClock;

    bool isPaused = false; // játék szünetel-e

    bool isPauseDisabled = false;

    sf::Font GameOverFont;
    sf::Font timeFont;
    sf::Font goldFont;
    sf::Font hpFont;
    sf::Font FinalFont;
    sf::Font YouWinFont;

    sf::Text GameOverText;
    sf::Text elapsedTimeText;
    sf::Text goldText;
    sf::Text hpText;
    sf::Text FinalText;
    sf::Text YouWinText;

    sf::Time elapsed;
    sf::Time deltaTime;

    sf::Time myTimer;
    sf::Time spawntime;
    sf::Clock waveTimer;

    int gold;
    int startinghp;

    sf::Texture blue_texture;
    sf::Texture red_texture;
    sf::Texture green_texture;
    sf::Texture yellow_texture;
    sf::Texture purple_texture;

    sf::Sprite blue_sprite;
    sf::Sprite red_sprite;
    sf::Sprite green_sprite;
    sf::Sprite yellow_sprite;
    sf::Sprite purple_sprite;

    sf::Texture blue_texture_tower;
    sf::Texture red_texture_tower;
    sf::Texture purple_texture_tower;

    sf::Sprite blue_sprite_tower;
    sf::Sprite red_sprite_tower;
    sf::Sprite purple_sprite_tower;

};

#endif