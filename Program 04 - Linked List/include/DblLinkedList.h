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

class Node
{ // fully defined here due to its simplicity
  public:
    Node()
    {
        next = prev = nullptr;
    }
    Node(std::string num)
    {
        data = num;
        next = prev = nullptr;
    }

    std::string data;
    Node* next;
    Node* prev;
};


class DblLinkedList
{
  public:
    DblLinkedList();

    bool push_back(const std::string& str);

    void resetIterator() const;
    bool hasMore() const;
    std::string next() const;

    void testConnections();

  private:
    Node *head, *tail;
    // mutable says that it can change in a const member function
    mutable Node* it;
    int count;
};

#endif
