#ifndef newSet_h
#define newSet_h
#include <string>

using namespace std;
typedef unsigned long ItemType;
//typedef string ItemType;


const int DEFAULT_MAX_ITEMS = 100;

class Set
{
    
    
public:
    Set();
    Set(int i);
    
    ~Set(); // destructor
    Set(const Set& other); // copy constructor
    Set& operator =(const Set& rhs); // assignment operator

    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int i, ItemType& value) const;
    void swap(Set& other);
    void dump() const;
    
private:
    ItemType* data;
    int m_size = DEFAULT_MAX_ITEMS;
    int m_numelements = 0;

};
#endif

