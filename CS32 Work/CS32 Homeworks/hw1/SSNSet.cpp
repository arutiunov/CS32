#include "SSNSet.h"
#include <iostream>
using namespace std;

SSNSet::SSNSet()
{
}


bool SSNSet::add(ItemType ssn)
{
    
    if (database.insert(ssn))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int SSNSet::size() const
{
    int size;
    size = database.size();
    return size;
}

void SSNSet::print() const
{
    ItemType placeholder;
    
    for (int i = 0; i < database.size(); i++)
    {
        database.get(i, placeholder);
        cout << placeholder << endl;
    }
}