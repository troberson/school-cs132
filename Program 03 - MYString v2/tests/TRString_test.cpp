////
// Name: Tamara Roberson
// Section: S
// Program Name: Program 2B - MYString v1
//
// Description: A dynamically-sized string class.
////


#include <TRString.h>
#include <string_utils.h>

#include <sstream>
#include <stdexcept>

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

SCENARIO("TRString: Set a string equal to another string", "[TRString]")
{
    GIVEN("Two strings")
    {
        TRString str1("foo");
        TRString str2("barbaz");

        WHEN("The second string is copied into the first")
        {
            str1 = str2;

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

SCENARIO("TRString: Copy another string", "[TRString]")
{
    GIVEN("A string")
    {
        TRString str1("foo");

        WHEN("A second string is created from the first")
        {
            TRString str2 = str1;

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

SCENARIO("TRString: Capacity needs to be increased", "[TRString]")
{
    GIVEN("A short string")
    {
        TRString word("hello");

        THEN("The capacity is 20")
        {
            REQUIRE(word.capacity() == 20);
        }
    }

    GIVEN("A long string")
    {
        TRString alpha("abcdefghijklmnopqrstuvwxyz");

        THEN("The capacity is 40")
        {
            REQUIRE(alpha.capacity() == 40);
        }
    }
}

SCENARIO("TRString: Get the character at position (safe)", "[TRString]")
{
    GIVEN("A word")
    {
        TRString word("word");

        WHEN("A character in bounds is requested")
        {
            THEN("The function returns the character")
            {
                REQUIRE(word.at(2) == 'r');
            }
        }

        WHEN("A character out of bounds is requested")
        {
            THEN("The function throws an out-of-bounds exception")
            {
                REQUIRE_THROWS_AS(word.at(10), std::out_of_range);
            }
        }
    }
}

SCENARIO("TRString: Get the character at position (unsafe)", "[TRString]")
{
    GIVEN("A word")
    {
        TRString word("word");

        WHEN("A character in bounds is requested")
        {
            THEN("The function returns the character")
            {
                REQUIRE(word[2] == 'r');
            }
        }

        WHEN("A character out of bounds is requested")
        {
            THEN("The function does not throw an exception")
            {
                REQUIRE_NOTHROW(word[10]);
            }
        }
    }
}

SCENARIO("TRString: Set the character at position", "[TRString]")
{
    GIVEN("A word")
    {
        TRString word("test");

        WHEN("A character in changed")
        {
            word[2] = 'x';

            THEN("A new word is formed")
            {
                int result = utils::string::string_compare(word.c_str(), "text");
                REQUIRE(0 == result);
            }
        }

        WHEN("All characters are set to the first")
        {
            for (int i{1}; i < word.length(); i++)
            {
                word[i] = word[0];
            }

            THEN("All the characters are the same")
            {
                int result = utils::string::string_compare(word.c_str(), "tttt");
                REQUIRE(0 == result);
            }
        }
   }
}



SCENARIO("TRString: Sorting", "[TRString]")
{
    GIVEN("'batman', 'cast', 'cat', 'category', and 'ZIP'")
    {
        TRString batman("batman");
        TRString cast("cast");
        TRString cat("cat");
        TRString category("category");
        TRString zip("ZIP");

        THEN("'batman' sorts before 'cat'")
        {
            REQUIRE(batman < cat);
        }

        THEN("'cat' sorts after 'batman'")
        {
            REQUIRE(cat > batman);
        }

        THEN("'cast' sorts before 'cat'")
        {
            REQUIRE(cast < cat);
        }

        THEN("'cat' sorts after 'cast'")
        {
            REQUIRE(cat > cast);
        }

        THEN("'category' sorts after 'cat'")
        {
            REQUIRE(category > cat);
        }

        THEN("'cat' sorts before 'category'")
        {
            REQUIRE(cat < category);
        }

        THEN("'cat' is the same as 'cat'")
        {
            REQUIRE(cat == cat);
        }

        THEN("'cat' sorts after 'ZIP'")
        {
            REQUIRE(cat > zip);
        }
    }
}

SCENARIO("TRString: Read the words from a stream", "[TRString]")
{
    GIVEN("A string object and a string stream with three words")
    {
        TRString str;
        std::stringstream stream("foo bar baz");

        WHEN("Read the string stream into the string object")
        {
            stream >> str;

            THEN("The string holds the first word")
            {
                int result =
                    utils::string::string_compare(str.c_str(), "foo");

                REQUIRE(0 == result);

                THEN("After reading again, the string holds the "
                     "second word")
                {
                    stream >> str;

                    int result = utils::string::string_compare(
                        str.c_str(), "bar");

                    REQUIRE(0 == result);

                    THEN("After reading again, the string holds the "
                         "third word")
                    {
                        stream >> str;

                        int result = utils::string::string_compare(
                            str.c_str(), "baz");

                        REQUIRE(0 == result);

                        THEN("Attempting to read a fourth time "
                             "stream is no longer good")
                        {
                            stream >> str;

                            REQUIRE(!stream);

                            THEN("String remains unchanged")
                            {
                                int result =
                                    utils::string::string_compare(
                                        str.c_str(), "baz");

                                REQUIRE(0 == result);
                            } // end THEN
                        } // end THEN
                    } // end THEN
                } // end THEN
            } // end THEN
        } // end WHEN
    } // end GIVEN
} // end SCENARIO


SCENARIO("TRString: Write string to a stream", "[TRString]")
{
    GIVEN("A string object and an output stream")
    {
        TRString str("foo");
        std::stringstream stream;

        WHEN("String object is written to the stream")
        {
            stream << str;

            THEN("Stream contains the contents of string")
            {
                int result = utils::string::string_compare(
                    stream.str().c_str(), str.c_str());

                REQUIRE(0 == result);
            }
        }
    }
}

SCENARIO("TRString: Concatenate two strings", "[TRString]")
{
    GIVEN("'bat' and 'man'")
    {
        TRString bat("bat");
        TRString man("man");

        WHEN("They are concatenated")
        {
            TRString batman = bat + man;

            THEN("They form 'batman'")
            {
                REQUIRE(batman == TRString("batman"));
            }
        }
    }
}


SCENARIO("TRString: Objects are counted", "[TRString]")
{
    GIVEN("Five strings")
    {
        const int old_created_count = TRString::getCreatedCount();

        // block scope so strings will be deleted
        // and we can check their counts again
        {
            TRString str1;
            TRString str2;
            TRString str3;
            TRString str4;
            TRString str5;

            THEN("The created count increases by 5")
            {
                REQUIRE(old_created_count + 5 == TRString::getCreatedCount());
            }

            THEN("The current count is 5")
            {

                REQUIRE(5 == TRString::getCurrentCount());
            }
        }

        WHEN("They are deleted")
        {
            THEN("The created count is unchanged")
            {
                // std::cout << "Number created: " << TRString::getCreatedCount() << "\n";
                REQUIRE(old_created_count + 5 == TRString::getCreatedCount());
            }

            THEN("The current count is 0")
            {
                REQUIRE(0 == TRString::getCurrentCount());
            }
        }
    }
}
