#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std;

History::History(const int nRows, const int nCols)
        :mRows(nRows), mCols(nCols)
{
    for (int i = 0; i < mRows; i++) // initializes all the values within the array to '.'
    {
        for (int j = 0; j < mCols; j++)
        {
            array[i][j] = 0;
        }
    }
}


bool History::record(int r, int c)
{
    bool result;
    if (r > mRows || c > mCols || r < 1 || c < 1)
        result = false;

    else
    {
        result = true;
    }

	array[r-1][c-1] = array[r-1][c-1] + 1;
	return result;
}

void History::display() const
{
    clearScreen();

	char placeholder[MAXROWS][MAXCOLS];

    for (int i = 0; i < mRows; i++)
    {
        for (int j = 0; j < mCols; j++)
        {
			if (array[i][j] == 0)
				placeholder[i][j] = '.';
			else if (array[i][j] == 26)
        		placeholder[i][j] = 'Z';
			else
				placeholder[i][j] = array[i][j] + 64;
		}
    }

	for (int k = 0; k < mRows; k++)
	{
		for (int l = 0; l < mCols; l++)
		{
			cout << placeholder[k][l];
		}
		cout << endl;
	}
    cout << endl;
}
