////
// Name: Tamara Roberson
// Section: S
// Program Name: Program 2B - MYString v1
//
// Description: A dynamically-sized string class.
////


#include <iostream>
#include <stdexcept>

#include <TRString.h>
#include <string_utils.h>


// Public methods
// Default Constructor
TRString::TRString()
{
    setEqualTo("");
}

// Construct from string
TRString::TRString(const char* str)
{
    setEqualTo(str);
}

// Return length
int TRString::length() const
{
    return this->end;
}

// Return capacity
int TRString::capacity() const
{
    return this->cap;
}

// Return character at a given index
char TRString::at(const int index) const
{
    return utils::string::get_char_at(this->str, index);
}

// Read from a stream
bool TRString::read(std::istream& istrm)
{
    // create a temporary buffer to read into
    // NOLINTNEXTLINE
    char buffer[READ_BUFFER_SIZE];

    // explicitly cast to a pointer instead of decaying
    char* buffer_ptr = static_cast<char*>(buffer);

    // read from the stream into the buffer
    istrm >> buffer_ptr;

    // return false if read failed
    if (istrm.fail() || istrm.bad())
    {
        return false;
    }

    // set the string to the buffer
    setEqualTo(buffer_ptr);

    // return: true for read successful
    return true;
}

// Write to a stream
void TRString::write(std::ostream& ostrm) const
{
    ostrm << this->str;
}

// Return the sort order compared to another TRString
int TRString::compareTo(const TRString& argStr) const
{
    return utils::string::string_compare(c_str(), argStr.c_str());
}

// Return C string representation
const char* TRString::c_str() const
{
    return this->str;
}

// Set the string equal to another TRString
void TRString::setEqualTo(const TRString& argStr)
{
    setEqualTo(argStr.c_str());
}

// Set the string equal to a C string
void TRString::setEqualTo(const char* argStr)
{
    this->str = utils::string::string_copy(argStr);
    update_length();
}


// Private methods
// Updated the stored length of the string
void TRString::update_length()
{
    this->end = utils::string::string_length(this->str);
}
