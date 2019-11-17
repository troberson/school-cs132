///
// Name: Tamara Roberson
// Section: S
// Program Name: Program 4 - LinkedList
//
// Description: A doubly-linked list.
///

#include <DblLinkedList.h>

#include <iostream>


DblLinkedList::DblLinkedList()
{
    head = nullptr;
    tail = nullptr;
    it = nullptr;
    count = 0;
}

DblLinkedList::DblLinkedList(const std::string& str) : DblLinkedList()
{
    this->push_back(str);
}


int DblLinkedList::getCount()
{
    return this->count;
}

void DblLinkedList::push_back(const std::string& str)
{
    // Create a new node
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    Node* new_node = new Node(str);

    // If there are no nodes in the list, set this as the head
    if (this->count == 0)
    {
        this->head = new_node;
    }

    // If there is already at least one entry in the list,
    // set the new node as the tail and link it with the old last entry.
    if (tail != nullptr)
    {
        new_node->prev = this->tail;
        this->tail->next = new_node;
    }

    this->tail = new_node;

    this->count++;
}

void DblLinkedList::resetIterator() const
{ // write second
  // needs to be written:  set it to head
}

bool DblLinkedList::hasMore() const
{ // and so on....
    // needs to be written: is it pointing to nullptr
    return false;
}

std::string DblLinkedList::next() const
{
    // needs to be written: gets the string the it pointer is pointing to
    //   then moves the it pointer to next "node" (could be nullptr)
    return std::string("stub");
}

void DblLinkedList::testConnections()
{
    // write test for connections:  loop through the list testing each node
    std::cout << "TEST CONNECTIONS Passed\n";
}
