////
// Name: Tamara Roberson
// Section: S
// Program Name: Program 6 - Tree Data Structure
//
// Description: A simple binary search tree for integers.
// Numbers can be inserted into the tree. A string representation of the
// elements in the tree can also be produced. Debug statements printed to
// the console are intentional and part of the assignement.
////

#include <sstream>

class Tree
{
    class Node
    {
      public:
        explicit Node(int val) : data(val)
        {
        }

        // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
        int data{};

        // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
        Node* left{};

        // NOLINTNEXTLINE(misc-non-private-member-variables-in-classes)
        Node* right{};
    };

  public:
    /**
     * Construct a new Tree.
     */
    Tree();

    /**
     * Insert a number into the tree.
     *
     * Duplicates are not added. Returns false if the number already
     * exists.
     *
     * @param newVal The value to add to the tree.
     * @returns True if the number was added, false otherwise.
     */
    bool insert(int newVal);


    /**
     * Write a string representation of the Tree to an output stream
     *
     * @param str The stream to write to.
     * @param tree The Tree to display.
     * @returns A reference to the stream.
     */
    friend std::ostream& operator<<(std::ostream& str, const Tree& tree);

  private:
    // recursively print a node and its children
    void print(std::ostream& ostr, Node* curNode) const;

    Node* root{};
    int count{};
};