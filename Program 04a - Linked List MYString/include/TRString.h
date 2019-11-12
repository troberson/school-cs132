////
// Name: Tamara Roberson
// Section: S
// Program Name: Program 3 - MYString v2
//
// Description: A dynamically-sized string class.
// This class holds a C-style string with an initial capacity
// of 20 characters. If it is changed to a string which requires and
// larger capacity, it is increased in steps of 20. The number of
// instances created since execusion and currently in memory are also
// tracked. Description: A dynamically-sized string class.
////

#ifndef TRSTRING_H
#define TRSTRING_H

#include <iostream>

// NOLINTNEXTLINE(hicpp-special-member-functions, cppcoreguidelines-special-member-functions)
class TRString
{
  private:
    // STATIC
    // Instance counters
    static int createdCount;
    static int currentCount;

    /** Size to increase the capacity of the string by each time */
    static const int CAPACITY_STEP = 20;

    // INSTANCE
    /** pointer to dynamic memory for storing the string */
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays)
    char* str = new char[CAPACITY_STEP];

    /** size of the memory available to use */
    int cap{CAPACITY_STEP};

    /** index of the end of the string (null-terminator) */
    int end{0};

  public:
    // STATIC
    /** Read buffer size */
    static const int READ_BUFFER_SIZE = 100;

    /**
     * Returns the number of TRStrings created since execution began.
     *
     * @returns The number of TRStrings created since execution began.
     */
    static int getCreatedCount();

    /**
     * Returns the number of TRStrings which currently are in memory.
     *
     * @returns The number of TRStrings which currently are in memory.
     */
    static int getCurrentCount();


    // INSTANCE
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


    /**
     * Returns the character at the given position.
     *
     * @param index Position of a character in the string.
     * @throw std::out_of_range If index is invalid.
     * @returns The character at the given position.
     */
    [[nodiscard]] char at(int index) const;

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
     * @returns A pointer to the current string.
     */
    TRString& operator=(const TRString& rvalue);

    /**
     * Append another string to the current string.
     *
     * @param rvalue The string to append.
     * @returns A pointer to the current string.
     */
    TRString& operator+=(const TRString& rvalue);

    /**
     * Returns the character at the given position.
     *
     * @warning Results in undefined behavior if position outside the
     *   bounds of the string.
     *
     * @param index Position of a character in the string.
     * @returns The character at the given position.
     */
    [[nodiscard]] char& operator[](int index) const;

    /**
     * Returns the character at the given position.
     *
     * @warning Results in undefined behavior if position outside the
     *   bounds of the string.
     *
     * @param index Position of a character in the string.
     * @returns The character at the given position.
     */
    [[nodiscard]] char& operator[](int index);
};

/**
 * Set the string to the first word from a stream.
 *
 * @param istrm An input stream.
 * @returns The input stream.
 */
std::istream& operator>>(std::istream& istrm, TRString& argStr);

/**
 * Write the string to a stream.
 *
 * @param ostrm An output stream.
 * @returns The output stream.
 */
std::ostream& operator<<(std::ostream& ostrm, const TRString& argStr);

/**
 * Returns if one string sorts before another.
 *
 * @param lhs A string.
 * @param rhs A string.
 * @returns True if @p lhs sorts before @p rhs, false otherwise.
 */
[[nodiscard]] bool operator<(const TRString& lhs,
                             const TRString& rhs);

/**
 * Returns if one string sorts after another.
 *
 * @param lhs A string.
 * @param rhs A string.
 * @returns True if @p lhs sorts after @p rhs, false otherwise.
 */
[[nodiscard]] bool operator>(const TRString& lhs,
                             const TRString& rhs);

/**
 * Returns if two string are equivalent.
 *
 * @param lhs A string.
 * @param rhs A string.
 * @returns True if the two strings are equivalent, false otherwise.
 */
[[nodiscard]] bool operator==(const TRString& lhs,
                              const TRString& rhs);

/**
 * Returns a string containing characters from @p lhs
 * followed by the characters from @p rhs.
 *
 * @param lhs A string.
 * @param rhs A string.
 * @returns A string containing characters from @p lhs
 *   followed by the characters from @p rhs.
 */
[[nodiscard]] TRString operator+(const TRString& lhs,
                                 const TRString& rhs);

#endif
