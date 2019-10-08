////
// Author:       Tamara Roberson
// Section:      S
// Assignment:   #2a - Comparing CStrings
// Description:  String utilities.
// This file contains two functions:
//   length(str):
//     Calculate the length of a null-terminated C string.
//
//   compareTo(const char* lstr, const char* rstr):
//     Determine the sort order of two null-terminated C strings.
////

#include <iostream> // std::endl, std::cout

using namespace std;

/**
 * Calculate the length of a null-terminated C string.
 *
 * @param str a string
 * @returns the length of the string
 */
int length(const char *str)
{
    // initialize length counter
    int len{0};

    // step through the string until we hit a null
    for (; str[len]; len++);

    // return the calculated length
    return len;
}

/**
 * Determine the sort order of two null-terminated C strings.
 *
 * @note The sort order depends on the encoding, such as ASCII.
 *
 * @param lstr a string
 * @param rstr a string
 * @returns -1 if @p lstr sorts before @p rstr,
 *  1 if @p rstr sorts before @p lstr,
 *  0 if the two strings are the same.
 */
int compareTo(const char *lstr, const char *rstr)
{
    // find the length of the left string
    int lstr_len = length(lstr);

    // walk through the characters of the left string
    for (int i = 0; i < lstr_len; i++)
    {
        // get each character at the same position
        char lchar = lstr[i];
        char rchar = rstr[i];

        // if the two characters are equal, continue to the next
        if (lchar == rchar)
        {
            continue;
        }

        // if the left character is less than right, return -1
        // otherwise, return 1
        return (lchar < rchar) ? -1 : 1;
    }

    // at this point, the two strings are equal
    // up to the length of the left string

    // if the two strings are equal, return 0
    // otherwise, if the right is longer, return -1
    return (lstr_len == length(rstr)) ? 0 : -1;
}


// MAIN
// Test the length() and compareTo() functions.
int main()
{
    char str1[] = "batman";
    char str2[] = "cat";
    char str3[] = "cast";
    char str4[] = "catagory";
    char str5[] = "ZIP";

    cout << "batman " << length(str1) << endl;
    cout << "cat " << length(str2) << endl;

    cout << "comparing " << str1 << " & " << str2 << " "
         << compareTo(str1, str2) << endl;
    cout << "comparing " << str2 << " & " << str1 << " "
         << compareTo(str2, str1) << endl;

    cout << "comparing " << str3 << " & " << str2 << " "
         << compareTo(str3, str2) << endl;
    cout << "comparing " << str2 << " & " << str3 << " "
         << compareTo(str2, str3) << endl;

    cout << "comparing " << str4 << " & " << str2 << " "
         << compareTo(str4, str2) << endl;
    cout << "comparing " << str2 << " & " << str4 << " "
         << compareTo(str2, str4) << endl;

    cout << "comparing " << str2 << " & " << str2 << " "
         << compareTo(str2, str2) << endl;

    cout << "comparing " << str2 << " & " << str5 << " "
         << compareTo(str2, str5) << endl;

    //   system("pause");
    return 0;
}

// OUTPUT:
//
// batman 6
// cat 3
// comparing batman & cat -1
// comparing cat & batman 1
// comparing cast & cat -1
// comparing cat & cast 1
// comparing catagory & cat 1
// comparing cat & catagory -1
// comparing cat & cat 0
// comparing cat & ZIP 1
