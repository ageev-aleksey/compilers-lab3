//
// Created by nrx on 02.05.2020.
//

#include "ast/Token.h"
#include "ast/Lexer.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ast/Parser.h>
#include "ast/NonTerminals.h"
#include "GraphToDOT.h"

int main(int argc, char **argv) {
    if(argc == 1) {
        std::cout << "Program required second argument of the path of  file with source code" << std::endl;
        return -1;
    }
    std::ifstream file;
    file.open(argv[1]);
    if(!file.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return -2;
    }
    std::string source;
    std::string buffer;
    while(!file.eof()) {
        buffer.clear();
        std::getline(file, buffer);
        buffer.push_back('\n');
        source.append(buffer);
    }
    std::cout << source << std::endl;

    Lexer lexer(source);
    Parser parser(lexer);
    auto AST = parser.run();
    std::cout << graphToDOT(AST) << std::endl;
    return 0;
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