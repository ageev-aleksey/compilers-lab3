//
// Created by nrx on 02.05.2020.
//

#ifndef LAB3_TOKEN_H
#define LAB3_TOKEN_H
#include <string>
#include <ostream>

enum TokenType {
    OBRACKET,
    CBRACKET,
    ORBRACKET,
    CRBRACKET,
    SEMICOLON,
    RELATION,
    SUM_OP,
    MUL_OP,
    ASSIGN,
    ID,
    CONST,
    END,
    UNDEFINED
};

struct Token {
    TokenType type;
    std::string value;
    bool operator==(const Token &other) const;
};

std::ostream &operator<<(std::ostream &stream, const TokenType &token);
std::ostream &operator<<(std::ostream &stream, const Token &token);
#endif //LAB3_TOKEN_H
