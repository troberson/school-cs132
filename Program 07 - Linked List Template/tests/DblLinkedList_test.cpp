////
// Name: Tamara Roberson
// Section: S
// Program Name: Program 7 - LinkedList Template
//
// Description: A doubly-linked ordered list which holds TRStrings.
// Elements can be added to the list with insert(), which will add them
// in case-insensitive order. If a match already exists, the element will
// not be added. The list may be traversed with a rudamentary iterator.
////

#include <DblLinkedList.h>
#include <TRString.h>
#include <string_utils.h>

#include <sstream>

#include <catch2/catch.hpp>

SCENARIO("DblLinkedList: Create an empty list")
{
    GIVEN("A new empty list")
    {
        DblLinkedList<int> list;

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
        DblLinkedList<TRString> list;

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
            // NOLINTNEXTLINE(performance-unnecessary-copy-initialization)
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


SCENARIO("Insert list entries in sorted order")
{
    GIVEN("An empty list")
    {
        DblLinkedList<TRString> list;

        WHEN("The words 'cat', 'ant', 'dog', and 'bat' are added")
        {
            list.insert(TRString("cat"));
            list.insert(TRString("ant"));
            list.insert(TRString("dog"));
            list.insert(TRString("bat"));

            THEN("The string representation is 'ant bat cat dog'")
            {
                std::ostringstream stream;
                stream << list;
                const char* result = stream.str().c_str();

                const char* expected = "ant bat cat dog";

                REQUIRE(0 ==
                        utils::string::string_compare(result, expected));
            }

            AND_THEN("The count is 4")
            {
                REQUIRE(4 == list.getCount());
            }


            AND_WHEN("The word 'BaT' is attempted to be added")
            {
                bool result = list.insert(TRString("BaT"));

                THEN("The attempt fails")
                {
                    REQUIRE(!result);
                }
            }
        }
    }
}


SCENARIO("An entry is removed from a list")
{
    GIVEN("A list of 'ant', 'bat', 'cat', 'dog'")
    {
        DblLinkedList<TRString> list;
        list.insert(TRString("cat"));
        list.insert(TRString("ant"));
        list.insert(TRString("dog"));
        list.insert(TRString("bat"));

        THEN("The count is 4")
        {
            REQUIRE(4 == list.getCount());
        }

        WHEN("'eagle' is removed")
        {
            bool result = list.remove(TRString("eagle"));

            THEN("The attempt fails")
            {
                REQUIRE(!result);
            }
        }

        AND_WHEN("'CAT' is removed")
        {
            list.remove(TRString("CAT"));

            THEN("The count is 3")
            {
                REQUIRE(3 == list.getCount());
            }

            AND_THEN("The string representation is 'ant bat dog'")
            {
                std::ostringstream stream;
                stream << list;
                const char* result = stream.str().c_str();

                const char* expected = "ant bat dog";

                REQUIRE(0 ==
                        utils::string::string_compare(result, expected));
            }
        }
    }
}
