//
// Created by nrx on 08.05.2020.
//

#ifndef COMPILERS_PARSEREXCEPTION_H
#define COMPILERS_PARSEREXCEPTION_H
#include <stdexcept>


class ParserException : public std::runtime_error {
public:
    ParserException(const std::string &msg);
};

#endif //COMPILERS_PARSEREXCEPTION_H
