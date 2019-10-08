////
// Name: Tamara Roberson
// Section: S
// Program Name: Program 2B - MYString v1
//
// Description: A dynamically-sized string class.
////


#include <iostream>

#include <TRString.h>


int main()
{
    std::cout << "Call Default Constructor:" << std::endl;
    TRString str1 = TRString();

    std::cout << "Call Constructor with string:" << std::endl;
    TRString str2 = TRString("foo");

    return 0;
}
