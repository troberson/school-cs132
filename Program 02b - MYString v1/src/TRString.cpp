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


TRString::TRString()
{
    setEqualTo("");
}

TRString::TRString(const char* str)
{
    setEqualTo(str);
}

int TRString::length() const
{
    return this->end;
}

int TRString::capacity() const
{
    return this->cap;
}

const char* TRString::c_str() const
{
    return this->str;
}

char TRString::at(const int index) const
{
    return utils::string::get_char_at(str, index);
}

void TRString::setEqualTo(const TRString& argStr)
{
    setEqualTo(argStr.c_str());
}

void TRString::setEqualTo(const char* argStr)
{
    this->str = utils::string::string_copy(argStr);
    update_length();
}

void TRString::update_length()
{
    this->end = utils::string::string_length(this->str);
}

