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

multiplayer::multiplayer()
{
	font.loadFromFile("DS-DIGIT.TTF");

	connect4.setFont(font);
	tictactoe.setFont(font);

	connect4.setCharacterSize(30);
	tictactoe.setCharacterSize(30);

	connect4.setFillColor(Color::Yellow);
	tictactoe.setFillColor(Color::Yellow);

	connect4.setPosition(435, 280);
	tictactoe.setPosition(425, 360);

	connect4.setString("PLAY CONNECT-4");
	tictactoe.setString("PLAY TIC-TAC-TOE");

	connect4_button.setSize(Vector2f(250, 50));
	tictactoe_button.setSize(Vector2f(250, 50));

	connect4_button.setFillColor(Color(0, 0, 128));
	tictactoe_button.setFillColor(Color(0, 0, 128));

	connect4_button.setPosition(410, 275);
	tictactoe_button.setPosition(410, 355);


}

bool multiplayer::play_connect4(float Mx, float My)
{
	if (connect4_button.getGlobalBounds().contains(Mx, My))
	{
		return true;
	}
	return false;
}

bool multiplayer::play_tictactoe(float Mx, float My)
{
	if (tictactoe_button.getGlobalBounds().contains(Mx, My))
	{
		return true;
	}
	return false;
}

void multiplayer::hover(float Mx, float My)
{
	if (connect4_button.getGlobalBounds().contains(Mx, My))
	{
		connect4.setFillColor(Color::Red);
	}
	else
	{
		connect4.setFillColor(Color::Yellow);
	}
	if (tictactoe_button.getGlobalBounds().contains(Mx, My))
	{
		tictactoe.setFillColor(Color::Red);
	}
	else
	{
		tictactoe.setFillColor(Color::Yellow);
	}
}

void multiplayer::draw(RenderWindow& window)
{
	window.draw(connect4_button);
	window.draw(tictactoe_button);
	window.draw(connect4);
	window.draw(tictactoe);
	window.display();
	window.clear();
}