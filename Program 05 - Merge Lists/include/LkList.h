#ifndef LKLIST_H
#define LKLIST_H
#include <string>

using namespace std;

class LkList
{

    class Node
    {
      public:
        Node()
        {
            next = prev = nullptr;
        }
        Node(int num)
        {
            data = num;
            next = prev = nullptr;
        }

        int data;
        Node* next;
        Node* prev;
    };

  public:
    LkList();
    virtual ~LkList();
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

  private:
    Node* head;
    Node* tail;
    mutable Node* it;
    int count;
};

ostream& operator<<(ostream& outStr, LkList& lst);

#endif // LKLIST_H
