#include "Set.h"
#include <iostream>

using namespace std;

Set::Set()
    :head(nullptr), tail(nullptr)
{
}

Set::~Set()
{
    while (head != nullptr) // while there is at least one element in the list...
    {
        Node* temp = head->m_next; // temp points to the element after the one getting deleted
        delete head; // delete the node
        head = temp; // assign head to the next element
    }
}

Set::Set(const Set& other)
{
    if (other.head != nullptr) // if other is not an empty set
    {
        this->head = new Node; // create a new node
        this->head->m_data = other.head->m_data; // set new Node's data equal to other's
        this->tail = head; // head and tail both point to first element in copied link list
        
        Node* temp = other.head; // create pointer equal to other's head
        
        while (temp->m_next != nullptr) // while we haven't reached end of other's list
        {
            insert(temp->m_next->m_data); // insert data from other
            temp = temp->m_next; // shift temporary pointer over one element
        }
        numelements++; // add one more count to the amount of elements (accounts for "new" action above)
    }
}


Set& Set::operator =(const Set& rhs)
{
    if (this != &rhs)
    {
        Set temporary(rhs); // create a copy of rhs (via copy constructor)
        swap (temporary);
    }
    return *this;
}


bool Set::empty() const
{
    if (numelements == 0)
        return true;
    else
        return false;
}

int Set::size() const
{
    return numelements;
}


bool Set::insert(const ItemType& value)
{
    if (contains(value)) // the value isn't already in the list
        return false;
    
    Node* temp = head; // save the old head
    
    if (temp != nullptr) // if the list isn't empty
    {
        head = new Node; // create a new node
        head->m_data = value;
        head->m_next = temp;
        head->m_prev = nullptr;
        temp->m_prev = head; // second element's m_prev points to newly created first element
    }
    else // if the list is empty
    {
        head = new Node(nullptr, nullptr, value);
        tail = head;
    }
    numelements++; // increase amount of elements by 1
    return true;
}

bool Set::erase(const ItemType& value)
{
    if (!contains(value)) // if the value is not in the list
        return false;
    
    Node* curr;
    
    for (curr = head; curr != nullptr && curr->m_data != value; curr = curr->m_next)
    {
        ; // identify the element in list with that value
    }
    
    if (curr != nullptr) // if curr is pointing to element with value
    {
        
        if (head->m_data == value) // if it's the first element in the list
        {
            head = curr->m_next; // head now points to 2nd element in list
            
            if (curr->m_next) // if there is more than one element in the linked list...
                curr->m_next->m_prev = nullptr; // second element is now first
            
            numelements--;
        }
        
        else if (tail->m_data == value) // if it's the last element in the list
        {
            tail = tail->m_prev; // tail now points to 2nd last element in list
            tail->m_next = nullptr; // 2nd to last element is now last
            
            if (size() == 1) // if there is now only 1 element in the list...
                head = tail; // head and tail both point to first node
            
            numelements--;
        }
        
        else // if it's an element in the middle
        {
            curr->m_prev->m_next = curr->m_next; // prev node's m_next pointer is equal to curr's m_next
            curr->m_next->m_prev = curr->m_prev;
            numelements--;
        }
        
        delete curr;
        
        if (numelements == 0) // if there are no more elements in the list
        {
            tail = nullptr;
        }

        return true;
    }
    else
        return false;
}


bool Set::contains(const ItemType& value) const
{
    Node *p;
    for (p = head; p != nullptr && p->m_data != value; p = p->m_next)
    {
        ; // cycle until we either encounter value or the end of list
    }
    
    if (p != nullptr) // if we have found the value
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Set::get(int pos, ItemType& value) const
{
    if (pos >= numelements || pos < 0) // impossible
       return false;
    
    Node* temp = head;
    for (int i = 0; i < pos; i++)
    {
        temp = temp->m_next;
    }
        
    value = temp->m_data;
    return true;
}

void Set::swap(Set& other)
{
    Node* temp_head = this->head; // temp head points to this list's first element
    Node* temp_tail = this->tail; // temp tail points to this list's last element
    
    this->head = other.head; // this list's head now points to first element of other
    this->tail = other.tail; // this list's tail now points to last element of other
    
    other.head = temp_head; // other list's head now points to first element of this
    other.tail = temp_tail; // other list's tail now points to last element of this
    
    int temp_size = size(); // temp_size has size of this list
    this->numelements = other.numelements;
    other.numelements = temp_size;
}

void Set::dump() const
{
    Node* temp;
    for (temp = this->head; temp != nullptr; temp = temp->m_next)
    {
        cerr << temp->m_data << endl;
    }
}


void unite(const Set& s1, const Set& s2, Set& result)
{
    Set temporary;
    for (int i = 0; i < s1.size(); i++)
    {
        ItemType placeholder;
        s1.get(i, placeholder);
        temporary.insert(placeholder);
    }
    
    for (int i = 0; i < s2.size(); i++)
    {
        ItemType placeholder;
        s2.get(i, placeholder);
        temporary.insert(placeholder);
    }
        result = temporary;
}



void subtract(const Set& s1, const Set& s2, Set& result)
{
    Set temporary = s1;

    for (int i = 0; i < s2.size(); i++)
    {
        ItemType placeholder;
        s2.get(i, placeholder);
        if (temporary.contains(placeholder)) // if temporary contains a value equal to placeholder
        {
            temporary.erase(placeholder); // erase that node
        }
    }
    result = temporary; 
}













