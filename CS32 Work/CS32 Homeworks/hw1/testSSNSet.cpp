#include "SSNSet.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
//    SSNSet set1;
//    set1.add("item1"); 
//    set1.add("item2");
//    assert(!set1.add("item1"));
//    cerr << set1.size() << endl; 
//    set1.print();
    
    SSNSet set2;
    set2.add(1);
    set2.add(2);
    assert(!set2.add(2));
    cerr << set2.size() << endl;
    set2.print();
    
}