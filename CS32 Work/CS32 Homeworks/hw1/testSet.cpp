//#include "Set.h"
//#include <iostream>
//#include <string>
//#include <cassert>
//using namespace std;
//
//
//int main ()
//
//{
//    Set ss;
//    ss.insert("A");
//    ss.insert("C");
//    ss.insert("A");
//    ss.insert("B");
//    string all;
//    for (int k = 0; k < ss.size(); k++)
//    {
//        string x;
//        ss.get(k, x);
//        all += x;
//    }
//
//    
//    Set ss2;
//    ss2.insert("pita");
//    ss2.insert("roti");
//    string s1;
//    assert(ss2.get(1, s1)  &&  (s1 == "roti"  ||  s1 == "pita"));
//    string s2;
//    assert(ss2.get(1, s2)  &&  s2 == s1);
//
//    Set ss3;
//    ss3.insert("focaccia");
//    assert(!ss3.contains(""));
//    ss3.insert("tortilla");
//    ss3.insert("");
//    ss3.insert("lavash");
//    
//    
//    assert(ss3.contains(""));
//    assert(ss3.size() == 4);
//    
//    assert(ss3.erase("focaccia"));
//    assert(ss3.size() == 3);
//    assert(ss3.contains("lavash"));
//    assert(ss3.contains("tortilla"));
//    assert(ss3.contains(""));
//    
//    
//    
//    
//    Set ss1;
//    ss1.insert("injera");
//    
//    Set ss4;
//    ss4.insert("matzo");
//    ss4.insert("dosa");
//    ss1.swap(ss4);
//    
//    cout << ss1.size() << endl;
//    cout << ss4.size() << endl;
//    ss1.dump();
//    ss4.dump();
//    
//    assert(ss1.size() == 2);
//    assert(ss1.contains("matzo"));
//    assert(ss1.contains("dosa"));
//    assert(ss4.size() == 1);
//    assert(ss4.contains("injera"));
//
//    
//    
//    Set s;
//    assert(s.empty());
//    ItemType x = "arepa";
//    assert( !s.get(42, x)  &&  x == "arepa"); // x unchanged by get failure
//    s.insert("chapati");
//    assert(s.size() == 1);
//    assert(s.get(0, x)  &&  x == "chapati");
//    cout << "Passed all tests" << endl;
//
//    Set s;
//    assert(s.empty());
//    ItemType x = 9876543;
//    assert( !s.get(42, x)  &&  x == 9876543); // x unchanged by get failure
//    s.insert(123456789);
//    assert(s.size() == 1);
//    assert(s.get(0, x)  &&  x == 123456789);
//    cout << "Passed all tests" << endl;
//}


//
#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Set uls;
    assert(uls.insert(10));
    assert(uls.insert(20));
    assert(uls.size() == 2);
    assert(uls.contains(20));
    ItemType x = 30;
    assert(uls.get(0, x)  &&  (x == 10  ||  x == 20));
    ItemType x2 = 40;
    assert(uls.get(1, x)  &&  (x == 10  ||  x == 20)  &&
           x != x2);
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}


//#include "Set.h"
//#include <string>
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
//    ItemType x = "bing";
//    assert(ss.get(0, x)  &&  (x == "roti"  ||  x == "pita"));
//    ItemType x2 = "barbari";
//    assert(ss.get(1, x)  &&  (x == "roti"  ||  x == "pita")  &&
//           x != x2);
//}
//
//int main()
//{
//    test();
//    cout << "Passed all tests" << endl;
//}