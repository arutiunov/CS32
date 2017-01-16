#ifndef QUEUE_H
#define QUEUE_H
#include <queue> 
#include <iostream>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    queue<Coord> coordQueue;
    Coord start_Coord(sr, sc);
    coordQueue.push(start_Coord);
    maze[sr][sc] = '@';
    
        while (!coordQueue.empty())
        {
            Coord current = coordQueue.front();
            int x, y;
            x = current.r();
            y = current.c();
            cerr << x << "," << y << endl;
            coordQueue.pop();
            
            if (current.r() == er && current.c() == ec)
                return true;
            
            if (maze[current.r() -1][current.c()] == '.') // can move north
            {
                Coord temp(current.r() -1, current.c());
                coordQueue.push(temp);
                maze[current.r() -1][current.c()] = '@';
            }
            
            
            if (maze[current.r()][current.c() + 1] == '.') // can move east
            {
                Coord temp(current.r(), current.c() + 1);
                coordQueue.push(temp);
                maze[current.r()][current.c() + 1] = '@';
            }
            
            if (maze[current.r() + 1][current.c()] == '.') // can move south
            {
                Coord temp(current.r() + 1, current.c());
                coordQueue.push(temp);
                maze[current.r() + 1][current.c()] = '@';
            }
            
            if (maze[current.r()][current.c() - 1] == '.') // can move west
            {
                Coord temp(current.r(), current.c() - 1);
                coordQueue.push(temp);
                maze[current.r()][current.c() - 1] = '@';
            }
        }
        
    return false;
}
#endif
