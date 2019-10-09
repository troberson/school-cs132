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

SCENARIO("TRString: Copy a string", "[TRString]")
{
    GIVEN("Two strings")
    {
        TRString str1("foo");
        TRString str2("barbaz");

        WHEN("The second string is copied into the first")
        {
            str1.setEqualTo(str2);

            THEN("The objects are different")
            {
                REQUIRE(&str1 != &str2);
            }

            THEN("The two strings have different C string pointers")
            {
                REQUIRE(str1.c_str() != str2.c_str());
            }

            THEN("The two strings have equivalent C strings")
            {
                const int result = utils::string::string_compare(
                    str1.c_str(), str2.c_str());

                REQUIRE(0 == result);
            }

            THEN("The two strings have the same length")
            {
                REQUIRE(str1.length() == str2.length());
            }
        }
    }
}
