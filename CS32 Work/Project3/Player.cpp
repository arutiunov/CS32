// Player.cpp

#include "provided.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/////////////// DEFINED CONSTANTS

const int WIN = 1;
const int TIE = 0;
const int LOSS = -1;


class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
    bool isInteractive() const; 
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
    int ratingSystem(Scaffold& board, const int& lastColumn, const int& connectGoal, const int& color);
    int immediateMove(Scaffold& board, const int& connectGoal, const int& color);
};


////////////// CLASS FUNCTIONS IMPLEMENTATIONS

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    int v = 0;
    cout << "Enter your column choice: ";
    do
    {
        cin >> v;
    }
    while (v <= 0 || v > s.cols() || s.checkerAt(v, s.levels()) != VACANT);
    return v;
}

bool HumanPlayerImpl::isInteractive() const
{
    return true;
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    for (int i = 0; i < s.cols(); i++)
    {
        if (s.checkerAt(i + 1, s.levels()) == VACANT)
            return i + 1;
    }
    return -1;
}


int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    
    Scaffold temporary = s;
    
    int move = immediateMove(temporary, N, color); // checks if CPU has imminent win

    if (move != TIE) // if CPU does have an imminent win
        return move; // return that column
    
    if (color == RED) // if CPU's color is RED
    {
        int move = immediateMove(temporary, N, BLACK); // check if opponent has immminent win
        if (move != TIE)
        {
            return move;
        }
    }
    else // CPU color must be black
    {
        int move = immediateMove(temporary, N, RED); // check if opponent has imminent win
        if (move != TIE)
        {
            return move;
        }
    }
    
    for (int i = 0; i < s.cols(); i++)
    {
        if (s.checkerAt(i + 1, s.levels()) == VACANT)
            return i + 1;
    }
    return -1;
}



int SmartPlayerImpl::immediateMove(Scaffold& board, const int& connectGoal, const int& color)
{
    int column = 0;
    for (int i = 1; i <= board.cols(); i++)
    {
        if (board.makeMove(i, color))
        {
            int outcome = ratingSystem(board, i, connectGoal, color);
            if (outcome == WIN)
            {
                board.undoMove();
                column = i;
                break;
            }
            board.undoMove();
        }
    }
    return column;
}

int SmartPlayerImpl::ratingSystem(Scaffold& board, const int& lastColumn, const int& connectGoal, const int& color)
{
    if (board.numberEmpty() == 0) // tie game, don't check board
        return TIE;
    
    int lastLevel = board.levels(); // set lastChecker to the top level of playing field in the column
    
    while (board.checkerAt(lastColumn, lastLevel) == VACANT) // searching for most recently placed checker's level
    {
        lastLevel--;
        if (lastLevel - 1 == 0) // if we've reached the bottom of the playing field
            break;
    }
    
    
    // RIGHT DIAGONAL CASE (DOWN & UP)
    int counter = 1;
    
    for (int i = 1; i <= connectGoal && (lastColumn + i <= board.cols()) && (lastLevel + i <= board.levels()); i++) // checking NE case
    {
        if (board.checkerAt(lastColumn + i, lastLevel + i) == color)
        {
            counter++;
        }
        else
            break;
    }
    
    if (counter == connectGoal)
        return WIN;
    
    
    for (int i = 1; i <= connectGoal && (board.cols() - i > 0) && (board.levels() - i > 0); i++) // checking SW case
    {
        if (board.checkerAt(lastColumn - i, lastLevel - i) == color)
        {
            counter++;
        }
        else
            break;
    }
    
    if (counter == connectGoal)
        return WIN;
    
    
    // LEFT DIAGONAL CASE (DOWN & UP)
    
    counter = 1;
    
    for (int i = 1; i <= connectGoal && (board.cols() - i > 0) && (lastLevel + i <= board.levels()); i++) // checking NW case
    {
        if (board.checkerAt(lastColumn - i, lastLevel + i) == color)
        {
            counter++;
        }
        else
            break;
    }
    
    if (counter == connectGoal)
        return WIN;
    
    for (int i = 1; i <= connectGoal && (lastColumn + i <= board.cols()) && (board.levels() - i > 0); i++) // checking SE case
    {
        if (board.checkerAt(lastColumn + i, lastLevel - i) == color)
        {
            counter++;
        }
        else
            break;
    }
    
    if (counter == connectGoal)
        return WIN;
    
    
    // DOWNWARDS CASE
    counter = 1;
    
    for (int i = 1; i <= connectGoal && (board.levels() - i > 0); i++)
    {
        if (board.checkerAt(lastColumn, lastLevel - i) == color)
        {
            counter++;
        }
        else
            break;
    }
    
    if (counter == connectGoal)
        return WIN;
    
    // HORIZONTAL CASE
    counter = 1;
    
    for (int i = 1; i <= connectGoal && (lastColumn - i > 0); i++) // checking WEST case
    {
        if (board.checkerAt(lastColumn - i, lastLevel) == color)
        {
            counter++;
        }
        else
            break;
    }
    
    if (counter == connectGoal)
        return WIN;
    
    for (int i = 1; i <= connectGoal && (lastColumn + i <= board.cols()); i++) // checking EAST case
    {
        if (board.checkerAt(lastColumn + i, lastLevel) == color)
        {
            counter++;
        }
        else
            break;
    }
    
    if (counter == connectGoal)
        return WIN; // return 1 or -1
    
    return 2; // tie game AND the game is not over (using 2 to indicate this)
}


//******************** Player derived class functions *************************

// These functions simply delegate to the Impl classes' functions.
// You probably don't want to change any of this code.

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
