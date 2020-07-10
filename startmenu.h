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

class startmenu
{
private:
	RectangleShape single_button, multi_button;
	Text mes1, mes2, single, multi;
	Font font;
public:
	startmenu();
	bool play_single(float,float);
	bool play_multi(float, float);
	void hover(float, float);
	void draw(RenderWindow& window);
};