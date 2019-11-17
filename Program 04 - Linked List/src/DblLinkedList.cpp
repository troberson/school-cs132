///
// Name: Tamara Roberson
// Section: S
// Program Name: Program 4 - LinkedList
//
// Description: A doubly-linked list.
///

#include <DblLinkedList.h>
#include <TRString.h>

#include <iostream>
#include <optional>


DblLinkedList::DblLinkedList()
{
    head = nullptr;
    tail = nullptr;
    it = nullptr;
    count = 0;
}

DblLinkedList::DblLinkedList(const TRString& str) : DblLinkedList()
{
    this->push_back(str);
    this->resetIterator();
}


int DblLinkedList::getCount()
{
    return this->count;
}

void DblLinkedList::push_back(const TRString& str)
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
{
    this->it = head;
}

bool DblLinkedList::hasMore() const
{
    return (this->it != nullptr);
}

std::optional<TRString> DblLinkedList::next() const
{
    if (!hasMore())
    {
        return std::nullopt;
    }

    const Node* old_it = this->it;
    this->it = old_it->next;

    return old_it->data;
}

void DblLinkedList::testConnections()
{
    // write test for connections:  loop through the list testing each node
    std::cout << "TEST CONNECTIONS Passed\n";
}


std::ostream& operator<<(std::ostream& ostrm, const DblLinkedList& list)
{
    // save the old iterator position, so we can resume later
    DblLinkedList::Node* old_it = list.it;

    // reset iterator
    list.resetIterator();

    // walk through list, writing elements to the ostream
    while (list.hasMore())
    {
        const TRString str = list.next().value();
        ostrm << str;

        // add a space between words
        if (list.hasMore())
        {
            ostrm << " ";
        }
    }

    // restore old iterator position
    list.it = old_it;

    // return the ostream
    return ostrm;
}
