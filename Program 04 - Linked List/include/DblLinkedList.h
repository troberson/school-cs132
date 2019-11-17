///
// Name: Tamara Roberson
// Section: S
// Program Name: Program 4 - LinkedList
//
// Description: A doubly-linked list.
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
    int getCount();


    /**
     * Add an entry to the end of the list.
     *
     * @param str The string to add.
     */
    void push_back(const TRString& str);


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
};


/**
 * Write the list to a stream.
 *
 * @param ostrm An output stream.
 * @returns The output stream.
 */
std::ostream& operator<<(std::ostream& ostrm, const DblLinkedList& list);

#endif
