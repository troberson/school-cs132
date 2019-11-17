///
// Name: Tamara Roberson
// Section: S
// Program Name: Program 4 - LinkedList
//
// Description: A doubly-linked list.
///

#include <DblLinkedList.h>
#include <string_utils.h>

#include <sstream>
#include <string>

#include <catch2/catch.hpp>

SCENARIO("DblLinkedList: Create an empty list")
{
    GIVEN("A new empty list")
    {
        DblLinkedList list;

        THEN("The count is 0")
        {
            REQUIRE(0 == list.getCount());
        }
    }

    GIVEN("A new list with a starting string")
    {
        std::string str = "test";
        DblLinkedList list(str);

        THEN("The count is 1")
        {
            REQUIRE(1 == list.getCount());
        }
    }
}


SCENARIO("Add strings to a list")
{
    GIVEN("An empty list")
    {
        DblLinkedList list;

        WHEN("A string 'hello' is added")
        {
            std::string hello = "hello";
            list.push_back(hello);

            THEN("The count is 1")
            {
                REQUIRE(1 == list.getCount());
            }

            AND_WHEN("The string 'world' is added")
            {
                std::string world = "world";
                list.push_back(world);

                THEN("The count is 2")
                {
                    REQUIRE(2 == list.getCount());
                }

                AND_THEN("The string representation is 'hello world'")
                {
                    std::ostringstream stream;
                    stream << list;
                    const char* result = stream.str().c_str();

                    REQUIRE(0 == utils::string::string_compare(
                                     result, "hello world"));
                }
            }
        }
    }
}