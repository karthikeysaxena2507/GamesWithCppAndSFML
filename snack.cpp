#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<deque>
#include<cstdio>
#include<string>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include"game.h"
#include"snake.h"
#include"snack.h"
using namespace std;
using namespace sf;

snack::snack()
{
	srand((unsigned)time(0));
	food.setFillColor(Color::Magenta);
	food.setSize(Vector2f(10, 10));
	float food_x = (rand() % 1000) + 1;
	float food_y = (rand() % 700) + 1;
	food.setPosition(Vector2f(food_x,food_y));
}

void snack::update(RenderWindow& window)
{
	while (true)
	{
		float food_x = (rand() % 1000) + 1;
		float food_y = (rand() % 700) + 1;
		if (food_x >= 30 && food_x <= 970 && food_y >= 80 && food_y <= 650)
		{
			food.setPosition(Vector2f(food_x, food_y));
			break;
		}
	}
}

RectangleShape snack::get_snack()
{
	return food;
}