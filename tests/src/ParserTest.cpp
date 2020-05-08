//
// Created by nrx on 08.05.2020.
//

#include "GraphToDOT.h"
#include "ast/Parser.h"
#include "gtest/gtest.h"


TEST(ParserTest, test1) {
    std::string text = "{ $id = $const * ( $id +$id) < ($id+$const)  * ( $const) }";
    Lexer lexer(text);
    Parser parser(lexer);
    auto res = parser.run();
    std::cout << graphToDOT(res);
}

