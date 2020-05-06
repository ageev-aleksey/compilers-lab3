//
// Created by nrx on 02.05.2020.
//

#ifndef LAB3_LEXER_H
#define LAB3_LEXER_H
#include "ast/Token.h"
#include "ast/Option.h"
#include <string>
#include <list>
enum LexerError {
    END_OF_TEXT,
    NOT_ERROR
};

class Lexer {
public:
    Lexer(const std::string &str);
    Lexer(const Lexer &lexer);

    Token next();
    void back();

private:
    Token makeToken(TokenType);
    Option<LexerError> isToken(const std::string &str);

    struct token_itr {
        std::string::iterator start;
        std::string::iterator end;
        void step();
        std::string get();
    };
    std::string text;
    token_itr current;
    token_itr before;
};



#endif //LAB3_LEXER_H
