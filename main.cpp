#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<cstdio>
#include<string>
#include<deque>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include"game.h"
#include"snake.h"
#include"snack.h"
#include"menu.h"
using namespace std;
using namespace sf;
int main()
{
    RenderWindow window(sf::VideoMode(1024, 768), "SNAKE GAME !!!");

    game GAME;
    GAME.set_font();
    GAME.set_text();
    GAME.set_sound();

    menu MENU;


    Cursor cursor;

    bool start = false;

    window.setFramerateLimit(25);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            GAME.set_snake_direction();
            if (Keyboard::isKeyPressed(Keyboard::R))
            {
                GAME.reset();
            }
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button==Mouse::Left)
            {
                if (!start)
                {
                    float Mx = Mouse::getPosition(window).x;
                    float My = Mouse::getPosition(window).y;
                    if (MENU.to_exit(Mx, My))
                    {
                        window.close();
                    }
                    else if (MENU.to_play(Mx, My))
                    {
                        start = true;
                    }
                }
                if (cursor.loadFromSystem(Cursor::Hand))
                {
                    window.setMouseCursor(cursor);
                }
            }
            float Mx = Mouse::getPosition(window).x;
            float My = Mouse::getPosition(window).y;
            if (MENU.hover(Mx, My))
            {
                if (cursor.loadFromSystem(Cursor::Hand))
                {
                    window.setMouseCursor(cursor);
                }
            }
        }
        if (cursor.loadFromSystem(Cursor::Arrow))
        {
            window.setMouseCursor(cursor);
        }
        if (!start) MENU.draw(window);
        if (start)
        {
            GAME.set_snake_movement(window);
            GAME.set_game_frame(window);
        }
    }
  	return 0;
}