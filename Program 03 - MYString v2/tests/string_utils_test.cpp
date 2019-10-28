////
// Name: Tamara Roberson
// Section: S
// Program Name: Program 2B - MYString v1
//
// Description: A dynamically-sized string class.
////


#include <string_utils.h>

#include <memory>
#include <stdexcept>

#include <catch2/catch.hpp>

namespace utils::string
{

SCENARIO("string_utils: Empty string", "[string_utils]")
{
    GIVEN("An empty string")
    {
        const char* str = "";

        THEN("String is empty")
        {
            REQUIRE(string_is_empty(str));
        }

        THEN("String length is 0")
        {
            REQUIRE(0 == string_length(str));
        }

        THEN("Character at position 0 is null")
        {
            REQUIRE('\0' == get_char_at(str, 0));
        }

        THEN("Attempting to get the character at index -1 fails")
        {
            REQUIRE_THROWS_AS(get_char_at(str, -1), std::out_of_range);
        }

        THEN("Attempting to get the character at index 1 fails")
        {
            REQUIRE_THROWS_AS(get_char_at(str, 1), std::out_of_range);
        }
    }
}

SCENARIO("string_utils: Short string", "[string_utils]")
{
    GIVEN("A short string")
    {
        const char* str = "cat";

        THEN("String is not empty")
        {
            REQUIRE(!string_is_empty(str));
        }

        THEN("String length is 3")
        {
            REQUIRE(3 == string_length(str));
        }

        THEN("Character at position 0 is c")
        {
            REQUIRE('c' == get_char_at(str, 0));
        }

        THEN("Attempting to get the character at index 4 fails")
        {
            REQUIRE_THROWS_AS(get_char_at(str, 4), std::out_of_range);
        }
    }
}


SCENARIO("string_utils: Sorting", "[string_utils]")
{
    GIVEN("'batman', 'cast', 'cat', 'category', and 'ZIP'")
    {
        THEN("'batman' sorts before 'cat'")
        {
            REQUIRE(0 > string_compare("batman", "cat"));
        }

        THEN("'cat' sorts after 'batman'")
        {
            REQUIRE(0 < string_compare("cat", "batman"));
        }

        THEN("'cast' sorts before 'cat'")
        {
            REQUIRE(0 > string_compare("cast", "cat"));
        }

        THEN("'cat' sorts after 'cast'")
        {
            REQUIRE(0 < string_compare("cat", "cast"));
        }

        THEN("'category' sorts after 'cat'")
        {
            REQUIRE(0 < string_compare("category", "cat"));
        }

        THEN("'cat' sorts after 'category'")
        {
            REQUIRE(0 > string_compare("cat", "category"));
        }

        THEN("'cat' is the same as 'cat'")
        {
            REQUIRE(0 == string_compare("cat", "cat"));
        }

        THEN("'cat' sorts after 'ZIP'")
        {
            REQUIRE(0 < string_compare("cat", "ZIP"));
        }
    }
}


SCENARIO("string_utils: Copy a string")
{
    GIVEN("One string")
    {
        const char* str1 = "test";

        WHEN("A new copy is created")
        {
            const char* str2 = string_copy(str1);

            THEN("The two pointers are different")
            {
                REQUIRE(str1 != str2);
            }

            THEN("The contents of the strings are the same")
            {
                REQUIRE(0 == string_compare(str1, str2));
            }
        }
    }
}

} // end namespace utils::string
