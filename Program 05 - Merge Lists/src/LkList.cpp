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
#include <sstream>

using namespace std;


void LkList::merge(LkList& src)
{
    LkList new_list;

    // SHORTCUT: Do nothing if src is empty
    if (src.count == 0)
    {
        return;
    }

    // SHORTCUT: If current list is empty, just swap src and current
    if (this->count == 0)
    {
        using std::swap;
        swap(*this, src);
        return;
    }

    resetIterator();
    src.resetIterator();

    // Function to move everything remaining in a list to the new list.
    auto moveRemainder = [&](LkList& lst) {
        if (lst.count <= 0)
        {
            return;
        }

        new_list.add_node(lst.it, new_list.tail);
        new_list.tail = lst.tail;
        new_list.updateSize();

        lst.head = nullptr;
        lst.tail = nullptr;
        lst.count = 0;
    };

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

        lst.head = end_node->next;
        end_node->next = nullptr;
        lst.updateSize();

        new_list.add_node(start_node, new_list.tail);
        new_list.updateSize();
        new_list.tail = end_node;
        lst.resetIterator();
    };


    // SHORTCUT: If the tail of this list is less than the head of the
    // source list, then just concatenate them.
    if (this->tail->data < src.head->data)
    {
        moveRemainder(*this);
        moveRemainder(src);
    }

    // SHORTCUT: or vice-versa
    else if (src.tail->data < this->head->data)
    {
        moveRemainder(src);
        moveRemainder(*this);
    }

    // Otherwise, check element-by-element
    else
    {
        // Process elements as long as some remain
        while (count > 0)
        {
            // If src list is exhausted, move the rest of the elements from
            // this list into the new list
            if (src.head == nullptr)
            {
                moveRemainder(*this);
                break;
            }

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

        // Move any remaining items from src list
        moveRemainder(src);
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

void LkList::unlink_node(Node* node)
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
    node->prev = nullptr;
    node->next = nullptr;

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
