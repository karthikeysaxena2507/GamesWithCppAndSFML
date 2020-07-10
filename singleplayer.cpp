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
#include"game.h"
#include"snack.h"
#include"gamemenu.h"
#include"snake.h"
#include"startmenu.h"
using namespace std;
using namespace sf;

gamemenu::gamemenu()
{
	font.loadFromFile("DS-DIGIT.TTF");

	play.setFont(font);
	exit.setFont(font);

	play.setCharacterSize(30);
	exit.setCharacterSize(30);

	play.setFillColor(Color::Yellow);
	exit.setFillColor(Color::Yellow);

	play.setPosition(450, 280);
	exit.setPosition(450, 360);

	play.setString("PLAY NOW");
	exit.setString("EXIT GAME");

	play_button.setSize(Vector2f(200, 50));
	exit_button.setSize(Vector2f(200, 50));

	play_button.setFillColor(Color(0,0,128));
	exit_button.setFillColor(Color(0,0,128));

	play_button.setPosition(410, 275);
	exit_button.setPosition(410, 355);


}

bool gamemenu::to_play(float Mx, float My)
{
	if (play_button.getGlobalBounds().contains(Mx, My))
	{
		return true;
	}
	return false;
}

bool gamemenu::to_exit(float Mx, float My)
{
	if (exit_button.getGlobalBounds().contains(Mx, My))
	{
		return true;
	}
	return false;
}

bool gamemenu::hover(float Mx, float My)
{
	if (play_button.getGlobalBounds().contains(Mx, My))
	{
		play.setFillColor(Color::Red);
		return true;
	}
	else
	{
		play.setFillColor(Color::Yellow);
		return true;
	}
	if (exit_button.getGlobalBounds().contains(Mx, My))
	{
		exit.setFillColor(Color::Red);
		return true;
	}
	else
	{
		exit.setFillColor(Color::Yellow);
		return true;
	}
	return false;
}

void gamemenu::draw(RenderWindow& window)
{
	window.draw(play_button);
	window.draw(exit_button);
	window.draw(play);
	window.draw(exit);
	window.display();
	window.clear();
}