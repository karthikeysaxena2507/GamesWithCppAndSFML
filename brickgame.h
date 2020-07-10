#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<cstdlib>
#include<cstdio>
#include<set>
using namespace std;
using namespace sf;

class brickgame
{
private:
	SoundBuffer buffer1, buffer2, buffer3;
	Sound sound1, sound2, sound3;
	Text data, close, gameover, restart, paused;
	Font font;

	int score;
	int lives;
	float time;
	int high_score;

	float window_width, window_height;
	float board_width, board_height;
	float brick_width, brick_height;
	float ball_radius;

	// MAKING AN OBJECT OF BOARD CLASS
	Vector2f boardposition;
	RectangleShape BOARD;
	float boardspeed;

	// EACH BRICK OBJECT
	RectangleShape brick;

	// MAKING AN OBJECT OF BALL CLASS
	Vector2f ballposition;
	CircleShape BALL;
	float ballspeed_x;
	float ballspeed_y;

	float tempx, tempy;

	// MAKING A SET TO STORE POSITIONS OF DESTROYED BRICKS
	set< pair<int, int> > st;


	// TO KNOW IF THE GAME IS PAUSED
	bool ispaused;
	
public:
	brickgame();
	void set_font();
	void set_text();
	void set_sound();
	void reset();
	void pause();
	void display(RenderWindow& window);
	void move_board();
	void handle_collison();
	void drawing_scene(RenderWindow& window);
};