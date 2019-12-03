////
// Name: Tamara Roberson
// Section: S
// Program Name: Program 5 - LinkedList Merge
//
// Description: A linked list with a merge function.
// The merge function moves all the elements from one sorted list
// into another another sorted list in a stable fashion.
////

#ifndef LKLIST_H
#define LKLIST_H
#include <string>

using namespace std;

// NOLINTNEXTLINE(hicpp-special-member-functions,cppcoreguidelines-special-member-functions)
class LkList
{

    class Node
    {
      public:
        Node() = default;
        explicit Node(int num) : data(num)
        {
        }

        // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
        int data{};

        // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
        Node* next{};

        // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
        Node* prev{};
    };

  public:
    LkList();
    virtual ~LkList();
    LkList(std::initializer_list<int> il);
    LkList(const LkList& other);
    LkList& operator=(LkList other);
    void swap(LkList& list) noexcept;

    bool insert(int num);
    void insert(const initializer_list<int>& il);

    void merge(LkList& src);

    void resetIterator() const;
    bool hasMore() const;
    int next() const;

    int size() const;
    void clear();

    std::string toString() const;

  private:
    Node* head;
    Node* tail;
    mutable Node* it;
    int count;


    /**
     * Add a number as a new node.
     *
     * If @p prev_node is 'nullptr', the new node is set as head.
     * If @p next_node is 'nullptr', the new node is set as tail.
     *
     * @param str The number to add.
     * @param prev_node The node which should be before the new node
     *   (default: nullptr).
     * @param next_node The node which should be after the new node.
     *   (default: nullptr)
     * @returns A pointer to the new node.
     */
    Node* add_node(int num, Node* prev_node = nullptr,
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

ostream& operator<<(ostream& outStr, const LkList& lst);

#endif // LKLIST_H
