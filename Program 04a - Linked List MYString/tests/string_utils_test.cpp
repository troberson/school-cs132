////
// Name: Tamara Roberson
// Section: S
// Program Name: Program 4A - Linked List MYString
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


SCENARIO("string_utils: Concatenate two strings", "[string_utils]")
{
    GIVEN("'bat' and 'man'")
    {
        const char* bat = "bat";
        const char* man = "man";

        WHEN("They are concatenated")
        {
            const char* batman = string_concat(bat, man);

            THEN("They form 'batman'")
            {
                int result = string_compare(batman, "batman");
                REQUIRE(0 == result);
            }
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

        THEN("'cat' sorts before 'ZIP'")
        {
            REQUIRE(0 > string_compare("cat", "ZIP"));
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


SCENARIO("string_utils: Get the last character in a string")
{
    GIVEN("An empty string")
    {
        const char* empty = "";

        THEN("The last character should be the null character")
        {
            REQUIRE('\0' == get_last_char(empty));
        }
    }

    GIVEN("The string 'hello'")
    {
        const char* hello = "hello";

        THEN("The last character should be 'o'")
        {
            REQUIRE('o' == get_last_char(hello));
        }
    }
}


SCENARIO("string_utils: Remove trailing punctuation")
{
    GIVEN("An empty string")
    {
        const char* empty = "";

        THEN("Removing the last character returns an empty string")
        {
            const char* result = remove_punct(empty);
            REQUIRE(string_is_empty(result));
        }
    }

    GIVEN("The string 'testing'")
    {
        const char* testing = "testing";

        THEN("Removing punctuation returns a new copy of the same string")
        {
            const char* testing2 = string_copy(testing);
            const char* result = remove_punct(testing);
            REQUIRE(0 == string_compare(result, testing2));
        }
    }

    GIVEN("The string 'Hello, World!''")
    {
        const char* hello = "Hello, World!";

        THEN("Removing the punctuation returns the string "
             "'Hello, World'")
        {
            const char* hello2 = "Hello, World";
            const char* result = remove_punct(hello);
            REQUIRE(0 == string_compare(result, hello2));
        }
    }
}

} // end namespace utils::string
