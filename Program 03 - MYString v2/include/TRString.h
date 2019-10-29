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

// NOLINTNEXTLINE(hicpp-special-member-functions, cppcoreguidelines-special-member-functions)
class TRString
{
  private:
    /** Read buffer size */
    static const int READ_BUFFER_SIZE = 100;

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


  public:
    /**
     * Create an empty TRString
     */
    TRString();

    /**
     * Copy an existing TRString
     *
     * @param mstr String to duplicate
     */
    TRString(const TRString& mstr);

    /**
     * Create a TRString
     *
     * @param str A string
     */
    explicit TRString(const char* str);

    /**
     * Destroy string
     */
    ~TRString();

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
     * @param ostrm An output stream.
     */
    void write(std::ostream& ostrm) const;

    /**
     * Returns a pointer to a C string representation
     *
     * @returns A C string.
     */
    [[nodiscard]] const char* c_str() const;

    /**
     * Set the string
     *
     * @param rvalue The string to set equal to.
     */
    TRString& operator=(const TRString& rvalue);

    /**
     * Returns the character at the given position.
     *
     * @warning Results in undefined behavior if position outside the bounds of the string.
     *
     * @param index Position of a character in the string.
     * @returns The character at the given position.
     */
    [[nodiscard]] char operator[](int index) const;

    /**
     * Compare the sort order of the object string to another string.
     *
     * @note The sort order depends on the encoding, such as ASCII.
     *
     * @param argStr The string to compare to.
     * @returns <0: The first character that does not match has a
     *   lower value in this string than in @p argStr. <br />
     * 0: The contents of both strings are equal.<br />
     * >0: The first character that does not match has a greater
     *   value in this string than in@ @p argStr.
     */
    [[nodiscard]] int compareTo(const TRString& argStr) const;
};

/**
* Set the string to the first word from a stream.
*
* @param istrm An input stream.
* @returns The input stream.
*/
std::istream& operator<<(const TRString& lvalue, std::istream& istrm);

/**
* Write the string to a stream.
*
* @param ostrm An output stream.
* @returns The output stream.
*/
std::ostream& operator>>(std::ostream& ostrm, const TRString& rvalue);


#endif
