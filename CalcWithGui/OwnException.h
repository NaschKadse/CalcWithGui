#ifndef OWNEXCEPTION_H
#define OWNEXCEPTION_H

#include <exception>
#include <string>

class OwnException : virtual public std::exception
{
protected:
    std::string error_message;

public:

    explicit OwnException(const std::string& msg);

    virtual ~OwnException();

    virtual const char* what() const throw ();

private:

};

#endif // !OWNEXCEPTION_H