// Game.cpp

#include "provided.h"
#include <iostream>

using namespace std;

class GameImpl
{
  public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black); 
    bool completed(int& winner) const; 
    bool takeTurn(); 
    void play(); 
    int checkerAt(int c, int r) const;
  private:
    Scaffold board;
    int connectGoal;
    int lastColumn = 0;
    Player* Red;
    Player* Black;
    bool redTurn = true;
};



GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black)
:board(nColumns, nLevels), connectGoal(N), Red(red), Black(black)
{}

bool GameImpl::completed(int& winner) const
{
    int color = 0;
    if (redTurn == true)
        color = BLACK;
    else
        color = RED;
    
    int lastLevel = board.levels(); // set lastChecker to the top level of playing field in the column
    

    while (checkerAt(lastColumn, lastLevel) == VACANT) // searching for most recently placed checker's level
    {
        lastLevel--;
        if (lastLevel - 1 == 0) // if we've reached the bottom of the playing field
            break;
    }

    
    // RIGHT DIAGONAL CASE (DOWN & UP)
    int counter = 1;
    
    for (int i = 1; i <= connectGoal && (lastColumn + i <= board.cols()) && (lastLevel + i <= board.levels()); i++) // checking NE case
    {
        if (checkerAt(lastColumn + i, lastLevel + i) == color)
        {
            counter++;
        }
        else
            break;
    }
    
    if (counter == connectGoal)
    {
        winner = color;
        return true;
    }

    
    
    for (int i = 1; i <= connectGoal && (board.cols() - i > 0) && (board.levels() - i > 0); i++) // checking SW case
    {
        if (checkerAt(lastColumn - i, lastLevel - i) == color)
        {
            counter++;
        }
        else
            break;
    }
    
    if (counter == connectGoal)
    {
        winner = color;
        return true;
    }

    
    // LEFT DIAGONAL CASE (DOWN & UP)
    
    counter = 1;
    
    for (int i = 1; i <= connectGoal && (board.cols() - i > 0) && (lastLevel + i <= board.levels()); i++) // checking NW case
    {
        if (checkerAt(lastColumn - i, lastLevel + i) == color)
        {
            counter++;
        }
        else
            break;
    }
    
    if (counter == connectGoal)
    {
        winner = color;
        return true;
    }

    
    for (int i = 1; i <= connectGoal && (lastColumn + i <= board.cols()) && (board.levels() - i > 0); i++) // checking SE case
    {
        if (checkerAt(lastColumn + i, lastLevel - i) == color)
        {
            counter++;
        }
        else
            break;
    }
    
    if (counter == connectGoal)
    {
        winner = color;
        return true;
    }



    // DOWNWARDS CASE
    counter = 1;
    
    for (int i = 1; i <= connectGoal && (board.levels() - i > 0); i++)
    {
        if (checkerAt(lastColumn, lastLevel - i) == color)
        {
            counter++;
        }
        else
            break;
    }
    
    if (counter == connectGoal)
    {
        winner = color;
        return true;
    }

    // HORIZONTAL CASE
    counter = 1;
    
    for (int i = 1; i <= connectGoal && (lastColumn - i > 0); i++) // checking WEST case
    {
        if (checkerAt(lastColumn - i, lastLevel) == color)
        {
            counter++;
        }
        else
            break;
    }
    
    if (counter == connectGoal)
    {
        winner = color;
        return true;
    }

    
    for (int i = 1; i <= connectGoal && (lastColumn + i <= board.cols()); i++) // checking EAST case
    {
        if (checkerAt(lastColumn + i, lastLevel) == color)
        {
            counter++;
        }
        else
            break;
    }
    
    if (counter == connectGoal)
    {
        winner = color;
        return true;
    }
    
    if (board.numberEmpty() == 0)
        winner = TIE_GAME;
    
    return false;
}

bool GameImpl::takeTurn()
{
    if (redTurn == true) // if it's the RED player's turn
    {
        lastColumn = Red->chooseMove(board, connectGoal, RED); // chooseMove returns column value (1 thru #cols)
        board.makeMove(lastColumn, RED); // register move RED player makes
        redTurn = false; // next move will be BLACK player's
        return true;
    }
    else
    {
        lastColumn = Black->chooseMove(board, connectGoal, BLACK);
        board.makeMove(lastColumn, BLACK);
        redTurn = true;
        return true;
    }
}

void GameImpl::play()
{
    int winner = 0;
    if (!Red->isInteractive() && !Black->isInteractive())
    {
        int i = 0;
        while (completed(winner) == false)
        {
            board.display();
            if (i%5 == 0)
            {
                cout << "Press enter to continue " << endl;
                cin.ignore(100000, '\n');
            }
            i++;
            takeTurn();
        }
    }
    else // at least one human player
        while (completed(winner) == false && board.numberEmpty() != 0)
        {
            board.display();
            takeTurn();
        }

    board.display();
    if (winner == RED)
        cout << "The game is over! RED player won the game!" << endl;
    else if (winner == BLACK)
        cout << "The game is over! BLACK player won the game!" << endl;
    else
        cout << "The game is a TIE! Nobody won this time!" << endl;
    
}

int GameImpl::checkerAt(int c, int r) const
{
    return board.checkerAt(c, r);
}


//******************** Game functions *******************************

// These functions simply delegate to GameImpl's functions.
// You probably don't want to change any of this code.

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}
 
bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}
 
int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}




