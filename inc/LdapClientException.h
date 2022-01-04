//
// Created by harpr on 04.01.2022.
//

#ifndef TWMAILER_LDAPCLIENTEXCEPTION_H
#define TWMAILER_LDAPCLIENTEXCEPTION_H

#include "exceptionBase.h"


class LdapClientException : public ExceptionBase {

public:
    LdapClientException(std::string message);

};

#endif //TWMAILER_LDAPCLIENTEXCEPTION_H
