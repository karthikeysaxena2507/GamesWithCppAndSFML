#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class connect4game
{
private:
    int turn;
    float val;
    Font font;
    Text text, restart;
    SoundBuffer buffer;
    Sound sound;
    vector<int> point;
    RectangleShape board;
    CircleShape piece,circle;
public:
    connect4game();
    void set_font();
    void set_text();
    void set_sound();
    void play_sound();
    void set_piece(float,float,RenderWindow& window);
    void construct_board(RenderWindow& window);
    int get_position(RenderWindow& window, int);
    void update_board(RenderWindow& window, int);
    void drawing_pieces(RenderWindow& window);
    int check_for_win(RenderWindow& window);
    void move_piece(RenderWindow& window, int, int);
    void display(RenderWindow& window,int);
    void reset(RenderWindow& window);
};