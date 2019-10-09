///
// Name: Tamara Roberson
// Section: S
// Program Name: Program 2B - MYString v1
//
// Description: A dynamically-sized string class.
////

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
 * Returns the character at the given index.
 *
 * @param index Index of a character in the string.
 * @throw std::out_of_range If index is invalid.
 * @returns The character at the given index.
 */
[[nodiscard]] char get_char_at(const char* str, int index);


/**
 * Compare the sort order of two strings
 *
 * @note The sort order depends on the encoding, such as ASCII.
 *
 * @param lstr a string
 * @param rstr a string
 * @returns
 *   <0 if @p lstr sorts before @p rstr,
 *   0 if the two strings are the same.
 *   >0 if @p rstr sorts before @p lstr,
 */
int string_compare(const char *lstr, const char *rstr);

} // end namespace utils::string
