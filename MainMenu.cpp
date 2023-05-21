#include "MainMenu.hpp"
#include <iostream>

MainMenu::MainMenu(float width, float height)
{
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        std::cout << "Nincs ilyen font" << std::endl;
    }
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(sf::Color::Red);
    mainMenu[0].setString("Play");
    mainMenu[0].setCharacterSize(100);
    mainMenu[0].setPosition(400, 200);

    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(sf::Color::Yellow);
    mainMenu[1].setString("Options");
    mainMenu[1].setCharacterSize(100);
    mainMenu[1].setPosition(400, 300);

    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(sf::Color::Yellow);
    mainMenu[2].setString("Quit");
    mainMenu[2].setCharacterSize(100);
    mainMenu[2].setPosition(400, 400);

    MainMenuSelected = 0;
}
MainMenu::~MainMenu()
{
}

void MainMenu::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < MAX_main_menu; i++)
    {
        window.draw(mainMenu[i]);
    }
}

void MainMenu::MoveUp()
{
    if (MainMenuSelected - 1 >= 0)
    {
        mainMenu[MainMenuSelected].setFillColor(sf::Color::Yellow);

        MainMenuSelected--;
        mainMenu[MainMenuSelected].setFillColor(sf::Color::Red);
    }
    else /// az első menüpont van kiválasztva
    {
        mainMenu[MainMenuSelected].setFillColor(sf::Color::Yellow);
        MainMenuSelected = 2;
        mainMenu[MainMenuSelected].setFillColor(sf::Color::Red);
    }
}

void MainMenu::MoveDown()
{
    if (MainMenuSelected + 1 < MAX_main_menu)
    {
        mainMenu[MainMenuSelected].setFillColor(sf::Color::Yellow);

        MainMenuSelected++;
        mainMenu[MainMenuSelected].setFillColor(sf::Color::Red);
    }
    else // utolsó menüpont van kiválasztva
    {
        mainMenu[MainMenuSelected].setFillColor(sf::Color::Yellow);

        MainMenuSelected = 0; // visszaugrunk az első menüpontra
        mainMenu[MainMenuSelected].setFillColor(sf::Color::Red);
    }
}
