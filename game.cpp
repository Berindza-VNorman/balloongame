#include "Game.hpp"
#include "TileMap.hpp"
#include "MainMenu.hpp"
#include <iostream>
#include <cmath>
#include <iomanip>

#include <SFML/Graphics.hpp>

Game::Game() : m_tile(Tile::Road, 0, 0, 0), m_tower(TowerType::BLUE, *this, 0, 0), m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game"), m_tileMap("map.txt"), gold(400), startinghp(15)
{

    m_window.setFramerateLimit(30);

    if (!timeFont.loadFromFile("fonts/arial.ttf"))
    {
        std::cerr << "Nem sikerült betölteni az idö betűtípust!" << std::endl;
    }
    if (!goldFont.loadFromFile("fonts/arial.ttf"))
    {
        std::cerr << "Nem sikerült betölteni a pénz betűtípust!" << std::endl;
    }
    if (!hpFont.loadFromFile("fonts/arial.ttf"))
    {
        std::cerr << "Nem sikerült betölteni az élet betűtípust!" << std::endl;
    }

    if (!GameOverFont.loadFromFile("fonts/arial.ttf"))
    {
        std::cerr << "Nem sikerült betölteni az idö betűtípust!" << std::endl;
    }
    if (!FinalFont.loadFromFile("fonts/arial.ttf"))
    {
        std::cerr << "Nem sikerült betölteni az idö betűtípust!" << std::endl;
    }

    // Betöltjük a texturákat

    blue_texture.loadFromFile("balloons/blue_balloon.png");
    red_texture.loadFromFile("balloons/red_balloon.png");
    green_texture.loadFromFile("balloons/green_balloon.png");
    yellow_texture.loadFromFile("balloons/yellow_balloon.png");
    purple_texture.loadFromFile("balloons/purple_balloon.png");

    // Létrehozunk egy új sprite-ot és beállítjuk neki a textúrát

    blue_sprite.setTexture(blue_texture);
    red_sprite.setTexture(red_texture);
    green_sprite.setTexture(green_texture);
    yellow_sprite.setTexture(yellow_texture);
    purple_sprite.setTexture(purple_texture);

    // load the tower textures

    blue_texture_tower.loadFromFile("towers/blue_basic.png");
    red_texture_tower.loadFromFile("towers/red_basic.png");
    purple_texture_tower.loadFromFile("towers/purple_basic.png");

    // Létrehozunk egy új sprite-ot és beállítjuk neki a textúrát

    blue_sprite_tower.setTexture(blue_texture_tower);
    red_sprite_tower.setTexture(red_texture_tower);
    purple_sprite_tower.setTexture(purple_texture_tower);

}

void Game::spamBalloons(float delay)
{
    static std::vector<std::vector<BalloonType>> waveBalloonTypes = {
        {BalloonType::RED},
        {BalloonType::RED, BalloonType::RED, BalloonType::RED, BalloonType::BLUE, BalloonType::BLUE, BalloonType::RED},
        {BalloonType::RED, BalloonType::BLUE, BalloonType::BLUE, BalloonType::BLUE, BalloonType::RED},
        {BalloonType::BLUE, BalloonType::BLUE, BalloonType::BLUE, BalloonType::BLUE, BalloonType::BLUE, BalloonType::GREEN},
        {BalloonType::BLUE, BalloonType::BLUE, BalloonType::BLUE, BalloonType::GREEN, BalloonType::GREEN, BalloonType::BLUE},
        {BalloonType::BLUE, BalloonType::GREEN, BalloonType::GREEN, BalloonType::GREEN, BalloonType::BLUE},
        {BalloonType::GREEN, BalloonType::GREEN, BalloonType::GREEN, BalloonType::GREEN, BalloonType::GREEN, BalloonType::YELLOW},
        {BalloonType::GREEN, BalloonType::GREEN, BalloonType::GREEN, BalloonType::YELLOW, BalloonType::YELLOW, BalloonType::GREEN},
        {BalloonType::GREEN, BalloonType::YELLOW, BalloonType::YELLOW, BalloonType::YELLOW, BalloonType::GREEN},
        {BalloonType::RED, BalloonType::BLUE, BalloonType::GREEN, BalloonType::YELLOW, BalloonType::PURPLE}};

    //static sf::Clock waveTimer;
    static int currentWaveIndex = 0;
    static int currentBalloonIndex = 0;

    if (currentWaveIndex >= waveBalloonTypes.size())
    {

        if (currentWaveIndex == waveBalloonTypes.size() && balloons.empty())
        {

            YouWinText.setFont(GameOverFont);
            YouWinText.setCharacterSize(100);
            YouWinText.setFillColor(sf::Color::Red);
            YouWinText.setPosition(300.f, 400.f);
            YouWinText.setString("YOU WIN!");
            setPauseDisabled(true); // ha meghaltál nincs unpause
            setisPausedToTrue();

            currentWaveIndex++;
        }
        return;
    }

    const std::vector<BalloonType> &balloonTypes = waveBalloonTypes[currentWaveIndex];

    if (waveTimer.getElapsedTime().asSeconds() >= delay)
    {
        if (currentBalloonIndex < balloonTypes.size())
        {
            balloons.push_back(std::make_unique<Balloon>(balloonTypes[currentBalloonIndex], *this));
            currentBalloonIndex++;
            waveTimer.restart();
        }
        else
        {
            currentWaveIndex++;
            currentBalloonIndex = 0;
            waveTimer.restart();
        }
        if (currentWaveIndex == 9)
        {

            FinalText.setFont(FinalFont);
            FinalText.setCharacterSize(65);
            FinalText.setFillColor(sf::Color::Black);
            FinalText.setPosition(350.f, 15.f);
            FinalText.setString("FINAL WAVE!");
        }
    }
}

