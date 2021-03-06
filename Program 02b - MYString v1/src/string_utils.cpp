///
// Name: Tamara Roberson
// Section: S
// Program Name: Program 2B - MYString v1
//
// Description: A dynamically-sized string class.
////

// NOTE: The requirements of this program require the use of raw
// pointers and pointer arithmetic for educational purposes.
// Specific clang-tidy rules are disabled where necessary.

#include <string_utils.h>

#include <stdexcept>


namespace utils::string
{

bool string_is_empty(const char* str)
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    return '\0' == str[0];
}

int string_length(const char* str)
{
    // initialize length counter
    int len{0};

    // step through the string until we hit a null
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    for (; str[len] != '\0'; len++) {};

    // return the calculated length
    return len;
}

char* string_copy(const char* str)
{
    // get the length of the string
    int len = string_length(str);

    // create a new string
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    char* new_str = new char[len + 1];

    // copy all elements of the given string into the new one
    for (int i = 0; i <= len; i++)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        new_str[i] = str[i];
    }

    // return new string
    return new_str;
}

char get_char_at(const char* str, const int index)
{
    if (index < 0 || index > string_length(str))
    {
        throw std::out_of_range("Invalid index");
    }

    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    return str[index];
}


int string_compare(const char* lstr, const char* rstr)
{
    char lchar;
    char rchar;

    do
    {
        // get the character under the lstr pointer and advance
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        lchar = *lstr++;

        // get the character under the rstr pointer and advance
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        rchar = *rstr++;

        // if we reach the end of lstr,
        // return the difference between lchar and null (usually 0)
        if (lchar == '\0')
        {
            return lchar - rchar;
        }

    // continue while characters are the same
    } while (lchar == rchar);

    // return the difference between the last characters
    return lchar - rchar;
}

} // end namespace utils::string
