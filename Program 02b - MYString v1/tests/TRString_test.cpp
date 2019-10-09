////
// Name: Tamara Roberson
// Section: S
// Program Name: Program 2B - MYString v1
//
// Description: A dynamically-sized string class.
////


#include <TRString.h>
#include <string_utils.h>

#include <catch2/catch.hpp>

SCENARIO("TRString: Empty string", "[TRString]")
{
    GIVEN("An empty string")
    {
        TRString str;

        THEN("The C String is empty")
        {
            REQUIRE(utils::string::string_is_empty(str.c_str()));
        }

        THEN("The length is 0")
        {
            REQUIRE(0 == str.length());
        }

        THEN("The capacity is 20")
        {
            REQUIRE(20 == str.capacity());
        }
}
}
