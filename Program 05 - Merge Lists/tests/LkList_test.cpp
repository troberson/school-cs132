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

#include <iostream>
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
            const auto result = l.toString();
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

                const auto result = l.toString();
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
                const auto result = l.toString();
                REQUIRE("1  2  3  " == result);
            }
        }
    }
}

SCENARIO("A list is cleared")
{
    GIVEN("A list of three elements")
    {
        LkList l{1, 2, 3};

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
        LkList list1{1, 2, 3};

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
                const auto result1 = list1.toString();
                const auto result2 = list2.toString();

                REQUIRE(result1 == result2);
            }
        }
    }
}

SCENARIO("Copy a list (Assignment Operator)")
{
    GIVEN("Two lists")
    {
        LkList list1{1, 2, 3};

        // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
        LkList list2{3, 4, 5, 6};

        WHEN("The second list is assigned to the first")
        {
            list2 = list1;

            THEN("The counts are the same")
            {
                REQUIRE(list1.size() == list2.size());
            }

            THEN("The string representations are the same")
            {
                const auto result1 = list1.toString();
                const auto result2 = list2.toString();

                REQUIRE(result1 == result2);
            }
        }
    }
}

SCENARIO("Merge two sorted lists")
{
    GIVEN("The lists {1,2,5,6,9} and {0,3,4,7,8}")
    {
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
        LkList list1{1, 2, 5, 6, 9};

        // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
        LkList list2{0, 3, 4, 7, 8};

        WHEN("The second list is merged into the first")
        {
            list1.merge(list2);


            THEN("The first list has size 10")
            {
                REQUIRE(10 == list1.size());
            }

            THEN("The second list has size 0")
            {
                REQUIRE(0 == list2.size());
            }

            THEN("The string representation of the first list is the "
                 "numbers 0-9")
            {
                const std::string desired{
                    "0  1  2  3  4  5  6  7  8  9  "};
                const auto result = list1.toString();

                REQUIRE(desired == result);
            }
        }
    }
}

SCENARIO("Merge #1: Source Overlaps Destination")
{
    GIVEN("Two lists")
    {
        LkList list1{0, 10, 20, 30, 40};
        LkList list2{1,  2,  3,  5,  11, 12, 13, 26, 27, 28,
                     29, 34, 35, 36, 37, 44, 45, 46, 47};

        const int size = list1.size() + list2.size();

        WHEN("The two lists are merged")
        {
            list1.merge(list2);

            THEN("The size is the combined size of the two lists")
            {
                REQUIRE(size == list1.size());
            }
        }
    }
}
