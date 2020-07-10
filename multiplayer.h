#pragma once
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
using namespace std;
using namespace sf;

class multiplayer
{
private:
	RectangleShape connect4_button, tictactoe_button;
	Text connect4, tictactoe;
	Font font;
public:
	multiplayer();
	void hover(float, float);
	bool play_connect4(float, float);
	bool play_tictactoe(float, float);
	void draw(RenderWindow& window);
};