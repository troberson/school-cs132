////
// Name: Tamara Roberson
// Section: S
// Program Name: Program 5 - LinkedList Merge
//
// Description: A linked list with a merge function.
// The merge function moves all the elements from one sorted list
// into another another sorted list in a stable fashion.
////


#include "LkList.h"
#include <iostream>

using namespace std;

void LkList::merge(LkList& src)
{

    // this is what you need to write.....

} // end of merge function


LkList::LkList()
{
    head = nullptr;
    tail = nullptr;
    it = nullptr;
    count = 0;
}

// LkList::~LkList(){}
// LkList::LkList(const LkList& other){}
// LkList& LkList::operator=(const LkList& rhs){}

int LkList::size()
{
    return count;
}

bool LkList::insert(int num)
{
    if (count == 0)
    { // empty list
        head = tail = new Node(num);
    }
    else
    { // >1 count, then add back
        Node* temp = new Node(num);
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
    count++;
    return true;
}

void LkList::insert(const initializer_list<int>& il)
{
    for (int ele : il)
    {
        insert(ele);
    }
}


void LkList::clear()
{
    if (count == 0)
        return;

    while (tail != head)
    {
        tail = tail->prev;
        delete tail->next;
    }
    delete head;
    head = tail = nullptr;
    count = 0;
}

void LkList::resetIterator()
{
    it = head;
}

bool LkList::hasMore()
{
    return (it != nullptr);
}

int LkList::next()
{
    int num = it->data;
    it = it->next;
    return num;
}

ostream& operator<<(ostream& outStr, LkList& lst)
{
    lst.resetIterator();
    while (lst.hasMore())
        outStr << lst.next() << "  ";
    return outStr;
}
