///
// Name: Tamara Roberson
// Section: S
// Program Name: Program 4 - LinkedList
//
// Description: A doubly-linked list.
///

#include <DblLinkedList.h>
#include <TRString.h>
#include <string_utils.h>

#include <sstream>

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
        const TRString str("test");
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
            TRString hello("hello");
            list.push_back(hello);

            THEN("The count is 1")
            {
                REQUIRE(1 == list.getCount());
            }

            AND_WHEN("The string 'world' is added")
            {
                TRString world("world");
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


SCENARIO("Copy a list (Copy Constructor)")
{
    GIVEN("A list")
    {
        DblLinkedList list1(TRString("a"));
        list1.push_back(TRString("b"));
        list1.push_back(TRString("c"));

        WHEN("A copy is made")
        {
            DblLinkedList list2(list1);

            THEN("The counts are the same")
            {
                REQUIRE(list1.getCount() == list2.getCount());
            }

            THEN("The string representations are the same")
            {
                std::ostringstream stream1;
                stream1 << list1;
                const char* result1 = stream1.str().c_str();

                std::ostringstream stream2;
                stream2 << list2;
                const char* result2 = stream2.str().c_str();

                REQUIRE(0 ==
                        utils::string::string_compare(result1, result2));
            }
        }
    }
}

SCENARIO("Copy a list (Assignment Operator)")
{
    GIVEN("Two lists")
    {
        DblLinkedList list1(TRString("a"));
        list1.push_back(TRString("b"));
        list1.push_back(TRString("c"));

        DblLinkedList list2(TRString("d"));
        list2.push_back(TRString("e"));
        list2.push_back(TRString("f"));
        list2.push_back(TRString("g"));

        WHEN("The second list is assigned to the first")
        {
            list2 = list1;

            THEN("The counts are the same")
            {
                REQUIRE(list1.getCount() == list2.getCount());
            }

            THEN("The string representations are the same")
            {
                std::ostringstream stream1;
                stream1 << list1;
                const char* result1 = stream1.str().c_str();

                std::ostringstream stream2;
                stream2 << list2;
                const char* result2 = stream2.str().c_str();

                REQUIRE(0 ==
                        utils::string::string_compare(result1, result2));
            }
        }
    }
}