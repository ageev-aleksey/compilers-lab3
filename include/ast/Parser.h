//
// Created by nrx on 02.05.2020.
//

#ifndef LAB3_PARSER_H
#define LAB3_PARSER_H

#include <array>
#include <sstream>
#include "ast/Lexer.h"
#include "ast/ParserException.h"
#include "regex/Graph.h"



class Parser {
public:
    using Graph_t = Graph<std::string, Empty>;
    explicit Parser(const Lexer &lexer);
    Graph_t run();
private:
    Graph_t::iterator createNode(std::string value, Graph_t::iterator linked);
    void prog();
    void block(Graph_t::iterator node);
    void op_list(Graph_t::iterator node);
    void op(Graph_t::iterator node);
    void tail(Graph_t::iterator node);
    void expr(Graph_t::iterator node);
    void expr_s(Graph_t::iterator node);
    void factor(Graph_t::iterator node);
    void term(Graph_t::iterator node);
    void term_s(Graph_t::iterator node);
    void ar_expr(Graph_t::iterator node);
    void ar_expr_s(Graph_t::iterator node);

    template<std::size_t N>
    void throwError_GetDontExpectedToken(std::array<TokenType, N> expected) {
        std::stringstream msg;
        msg << "In line: " << lexer.line() << "; column: " << lexer.column() << ";\n";
        if constexpr (N == 1) {
            msg << "Expected symbol type: " << expected[0];
        } else {
            msg << "one of the following characters was expected: ";
            for(int i = 0; i < N-1; i++) {
                msg << expected[i] << ", ";
            }
            msg << expected[N-1];
        }
        msg << "; But the actual type of symbol:" << lexer.get();
        throw ParserException(msg.str());
    }

    Lexer lexer;
    Graph_t graph;
};
#endif //LAB3_PARSER_H
