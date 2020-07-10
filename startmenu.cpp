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

startmenu::startmenu()
{
	font.loadFromFile("DS-DIGIT.TTF");

	mes1.setFont(font);
	mes2.setFont(font);

	mes1.setCharacterSize(30);
	mes2.setCharacterSize(30);

	mes1.setFillColor(Color::Cyan);
	mes2.setFillColor(Color::Yellow);

	mes1.setPosition(380, 50);
	mes2.setPosition(405, 200);

	mes1.setString("WELCOME TO GAME WORLD !");
	mes2.setString("SELECT PLAYER TYPE");

	single.setFont(font);
	multi.setFont(font);

	single.setCharacterSize(30);
	multi.setCharacterSize(30);

	single.setFillColor(Color::Yellow);
	multi.setFillColor(Color::Yellow);

	single.setPosition(460, 280);
	multi.setPosition(460, 360);

	single.setString("ONE PLAYER");
	multi.setString("TWO PLAYER");

	single_button.setSize(Vector2f(250, 50));
	multi_button.setSize(Vector2f(250, 50));

	single_button.setFillColor(Color(0, 0, 128));
	multi_button.setFillColor(Color(0, 0, 128));

	single_button.setPosition(410, 275);
	multi_button.setPosition(410, 355);
}

bool startmenu::play_single(float Mx, float My)
{
	if (single_button.getGlobalBounds().contains(Mx, My))
	{
		return true;
	}
	return false;
}

bool startmenu::play_multi(float Mx, float My)
{
	if (multi_button.getGlobalBounds().contains(Mx, My))
	{
		return true;
	}
	return false;
}


void startmenu::hover(float Mx, float My)
{
	if (single_button.getGlobalBounds().contains(Mx, My))
	{
		single.setFillColor(Color::Red);
	}
	else
	{
		single.setFillColor(Color::Yellow);
	}
	if (multi_button.getGlobalBounds().contains(Mx, My))
	{
		multi.setFillColor(Color::Red);
	}
	else
	{
		multi.setFillColor(Color::Yellow);
	}
}


void startmenu::draw(RenderWindow& window)
{
	window.draw(mes1);
	window.draw(mes2);
	window.draw(single_button);
	window.draw(multi_button);
	window.draw(single);
	window.draw(multi);
	window.display();
	window.clear();
}
