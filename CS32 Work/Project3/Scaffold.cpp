#ifndef SCAFFOLDIMP_H
#define SCAFFOLDIMP_H

#include "provided.h"
#include <vector>
#include <iostream>
#include <stack>
#include <cassert>
using namespace std;


class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nLevels);
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const;
    void display() const;
    bool makeMove(int column, int color);
    int undoMove();
    
  private:
    int mColumns;
    int mLevels;
    vector<vector<int>> playBoard;
    struct moveHistory
    {
    stack<int> lastLevel;
    stack<int> lastColumn;
    };
    moveHistory recorder;
};


ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
			:mColumns(nColumns), mLevels(nLevels), playBoard(nColumns, vector<int>(nLevels, VACANT))
{
    if (nColumns <= 0 || nLevels <= 0)
    {
        cout << "Invalid dimensions! Terminating prorgram." << endl;
        exit(1);
    }
}

int ScaffoldImpl::cols() const
{
    return mColumns;
}

int ScaffoldImpl::levels() const
{
    return mLevels;
}

int ScaffoldImpl::numberEmpty() const
{
	int numEmpty = 0;
    for (int i = 0; i < mColumns; i++)
	{
		for (int j = 0; j < mLevels; j++)
		{
			if (playBoard[i][j] == VACANT)
				numEmpty++;
		}
	}
	return numEmpty;
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    if (column > 0 && level > 0 && column <= cols() && level <= levels())
    {
        if (playBoard[column - 1][level - 1] == RED) // using internal system of (o to cols/levels - 1)
            return RED;
        else if (playBoard[column - 1][level - 1] == BLACK)
            return BLACK;
    }
	return VACANT;
}

void ScaffoldImpl::display() const
{
	for (int i = mLevels - 1; i >= 0; i--)
		{
            cout << "|"; // first side of column

			for (int j = 0; j < mColumns; j++) // note the < is to draw the sides of the playing field
			{
				if (playBoard[j][i] == RED)
					cout << "R";
				else if (playBoard[j][i] == BLACK)
					cout << "B";
				else if (playBoard[j][i] == VACANT)
					cout << " ";
                cout << "|";
			}
            
            cout << endl; // end of the row
        }
    for (int z = 0; z < mColumns; z++)
    {
        cout << "+-";
    }
    
    cout << "+" << endl;
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    if (column > 0 && column <= cols() && checkerAt(column, mLevels) == VACANT)
    {
        
        int i = mLevels;
        while (checkerAt(column, i) == VACANT && i > 0) // find the lowest level that's vacant
            i--;
        
        playBoard[column - 1][i] = color;
        recorder.lastColumn.push(column - 1);
        recorder.lastLevel.push(i);
        return true;
    }
    return false;
}

int ScaffoldImpl::undoMove()
{
    if (recorder.lastColumn.size() != 0 && recorder.lastLevel.size() != 0)
    {
        int i = recorder.lastColumn.top();
        recorder.lastColumn.pop();
        int j = recorder.lastLevel.top();
        recorder.lastLevel.pop();
        playBoard[i][j] = VACANT;
        return i + 1;
    }
    return 0;
}






//******************** Scaffold functions *******************************

// These functions simply delegate to ScaffoldImpl's functions.
// You probably don't want to change any of this code.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}

Scaffold::~Scaffold()
{
    delete m_impl;
}

Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}

Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}

int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}

void Scaffold::display() const
{
    m_impl->display();
}

bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}

int Scaffold::undoMove()
{
    return m_impl->undoMove();
}

#endif
