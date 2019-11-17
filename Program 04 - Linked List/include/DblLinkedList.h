///
// Name: Tamara Roberson
// Section: S
// Program Name: Program 4 - LinkedList
//
// Description: A doubly-linked list.
///

#ifndef DBLLINKEDLIST_H
#define DBLLINKEDLIST_H
#include <string>


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
    explicit DblLinkedList(const std::string& str);

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
    void push_back(const std::string& str);

    void resetIterator() const;
    bool hasMore() const;
    std::string next() const;

    void testConnections();

  private:
    class Node
    { // fully defined here due to its simplicity
      public:
        Node()
        {
            next = prev = nullptr;
        }
        explicit Node(const std::string& str)
        {
            data = str;
            next = prev = nullptr;
        }

        // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
        std::string data;

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

#endif
