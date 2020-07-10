#include <SFML/Graphics.hpp>
#include<cstdlib>
#include<cstdio>
#include<SFML/Audio.hpp>
#include"connect4game.h"
using namespace sf;
using namespace std;


connect4game::connect4game()
{
    // A TURN VARIABLE IS USED TO DETERMINE WHOSE PLAYER TURN IT IS
    // IF IT IS EVEN 1ST PLAYER (RED) WILL MOVE
    // IF IT IS ODD 2ND PLAYER (YELLOW) WILL MOVE
    turn = 0;

    val = 5;

    // A POINT ARRAY USED TO DETERMINE WHICH POINT IS RED, YELLOW AND EMPTY
    point.resize(100);

    // OUR BOARD(6X7) WILL LOOK LIKE:
    /*
        1  2  3  4  5  6  7
        8  9  10 11 12 13 14
        15 16 17 18 19 20 21
        22 23 24 25 26 27 28
        29 30 31 32 33 34 35
        36 37 38 39 40 41 42
    */

    // INITIALLY ALL POINTS ARE EMPTY
    for (int i = 0; i < 100; i++)  point[i] = -1;

    // OUR BACKGROUND BOARD -- HERE I HAVE MADE A (6X7) BOARD
    board.setFillColor(Color::Blue);
    board.setSize(Vector2f(615, 570));
    board.setPosition(val, 130);
    board.setOutlineThickness(2);
    board.setOutlineColor(Color::Black);

    // A CIRCULAR PIECE WHICH I WILL USE TO FILL THE BOARD
    // WE WILL SET ITS POSITION AND COLOR AS REQUIRED IN FUTURE
    piece.setRadius(35);
    piece.setOrigin(17.5, 17.5);
    piece.setOutlineThickness(2);
    piece.setOutlineColor(Color::Black);


    // HIVERING THE OBJECT TO BE DROPPED
    circle.setRadius(35);
    circle.setOrigin(35, 35);
    circle.setOutlineThickness(3);
    circle.setOutlineColor(Color::Black);

}

void connect4game::set_font()
{
    font.loadFromFile("DS-DIGIT.TTF");
    restart.setFont(font);
    text.setFont(font);
}

void connect4game::set_text()
{
    restart.setPosition(190+val, 5);
    restart.setCharacterSize(20);
    restart.setFillColor(Color::Black);
    restart.setString("PRESS R TO RESTART THE GAME");

    text.setCharacterSize(30);
    text.setFillColor(Color::Black);
}



void connect4game::set_sound()
{
    buffer.loadFromFile("baseball_hit.wav");
    sound.setBuffer(buffer);
}

void connect4game::play_sound()
{
    sound.play();
}

void connect4game::set_piece(float Mx,float My,RenderWindow& window)
{
    if ((turn % 2) == 0)
    {
        circle.setFillColor(Color::Red);
    }
    else if ((turn % 2) != 0)
    {
        circle.setFillColor(Color::Yellow);
    }
    circle.setPosition((float)Mx, (float)My);
    window.draw(circle);
}


// A SIMPLE FUNCTION TO DRAW OUR BOARD
void connect4game::construct_board(RenderWindow& window)
{
    window.draw(board);
}

// A FUNCTION USED TO ACCESS THE BOTTOM-MOST UNFILLED POINT IN THE "COL" COLUMN
int connect4game::get_position(RenderWindow& window, int col)
{
    int i = 5;
    while (i >= 0)
    {
        // y VARIABLE STORES THE CURERNT VALUE OF POINT
        int y = (col + (7 * i));
        // IT MUST BE EMPTY
        if (point[y] == (-1)) return y;
        i--;
    }
    // IF WHOLE  COLUMN IS FILLED
    return -1;
}


// UPDATING THE BOARD WITH INPUT FROM USER
void connect4game::update_board(RenderWindow& window, int pos)
{
    if ((turn % 2) == 0) // IF TURN IS EVEN RED WILL MOVE
    {
        point[pos] = 1;
        turn++; // INCREMENT TURN FOR NEXT PLAYER TO MOVE
    }
    else if ((turn % 2) != 0) // IF TURN IS ODD YELLOW WILL MOVE
    {
        point[pos] = 2;
        turn++;  // INCREMENT TURN FOR NEXT PLAYER TO MOVE
    }
}

