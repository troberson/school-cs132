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
#include <iomanip>
#include <iostream>


using namespace std;

int main()
{

    LkList list;
    LkList list2;


    list.insert({0, 10, 20, 30, 40});
    list2.insert({1, 2, 3, 5, 11, 12, 13, 26, 27, 28, 29, 34, 35, 36, 37,
                  44, 45, 46, 47});

    list.merge(list2);

    cout << "Merge #1 (source overlaps destination): \n" << list << endl;
    cout << "List size after merge: " << list.size() << endl;
    cout << endl << endl;

    list.clear();
    list2.clear();
    //------------------------

    list.merge(list2);

    cout << "Merge #2 (empty merge): \n" << list << endl;
    cout << "List size after merge: " << list.size() << endl;
    cout << endl << endl;

    list.clear();
    list2.clear();
    //------------------------

    list2.insert({0, 10, 20, 30, 40});

    list.merge(list2);

    cout << "Merge #3 (into an empty list): \n" << list << endl;
    cout << "List size after merge: " << list.size() << endl;
    cout << endl << endl;

    list.clear();
    list2.clear();
    //------------------------

    //
    // list.insert( { 0, 5, 10, 15, 20, 25, 30, 35, 40} );
    //
    //
    // list.merge(list2);
    //
    // cout << "Merge #4 (from an empty list): \n" << list << endl;
    // cout << "List size after merge: " << list.size() << endl;
    // cout << endl << endl;
    //
    // list.clear();
    // list2.clear();
    //------------------------


    // list.insert( { 40, 47, 54, 61, 68 } );
    //
    // list2.insert( { 0, 3, 6, 9, 12, 15, 18 } );


    // list.merge(list2);

    // cout << "Merge #5(source before destination): \n" << list << endl;
    // cout << "List size after merge: " << list.size() << endl;
    // cout << endl << endl;
    //
    // list.clear();
    // list2.clear();
    //
    //------------------------

    // list.insert( { 10, 17, 21, 28 } );
    //
    // list2.insert( { 50, 53, 56, 59, 62, 65 } );
    //
    // list.merge(list2);
    //
    // cout << "Merge #6(source after destination): \n" << list << endl;
    // cout << "List size after merge: " << list.size() << endl;
    // cout << endl << endl;
    //
    // list.clear();
    // list2.clear();
    //------------------------

    // list.insert( { 0, 9, 18, 27 } );
    //
    // list2.insert( { -6, -4, -2, 0, 2, 4, 6, 8, 10, 12, 16,
    //                 18, 20, 22, 24, 26, 28, 30, 32, 34 } );
    //
    // list.merge( list2 );
    //
    // cout << "Merge #7(source overlaps destination):\n" << list << endl;
    // cout << "List size after merge: " << list.size() << endl;
    // cout << endl << endl;
    //
    // list.clear();
    // list2.clear();
    //------------------------

    // list.insert( { -6, 2, 10, 18, 26, 34 } );
    //
    // list2.insert( { 10, 13, 16, 19, 22, 25 } );
    //
    // list.merge( list2 );
    //
    // cout << "Merge #8(source within destination):\n" << list << endl;
    // cout << "List size after merge: " << list.size() << endl;
    // cout << endl << endl;
    //
    // list.clear();
    // list2.clear();


    //------------------------

    return 0;
}
