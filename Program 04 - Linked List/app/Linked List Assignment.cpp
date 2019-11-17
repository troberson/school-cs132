#include <DblLinkedList.h>
#include <TRString.h>

#include <iostream>

int main()
{
    DblLinkedList list;
    list.push_back(TRString("1")); // insert back...into empty list
    list.push_back(TRString("2")); // insert back
    list.push_back(TRString("3"));
    list.push_back(TRString("4"));
    list.push_back(TRString("5"));
    list.push_back(TRString("6"));
    list.push_back(TRString("7"));
    list.push_back(TRString("8"));
    list.push_back(TRString("9"));
    list.push_back(TRString("10"));

    list.resetIterator();
    while (list.hasMore())
    {
        std::cout << list.next().value() << std::endl;
    }

    list.testConnections();

    return 0;
}
