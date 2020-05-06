//
// Created by nrx on 02.05.2020.
//

#ifndef LAB3_LEXER_H
#define LAB3_LEXER_H
#include "ast/Token.h"
#include <string>
#include <list>

class Lexer {
public:
    Lexer(const std::string &str);
    Lexer(const Lexer &lexer);

    Token next();
    void back();

private:
    std::list<std::string> strList;
    std::list<std::string>::iterator itr;
};


#endif //LAB3_LEXER_H
