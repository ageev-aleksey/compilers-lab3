//
// Created by nrx on 02.05.2020.
//

#include "ast/Token.h"

std::ostream &operator<<(std::ostream &stream, const Token &token)
{
    switch(token.type) {
        case ID:
            stream << "ID";
            break;
        case CONST:
            stream << "CONST";
            break;
        case RELATION:
            stream << "RELATION";
            break;
        case SEMICOLON:
            stream << "SEMICOLON";
            break;
        case ASSIGN:
            stream << "ASSIGNMENT";
            break;
        case OBRACKET:
            stream << "OBRACKET";
            break;
        case CBRACKET:
            stream << "CBRACKET";
            break;
        case CRBRACKET:
            stream << "CRBRACKET";
            break;
        case ORBRACKET:
            stream << "ORBRACKET";
            break;
        case SUM_OP:
            stream << "{SUM_OP, " << token.value << "}";
            break;
        case MUL_OP:
            stream << "{MUL_OP, " << token.value << "}";
            break;
        case END:
            stream << "END";
            break;
        case UNDEFINED:
            stream << "UNDEFINED";
            break;
}
return stream;
}
