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

    void testConnections();


    // Friend Output
    friend std::ostream& operator<<(std::ostream& ostrm,
                                    const DblLinkedList& list);

  private:
    class Node
    { // fully defined here due to its simplicity
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

#endif
