///
// Name: Tamara Roberson
// Section: S
// Program Name: Program 4A - LinkedList MYString
//
// Description: String utilities.
// These are a collection of functions for working with C-style string
// (null-terminated char arrays). Primarily, these are educational
// re-implementations of standard C string functions such as strcmp()
// and strlen().
////

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

namespace utils::string
{

/**
 * Check if a C string is empty.
 *
 * @param str Pointer to a C string.
 * @returns True if the string is empty, false otherwise.
 */
[[nodiscard]] bool string_is_empty(const char* str);


/**
 * Calculate the length of a C string.
 *
 * @param str Pointer to a C string
 * @returns The length of the string
 */
[[nodiscard]] int string_length(const char* str);


/**
 * Copy a C string.
 *
 * @note New copy is dynamically-allocated,
 *   don't forget to delete it.
 *
 * @param str Pointer to a C string.
 * @returns Pointer to a new copy of the string.
 */
[[nodiscard]] char* string_copy(const char* str);


/**
 * Copy a C string with a fixed size output.
 *
 * @note New copy is dynamically-allocated,
 *   don't forget to delete it.
 *
 * @param str Pointer to a C string.
 * @param len Length of the output string.
 * @returns Pointer to a new copy of the string.
 */
[[nodiscard]] char* string_copy(const char* str, int len);


/**
 * Copy a C string to an existing string.
 *
 * @note New copy is dynamically-allocated,
 *   don't forget to delete it.
 *
 * @param str Pointer to a C string.
 * @param len Length of the output string.
 * @param[out] out_str An existing string to copy into.
 */
void string_copy(const char* str, int len, char* out_str);


/**
 * Returns the concatenation of two strings.
 *
 * @param lstr A string.
 * @param rstr A string.
 * @returns Pointer to a new string which is the concatenation of
 *   @p lstr and @p rstr.
 */
char* string_concat(const char* lstr, const char* rstr);


/**
 * Returns the character at the given index of the string.
 *
 * @param str A string.
 * @param index Index of a character in the string.
 * @throw std::out_of_range If index is invalid.
 * @returns The character at the given index.
 */
[[nodiscard]] char get_char_at(const char* str, int index);


/**
 * Returns the last character in the string.
 *
 * @note Returns the null character if string is empty.
 *
 * @param str A string.
 * @returns The last character in the string.
 */

[[nodiscard]] char get_last_char(const char* str);


/**
 * Returns the string without a trailing punctuation mark.
 *
 * @note Punctuation is defined by the ispunct() library function.
 *
 * @note Only removes a single trailing punctuation mark.
 *
 * @param str A string.
 * @returns The string without a trailing punctuation mark.
 */
[[nodiscard]] char* remove_punct(const char* str);


/**
 * Compare the sort order of two strings
 *
 * @note The sort order depends on the encoding, such as ASCII.
 *
 * @param lstr A string
 * @param rstr A string
 * @returns
 *   <0 if @p lstr sorts before @p rstr,
 *   0 if the two strings are the same.
 *   >0 if @p rstr sorts before @p lstr,
 */
[[nodiscard]] int string_compare(const char* lstr, const char* rstr);

} // end namespace utils::string

#endif
