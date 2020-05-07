//
// Created by nrx on 02.05.2020.
//

#include "ast/Token.h"

bool Token::operator==(const Token &other) const{
    return (this->type == other.type) && (this->value == other.value);
}


std::ostream &operator<<(std::ostream &stream, const Token &token)
{
    switch(token.type) {
        case ID:
            stream << "{ID, '" << token.value << "'}";
            break;
        case CONST:
            stream << "{CONST, '" << token.value <<  "'}";
            break;
        case RELATION:
            stream << "{RELATION, '" << token.value <<  "'}";
            break;
        case SEMICOLON:
            stream << "{SEMICOLON, '" << token.value <<  "'}";
            break;
        case ASSIGN:
            stream << "{ASSIGNMENT, '" << token.value <<  "'}";
            break;
        case OBRACKET:
            stream << "{OBRACKET, '" << token.value <<  "'}";
            break;
        case CBRACKET:
            stream << "{CBRACKET, '" << token.value <<  "'}";
            break;
        case CRBRACKET:
            stream << "{CRBRACKET, '" << token.value <<  "'}";
            break;
        case ORBRACKET:
            stream << "{ORBRACKET, '" << token.value <<  "'}";
            break;
        case SUM_OP:
            stream << "{SUM_OP, '" << token.value << "'}";
            break;
        case MUL_OP:
            stream << "{MUL_OP, '" << token.value << "'}";
            break;
        case END:
            stream << "{END, }";
            break;
        case UNDEFINED:
            stream << "{UNDEFINED, }";
            break;
}
return stream;
}
