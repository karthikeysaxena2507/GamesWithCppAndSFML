#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
using namespace sf;
using namespace std;
class tictactoegame
{
private:
	int turn; // TO STORE NUMBER OF MOVES SO FAR

	RectangleShape line_left, line_right; // LEFT AND RIGHT ALIGNED LINES USED TO DRAW A CROSS

	RectangleShape grid; // OUR INITIAL GRID WHICH WILL BE A RECTANGLE UPON WHICH WE WILL DRAW SQUARES TO MAKE IT LOOK LIKE A GRID

	CircleShape circle;  // FOR MAKING A ZERO

	Font font;

	Sound sound;
	SoundBuffer buffer;

	Text win1, win2, gameover, draw, restart, message;

	vector<RectangleShape> boxes; // THE SQUARE SHAPES TO BE DRAWN ON GRID

	vector<float> zero, cross; // USED TO STORE WHICH BOXES ARE AND ZERO AND WHICH ARE CROSS

public:
	tictactoegame(); // A CONSTRUCTOR OF GAME CLASS

	void set_text();

	void play_sound();

	void set_sound();

	void set_font();

	void construct_grid(RenderWindow& window); // DRAWS THE GRID

	void fill_your_choice(RenderWindow& window); // FUNCTION TO FILL CHOICES IN GRID (ZERO OR CROSS)

	void drawing_choices(RenderWindow& window); // FUNCTION TO DRAW DESIRED CHOICE ON GRID

	int check_for_win(RenderWindow& window); // CHECKING THE CONDITION FOR WINNING

	void display(RenderWindow& window,int); // DISPLAYING THE SFML WINDOW

	void reset(RenderWindow& window); // TO RESTART THE GAME

};