sf::Texture &Game::getTexture(BalloonType type)
{
    switch (type)
    {
    case BalloonType::BLUE:
        return blue_texture;
    case BalloonType::RED:
        return red_texture;
    case BalloonType::GREEN:
        return green_texture;
    case BalloonType::YELLOW:
        return yellow_texture;
    case BalloonType::PURPLE:
        return purple_texture;
    default:
        throw std::invalid_argument("Invalid balloon type");
    }
}

sf::Texture &Game::getTextureTower(TowerType type)
{
    switch (type)
    {
    case TowerType::BLUE:
        return blue_texture_tower;
    case TowerType::RED:
        return red_texture_tower;
    case TowerType::PURPLE:
        return purple_texture_tower;
    // Add more cases for other balloon types as needed
    default:
        throw std::invalid_argument("Invalid balloon type");
    }
}
int Game::getGold() const
{
    return gold;
}

void Game::BuildRed()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

    bool canBuild = true;
    float minDistance = 75.0f;

    for (const auto &tower : towers)
    {
        float distance = std::sqrt(std::pow(tower->getPosition().x - mousePos.x, 2) +
                                   std::pow(tower->getPosition().y - mousePos.y, 2));
        if (distance < minDistance)
        {
            canBuild = false;
            break;
        }
    }
    



    for (int y = 0; y < m_tileMap.MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < m_tileMap.MAP_WIDTH; ++x)
        {
            const auto &tile = m_tileMap.m_tiles[y][x];
            if (tile->getType() != Tile::Grass && tile->getSprite().getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                canBuild = false;
            }
        }
    }
    if (canBuild && Tower(TowerType::RED, *this, 0, 0).getCost() <= getGold())
    {
        towers.push_back(std::make_unique<Tower>(TowerType::RED, *this, mousePos.x, mousePos.y));
        gold -= Tower(TowerType::RED, *this, 0, 0).getCost();
    }
}

void Game::BuildBlue()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

    bool canBuild = true;
    float minDistance = 75.0f;

    for (const auto &tower : towers)
    {
        float distance = std::sqrt(std::pow(tower->getPosition().x - mousePos.x, 2) +
                                   std::pow(tower->getPosition().y - mousePos.y, 2));
        if (distance < minDistance)
        {
            canBuild = false;
            break;
        }
    }

    for (int y = 0; y < m_tileMap.MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < m_tileMap.MAP_WIDTH; ++x)
        {
            const auto &tile = m_tileMap.m_tiles[y][x];
            if (tile->getType() != Tile::Grass && tile->getSprite().getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                canBuild = false;
            }
        }
    }

    if (canBuild && Tower(TowerType::BLUE, *this, 0, 0).getCost() <= getGold())
    {
        towers.push_back(std::make_unique<Tower>(TowerType::BLUE, *this, mousePos.x, mousePos.y));
        gold -= Tower(TowerType::BLUE, *this, 0, 0).getCost();
    }
}
void Game::BuildPurple()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

    bool canBuild = true;
    float minDistance = 75.0f;

    for (const auto &tower : towers)
    {
        float distance = std::sqrt(std::pow(tower->getPosition().x - mousePos.x, 2) +
                                   std::pow(tower->getPosition().y - mousePos.y, 2));
        if (distance < minDistance)
        {
            canBuild = false;
            break;
        }
    }

    for (int y = 0; y < m_tileMap.MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < m_tileMap.MAP_WIDTH; ++x)
        {
            const auto &tile = m_tileMap.m_tiles[y][x];
            if (tile->getType() != Tile::Grass && tile->getSprite().getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                canBuild = false;
            }
        }
    }

    if (canBuild && Tower(TowerType::PURPLE, *this, 0, 0).getCost() <= getGold())
    {
        towers.push_back(std::make_unique<Tower>(TowerType::PURPLE, *this, mousePos.x, mousePos.y));
        gold -= Tower(TowerType::PURPLE, *this, 0, 0).getCost();
    }
}