// REDRAWING OUR PIECES BASED ON INPUT
void connect4game::drawing_pieces(RenderWindow& window)
{
    int i;
    /* IN TOTAL WE HAVE 42 PIECES ,WE ITERATE OVER THEM AND SEE THEIR COLOR
        IF VALUE IS 1, THEN PIECE IS  RED
        IF VALUE IS 2, THEN PIECE IS YELLOW
        IF VALUE IS -1, THEN PIECE IS EMPTY
    */
    for (i = 0; i < 42; i++)
    {
        // ACCESING THE CURRENT X COORDINATE OF PIECE
        float curr_x = (20 + 90 * (i % 7));

        // ACCESSING THE CURRENT Y COORDINATE OF PIECE
        float curr_y = (160 + 90 * (i / 7));

        // SETTING THE CURRENT POSITION OF PIECE TO DRAW IT
        piece.setPosition(curr_x + val, curr_y);


        if (point[i] == (-1))
        {
            piece.setFillColor(Color::Cyan);
            window.draw(piece);
        }
        else if (point[i] == 1)
        {
            piece.setFillColor(Color::Red);
            window.draw(piece);
        }
        else if (point[i] == 2)
        {
            piece.setFillColor(Color::Yellow);
            window.draw(piece);
        }
    }
}

// CHECK IF ANY PLAYER HAS WON OR NOT
int connect4game::check_for_win(RenderWindow& window)
{
    int i, cr, cy, k, j;
    for (i = 1; i <= 42; i++)
    {
        // HORIZONTALLY
        j = i, cr = 0, cy = 0;
        for (k = 1; k <= 4; k++)
        {
            if (point[j] == 1) cr++;
            if (point[j] == 2) cy++;
            j++;
        }
        if (cr == 4) return 1;
        else if (cy == 4) return 2;

        // VERTICALLY
        j = i, cr = 0, cy = 0;
        for (k = 1; k <= 4; k++)
        {
            if (point[j] == 1) cr++;
            if (point[j] == 2) cy++;
            j += 7;
        }
        if (cr == 4) return 1;
        else if (cy == 4) return 2;

        // DIAGONALLY RIGHT
        j = i, cr = 0, cy = 0;
        for (k = 1; k <= 4; k++)
        {
            if (point[j] == 1) cr++;
            if (point[j] == 2) cy++;
            j += 8;
        }
        if (cr == 4) return 1;
        else if (cy == 4) return 2;

        // DIAGONALLY LEFT
        if (i >= 2)
        {
            j = i, cr = 0, cy = 0;
            for (k = 1; k <= 4; k++)
            {
                if (point[j] == 1) cr++;
                if (point[j] == 2) cy++;
                j += 6;
            }
            if (cr == 4) return 1;
            else if (cy == 4) return 2;
        }
    }
    return 0;
}

// DISPLAYING THE SFML WINDOW
void connect4game::display(RenderWindow& window,int win)
{
    if (win == 1)
    {
        text.setPosition(190 + val, 40);
        text.setString("RED WON THE GAME");
        window.draw(text);
        text.setPosition(240 + val, 80);
        text.setString("GAME OVER");
        window.draw(text);
    }
    else if (win == 2)
    {
        text.setPosition(190 + val, 40);
        text.setString("YELLOW WON THE GAME");
        window.draw(text);
        text.setPosition(240 + val, 80);
        text.setString("GAME OVER");
        window.draw(text);
    }
    else if (win == 0 && turn >= 43)
    {
        text.setPosition(190 + val, 40);
        text.setString("THE GAME IS DRAWN");
        window.draw(text);
        text.setPosition(240 + val, 80);
        text.setString("GAME OVER");
        window.draw(text);
    }
    window.draw(restart);
    window.display();
    window.clear(Color::Cyan);
}


// RESTART THE GAME
void connect4game::reset(RenderWindow& window)
{
    turn = 0;
    for (int i = 0; i < 100; i++)  point[i] = -1;
}

// DROPPING DOWN THE PIECE
void connect4game::move_piece(RenderWindow& window, int target_y, int target_x)
{
    float c = 160;
    if ((turn % 2) == 0)
    {
        piece.setFillColor(Color::Red);
    }
    if ((turn % 2) != 0)
    {
        piece.setFillColor(Color::Yellow);
    }
    while (c < target_y)
    {
        piece.setPosition((float)target_x + val, (float)c);
        c += 2.0f;
        window.draw(piece);
    }
}


