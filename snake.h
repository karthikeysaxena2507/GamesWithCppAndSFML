#pragma once
#include<iostream>
#include<deque>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<cstdio>
#include<set>
#include<string>
#include<sstream>
#include<string.h>
#include<cstdlib>
#include<ctime>
using namespace sf;
using namespace std;

class snake
{
private:
	vector<RectangleShape> parts;
	int body_length;
	float length = 15;
public:
	snake();
	bool collision_with_wall(RenderWindow& window);
	bool collision_with_itself();
	void update(RenderWindow& window,float,float);
	void update_motion(float,float);
	void reset();
	RectangleShape get_head();
	void draw_body(RenderWindow& window);
};