#include "newSet.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Set::Set()
{
    data = new ItemType[DEFAULT_MAX_ITEMS];
    m_size = DEFAULT_MAX_ITEMS;
}

Set::Set(int i)
{
    if (i <= 0) // class invariant
    {
        cerr << "Can't have a set with negative or 0 amount of members!" << endl;
        exit(1); 
    }
    data = new ItemType[i];
    m_size = i; 
}

Set::~Set()
{
    delete [] data;
}


Set::Set(const Set& other)
{
    m_size = other.m_size;
    m_numelements = other.m_numelements;
    data = new ItemType[m_size];
    
    for (int i = 0; i < m_size; i++)
    {
        data[i] = other.data[i];
    }
}

Set& Set::operator =(const Set& rhs)
{
    if (this != &rhs)
    {
        Set temporary(rhs);
        swap(temporary);
    }
    return *this;
}


bool Set::empty() const
{
    if (m_numelements > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int Set::size() const
{
    return m_numelements; // index is 1 less than total amount
}


bool Set::insert(const ItemType& value)
{
    
    if (contains(value)) // if value is already in the array
    {
        return false; // return false, don't insert it 
    }
    
    if (m_numelements == m_size) // if the amount and size are equal
    {
        return false;
    }
    
    data[m_numelements++] = value;
    return true;

}

bool Set::erase(const ItemType& value)
{
    if (empty())
        return false;
    
   
    for (int i = 0; i < m_numelements; i++)
    {
        if (data[i] == value)
        {
            data[i] = data[m_numelements - 1]; // replace the element with the last element
            m_numelements--; // decrease the size by 1
            return true;
        }
    }
    return false;
}


bool Set::contains(const ItemType& value) const
{
    for (int i = 0; i < m_numelements; i++)
    {
        if (data[i] == value)
            return true;
    }
    return false;
}

bool Set::get(int i, ItemType& value) const
{
    if (i >= 0 && i < this->size())
    {
        value = data[i];
        return true;
    }
    else
    {
        return false;
    }
}


void Set::swap(Set& other)
{
    ItemType* temp;
    int size_temp = 0;
    int numelements_temp = 0;
    
    // swapping sizes
    size_temp = other.m_size;
    other.m_size = this->m_size;
    this->m_size = size_temp;
    
    // swapping m_numelements
    numelements_temp = other.m_numelements;
    other.m_numelements = this->m_numelements;
    this->m_numelements = numelements_temp;
    
    // swapping memory addresses of arrays
    temp = other.data;
    other.data = this->data;
    this->data = temp;
}


void Set::dump() const
{
    for (int i = 0; i < m_numelements; i++)
    {
        cerr << data[i] << endl;
    }
}

