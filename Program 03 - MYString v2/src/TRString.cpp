////
// Name: Tamara Roberson
// Section: S
// Program Name: Program 2B - MYString v1
//
// Description: A dynamically-sized string class.
////

#include <algorithm>
#include <cmath>
#include <iostream>

#include <TRString.h>
#include <string_utils.h>


// Static
// Instance counters
int TRString::createdCount = 0;
int TRString::currentCount = 0;

int TRString::getCreatedCount()
{
    return createdCount;
}

int TRString::getCurrentCount()
{
    return currentCount;
}


// Public methods
// Default constructor
TRString::TRString() : TRString("")
{
}

// Copy constructor
TRString::TRString(const TRString& mstr) : TRString(mstr.c_str())
{
}

// Construct from string
TRString::TRString(const char* str)
{
    // increase instance counters
    TRString::createdCount++;
    TRString::currentCount++;

    setEqualTo(str);
}

// Destructor
TRString::~TRString()
{
    // decrease current instance counter
    TRString::currentCount--;

    // delete string data
    delete [] this->str;
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

// Return C string representation
const char* TRString::c_str() const
{
    return this->str;
}


// Operator overloads
// Set the string equal to another TRString
TRString& TRString::operator=(const TRString& rvalue)
{
    setEqualTo(rvalue);
    return *this;
}

// Return character at a given index (const)
char& TRString::operator[](const int index) const
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    return this->str[index];
}

// Return character at a given index (const)
char& TRString::operator[](const int index)
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    return this->str[index];
}

// Attempt to read a word from a stream
std::istream& operator>>(std::istream& istrm, TRString& argStr)
{
    // create a temporary buffer to read into
    // NOLINTNEXTLINE
    char buffer[TRString::READ_BUFFER_SIZE];

    // explicitly cast to a pointer instead of decaying
    char* buffer_ptr = static_cast<char*>(buffer);

    // read from the stream into the buffer
    // if successful, set the string to the buffer
    if (istrm >> buffer_ptr)
    {
        argStr.setEqualTo(buffer_ptr);
    }

    return istrm;
}

// Write to a stream
std::ostream& operator<<(std::ostream& ostrm, const TRString& argStr)
{
    ostrm << argStr.c_str();
    return ostrm;
}

// Sort order comparison
bool operator<(const TRString& lhs, const TRString& rhs)
{
    return 0 > utils::string::string_compare(lhs.c_str(), rhs.c_str());
}

bool operator>(const TRString& lhs, const TRString& rhs)
{
    return rhs < lhs;
}

bool operator==(const TRString& lhs, const TRString& rhs)
{
    return 0 == utils::string::string_compare(lhs.c_str(), rhs.c_str());
}

// Concatenation
TRString operator+(const TRString& lhs, const TRString& rhs)
{
    const char* new_str = utils::string::string_concat(lhs.c_str(), rhs.c_str());
    return TRString(new_str);
}

// Set the string equal to another TRString
void TRString::setEqualTo(const TRString& argStr)
{
    setEqualTo(argStr.c_str());
}

// Set the string equal to a C string
void TRString::setEqualTo(const char* argStr)
{
    // calculate the new length and required capacity
    int new_len = utils::string::string_length(argStr);
    auto new_len_dbl = static_cast<double>(new_len);

    int capacity_steps = ceil(new_len_dbl / CAPACITY_STEP);
    capacity_steps = std::max(1, capacity_steps);

    int capacity = capacity_steps * CAPACITY_STEP;

    // If we need additional capacity, delete the old string
    // and allocate a larger size. Otherwise, just copy the new
    // string into the existing one.
    if (capacity > this->cap)
    {
        // create a temporary string
        //   if we delete the old string and set the new
        //   without a temporary, we risk a use-after-free
        //   if the copying fails.
        char* tmp = utils::string::string_copy(argStr, capacity);

        // delete old string
        delete [] this->str;

        // set the string
        this->str = tmp;

        // update the saved capacity
        this->cap = capacity;
    } else {
        // copy the new string into the existing string
        utils::string::string_copy(argStr, new_len, this->str);
    }

    // update the saved string length
    this->end = new_len;
}