void Game::Sell()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);

    // Keresd meg a megfelelő tornyot
    for (auto it = towers.begin(); it != towers.end(); ++it)
    {
        auto &tower = *it;
        if (tower->getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            gold += tower->getCost() / 2;
            towers.erase(it);
            return;
        }
    }
}

void Game::addGold(int value)
{
    gold += value;
}

void Game::handleEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_window.close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::P && !isPauseDisabled)
            {

                if (isPaused)
                {
                    isPaused = false;
                }
                else
                {

                    isPaused = true;
                }
            }
            break;
        case sf::Event::KeyReleased:
            if (event.key.code == sf::Keyboard::F)
            {
                BuildRed();
            }

            if (event.key.code == sf::Keyboard::G)
            {
                BuildBlue();
            }

            if (event.key.code == sf::Keyboard::H)
            {
                BuildPurple();
            }
            if (event.key.code == sf::Keyboard::S)
            {
                Sell();
            }
        }
    }
}

void Game::update(float dt)
{
    // update colision ballon-tower

    for (auto it = towers.begin(); it != towers.end(); it++)
    {
        (*it)->update(dt);
    }

    // update all balloons

    for (auto it = balloons.begin(); it != balloons.end();)
    {
        if ((*it)->update(dt))
        {
            // balloon reached final destination, remove it from the game
            it = balloons.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Game::render()
{
    m_window.clear();

    // Draw tiles, map
    for (int i = 0; i < MAP_SIZE; ++i)
    {
        for (int j = 0; j < MAP_SIZE; ++j)
        {
            m_window.draw(m_tileMap.getSprite(j, i));
        }
    }

    // Timer
    elapsedTimeText.setFont(timeFont);
    elapsedTimeText.setCharacterSize(35);
    elapsedTimeText.setFillColor(sf::Color::Black);
    elapsedTimeText.setPosition(825.f, 0.f);

    // Set elapsed time string in 00:00 format
    elapsed = myTimer;
    int seconds = static_cast<int>(std::round(elapsed.asSeconds()));
    int minutes = seconds / 60;
    seconds %= 60;
    std::ostringstream timeString;
    timeString << std::setfill('0') << std::setw(2) << minutes << ":"
               << std::setfill('0') << std::setw(2) << seconds;
    elapsedTimeText.setString(timeString.str());

    // Draw elapsed time text
    m_window.draw(elapsedTimeText);

    // gold set up
    goldText.setFont(goldFont);
    goldText.setCharacterSize(30);
    goldText.setFillColor(sf::Color::Black);
    goldText.setPosition(730.f, 110.f);

    std::string goldStr = std::to_string(gold);
    std::string currentGold = "Current Gold: " + goldStr;
    goldText.setString(currentGold);

    // Draw the gold
    m_window.draw(goldText);

    // Update the gold if 10 seconds elapsed + 10 gold
    deltaTime = goldTime.restart();

    elapsedTime += deltaTime.asSeconds();
    int goldToAdd = static_cast<int>(elapsedTime / 10.f) * 10;
    if (goldToAdd > 0)
    {
        gold += goldToAdd;
        elapsedTime -= 10;
        // Update the text as well
        goldStr = std::to_string(gold);
        currentGold = "Current Gold: " + goldStr;
        goldText.setString(currentGold);
    }

    // Hp text
    hpText.setFont(hpFont);
    hpText.setCharacterSize(30);
    hpText.setFillColor(sf::Color::Black);
    hpText.setPosition(728.f, 210.f);

    std::string lifeStr = std::to_string(startinghp);
    std::string currentHp = "Current HP: " + lifeStr;
    hpText.setString(currentHp);
    // draw the hp
    m_window.draw(hpText);

    for (auto &balloon : balloons)
    {
        m_window.draw(*balloon);
    }

    if (startinghp == 0)
    {
        GameOverText.setFont(GameOverFont);
        GameOverText.setCharacterSize(100);
        GameOverText.setFillColor(sf::Color::Red);
        GameOverText.setPosition(300.f, 400.f);
        std::string over = "GAME OVER!";
        GameOverText.setString(over);

        m_window.draw(GameOverText);
    }
    for (auto &tower : towers)
    {
        m_window.draw(*tower);
    }
    m_window.draw(FinalText);
    m_window.draw(YouWinText);
    m_window.display();
}

void Game::run()
{
    sf::Clock clock;
    sf::Time elapsed;

    // Time tracking
    myTimer = sf::Time::Zero;
    sf::Clock loopClock;

    while (m_window.isOpen())
    {
        sf::Time deltaTime = loopClock.restart();
        if (!isPaused)
        {
            myTimer += deltaTime; //->timer + deltatime until no pause
            spamBalloons(delayBetweenBalloons);
            elapsed = clock.restart(); // now the moving is same in all fps
            update(elapsed.asSeconds());
            render();
        }
        else
        {
            waveTimer.restart();
            clock.restart(); // movement stop when pause
            goldTime.restart();
        }
        handleEvents();
    }
}
