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

class snack
{
private:
	RectangleShape food;

public:
	snack();
	void update(RenderWindow& window);
	RectangleShape get_snack();
};