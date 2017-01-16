#include "Set.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Set::Set()
{
}


bool Set::empty() const
{
    if (m_size > 0)
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
    return m_size;
}


bool Set::insert(const ItemType& value)
{
    if (m_size == DEFAULT_MAX_ITEMS) // array is already full
        return false;

    if (contains(value)) // array already contains that value
    {
        return false;
    }
    data[m_size] = value; // assign new value to new index
    m_size++; // increase index of array by 1
    return true; // if cycles through loop and never finds empty element
}

bool Set::erase(const ItemType& value)
{
    if (empty())
        return false;
    
    for (int i = 0; i < m_size; i++)
    {
        if (data[i] == value)
        {
            data[i] = data[m_size - 1]; // replace the element with the last element
            m_size--; // decrease the size by 1
            return true;
        }
    }
    return false;
}



bool Set::contains(const ItemType& value) const
{
    for (int i = 0; i < m_size; i++)
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
    int size_temp = 0;

    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        ItemType temp = other.data[i];
        other.data[i] = this->data[i];
        this->data[i] = temp;
    }

    size_temp = other.m_size;
    other.m_size = this->m_size;
    this->m_size = size_temp; 
    
}

void Set::dump() const
{
    for (int i = 0; i < m_size; i++)
    {
        cerr << data[i] << endl;
    }
}




