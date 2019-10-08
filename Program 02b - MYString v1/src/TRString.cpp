////
// Name: Tamara Roberson
// Section: S
// Program Name: Program 2B - MYString v1
//
// Description: A dynamically-sized string class.
////


#include <iostream>

#include <TRString.h>

TRString::TRString()
{
    std::cout << "\tinside default constructor" << std::endl;
}

TRString::TRString(const char* ptr)
{
    std::cout << "\tconstructing from cstring: " << ptr << std::endl;
}
