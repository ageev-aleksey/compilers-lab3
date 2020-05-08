//
// Created by nrx on 02.05.2020.
//

#ifndef LAB3_PARSER_H
#define LAB3_PARSER_H

#include "regex/Graph.h"
#include "ast/Lexer.h"

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
    void relation(Graph_t::iterator node);
    void mul_op(Graph_t::iterator node);
    void sum_op(Graph_t::iterator node);
    void id(Graph_t::iterator node);
    void _const(Graph_t::iterator node);
    Lexer lexer;
    Graph_t graph;
};
#endif //LAB3_PARSER_H
