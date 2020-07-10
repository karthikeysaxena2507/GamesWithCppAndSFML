#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<cstdlib>
#include<cstdio>
#include<set>
#include<sstream>
#include "brickgame.h"
using namespace std;
using namespace sf;

brickgame::brickgame()
{

	score = 0;
	lives = 3;
	time = 0;
	high_score = 0;

	brick.setSize(Vector2f(20, 10));
	brick.setFillColor(Color::Magenta);
	brick.setOutlineThickness(2);
	brick.setOutlineColor(Color(0, 100, 0));

	ispaused = false;

	window_width = 1024, window_height = 768;
	board_width = 100, board_height = 10;
	brick_width = 20, brick_height = 10;
	ball_radius = 5;

	// SETTING UP THE INITIAL POSITION OF BOARD
	
	tempx = 0;
	tempy = 0;
	
	boardposition.x = 400;
	boardposition.y = 753;
	boardspeed = 8.5f;
	// SETTING UP THE DIMENSIONS, COLOR AND THE POSITION OF BOARD
	BOARD.setSize(Vector2f(100, 10));
	BOARD.setFillColor(Color(0, 255, 0));
	BOARD.setPosition(boardposition);
	BOARD.setOutlineThickness(3);
	BOARD.setOutlineColor(Color::Red);

	// SETTING UP THE INITIAL POSITION OF THE BALL
	ballposition.x = 100;
	ballposition.y = 400;
	ballspeed_x = 0.2f;
	ballspeed_y = 6.5f;
	// SETTING UP THE RADIUS, COLOR AND POSITION OF BALL
	BALL.setRadius(5);
	BALL.setFillColor(Color::Yellow);
	BALL.setPosition(ballposition);
}

void brickgame::set_font()
{
	font.loadFromFile("DS-DIGIT.ttf");
	data.setFont(font);
	close.setFont(font);
	restart.setFont(font);
	paused.setFont(font);
	gameover.setFont(font);
}

void brickgame::set_text()
{
	data.setCharacterSize(25);
	data.setPosition(300, 1);
	data.setFillColor(Color::Yellow);

	close.setCharacterSize(20);
	close.setPosition(360, 400);
	close.setFillColor(Color::Yellow);

	restart.setCharacterSize(20);
	restart.setPosition(380, 440);
	restart.setFillColor(Color::Yellow);

	gameover.setCharacterSize(50);
	gameover.setPosition(400, 325);
	gameover.setFillColor(Color::Green);

	paused.setCharacterSize(25);
	paused.setPosition(360, 300);
	paused.setFillColor(Color::Yellow);

}

void brickgame::set_sound()
{
	buffer1.loadFromFile("boing_spring.wav");
	buffer2.loadFromFile("baseball_hit.wav");
	buffer3.loadFromFile("honk_x.wav");
	sound1.setBuffer(buffer1);
	sound2.setBuffer(buffer2);
	sound3.setBuffer(buffer3);
}

void brickgame::reset()
{
	lives = 3;
	st.clear();
}

void brickgame::pause()
{
	if (Keyboard::isKeyPressed(Keyboard::P))
	{
		if (ispaused)
		{
			ballspeed_x = tempx;
			ballspeed_y = tempy;
			ispaused = false;
		}
		else if (!ispaused)
		{
			tempx = ballspeed_x;
			tempy = ballspeed_y;
			ballspeed_x = 0;
			ballspeed_y = 0;
			ispaused = true;
		}
	}
}

void brickgame::move_board()
{
	if (Keyboard::isKeyPressed(Keyboard::Left) && (BOARD.getPosition().x>=0))
	{
		boardposition.x -= boardspeed;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right) && (BOARD.getPosition().x + board_width) <= window_width)
	{
		boardposition.x += boardspeed;
	}
}

void brickgame::display(RenderWindow& window)
{
	std::stringstream sd, sp, sc;
	if (score > high_score) high_score = score;
	sp << "PRESS P TO PAUSE THE GAME";
	sc << "PRESS SPACEBAR TO CLOSE THE GAME";
	sd << "Score:" << score << "    Lives:" << lives << "   time:" << (time / 1000) << "   high score:" << high_score;
	data.setString(sd.str());
	paused.setString(sp.str());
	close.setString(sc.str());
	restart.setString("PRESS R TO RESTART THE GAME");
	window.draw(data);
	window.draw(restart);
	window.draw(paused);
	window.draw(close);


	if (lives <= 0 || st.size() >= 348)
	{
		lives = 0;
		score = 0;
		time = 0;
		sound3.play();
		std::stringstream sg, sc;
		sg << "GAMEOVER";
		sc << "PRESS SPACEBAR TO CLOSE THE GAME";
		close.setString(sc.str());
		gameover.setString(sg.str());
		window.draw(gameover);
		window.draw(close);
	}

	if (lives > 0 && !ispaused)
	{
		// UPDATING THE POSITIONS OF BALL AND BOARD
		time++;
		ballposition.x += ballspeed_x;
		ballposition.y += ballspeed_y;
		BALL.setPosition(ballposition);
		BOARD.setPosition(boardposition);
	}

	//DRAWING THE BALL AND  BOARD AFTER SETTING THEIR POSITIONS
	window.draw(BALL);
	window.draw(BOARD);

	// DISPLAYING OUR FRAMEWORK
	window.display();

	// CLEARING OUR WINDOW FOR NEXT RUN
	window.clear(Color(0, 0, 128));

}


