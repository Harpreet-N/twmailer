//
// Created by harpr on 04.01.2022.
//

#include "exceptionBase.h"

ExceptionBase::ExceptionBase(std::string errorMessage)
        : errorMessage(errorMessage) {
}

ExceptionBase::~ExceptionBase() {
}

const char *ExceptionBase::what() const throw() {
    return errorMessage.c_str();
}