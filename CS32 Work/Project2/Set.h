#ifndef SET_H
#define SET_H
#include <string>

typedef int ItemType;
//typedef std::string ItemType;

//typedef unsigned long ItemType;

class Set
{
public:
    Set();
    ~Set(); // destructor
    Set(const Set& other); // copy constructor
    Set& operator =(const Set& rhs); // assignment operator
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    void swap(Set& other);
    void dump() const; 
private:
    struct Node
    {
        Node() {} // default constructor for object of Node type
        Node(Node* next, Node* prev) : m_next(next), m_prev(prev) {} 
        Node(Node* next, Node* prev, ItemType item) : m_next(next), m_prev(prev), m_data(item) {}
        ItemType m_data; // actual data of the node
        Node* m_next = nullptr; // pointer to the next element of the list
        Node* m_prev = nullptr; // pointer to the previous element of the list
    };
    Node* head = nullptr; // pointer to the first element of the list
    Node* tail = nullptr; // pointer to the last element of the list
    int numelements = 0; // amount of elements in the list
};

// external functions
void unite(const Set& s1, const Set& s2, Set& result);

void subtract(const Set& s1, const Set& s2, Set& result);


#endif