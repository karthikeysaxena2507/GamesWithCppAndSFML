#include <SFML/Graphics.hpp>
#include<cstdlib>
#include<cstdio>
#include"tictactoegame.h"
#include<SFML/Audio.hpp>
using namespace sf;
using namespace std;

// A CONSTRUCTOR OF GAME CLASS 
tictactoegame::tictactoegame()
{
    turn = 0;
    zero.resize(10);
    cross.resize(10);
    boxes.resize(10);
    for (int i = 0; i <= 9; i++)
    {
        zero[i] = 0;
        cross[i] = 0;
    }

    // SETTING ROTATION OF LINES TO FORM A CROSS
    line_left.setSize(Vector2f(141, 5));
    line_right.setSize(Vector2f(141, 5));
    line_left.rotate(45);
    line_right.rotate(135);
    line_left.setFillColor(Color::White);
    line_right.setFillColor(Color::White);

    // MAKING THE ZERO 
    circle.setRadius(30);
    circle.setOutlineThickness(5);
    circle.setOutlineColor(Color::White);
    circle.setFillColor(Color::Blue);

    // DESIGNING OUR GRID
    grid.setSize(Vector2f(380, 380));
    grid.setPosition(Vector2f(280, 130));
    grid.setFillColor(Color::Yellow);
}

void tictactoegame::set_font()
{
    font.loadFromFile("DS-DIGIT.TTF");
    win1.setFont(font);
    win2.setFont(font);
    gameover.setFont(font);
    draw.setFont(font);
    restart.setFont(font);
    message.setFont(font);
}

void tictactoegame::set_text()
{
    // SETTING THE SIZE OF THE MESSAGES TO BE DISPLAYED
    win1.setCharacterSize(20);
    win2.setCharacterSize(20);
    draw.setCharacterSize(20);
    restart.setCharacterSize(20);
    gameover.setCharacterSize(40);
    message.setCharacterSize(20);

    // SETTING UP THE POSITIONS OF THE TEXT TO BE DISPLAYED ON SFML WINDOW
    win1.setPosition(300, 50);
    win2.setPosition(300, 50);
    draw.setPosition(375, 50);
    restart.setPosition(350, 550);
    gameover.setPosition(375, 70);
    message.setPosition(260, 20);

    // JUST FILLING UP THE COLOR (YOU CAN CHOOSE ANY)
    win1.setFillColor(Color::Green);
    win2.setFillColor(Color::Green);
    gameover.setFillColor(Color::Yellow);
    draw.setFillColor(Color::Green);
    restart.setFillColor(Color::Magenta);
    message.setFillColor(Color::Magenta);

    restart.setString("PRESS R TO RESTART THE GAME");
    message.setString("PLAYER WITH X WILL MOVE FIRST AND WILL BE PLAYER 1");
}

void tictactoegame::set_sound()
{
    buffer.loadFromFile("baseball_hit.wav");;
    sound.setBuffer(buffer);
}

void tictactoegame::play_sound()
{
    sound.play();
}

