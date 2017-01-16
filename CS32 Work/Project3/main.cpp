#include "provided.h"
#include <iostream>
#include <cassert>
using namespace std;



void doPlayerTests()
{
    HumanPlayer hp("Marge");
    assert(hp.name() == "Marge"  &&  hp.isInteractive());
    BadPlayer bp("Homer");
    assert(bp.name() == "Homer"  &&  !bp.isInteractive());
    SmartPlayer sp("Lisa");
    assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
    
    Scaffold s(3, 2);
    s.makeMove(1, RED);
    s.makeMove(1, BLACK);
    cout << "=========" << endl;
    int n = hp.chooseMove(s, 3, RED);
    cout << "=========" << endl;
    assert(n == 2  ||  n == 3);
    n = bp.chooseMove(s, 3, RED);
    assert(n == 2  ||  n == 3);
    n = sp.chooseMove(s, 3, RED);
    assert(n == 2  ||  n == 3);
    
    Scaffold s2(5, 5);
    HumanPlayer human1("human1");
    assert(human1.name() == "human1"  &&  hp.isInteractive());
    int n1 = human1.chooseMove(s2, 3, BLACK);
    assert(n1 >= 1 && n1 <= 5);
    
    Scaffold s3(5, 5);
    BadPlayer bp1("badplayer1");
    BadPlayer bp2("badplayer2");
    while (s3.numberEmpty() != 0) // checker should exactly alternate
    {
        int i = bp1.chooseMove(s3, 5, RED);
        s3.makeMove(i, RED);
        i = bp2.chooseMove(s3, 5, BLACK);
        s3.makeMove(i, BLACK);
    }
    s3.display();
    
    Scaffold s4(5, 5);
    HumanPlayer hp3("artiom");
    SmartPlayer sp1("smartaplayer");
    Game g5(5, 5, 3, &hp3, &sp1);
    g5.play();

}

void doScaffoldTests()
{
    Scaffold test0(3, 2);
    assert(test0.cols() == 3  &&  test0.levels() == 2  &&
           test0.numberEmpty() == 6);
    assert(test0.makeMove(1, RED));
    assert(test0.makeMove(1, BLACK));
    assert(!test0.makeMove(1, RED));
    assert(test0.numberEmpty() == 4);
    assert(test0.checkerAt(1, 1) == RED  &&  test0.checkerAt(1, 2) == BLACK);
    assert(test0.checkerAt(2, 1) == VACANT);
//    test0.display();
    
    
    Scaffold test2(5, 5);
    assert(test2.cols() == 5  &&  test2.levels() == 5  &&
           test2.numberEmpty() == 25);
    assert(!test2.makeMove(0, RED)); // can't make a move out of bounds to the left
    assert(!test2.makeMove(6, RED)); // can't make a move out of bounds to the right
    assert(test2.makeMove(1, RED));
    assert(test2.checkerAt(1, 1) == RED);
    assert(test2.numberEmpty() == 24);
    test2.undoMove();
    assert(test2.numberEmpty() == 25); 
    for (int i = 1; i < 6; i++)
        test2.makeMove(2, BLACK);
    assert(!test2.makeMove(2, BLACK)); // column is full so can't move there
//    test2.display();
    
    Scaffold test3(3, 3);
    for (int i = 1; i <= 3; i++)
        test3.makeMove(1, BLACK);
//    test3.display();
    assert(test3.numberEmpty() == 6);
    
    assert(test3.undoMove() == 1);
    assert(test3.numberEmpty() == 7);
    assert(test3.undoMove() == 1);
    assert(test3.numberEmpty() == 8);
    assert(test3.undoMove() == 1);
    assert(test3.numberEmpty() == 9);
    assert(test3.undoMove() == 0); // nomore moves to undo
    assert(test3.checkerAt(25, 100) == VACANT); // should still return vacant even though it's out of scope
    
    Scaffold test4(6, 6);
    for (int i = 1; i <= 6; i++)
        for (int j = 1; j <= 6; j++)
        {
            assert(test4.checkerAt(i, j) == VACANT); // all values initialized to vacant
        }
    
    Scaffold test5(5, 5);
    for (int i = 1; i <= 5; i++)
        test5.makeMove(i, BLACK);
    assert(test5.undoMove() == 5);
    assert(test5.undoMove() == 4);
    assert(test5.undoMove() == 3);
    assert(test5.undoMove() == 2);
    assert(test5.undoMove() == 1);
}

void doGameTests()
{
    BadPlayer bp1("Bart");
    BadPlayer bp2("Homer");
    Game g(2, 2, 2, &bp1, &bp2);
    int winner;
    assert(!g.completed(winner));
    
    g.takeTurn();  // Red's first move
    assert(!g.completed(winner)  &&
           (g.checkerAt(1, 1) == RED  ||  g.checkerAt(2, 1) == RED));
    g.takeTurn();  // Black's first move
    assert(!g.completed(winner));
    g.takeTurn();  // Red's second move; Red must win
    assert(g.completed(winner)  &&  winner == RED);
    
    
    HumanPlayer hp1("HumanPlayer1");
    BadPlayer bp_1("BadPlayer1");
    Game g2(5, 5, 3, &hp1, &bp_1);
    int winner_1 = 0;
    assert(!g2.completed(winner_1));
    g2.play();
    
    BadPlayer bp_2("BadPlayer2");
    BadPlayer bp_3("BadPlayer3");
    Game g3(5, 5, 4, &bp_2, &bp_3);
    g3.play();
    
    
}

int main()
{
    HumanPlayer hp("Artiom");
    SmartPlayer sp("Kedar");
    Game g(5, 5, 4, &hp, &sp);
    g.play();
   
    doGameTests();
    doScaffoldTests();
    doPlayerTests();
    cout << "Passed all tests" << endl;
}

