//
// Created by nrx on 02.05.2020.
//

#ifndef LAB3_TOKEN_H
#define LAB3_TOKEN_H
#include <string>
#include <ostream>

enum TokenType {
    EXPR,
    AR_EXPR,
    SUM_OP,
    MUL_OP,
    TERM,
    FACTOR,
    ID,
    CONST,
    RELATION,
    SEMICOLON,
    ASSIGNMENT,
    OBRACKET,
    CBRACKET,
    END,
    UNDEFINED
};

struct Token {
    TokenType type;
    std::string value;
};

std::ostream &operator<<(std::ostream &stream, const Token &token);
#endif //LAB3_TOKEN_H
