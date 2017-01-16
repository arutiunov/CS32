#include "Set.h" 
#include <iostream>
#include <cassert>

using namespace std;

int main()
{

//// TESTING DEFAULT CONSTRUCTOR
    Set ss;
    ItemType value;
    // For an empty set:
    assert(ss.size() == 0);        // test size
    assert(ss.empty());            // test empty
    assert(!ss.erase(1));     // nothing to remove
    assert(!ss.contains(2)); // no elements in the list 
    assert(!ss.get(-1, value)); // no elements to get
    
// TESTING COPY CONSTRUCTOR
    Set ss1;
    for (int i = 0; i < 21; i++)
    {
        ss1.insert(i);
    }
    Set ss2(ss1); // testing copy constructor
//    cerr << ss1.size() << endl;
//    cerr << ss2.size() << endl;
    assert(ss2.size() == 21);
    assert(ss1.contains(15));
    assert(ss1.contains(20));
    
    Set ss3;
    Set ss4(ss3); // testing copy constructor if initial Set is empty
    assert(ss3.size() == 0);
    assert(!ss3.contains(10));
    
    
// TESTING ASSIGNMENT OPERATOR
    Set ss5;
    for (int i = 0; i < 15; i++)
    {
        ss5.insert(i);
    }
    
//    cerr << ss5.size() << endl;
    Set ss6 = ss5; // testing regular assingment operator settings
    
//    cerr << ss6.size() << endl;
//    ss6.dump();
    assert(ss6.size() == 15);
    
    Set ss7;
    for (int i = 0; i < 10; i++)
    {
        ss7.insert(i);
    }
    ss7 = ss7; // testing if you can assign object to itself
    assert (ss7.size() == 10);
    
    Set test3;
    for (int i = 15; i < 25; i++)
        test3.insert(i);
    Set test4;
    for (int i = 16; i < 25; i++)
        test4.insert(i);
    test4 = test3; // testing if old nodes are properly overriden
    assert(test4.size() == 10);
    assert(test4.contains(15));
    
    
// TESTING EMPTY
    Set ss8;
    assert(ss8.empty());
    
// TESTING INSERT FUNCTION
    Set ss9;
    for (int i = 0; i < 15; i++)
        ss9.insert(i);
    assert(!ss9.insert(13)); // already contains
    assert(ss9.insert(25)); // regular insert
    assert(ss9.size() == 16);
    
    Set test5;
    test5.insert(5); // regular insert as first element
    assert(test5.size() == 1);
    test5.insert(6); // regular insert as second element
    assert(test5.size() == 2);
    test5.insert(7); // regular insert as third element
    assert(test5.contains(7));
    
    
// TESTING ERASE FUNCTION
    Set ss11;
    for (int i = 0; i < 15; i++)
        ss11.insert(i);
    for (int i = 0; i < 3; i++)
        ss11.erase(i);
    assert(ss11.size() == 12); // testing erase's effect on list's size
    assert(!ss11.erase(69)); // not conatined
    assert(ss11.size() == 12);
    ss11.erase(14); // erase from the back
    ss11.erase(3); // erase from the front
    assert(ss11.size() == 10);
    ss11.erase(8); // erase from the middle
    assert(ss11.size() == 9);
    
    Set test10; // erase a single-element list
    test10.insert(1);
    test10.erase(1);
    assert(test10.size() == 0);
    assert(!test10.contains(1));
    assert(test10.empty());
    
    Set test11;
    assert(!test11.erase(25));  // erase an empty list
    


// TESTING CONTAINS FUNCTION
    Set ss12;
    ss12.insert(1);
    assert(!ss12.contains(0));
    assert(ss12.contains(1));
    
// TESTING GET FUNCTION
    Set ss13;
    for (int i = 0; i < 30; i++)
        ss13.insert(i);
    int var(0);
    assert(ss13.get(27, var));
    assert(var == 2); // testing var's value
//    cerr << "Var is " << var << endl;
    assert(!ss13.get(-20, var)); // testing that you can't have negative pos
    
        
    
// TESTING SWAP FUNCTION
    Set ss14;
    for (int i = 0; i < 10; i++)
        ss14.insert(i);
    ss14.swap(ss14); // testing swap function on itself
    
    Set ss15;
    ss15.insert(1);
    ss15.swap(ss14); // testing regular swap function
    assert(ss14.size() == 1);
    assert(ss14.contains(1));
    assert(!ss14.contains(2));
    assert(ss15.size() == 10);
    assert(ss15.contains(7));
    
    Set ss16; // testing swap function with an empty list
    ss16.swap(ss15);
    assert(ss15.size() == 0);
    
    
//     TESTING UNITE FUNCTION

    Set ss17;
    for (int i = 0; i < 20; i++)
        ss17.insert(i);
    unite(ss17, ss17,ss17); // testing for unite function called on itself
    assert(ss17.size() == 20);
    assert(ss17.contains(19));
//    cerr << "---" << endl;
//    ss17.dump();
    
    Set ss18;
    Set result18;
    for (int i = 0; i < 21; i++) // testing for unite function + empty result set
        ss18.insert(i);
    unite(ss17, ss18, result18);
    assert(result18.size() == 21);
    assert(result18.contains(19));
    
    Set ss19;
    Set ss20;
    Set result19;
    for (int i  = 0; i < 50; i++) // filling up result before
        result19.insert(i);
    ss19.insert(2009);
    for (int i = 70; i < 95; i++)
        ss20.insert(i);
    unite(ss19, ss20, result19);
    assert(result19.size() == 26 );
    assert(! result19.contains(0));
    
    Set test69;
    for (int i = 0; i < 10; i++)
    {
        test69.insert(i);
    }
    
    Set test70;
    
    Set result69; // result list has some elements that are result of unite function
    for (int i = 0; i < 7; i++)
        result69.insert(i);
    
    unite (test69, test70, result69);
    assert(result69.contains(9));
    assert(result69.size() == 10);
    
    
    
//     TESTING SUBTRACT FUNCTION
    
    
    
    Set ss21;
    for (int i = 0; i < 25; i++)
        ss21.insert(i);
    subtract(ss21, ss21, ss21); // testing with all 3 parameters as one set
    assert(ss21.size() == 0);
    assert(! ss21.contains(20));
    assert(ss21.empty());
    
    Set ss22;
    for (int i = 0; i < 5; i++)
        ss22.insert(i);
    Set ss23;
    for (int i = 0; i < 4; i++)
        ss23.insert(i);
    Set result22;
//    cerr << ss22.size() << endl;
//    cerr << ss23.size() << endl;
    subtract(ss22, ss23, result22); // testing normal subtract function functionality
//    cerr << result22.size() << endl;
    assert(result22.size() == 1);
    assert(result22.contains(4));
    
    Set ss24;
    for (int i = 0; i < 10; i++)
        ss24.insert(i);
    Set ss25;
    for (int i = 0; i < 6; i++)
        ss25.insert(i);
    Set result23;
    for (int i = 25; i < 35; i++)
        result23.insert(i);
    subtract(ss24, ss25, result23); // testing subtract function if result list already contains elements
    assert(result23.size() == 4);
    assert(!result23.contains(30));
    assert(result23.contains(8));
    
    cerr << "Passed all tests!" << endl;


}


