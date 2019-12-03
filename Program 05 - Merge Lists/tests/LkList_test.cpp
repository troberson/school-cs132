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

#include <sstream>
#include <string>

#include <catch2/catch.hpp>

SCENARIO("Create an empty list")
{
    GIVEN("An empty list")
    {
        LkList l;

        THEN("Count is 0")
        {
            REQUIRE(0 == l.size());
        }

        THEN("String representation is empty")
        {
            std::ostringstream stream;
            stream << l;
            std::string result = stream.str();

            REQUIRE(result.empty());
        }
    }
}

SCENARIO("Items are added to a list")
{
    GIVEN("An empty list")
    {
        LkList l;

        WHEN("A number is inserted")
        {
            const int num{42};
            l.insert(num);

            THEN("Size is 1")
            {
                REQUIRE(1 == l.size());
            }

            THEN("String representation is the number")
            {
                std::string num_str = std::to_string(num);
                num_str +=
                    "  "; // FIXME: two spaces are always added at the end

                std::ostringstream stream;
                stream << l;
                std::string result = stream.str();

                REQUIRE(num_str == result);
            }
        }

        WHEN("A list of three numbers (1, 2, 3) are added")
        {
            l.insert({1, 2, 3});

            THEN("Size is 3")
            {
                REQUIRE(3 == l.size());
            }

            THEN("String representation is '1  2  3  '")
            {
                std::ostringstream stream;
                stream << l;
                std::string result = stream.str();


                REQUIRE("1  2  3  " == result);
            }
        }
    }
}

SCENARIO("A list is cleared")
{
    GIVEN("A list of three elements")
    {
        LkList l;
        l.insert({1, 2, 3});

        THEN("Size is 3")
        {
            REQUIRE(3 == l.size());
        }

        WHEN("List is cleared")
        {
            l.clear();

            THEN("Size is 0")
            {
                REQUIRE(0 == l.size());
            }
        }
    }
}


SCENARIO("Copy a list (Copy Constructor)")
{
    GIVEN("A list")
    {
        LkList list1;
        list1.insert({1, 2, 3});

        WHEN("A copy is made")
        {
            // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
            LkList list2(list1);

            THEN("The counts are the same")
            {
                REQUIRE(list1.size() == list2.size());
            }

            THEN("The string representations are the same")
            {
                std::ostringstream stream1;
                stream1 << list1;
                const auto result1 = stream1.str();

                std::ostringstream stream2;
                stream2 << list2;
                const auto result2 = stream2.str();

                REQUIRE(result1 == result2);
            }
        }
    }
}

SCENARIO("Copy a list (Assignment Operator)")
{
    GIVEN("Two lists")
    {
        LkList list1;
        list1.insert({1, 2, 3});

        LkList list2{};
        list2.insert({3, 4, 5, 6});

        WHEN("The second list is assigned to the first")
        {
            list2 = list1;

            THEN("The counts are the same")
            {
                REQUIRE(list1.size() == list2.size());
            }

            THEN("The string representations are the same")
            {
                std::ostringstream stream1;
                stream1 << list1;
                const auto result1 = stream1.str();

                std::ostringstream stream2;
                stream2 << list2;
                const auto result2 = stream2.str();

                REQUIRE(result1 == result2);
            }
        }
    }
}
