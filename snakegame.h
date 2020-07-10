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
#include "snake.h"
#include "snack.h"
using namespace std;
using namespace sf;
class snakegame
{
private:
	Text gameover, points, restart;
	Font font;
	SoundBuffer buffer;
	Sound sound;
	snack SNACK;
	snake SNAKE;
	float score,high_score,lives;
	float move_in_x;
	float move_in_y;
	bool game_over;
	bool pause;
public:
	snakegame();
	void set_font();
	void set_text();
	void set_sound();
	void reset();
	void set_snake_direction();
	void set_snake_movement(RenderWindow& window);
	void set_game_frame(RenderWindow& window);
};