////
// Name: Tamara Roberson
// Section: S
// Program Name: Program 4 - LinkedList
//
// Description: A doubly-linked ordered list which holds TRStrings.
// Elements can be added to the list with insert(), which will add them
// in case-insensitive order. If a match already exists, the element will
// not be added. The list may be traversed with a rudamentary iterator.
////

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
    push_back(str);
    resetIterator();
}

DblLinkedList::DblLinkedList(const DblLinkedList& list) : DblLinkedList()
{
    list.process([&list, this]() -> std::optional<bool> {
        this->push_back(list.next().value());
        return {};
    });
}

DblLinkedList::~DblLinkedList()
{
    clear();
}

void DblLinkedList::clear()
{
    while (this->count > 0)
    {
        del_node(this->head);
    }
}

DblLinkedList& DblLinkedList::operator=(DblLinkedList list)
{
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

int DblLinkedList::getCount() const
{
    return this->count;
}

void DblLinkedList::push_back(const TRString& str)
{
    Node* new_node = add_node(str, this->tail, nullptr);

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
        push_back(str);
        return true;
    }

    // if new entry is smaller than current head,
    // make the new entry the new head
    if (str < this->head->data)
    {
        add_node(str, nullptr, this->head);
        return true;
    }

    // walk through the list, looking for an entry that is larger
    // we'll put the new entry right before it or fail if we find
    // an equivalent entry already exists.
    auto result = this->process([&str, this]() -> std::optional<bool> {
        auto cur_ptr = this->it;
        auto cur_val = next().value();

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

        return {};
    });

    // return success if entry added, failure if entry already exists
    if (result.has_value())
    {
        return result.value();
    }

    // if we reach the end, the new entry must be larger than the
    // current largest entry, so it becomes the new tail
    push_back(str);
    return true;
}


bool DblLinkedList::remove(const TRString& str)
{
    // we can't remove anything from an empty list
    if (this->count == 0)
    {
        return false;
    }

    // walk through the list, looking for a match
    auto result = this->process([&str, this]() -> std::optional<bool> {
        auto cur_ptr = this->it;
        auto cur_val = next().value();

        // found a match, delete it and return success
        if (cur_val == str)
        {
            del_node(cur_ptr);
            return true;
        }

        return {};
    });

    // return true on success, false otherwise
    return result.has_value() && result.value();
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
        return {};
    }

    const Node* old_it = this->it;
    this->it = old_it->next;

    return old_it->data;
}


std::ostream& operator<<(std::ostream& ostrm, const DblLinkedList& list)
{
    // save the old iterator position, so we can resume later
    DblLinkedList::Node* old_it = list.it;


    // walk through list, writing elements to the ostream
    list.process([&]() -> std::optional<bool> {
        const TRString str = list.next().value();
        ostrm << str;

        // add a space between words
        if (list.hasMore())
        {
            ostrm << " ";
        }

        return {};
    });

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
    if (node_left != nullptr)
    {
        node_left->next = node_right;
    }

    if (node_right != nullptr)
    {
        node_right->prev = node_left;
    }
}

void DblLinkedList::del_node(Node* node)
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
