//
// Created by nrx on 02.05.2020.
//

#include "ast/Token.h"

std::ostream &operator<<(std::ostream &stream, const Token &token)
{
switch(token.type) {
case EXPR:
stream << "EXPR";
break;
case AR_EXPR:
stream << "AR_EXPR";
break;
case SUM_OP:
stream << "SUM_OP";
break;
case MUL_OP:
stream << "MUL_OP";
break;
case TERM:
stream << "TERM";
break;
case FACTOR:
stream << "FACTOR";
break;
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
case ASSIGNMENT:
stream << "ASSIGNMENT";
break;
case OBRACKET:
stream << "OBRACKET";
break;
case CBRACKET:
stream << "CBRACKET";
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
