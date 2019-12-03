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
    LkList new_list;

    resetIterator();
    src.resetIterator();

    auto printLists = [&]() {
        auto old_it1 = this->it;
        auto old_it2 = src.it;
        std::cout << "List 1: " << toString() << " (Size: " << count
                  << ")\n"
                  << "List 2: " << src.toString()
                  << " (Size: " << src.count << ")\n"
                  << "New List: " << new_list.toString()
                  << " (Size: " << new_list.count << ")" << std::endl;
        this->it = old_it1;
        src.it = old_it2;
    };

    // Process elements as long as some remain
    while (count > 0)
    {
        // If src list is exhausted, move the rest of the elements from
        // this list into the new list
        if (src.head == nullptr)
        {
            unlink_node(it, true, false);
            new_list.add_node(it, new_list.tail);
            break;
        }

        // Function to move a block of numbers starting from the head of
        // one list to the new list, as long as they are less than the
        // first element in cmplist.
        auto moveBlock = [&](LkList& lst, const LkList& cmplst) {
            auto start_node = lst.head;
            auto end_node = lst.it;
            while (lst.hasMore() && lst.it->data <= cmplst.head->data)
            {
                end_node = lst.it;
                lst.next();
            }
            lst.unlink_node(start_node, true, false);
            lst.unlink_node(end_node, false, true);
            lst.updateSize();

            new_list.add_node(start_node, new_list.tail);
            new_list.updateSize();
            new_list.tail = end_node;
            lst.resetIterator();
        };

        // Move from one list or the other, depending on which has the
        // lower starting element
        if (head->data <= src.head->data)
        {
            moveBlock(*this, src);
        }
        else
        {
            moveBlock(src, *this);
        }
    }

    // Swap the new list with the current list
    using std::swap;
    new_list.swap(*this);
}


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
void LkList::updateSize()
{
    resetIterator();
    int new_count{};
    while (hasMore())
    {
        next();
        new_count++;
    }
    resetIterator();

    this->count = new_count;
}

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
    if (node_left == nullptr)
    {
        this->head = node_right;
    }
    else
    {
        node_left->next = node_right;
    }

    if (node_right == nullptr)
    {
        this->tail = node_left;
    }
    else
    {
        node_right->prev = node_left;
    }
}

void LkList::unlink_node(Node* node, const bool unlink_prev /* = true */,
                         const bool unlink_next /* = true */)
{
    // Can't delete nothing
    if (node == nullptr)
    {
        return;
    }

    // Save the previous and next pointers
    Node* node_prev = node->prev;
    Node* node_next = node->next;

    // Unlink previous and next nodes
    if (unlink_prev)
    {
        node->prev = nullptr;
    }

    if (unlink_next)
    {
        node->next = nullptr;
    }

    // Update head and tail
    if (this->head == node)
    {
        this->head = node_next;
    }

    if (this->tail == node)
    {
        this->tail = node_prev;
    }

    // Link the previous and next nodes together
    link_nodes(node_prev, node_next);

    // Decrease the count
    this->count--;
}

void LkList::del_node(Node* node)
{
    unlink_node(node);

    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    delete node;
}
