///
// Name: Tamara Roberson
// Section: S
// Program Name: Program 7 - LinkedList Template
//
// Description: A doubly-linked ordered list which holds TRStrings.
// Elements can be added to the list with insert(), which will add them
// in case-insensitive order. If a match already exists, the element will
// not be added. The list may be traversed with a rudamentary iterator.
///

#ifndef DBLLINKEDLIST_H
#define DBLLINKEDLIST_H

#include <optional>
#include <string> // see FIXME in operator<< overload

template <typename T> class Node
{
  public:
    Node()
    {
        next = prev = nullptr;
    }

    explicit Node(T data) : data(data)
    {
        next = prev = nullptr;
    }

    // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
    T data;

    // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
    Node* next;

    // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
    Node* prev;
};


// NOLINTNEXTLINE(hicpp-special-member-functions,cppcoreguidelines-special-member-functions)
template <typename T> class DblLinkedList
{
  public:
    /**
     * Create a new linked list.
     */
    DblLinkedList<T>();

    /**
     * Create a new linked list that includes the given element.
     *
     * @param str An element for the list.
     */
    explicit DblLinkedList<T>(const T& data);


    /**
     * Copy an existing DblLinkedList.
     *
     * @param list The list to copy.
     */
    DblLinkedList<T>(const DblLinkedList<T>& list);


    /**
     * Delete a DblLinkedList.
     */
    ~DblLinkedList<T>();


    /**
     * Assign the DblLinkedList to have the same values as another.
     *
     * @param list The list to copy.
     * @returns The current list.
     */
    DblLinkedList<T>& operator=(DblLinkedList<T> list);

    /**
     * Clear a list.
     */
    void clear();

    /**
     * Swap values with another list.
     *
     * @param list The list to swap with.
     */
    void swap(DblLinkedList<T>& list) noexcept;


    /**
     * Return the number of entries in the list.
     *
     * @returns The number of entries in the list.
     */
    int getCount() const;


    /**
     * Return the number of entries in the list.
     *
     * @returns The number of entries in the list.
     */
    int size() const;


    /**
     * Add an entry to the end of the list.
     *
     * @param data The data to add.
     */
    void push_back(const T& data);


    /**
     * Insert a new entry into the list.
     *
     * The entry is added in case-insensitive sorted order.
     * Entries matching an existing case-insensitive entry will not be
     * added.
     *
     * @param data The data to add.
     * @returns True if data was added, False otherwise.
     */
    bool insert(const T& data);


    /**
     * Remove an entry with the given value.
     *
     * @param data The data to remove.
     * @returns True if data was removed, False otherwise.
     */
    bool remove(const T& data);


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
    std::optional<T> next() const;


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


    // PRIVATE
  private:
    Node<T>* head{};
    Node<T>* tail{};

    // mutable says that it can change in a const member function
    mutable Node<T>* it{};
    int count{0};


    /**
     * Add data as a new node.
     *
     * If @p prev_node is 'nullptr', the new node is set as head.
     * If @p next_node is 'nullptr', the new node is set as tail.
     *
     * @param data The data to add.
     * @param prev_node The node which should be before the new node
     *   (default: nullptr).
     * @param next_node The node which should be after the new node.
     *   (default: nullptr)
     * @returns A pointer to the new node.
     */
    Node<T>* add_node(const T& data, Node<T>* prev_node = nullptr,
                      Node<T>* next_node = nullptr);


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
    Node<T>* add_node(Node<T>* new_node, Node<T>* prev_node = nullptr,
                      Node<T>* next_node = nullptr);


    /**
     * Delete a node.
     *
     * @param node The node to delete.
     */
    void del_node(Node<T>* node);


    /**
     * Link two nodes.
     *
     * @param node_left The first node (default: nullptr).
     * @param node_right The second node (default: nullptr).
     */
    void link_nodes(Node<T>* node_left = nullptr,
                    Node<T>* node_right = nullptr);
};


/// DEFINITIONS

/**
 * Write the list to a stream.
 *
 * @param ostrm An output stream.
 * @returns The output stream.
 */

template <typename T>
std::ostream& operator<<(std::ostream& ostrm, const DblLinkedList<T>& list)
{
    // walk through list, writing elements to the ostream
    list.process([&]() -> std::optional<bool> {
        const T data = list.next().value();
        ostrm << data;

        // add a space between words
        if (list.hasMore())
        {
            // FIXME: can't seem to use simple char, compilation fails
            // with: "error: invalid operands to binary expression
            // ('std::ostream' (aka 'basic_ostream<char>') and 'char')"
            // ostrm << ' ';
            ostrm << std::string(" ");
        }

        return {};
    });

    // return the ostream
    return ostrm;
}