void brickgame::handle_collison()
{
	// HANDLING SIDEWAYS COLLISION OF BALL WITH WALLS
	if ((BALL.getPosition().x + ball_radius) >= window_width || BALL.getPosition().x <= 0)
	{
		ballspeed_x = (-1) * ballspeed_x;
	}
	// HANDLING COLLISION OF BALL WITH TOP SURFACE
	if ((BALL.getPosition().y + ball_radius) <= 0)
	{
		ballspeed_y = (-1) * ballspeed_y;
	}
	// HANDLING COLLISION OF BALL WITH BOTTOM SURFACE
	if ((BALL.getPosition().y + ball_radius) >= window_height)
	{
		sound3.play();
		ballspeed_y = (-1) * ballspeed_y;
		lives--;
	}
	// HANDLING THE BALL COLLISION WITH BOARD
	if (BALL.getPosition().x >= BOARD.getPosition().x && BALL.getPosition().x <= (BOARD.getPosition().x + board_width) && BALL.getPosition().y >= (window_height - (2 * board_height) - 5))
	{
		sound2.play();
		ballspeed_y = (-1) * ballspeed_y;
		if (BALL.getPosition().x >= BOARD.getPosition().x && BALL.getPosition().x < (BOARD.getPosition().x + (board_width / 2)) && ballspeed_x > 0)
		{
			if (ballspeed_x < 0) ballspeed_x = -1.5f;
			else ballspeed_x = 1.5f;
			// DEFINING THE DEGREE OF ROTATION OF BALL BY ADJUSTING ITS SPEED
			float c = 1, a = BOARD.getPosition().x;
			while (a < BALL.getPosition().x && c <= 3.0f)
			{
				a += 5.0f;
				c += 0.5f;
			}
			ballspeed_x = (c * ballspeed_x);
			if (ballspeed_x > 0) ballspeed_x = (-1) * ballspeed_x;
		}
		else if (BALL.getPosition().x > (BOARD.getPosition().x + (board_width / 2)) && BALL.getPosition().x <= (BOARD.getPosition().x + board_width) && ballspeed_x < 0)
		{
			if (ballspeed_x < 0) ballspeed_x = -1.5f;
			else ballspeed_x = 1.5f;
			// DEFINING THE DEGREE OF ROTATION OF BALL BY ADJSUTING THE SPEED
			float c = 1, a = BOARD.getPosition().x + (board_width / 2);
			while (a < BALL.getPosition().x && c <= 3.0f)
			{
				a += 5.0f;
				c += 0.5f;
			}
			ballspeed_x = (c * ballspeed_x);
			if (ballspeed_x < 0) ballspeed_x = (-1) * ballspeed_x;
		}
		else if (BALL.getPosition().x == (BOARD.getPosition().x + (board_width / 2)))
		{
			ballspeed_x = 0;
		}
	}
}


void brickgame::drawing_scene(RenderWindow& window)
{
	// DRAWING THE BRICKS ALONGWITH HANDLING COLLISION OF BALL WITH THEM, HERE BRICKS ARE PLACE AT A REGULAR INTERVAL
	float x = brick_width;
	float y = (3 * brick_height);
	while (true)
	{
		brick.setPosition(x, y);
		if (!st.count({ x, y }))
		{
			if (brick.getGlobalBounds().contains(BALL.getPosition().x, BALL.getPosition().y))
			{
				sound1.play();
				st.insert({ x,y });
				score++;
				if (BALL.getPosition().x >= x && BALL.getPosition().x <= (x + brick_width) / 2)
				{
					ballspeed_y = (-1) * ballspeed_y;
					ballspeed_x = (-1) * ballspeed_x;
				}
				else if ((BALL.getPosition().x > (x + brick_width) / 2) && BALL.getPosition().x <= (x + brick_width))
				{
					ballspeed_y = (-1) * ballspeed_y;
				}
			}
			else
			{
				window.draw(brick);
			}
		}
		x += (brick_width / 2) + brick_width;
		if (x >= window_width - brick_width)
		{
			y += brick_height + (brick_height / 2);
			x = brick_width;
		}
		if (y >= (window_height / 3)) break;
	}
}