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
    add_node(num, tail);
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
    while (this->count > 0)
    {
        del_node(this->head);
    }
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
    {
        outStr << lst.next() << "  ";
    }
    return outStr;
}

// PRIVATE FUNCTIONS
LkList::Node* LkList::add_node(const int num,
                               Node* prev_node /* = nullptr */,
                               Node* next_node /* = nullptr */)
{
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    return add_node(new Node(num), prev_node, next_node);
}

LkList::Node* LkList::add_node(Node* new_node,
                               Node* prev_node /* = nullptr */,
                               Node* next_node /* = nullptr */)
{
    // Set as head or link the previous node
    if (prev_node == nullptr)
    {
        this->head = new_node;
    }
    else
    {
        this->link_nodes(prev_node, new_node);
    }

    // Set as tail or link the next node
    if (next_node == nullptr)
    {
        this->tail = new_node;
    }
    else
    {
        this->link_nodes(new_node, next_node);
    }

    // Increase the node count
    this->count++;

    // Return the new node
    return new_node;
}

void LkList::link_nodes(Node* node_left /* = nullptr */,
                        Node* node_right /* = nullptr */)
{
    if (node_left != nullptr)
    {
        node_left->next = node_right;
    }

    if (node_right != nullptr)
    {
        node_right->prev = node_left;
    }
}

void LkList::del_node(Node* node)
{
    // Can't delete nothing
    if (node == nullptr)
    {
        return;
    }

    // Save the previous and next pointers
    Node* node_prev = node->prev;
    Node* node_next = node->next;

    // Update head and tail
    if (this->head == node)
    {
        this->head = node_next;
    }

    if (this->tail == node)
    {
        this->tail = node_prev;
    }
    // Delete the node
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    delete node;

    // Link the previous and next nodes together
    link_nodes(node_prev, node_next);

    // Decrease the count
    this->count--;
}
