#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <SFML/Graphics.hpp>
#define MAX_main_menu 3

class MainMenu
{
public:
    MainMenu(float width, float height);
    ~MainMenu();

    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();

    int MainMenuPressed() { return MainMenuSelected; }

private:
    int MainMenuSelected;
    sf::Font font;
    sf::Text mainMenu[MAX_main_menu];
};

#endif