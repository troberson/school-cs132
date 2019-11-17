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
#include <utility>


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

DblLinkedList::DblLinkedList(const DblLinkedList& list) : DblLinkedList()
{
    while (list.hasMore())
    {
        this->push_back(list.next().value());
    }
}

DblLinkedList::~DblLinkedList()
{
    this->resetIterator();
    while (this->hasMore())
    {
        Node* next_it = this->it->next;
        delete this->it;
        this->it = next_it;
        this->count--;
    }
}

DblLinkedList& DblLinkedList::operator=(DblLinkedList list)
{
    // copy-and-swap could be slow and memory-intensive for very large
    // lists, as it requires the creation of a temporary copy, but ensures
    // that our list remains in a valid state.

    // copy-and-swap does not require a self-assignment check.

    list.swap(*this);
    return *this;
}

void DblLinkedList::swap(DblLinkedList& list) noexcept
{
    // unqualified "swap" allows for overloads to step in with ADL
    using std::swap;
    swap(list.head, this->head);
    swap(list.tail, this->tail);
    swap(list.count, this->count);
}

int DblLinkedList::getCount()
{
    return this->count;
}

void DblLinkedList::push_back(const TRString& str)
{
    Node* new_node = this->add_node(str, this->tail, nullptr);

    // if there is no head, set this new node to the head
    if (this->head == nullptr)
    {
        this->head = new_node;
    }
}


bool DblLinkedList::insert(const TRString& str)
{
    // if there are no nodes in the list, add new new entry
    if (this->count == 0)
    {
        this->push_back(str);
        return true;
    }

    // if new entry is smaller than current head,
    // make the new entry the new head
    if (str < this->head->data)
    {
        this->add_node(str, nullptr, this->head);
        return true;
    }

    // reset iterator
    this->resetIterator();


    // walk through the list, looking for an entry that is larger
    // we'll put the new entry right before it or fail if we find
    // an equivalent entry already exists.
    while (this->hasMore())
    {
        auto cur_ptr = this->it;
        auto cur_val = this->next().value();

        // if we reach an entry whose value is equal to the new entry,
        // keep the old entry and do not add the new entry, return failure.
        if (cur_val == str)
        {
            return false;
        }

        // if we reach an entry that has a larger value than the new entry,
        // then insert it before that entry
        if (cur_val > str)
        {
            add_node(str, cur_ptr->prev, cur_ptr);
            return true;
        }
    }

    // if we reach the end, the new entry must be larger than the current
    // largest entry, so it becomes the new tail
    this->push_back(str);
    return true;
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


// PRIVATE FUNCTIONS
DblLinkedList::Node*
DblLinkedList::add_node(const TRString& str,
                        Node* prev_node /* = nullptr */,
                        Node* next_node /* = nullptr */)
{
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    return add_node(new Node(str), prev_node, next_node);
}


DblLinkedList::Node*
DblLinkedList::add_node(Node* new_node, Node* prev_node /* = nullptr */,
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

void DblLinkedList::link_nodes(Node* node_left /* = nullptr */,
                               Node* node_right /* = nullptr */)
{
    node_left->next = node_right;
    node_right->prev = node_left;
}
