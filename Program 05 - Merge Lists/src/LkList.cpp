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
#include <sstream>

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

LkList::~LkList()
{
    clear();
}

LkList::LkList(const LkList& other) : LkList()
{
    other.resetIterator();
    while (other.hasMore())
    {
        insert(other.next());
    }
}

LkList::LkList(std::initializer_list<int> il) : LkList()
{
    insert(il);
}

LkList& LkList::operator=(LkList other)
{
    // copy-and-swap does not require a self-assignment check.
    other.swap(*this);
    return *this;
}

void LkList::swap(LkList& list) noexcept
{
    // unqualified "swap" allows for overloads to step in with ADL
    using std::swap;
    swap(list.head, this->head);
    swap(list.tail, this->tail);
    swap(list.count, this->count);
}


int LkList::size() const
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

void LkList::resetIterator() const
{
    it = head;
}

bool LkList::hasMore() const
{
    return (it != nullptr);
}

int LkList::next() const
{
    int num = it->data;
    it = it->next;
    return num;
}

std::string LkList::toString() const
{
    std::ostringstream stream;
    stream << static_cast<const LkList&>(*this);
    return stream.str();
}

ostream& operator<<(ostream& outStr, const LkList& lst)
{
    lst.resetIterator();
    while (lst.hasMore())
        outStr << lst.next() << "  ";
    return outStr;
}
