#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "MainMenu.hpp"

int main()
{

    sf::RenderWindow MENU(sf::VideoMode(980, 980), "Tower Defense Game");

    MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);

    // set background
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(980, 980));
    sf::Texture Maintexture;
    Maintexture.loadFromFile("mainmenupics/background.png");
    background.setTexture(&Maintexture);

    // photo to option
    sf::RectangleShape Obackground;
    Obackground.setSize(sf::Vector2f(980, 980));
    sf::Texture Optiontexture;
    Optiontexture.loadFromFile("mainmenupics/option.png");
    Obackground.setTexture(&Optiontexture);

    while (MENU.isOpen())
    {
        sf::Event event;

        while (MENU.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                MENU.close();
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    mainMenu.MoveUp();
                    break;
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    mainMenu.MoveDown();
                    break;
                }
                if (event.key.code == sf::Keyboard::Return)
                {
                    sf::RenderWindow Play(sf::VideoMode(980, 980), "game_name");
                    sf::RenderWindow OPTIONS(sf::VideoMode(980, 980), "OPTIONS");

                    int x = mainMenu.MainMenuPressed();
                    if (x == 0)
                    {
                        while (Play.isOpen())
                        {
                            sf::Event aevent;
                            while (Play.pollEvent(aevent))
                            {
                                if (aevent.type == sf::Event::Closed)
                                {
                                    Play.close();
                                }
                                if (aevent.type == sf::Event::KeyPressed)
                                {
                                    if (aevent.key.code == sf::Keyboard::Escape)
                                    {
                                        Play.close();
                                    }
                                }
                            }

                            OPTIONS.close();
                            Play.close();
                            MENU.close();

                            Game game;
                            game.run();

                            return 0;
                        }
                    }
                    if (x == 1)
                    {
                        while (OPTIONS.isOpen())
                        {
                            sf::Event aevent;
                            while (OPTIONS.pollEvent(aevent))
                            {
                                if (aevent.type == sf::Event::Closed)
                                {
                                    OPTIONS.close();
                                }
                                if (aevent.type == sf::Event::KeyPressed)
                                {
                                    if (aevent.key.code == sf::Keyboard::Escape)
                                    {
                                        OPTIONS.close();
                                    }
                                }
                            }
                            Play.close();
                            OPTIONS.clear();
                            OPTIONS.draw(Obackground);

                            OPTIONS.display();
                        }
                    }

                    if (x == 2)
                        MENU.close();
                    break;
                }
            }
        }
        MENU.clear();
        MENU.draw(background);
        mainMenu.draw(MENU);
        MENU.display();
    }
}