template <typename T> DblLinkedList<T>::DblLinkedList() = default;

template <typename T>
DblLinkedList<T>::DblLinkedList(const T& data) : DblLinkedList<T>()
{
    push_back(data);
    resetIterator();
}

template <typename T>
DblLinkedList<T>::DblLinkedList(const DblLinkedList<T>& list)
    : DblLinkedList<T>()
{
    list.process([&list, this]() -> std::optional<bool> {
        this->push_back(list.next().value());
        return {};
    });
}

template <typename T> DblLinkedList<T>::~DblLinkedList()
{
    clear();
}

template <typename T> void DblLinkedList<T>::clear()
{
    while (this->count > 0)
    {
        del_node(this->head);
    }
}


template <typename T>
DblLinkedList<T>& DblLinkedList<T>::operator=(DblLinkedList<T> list)
{
    // copy-and-swap does not require a self-assignment check.

    list.swap(*this);
    return *this;
}

template <typename T>
void DblLinkedList<T>::swap(DblLinkedList<T>& list) noexcept
{
    // unqualified "swap" allows for overloads to step in with ADL
    using std::swap;
    swap(list.head, this->head);
    swap(list.tail, this->tail);
    swap(list.count, this->count);
}

template <typename T> int DblLinkedList<T>::getCount() const
{
    return this->count;
}

template <typename T> int DblLinkedList<T>::size() const
{
    return getCount();
}

template <typename T> void DblLinkedList<T>::push_back(const T& data)
{
    Node<T>* new_node = add_node(data, this->tail, nullptr);

    // if there is no head, set this new node to the head
    if (this->head == nullptr)
    {
        this->head = new_node;
    }
}

template <typename T> bool DblLinkedList<T>::insert(const T& data)
{
    // if there are no nodes in the list, add new new entry
    if (this->count == 0)
    {
        push_back(data);
        return true;
    }

    // if new entry is smaller than current head,
    // make the new entry the new head
    if (data < this->head->data)
    {
        add_node(data, nullptr, this->head);
        return true;
    }

    // walk through the list, looking for an entry that is larger
    // we'll put the new entry right before it or fail if we find
    // an equivalent entry already exists.
    auto result = this->process([&data, this]() -> std::optional<bool> {
        auto cur_ptr = this->it;
        auto cur_val = next().value();

        // if we reach an entry whose value is equal to the new entry,
        // keep the old entry and do not add the new entry, return failure.
        if (cur_val == data)
        {
            return false;
        }

        // if we reach an entry that has a larger value than the new entry,
        // then insert it before that entry
        if (cur_val > data)
        {
            add_node(data, cur_ptr->prev, cur_ptr);
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
    push_back(data);
    return true;
}


template <typename T> bool DblLinkedList<T>::remove(const T& data)
{
    // we can't remove anything from an empty list
    if (this->count == 0)
    {
        return false;
    }

    // walk through the list, looking for a match
    auto result = this->process([&data, this]() -> std::optional<bool> {
        auto cur_ptr = this->it;
        auto cur_val = next().value();

        // found a match, delete it and return success
        if (cur_val == data)
        {
            del_node(cur_ptr);
            return true;
        }

        return {};
    });

    // return true on success, false otherwise
    return result.has_value() && result.value();
}

template <typename T> void DblLinkedList<T>::resetIterator() const
{
    this->it = head;
}

template <typename T> bool DblLinkedList<T>::hasMore() const
{
    return (this->it != nullptr);
}

template <typename T> std::optional<T> DblLinkedList<T>::next() const
{
    if (!hasMore())
    {
        return {};
    }

    const Node<T>* old_it = this->it;
    this->it = old_it->next;

    return old_it->data;
}


// PRIVATE FUNCTIONS
template <typename T>
Node<T>* DblLinkedList<T>::add_node(const T& data,
                                    Node<T>* prev_node /* = nullptr */,
                                    Node<T>* next_node /* = nullptr */)
{
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    return add_node(new Node(data), prev_node, next_node);
}

template <typename T>
Node<T>* DblLinkedList<T>::add_node(Node<T>* new_node,
                                    Node<T>* prev_node /* = nullptr */,
                                    Node<T>* next_node /* = nullptr */)
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

template <typename T>
void DblLinkedList<T>::link_nodes(Node<T>* node_left /* = nullptr */,
                                  Node<T>* node_right /* = nullptr */)
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

template <typename T> void DblLinkedList<T>::del_node(Node<T>* node)
{
    // Can't delete nothing
    if (node == nullptr)
    {
        return;
    }

    // Save the previous and next pointers
    Node<T>* node_prev = node->prev;
    Node<T>* node_next = node->next;

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