void tictactoegame::construct_grid(RenderWindow& window)
{
    int i, j, x = 300, y = 150, k = 1;
    // DRAWING OUR GRID
    window.draw(grid);
    for (i = 0; i <= 2; i++)
    {
        x = 300;
        for (j = 0; j <= 2; j++)
        {
            window.draw(boxes[k]);
            boxes[k].setSize(Vector2f(100, 100));
            boxes[k].setPosition(Vector2f(x, y));
            boxes[k].setFillColor(Color::Blue);
            k++;
            x += 120;
        }
        y += 120;
    }
}
void tictactoegame::fill_your_choice(RenderWindow& window)
{
    //FILLING THE ZERO AND CROSS ARRAY ACCORING TO TURN BY CHECKING THE POSITION OF MOUSE
    int k, i;
    for (k = 1; k <= 9; k++)
    {
        float Mx = Mouse::getPosition(window).x;
        float My = Mouse::getPosition(window).y;
        float Bx = boxes[k].getPosition().x;
        float By = boxes[k].getPosition().y;
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (Mx >= Bx && My >= By && Mx <= Bx + 100 && My <= By + 100)
            {
                if ((turn % 2) == 0 && cross[k] == 0 && zero[k] == 0)
                {
                    cross[k] = 1;
                    turn++;
                }
                else if ((turn % 2) != 0 && cross[k] == 0 && zero[k] == 0)
                {
                    zero[k] = 1;
                    turn++;
                }
            }
        }
    }
}
void tictactoegame::drawing_choices(RenderWindow& window)
{
    int k;
    // DRAWING THE ZERO AND CROSS ACCORDING TO INFORMATION WE UPDATED IN BOTH ARRAYS
    for (k = 1; k <= 9; k++)
    {
        float Bx = boxes[k].getPosition().x;
        float By = boxes[k].getPosition().y;
        if (zero[k] == 1)
        {
            circle.setPosition(Bx + 20, By + 20);
            window.draw(circle);
        }
        else if (cross[k] == 1)
        {
            line_left.setPosition(Bx, By);
            line_right.setPosition(Bx + 100, By);
            window.draw(line_left);
            window.draw(line_right);
        }
    }
}
int tictactoegame::check_for_win(RenderWindow& window)
{
    int x, y;
    // CHECK TEH CONDITIONS FOR WIN 
    //HORIZONTAL
    for (x = 1; x <= 9; x += 3)
    {
        int z = 0;
        int c = 0;
        for (y = x; y < (x + 3); y++)
        {
            if (zero[y] == 1) z++;
            if (cross[y] == 1) c++;
        }
        if (z == 3)
        {
            return 2;
        }
        else if (c == 3)
        {
            return 1;
        }
    }
    //VERTICAL
    for (x = 1; x <= 3; x++)
    {
        int z = 0;
        int c = 0;
        for (y = x; y <= 9; y += 3)
        {
            if (zero[y] == 1) z++;
            if (cross[y] == 1) c++;
        }
        if (z == 3)
        {
            return 2;
        }
        else if (c == 3)
        {
            return 1;
        }
    }
    // DIAGONALLY
    if (zero[1] == 1 && zero[5] == 1 && zero[9] == 1)
    {
        return 2;
    }
    if (cross[1] == 1 && cross[5] == 1 && cross[9] == 1)
    {
        return 1;
    }
    if (cross[3] == 1 && cross[5] == 1 && cross[7] == 1)
    {
        return 1;
    }
    if (zero[3] == 1 && zero[5] == 1 && zero[7] == 1)
    {
        return 2;
    }
    return 0;
}
void tictactoegame::display(RenderWindow& window,int state)
{
    // IF STATE == 1 , MEANS PLAYER 1 WON
    // IF STATE == 2 , MEANS PLAYER 2 WON
    // IF STATE == 3 , MEANS GAME IS EITHER IN PROGRESS OR IT IS A DRAW
    if (state == 1)
    {
        // PLAYER 1 WON, SO DISPLAY THAT MESSAGE
        gameover.setString("GAMEOVER");
        window.draw(gameover);
        win1.setString("PLAYER 1, YOU WON THE GAME , CONGRATS");
        window.draw(win1);
    }
    else if (state == 2)
    {
        // PLAYER 2 WON, SO DISPLAY THAT MESSAGE
        gameover.setString("GAMEOVER");
        window.draw(gameover);
        win2.setString("PLAYER 2, YOU WON THE GAME , CONGRATS");
        window.draw(win2);
    }
    else if (state == 3 && turn >= 9)
    {
        // IF NUMBER OF TURNS ARE MORE THAN OR EQUAL TO 9 THEN GAME IS DRAWN
        gameover.setString("GAMEOVER");
        window.draw(gameover);
        draw.setString("THE GAME HAS DRAWN");
        window.draw(draw);
    }
    window.draw(message);
    window.draw(restart);
    window.display();
    window.clear(Color::Black);
}

void tictactoegame::reset(RenderWindow& window)
{
    // WILL RRESET ALL CHANGES
    int i;
    for (i = 0; i <= 9; i++)
    {
        zero[i] = 0;
        cross[i] = 0;
        turn = 0;
    }
}