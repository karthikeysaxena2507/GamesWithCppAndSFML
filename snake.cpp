#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<cstdio>
#include<string>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include<deque>
#include"game.h"
#include"snake.h"
#include"snack.h"
using namespace std;
using namespace sf;

snake::snake()
{
    RectangleShape head;
    head.setPosition(600, 400);
    head.setFillColor(Color::Red);
    head.setSize(Vector2f(length, length));
    head.setOutlineThickness(2);
    head.setOutlineColor(Color::Yellow);
    parts.push_back(head);
    body_length = 1;

}

RectangleShape snake::get_head()
{
    return parts[0];
}

void snake::update_motion(float move_in_x,float move_in_y)
{
    int i;
    for (i = parts.size() - 1; i > 0; i--)
    {
        parts[i].setPosition(parts[i - 1].getPosition().x, parts[i - 1].getPosition().y);
    }
    if (move_in_x == -1 && move_in_y == 0) // LEFT
    {
        parts[0].move(-length, 0);
    }
    else if (move_in_x == 1 && move_in_y == 0) //RIGHT
    {
        parts[0].move(length, 0);
    }
    else if (move_in_x == 0 && move_in_y == 1) // DOWN
    {
        parts[0].move(0, length);
    }
    else if (move_in_x == 0 && move_in_y == -1) //UP
    {
        parts[0].move(0, -length);
    }
}

bool snake::collision_with_itself()
{
    RectangleShape head = parts[0];
    float i = 4;
    while (i < parts.size())
    {
        if (head.getGlobalBounds().contains(parts[i].getPosition().x, parts[i].getPosition().y))
        {
            return true;
        }
        i++;
    }
    return false;
}

bool snake::collision_with_wall(RenderWindow& window)
{
    float head_x = parts[0].getPosition().x;
    float head_y = parts[0].getPosition().y;
    float x = window.getSize().x;
    float y = window.getSize().y;
    if ((head_x + 15) >= x || head_x <= 0 || (head_y + 15) >= y || head_y <= 0)
    {
        return true;
    }
    return false;
}

void snake::update(RenderWindow& window,float move_in_x,float move_in_y)
{
    body_length++;
    float new_x = parts[parts.size() - 1].getPosition().x;
    float new_y = parts[parts.size() - 1].getPosition().y;
    RectangleShape part;
    part.setSize(Vector2f(length, length));
    part.setFillColor(Color::Green);
    part.setOutlineThickness(2);
    part.setOutlineColor(Color::Yellow);
    if (move_in_x == -1 && move_in_y == 0) // LEFT
    {
        new_x += length;
    }
    if (move_in_x == 1 && move_in_y == 0) //RIGHT
    {
        new_x -= length;
    }
    if (move_in_x == 0 && move_in_y == 1) // DOWN
    {
        new_y -= length;
    }
    if (move_in_x == 0 && move_in_y == -1) //UP
    {
        new_y += length;
    }
    part.setPosition(new_x, new_y);
    parts.push_back(part);
}

void snake::draw_body(RenderWindow& window)
{
    int i;
    for (i = 0; i < body_length; i++)
    {
        window.draw(parts[i]);
    }
}

void snake::reset()
{
    while (!parts.empty()) parts.pop_back();
    RectangleShape head;
    head.setPosition(600, 400);
    head.setFillColor(Color::Red);
    head.setSize(Vector2f(length, length));
    head.setOutlineThickness(2);
    head.setOutlineColor(Color::Yellow);
    parts.push_back(head);
    body_length = 1;
}