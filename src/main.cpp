//
// Created by nrx on 02.05.2020.
//

#include "ast/Token.h"
#include "ast/Lexer.h"
#include <string>
#include <iostream>
#include "ast/NonTerminals.h"

int main() {
    std::cout << NonTerminals::OP << std::endl;
}



//int main() {
//    //TODO Добавить в обработку перевод строки и все остальные символы пространства, их надо пропускать
//    std::string str(" { $id=$const+$const<$const      +$const     }   ");
//    Lexer l(str);
//    Token t = l.next();
//    while(t.type != TokenType::UNDEFINED) {
//        std::cout << t  << std ::endl;
//        t = l.next();
//    }
//
//}