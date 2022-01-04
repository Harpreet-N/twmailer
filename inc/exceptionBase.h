//
// Created by harpr on 04.01.2022.
//

#ifndef TWMAILER_EXCEPTIONBASE_H
#define TWMAILER_EXCEPTIONBASE_H

#include <exception>
#include <string>

class ExceptionBase : public std::exception {
public:
    std::string GetErrorMessage() const { return errorMessage; };

    ExceptionBase(std::string errorMessage);

    ~ExceptionBase();

    virtual const char *what() const throw();

private:
    std::string errorMessage;
};

#endif //TWMAILER_EXCEPTIONBASE_H
