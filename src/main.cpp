//
// Created by nrx on 02.05.2020.
//

#include "ast/Token.h"
#include "ast/Lexer.h"
#include <string>
#include <iostream>

int main() {
    std::string str("{ $id = @const + @const < @const + @const }");
    Lexer l(str);
    Token t = l.next();
    while(t.type != TokenType::END) {
        std::cout << t  << std ::endl;
        t = l.next();
    }

}