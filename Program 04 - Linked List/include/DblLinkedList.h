///
// Name: Tamara Roberson
// Section: S
// Program Name: Program 4 - LinkedList
//
// Description: A doubly-linked list.
///

#ifndef DBLLINKEDLIST_H
#define DBLLINKEDLIST_H
#include <string>

using namespace std;

class Node
{ // fully defined here due to its simplicity
  public:
    Node()
    {
        next = prev = nullptr;
    }
    Node(string num)
    {
        data = num;
        next = prev = nullptr;
    }

    string data;
    Node* next;
    Node* prev;
};


class DblLinkedList
{
  public:
    DblLinkedList();

    bool push_back(const string& str);

    void resetIterator() const;
    bool hasMore() const;
    string next() const;

    void testConnections();

  private:
    Node *head, *tail;
    mutable Node*
        it; // mutable says that it can change in a const member function
    int count;
};

#endif
