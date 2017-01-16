#ifndef HISTORY_H
#define HISTORY_H
#include "globals.h"

class History
{
public:
	History(const int nRows, const int nCols);
	bool record(int r, int c);
	void display() const;
private:
	int mRows;
    int mCols;
    int array[MAXROWS][MAXCOLS];
};

#endif