//#include "Set.h"
//#include <type_traits>
//
//#define CHECKTYPE(f, t) { auto p = (t)(f); (void)p; }
//
//static_assert(std::is_default_constructible<Set>::value,
//              "Set must be default-constructible.");
//static_assert(std::is_copy_constructible<Set>::value,
//              "Set must be copy-constructible.");
//
//void thisFunctionWillNeverBeCalled()
//{
//    CHECKTYPE(&Set::operator=, Set& (Set::*)(const ItemType&));
//    CHECKTYPE(&Set::empty,     bool (Set::*)() const);
//    CHECKTYPE(&Set::size,      int  (Set::*)() const);
//    CHECKTYPE(&Set::insert,    bool (Set::*)(const ItemType&));
//    CHECKTYPE(&Set::erase,     bool (Set::*)(const ItemType&));
//    CHECKTYPE(&Set::contains,  bool (Set::*)(const ItemType&) const);
//    CHECKTYPE(&Set::get,       bool (Set::*)(int, ItemType&) const);
//    CHECKTYPE(&Set::swap,      void (Set::*)(Set&));
//    CHECKTYPE(unite,    void (*)(const Set&, const Set&, Set&));
//    CHECKTYPE(subtract, void (*)(const Set&, const Set&, Set&));
//}
//
//int main()
//{}

//#include "Set.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void test()
//{
//    Set ss;
//    assert(ss.insert("roti"));
//    assert(ss.insert("pita"));
//    assert(ss.size() == 2);
//    assert(ss.contains("pita"));
//    ItemType x = "focaccia";
//    assert(ss.get(0, x)  &&  (x == "roti"  ||  x == "pita"));
//}
//
//int main()
//{
//    test();
//    cout << "Passed all tests" << endl;
//}

//
//#include "Set.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void test()
//{
//    Set uls;
//    assert(uls.insert(10));
//    assert(uls.insert(20));
//    assert(uls.size() == 2);
//    assert(uls.contains(20));
//    ItemType x = 30;
//    assert(uls.get(0, x)  &&  (x == 10  ||  x == 20));
//}
//
//int main()
//{
//    test();
//    cout << "Passed all tests" << endl;
//}
