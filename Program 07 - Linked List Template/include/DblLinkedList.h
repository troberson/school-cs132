///
// Name: Tamara Roberson
// Section: S
// Program Name: Program 4 - LinkedList
//
// Description: A doubly-linked ordered list which holds TRStrings.
// Elements can be added to the list with insert(), which will add them
// in case-insensitive order. If a match already exists, the element will
// not be added. The list may be traversed with a rudamentary iterator.
///

#ifndef DBLLINKEDLIST_H
#define DBLLINKEDLIST_H

#include <TRString.h>

#include <optional>

class Node
{
  public:
    Node()
    {
        next = prev = nullptr;
    }

    explicit Node(const TRString& str)
    {
        data = str;
        next = prev = nullptr;
    }

    // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
    TRString data;

    // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
    Node* next;

    // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
    Node* prev;
};


// NOLINTNEXTLINE(hicpp-special-member-functions,cppcoreguidelines-special-member-functions)
class DblLinkedList
{
  public:
    /**
     * Create a new linked list.
     */
    DblLinkedList();

    /**
     * Create a new linked list that includes the given element.
     *
     * @param str An element for the list.
     */
    explicit DblLinkedList(const TRString& str);


    /**
     * Copy an existing DblLinkedList.
     *
     * @param list The list to copy.
     */
    DblLinkedList(const DblLinkedList& list);


    /**
     * Delete a DblLinkedList.
     */
    ~DblLinkedList();


    /**
     * Assign the DblLinkedList to have the same values as another.
     *
     * @param list The list to copy.
     * @returns The current list.
     */
    DblLinkedList& operator=(DblLinkedList list);

    /**
     * Clear a list.
     */
    void clear();

    /**
     * Swap values with another list.
     *
     * @param list The list to swap with.
     */
    void swap(DblLinkedList& list) noexcept;


    /**
     * Return the number of entries in the list.
     *
     * @returns The number of entries in the list.
     */
    int getCount() const;


    /**
     * Add an entry to the end of the list.
     *
     * @param str The string to add.
     */
    void push_back(const TRString& str);


    /**
     * Insert a new entry into the list.
     *
     * The entry is added in case-insensitive sorted order.
     * Entries matching an existing case-insensitive entry will not be
     * added.
     *
     * @param str The string to add.
     * @returns True if string was added, False otherwise.
     */
    bool insert(const TRString& str);


    /**
     * Remove an entry with the given value.
     *
     * @param str The string to remove.
     * @returns True if string was removed, False otherwise.
     */
    bool remove(const TRString& str);


    /**
     * Set the iterator to point to the head node.
     */
    void resetIterator() const;


    /**
     * Returns true if the iterator is pointing to a valid node.
     *
     * @returns True if the iterator is pointing to a valid node, False
     *   otherwise.
     */
    bool hasMore() const;


    /**
     * Returns the iterator's current node data and advances to the next
     * node.
     *
     * @note Iterator does not move if this is the tail node.
     *
     * @returns An optional class containing the node data.
     */
    std::optional<TRString> next() const;


    /**
     * Execute a function on every element of the list.
     *
     * @param func The function to execute.
     * @returns The return value of the function (type may vary).
     */
    template <typename F> std::optional<bool> process(F func) const
    {
        std::optional<bool> result;

        resetIterator();
        while (hasMore())
        {
            result = func();

            // break early if requested by function
            if (result.has_value())
            {
                return result.value();
            }
        }
        return result;
    }


    // Friend Output
    friend std::ostream& operator<<(std::ostream& ostrm,
                                    const DblLinkedList& list);


    // PRIVATE
  private:
    Node *head, *tail;

    // mutable says that it can change in a const member function
    mutable Node* it;
    int count;


    /**
     * Add a TRString as a new node.
     *
     * If @p prev_node is 'nullptr', the new node is set as head.
     * If @p next_node is 'nullptr', the new node is set as tail.
     *
     * @param str The string to add.
     * @param prev_node The node which should be before the new node
     *   (default: nullptr).
     * @param next_node The node which should be after the new node.
     *   (default: nullptr)
     * @returns A pointer to the new node.
     */
    Node* add_node(const TRString& str, Node* prev_node = nullptr,
                   Node* next_node = nullptr);


    /**
     * Add a node.
     *
     * If @p prev_node is 'nullptr', the new node is set as head.
     * If @p next_node is 'nullptr', the new node is set as tail.
     *
     * @param new_node The node to add.
     * @param prev_node The node which should be before the new node
     *   (default: nullptr).
     * @param next_node The node which should be after the new node.
     *   (default: nullptr)
     * @returns A pointer to the new node.
     */
    Node* add_node(Node* new_node, Node* prev_node = nullptr,
                   Node* next_node = nullptr);


    /**
     * Delete a node.
     *
     * @param node The node to delete.
     */
    void del_node(Node* node);


    /**
     * Link two nodes.
     *
     * @param node_left The first node (default: nullptr).
     * @param node_right The second node (default: nullptr).
     */
    void link_nodes(Node* node_left = nullptr, Node* node_right = nullptr);
};


/**
 * Write the list to a stream.
 *
 * @param ostrm An output stream.
 * @returns The output stream.
 */
std::ostream& operator<<(std::ostream& ostrm, const DblLinkedList& list);


/// DEFINITIONS

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
    Node* old_it = list.it;


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
Node* DblLinkedList::add_node(const TRString& str,
                              Node* prev_node /* = nullptr */,
                              Node* next_node /* = nullptr */)
{
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    return add_node(new Node(str), prev_node, next_node);
}


Node* DblLinkedList::add_node(Node* new_node,
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

#endif
