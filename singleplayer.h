#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<cstdio>
#include<string>
#include<sstream>
#include<deque>
#include<cstdlib>
#include<ctime>
using namespace std;
using namespace sf;

class gamemenu
{
private:
	RectangleShape play_button, exit_button;
	Text play, exit;
	Font font;
public:
	gamemenu();
	bool hover(float, float);
	bool to_play(float, float);
	bool to_exit(float, float);
	void draw(RenderWindow& window);
};