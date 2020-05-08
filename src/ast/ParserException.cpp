//
// Created by nrx on 08.05.2020.
//

#include "ast/ParserException.h"

ParserException::ParserException(const std::string &msg) : std::runtime_error(msg)
{}