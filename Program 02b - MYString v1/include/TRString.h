////
// Name: Tamara Roberson
// Section: S
// Program Name: Program 2B - MYString v1
//
// Description: A dynamically-sized string class.
////

#ifndef TRSTRING_H
#define TRSTRING_H

#include <iostream>

class TRString
{
  private:

    /** Size to increase the capacity of the string by each time */
    static const int CAPACITY_STEP = 20;

    /** pointer to dynamic memory for storing the string */
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays)
    char* str = new char[CAPACITY_STEP];

    /** size of the memory available to use */
    int cap{CAPACITY_STEP};

    /** index of the end of the string (null-terminator) */
    int end{0};


    /**
     * Update the saved length of the string.
     */
    void update_length();

  public:
    /**
     * Create an empty TRString
     */
    TRString();

    /**
     * Create a TRString
     *
     * @param str A string
     */
    explicit TRString(const char* str);

    /**
     * Return the length of the string
     *
     * @returns The length of the string
     */
    [[nodiscard]] int length() const;

    /**
     * Return the capacity of the string
     *
     * @note This is fixed in Program 2 at 20 characters.
     *
     * @returns The capacity of the string.
     */
    [[nodiscard]] int capacity() const;

    /**
     * Returns the character at the given position.
     *
     * @param index Position of a character in the string.
     * @throw std::out_of_range If index is invalid.
     * @returns The character at the given position.
     */
    [[nodiscard]] char at(int index) const;

    /**
     * Read one word from a stream.
     *
     * @param istrm An input stream.
     * @returns True if read was successful, False otherwise.
     */
    bool read(std::istream& istrm);

    /**
     * Write the string to a stream.
     *
     * @para ostrm An output stream.
     */
    void write(std::ostream& ostrm) const;

    /**
     * Compare the sort order of the object string to another string.
     *
     * @note The sort order depends on the encoding, such as ASCII.
     *
     * @param argStr The string to compare to.
     * @returns <0: The first character that does not match has a
     *   lower value in this string than in @p argStr.<br />
     * 0: The contents of both strings are equal.<br />
     * >0: The first character that does not match has a greater
     *   value in this string than in@ @p argStr.
     */
    [[nodiscard]] int compareTo(const TRString& argStr) const;

    /**
     * Returns a pointer to a C string representation
     *
     * @returns A C string.
     */
    [[nodiscard]] const char* c_str() const;

    /**
     * Set the string.
     *
     * @param argStr The string to set equal to.
     */
    void setEqualTo(const TRString& argStr);

    /**
     * Set the string
     *
     * @param argStr The string to set equal to.
     */
     void setEqualTo(const char* argStr);
};

#endif
