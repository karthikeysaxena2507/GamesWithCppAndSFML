#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<cstdio>
#include<string>
#include<sstream>
#include<string.h>
#include<deque>
#include<cstdlib>
#include<ctime>
#include"snakegame.h"
#include"snack.h"
#include"singleplayer.h"
#include"multiplayer.h"
#include"snake.h"
#include"startmenu.h"
using namespace std;
using namespace sf;


snakegame::snakegame()
{
    lives = 5;
    score = 0;
    high_score = 0;
    move_in_x = 0;
    move_in_y = 0;
    game_over = false;
    pause = false;
}


void snakegame::set_text()
{

    gameover.setFillColor(Color::Yellow);
    points.setFillColor(Color::Yellow);
    restart.setFillColor(Color::Yellow);

    gameover.setPosition(420, 300);
    points.setPosition(300, 0);
    restart.setPosition(320, 40);

    gameover.setCharacterSize(30);
    restart.setCharacterSize(30);
    points.setCharacterSize(30);

    gameover.setString("GAME-OVER");
    restart.setString("PRESS R TO RESTART THE GAME");

}


void snakegame::set_font()
{
    font.loadFromFile("DS-DIGIT.TTF");
    gameover.setFont(font);
    points.setFont(font);
    restart.setFont(font);
}

void snakegame::set_sound()
{
    buffer.loadFromFile("baseball_hit.wav");
    sound.setBuffer(buffer);
}

void snakegame::reset()
{
    score = 0;
    lives = 5;
    move_in_x = 0;
    move_in_y = 0;
    game_over = false;
    SNAKE.reset();
}



void snakegame::set_game_frame(RenderWindow& window)
{
    stringstream ss;
    ss <<"LIVES: " << lives << "  SCORE: " << score << "  " << " HIGH SCORE: " << high_score;
    points.setString(ss.str());
    window.draw(points);
    window.draw(restart);
    window.draw(SNACK.get_snack());
    window.display();
    window.clear(Color(0,0,128));
}

void snakegame::set_snake_direction()
{
    if (Keyboard::isKeyPressed(Keyboard::Up))
    {
        move_in_y = (-1);
        move_in_x = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down))
    {
        move_in_y = 1;
        move_in_x = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        move_in_y = 0;
        move_in_x = 1;
    }
    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        move_in_y = 0;
        move_in_x = (-1);
    }
}

void snakegame::set_snake_movement(RenderWindow& window)
{
    if(!game_over && !pause) SNAKE.update_motion(move_in_x, move_in_y);
    if (game_over) window.draw(gameover);
    if (Keyboard::isKeyPressed(Keyboard::P))
    {
        if (pause) pause = false;
        else if (!pause) pause = true;
    }
    if (SNAKE.collision_with_wall(window))  
    {
        game_over = true;
    }
    if (SNAKE.collision_with_itself())
    {
        if (!game_over) lives--;
        if (lives == 0) game_over = true;
    }
    RectangleShape food = SNACK.get_snack();
    RectangleShape head = SNAKE.get_head();
    if (head.getGlobalBounds().contains(food.getPosition().x,food.getPosition().y))
    {
        SNAKE.update(window,move_in_x,move_in_y);
        SNACK.update(window);
        score++;
        high_score = max(high_score, score);
        sound.play();
    }
    SNAKE.draw_body(window);
}