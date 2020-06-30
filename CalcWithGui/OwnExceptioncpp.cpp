#include "OwnException.h"

OwnException::OwnException(const std::string& msg) : error_message(msg)
{

}

OwnException::~OwnException()
{

}

const char* OwnException::what() const throw ()
{
    return error_message.c_str();
}