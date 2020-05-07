//
// Created by nrx on 07.05.2020.
//
#include "ast/Lexer.h"
#include "gtest/gtest.h"
#include "../../include/ast/Lexer.h"

TEST(LexerTest, test) {
    std::string text = "{$id=$const}";
    Lexer lexer(text);
    std::vector<Token> tokens;
    std::vector<Token> ok{{OBRACKET, "{"}, {ID, "$id"}, {ASSIGN, "="},
                             {CONST, "$const"}, {CBRACKET, "}"}};
    Token tok = lexer.next();
    int i = 0;
    while ( tok.type != TokenType::END) {
        tokens.push_back(tok);
        tok = lexer.next();
        i++;
        if(i > 5) {
            FAIL();
        }
    }

    ASSERT_EQ(tokens, ok);
}


TEST(LexerTest, testOnSpace) {
    std::string text = "{    $id \n = \t $const    }";
    Lexer lexer(text);
    std::vector<Token> tokens;
    std::vector<Token> ok{{OBRACKET, "{"}, {ID, "$id"}, {ASSIGN, "="},
                          {CONST, "$const"}, {CBRACKET, "}"}};
    Token tok = lexer.next();
    int i = 0;
    while ( tok.type != TokenType::END) {
        tokens.push_back(tok);
        tok = lexer.next();
        i++;
        if(i > 5) {
            FAIL();
        }
    }

    ASSERT_EQ(tokens, ok);
}

TEST(LexerTest, testOnAllTokensType) {
    std::string text = "{(})$id$const>>=<<=<>=;==";
    Lexer lexer(text);
    std::vector<Token> tokens;
    std::vector<Token> ok{{OBRACKET, "{"}, {ORBRACKET, "("}, {CBRACKET, "}"},
                          {CRBRACKET, ")"}, {ID, "$id"}, {CONST, "$const"},
                          {RELATION, ">"},  {RELATION, ">="},  {RELATION, "<"},
                          {RELATION, "<="},  {RELATION, "<>"},  {ASSIGN, "="},
                          {SEMICOLON, ";"},  {RELATION, "=="}};
    Token tok = lexer.next();
    int i = 0;
    while ( tok.type != TokenType::END) {
        tokens.push_back(tok);
        tok = lexer.next();
        i++;
        if(i > 15) {
            FAIL();
        }
    }

    ASSERT_EQ(tokens, ok);
}

TEST(LexerTest, testBack) {
    std::string text = "{}";
    Lexer lexer(text);
    Token tok = lexer.next();
    Token ok1{OBRACKET, "{"};
    Token ok2{CBRACKET, "}"};
    ASSERT_EQ(tok, ok1);
    tok = lexer.next();
    ASSERT_EQ(tok, ok2);
    lexer.back();
    tok = lexer.next();
    ASSERT_EQ(tok, ok2);
}