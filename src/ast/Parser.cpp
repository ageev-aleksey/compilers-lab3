//
// Created by nrx on 07.05.2020.
//

#include <ast/ParserException.h>
#include <sstream>
#include "ast/Parser.h"
#include "ast/NonTerminals.h"




Parser::Graph_t::iterator Parser::createNode(std::string value, Parser::Graph_t ::iterator linked) {
    auto node = graph.addNodeInBack(value);
    graph.addLink(linked, node, Empty{});
    return node;
}

 Parser::Parser(const Lexer &lexer) : lexer(lexer)
 {}


 Parser::Graph_t Parser::run() {
    prog();
    return graph;
}

/**
 * <prog> := <block>
 */
void Parser::prog() {
    try {
        auto root = graph.addNodeInBack(NonTerminals::PROG);
        block(root);
    } catch (ParserException &exp) {
        std::cout << "Parsing Error: " << exp.what() << std::endl;
    }

}

/**
 * <block> := '{' <op_list> '}'
 */
void Parser::block(Parser::Graph_t ::iterator node) {
    auto blockNode = createNode(NonTerminals::BLOCK, node);
    Token tok = lexer.next();
    if(tok.type == OBRACKET) {
        auto openBracketNode = createNode(tok.value, blockNode);
        op_list(blockNode);
        tok = lexer.next();
        if(tok.type == CBRACKET) {
            auto closeBracketNode = createNode(tok.value, blockNode);
        } else {
           throwError_GetDontExpectedToken(std::array<TokenType, 1>{CBRACKET});
        }
    } else {
        throwError_GetDontExpectedToken(std::array<TokenType, 1>{OBRACKET});
    }
}


/**
 * <op_list> := <op><tail>
 */
void Parser::op_list(Parser::Graph_t ::iterator node) {
    auto opListNode =createNode(NonTerminals::OP_LIST, node);
    op(opListNode);
    tail(opListNode);
}

/**
 * <op> := <id>'='<expr>
 *       | '{'<op_list>'}'
 */
void Parser::op(Parser::Graph_t ::iterator node) {
   auto opNode = createNode(NonTerminals::OP, node);
    Token tok = lexer.next();
    if(tok.type == OBRACKET) {
        auto openBracketNode = createNode(tok.value, opNode);
        op_list(opNode);
        tok = lexer.next();
        if(tok.type == CBRACKET) {
            auto closeBracketNode = createNode(tok.value, opNode);
        } else {
            throwError_GetDontExpectedToken(std::array<TokenType, 1>{OBRACKET});
        }
    } else if (tok.type == ID) {
        auto idNode = createNode("ID", opNode);
        createNode(tok.value, idNode);
        tok = lexer.next();
        if(tok.type == ASSIGN) {
            auto assignNode = createNode(tok.value, opNode);
            expr(opNode);
        } else {
            throwError_GetDontExpectedToken(std::array<TokenType, 1>{ASSIGN});
        }
    } else {
        throwError_GetDontExpectedToken(std::array<TokenType, 2>{OBRACKET, ID});
    }
}


/**
 * <tail> := ';'<op><tail>
 *         | <epsilon>
*/
void Parser::tail(Parser::Graph_t::iterator node) {
    auto tailNode = createNode(NonTerminals::TAIL, node);
    Token tok = lexer.next();
    if(tok.type == SEMICOLON) {
        auto nodeSemicolon = createNode(tok.value, tailNode);
        op(node);
        tail(node);
    } else {
        auto epsilonNode = createNode("<EPSILON>", tailNode);
        lexer.back();
    }
}


/**
 * <expr> := <ar_expr><expr'>
 */
void Parser::expr(Graph<std::string, Empty>::iterator node) {
    auto exprNode = createNode(NonTerminals::EXPR, node);
    ar_expr(exprNode);
    expr_s(exprNode);
}

/**
 * <expr'> := <relation><ar_expr>
 *          | <epsilon>
 */
void Parser::expr_s(Parser::Graph_t ::iterator node) {
    auto expr_sNode = createNode(NonTerminals::EXPR_S, node);
    Token tok = lexer.next();
    if(tok.type == RELATION) {
        auto relationNode = createNode("RELATION", expr_sNode);
        createNode(tok.value, relationNode);
        ar_expr(expr_sNode);
    } else {
        lexer.back();
        auto epsilonNode = createNode("<EPSILON>", expr_sNode);
    }
}

/**
 * <factor> := <id>|<const>|'('<ar_expr>')'
 */
void Parser::factor(Parser::Graph_t ::iterator node) {
    auto factorNode = createNode(NonTerminals::FACTOR, node);
    Token tok = lexer.next();
    switch(tok.type) {
        case ID: {
            auto idNode = createNode("ID", factorNode);
            createNode(tok.value, idNode);
            break;
        }
        case CONST: {
            auto constNode = createNode("CONST", factorNode);
            createNode(tok.value, constNode);
            break;
        }
        case ORBRACKET: {
            auto orbracketNode = createNode("ORBRACKET", factorNode);
            createNode(tok.value, orbracketNode);
            auto ar_exprNode = createNode(NonTerminals::AR_EXPR, factorNode);
            ar_expr(ar_exprNode);
            tok = lexer.next();
            if(tok.type == CRBRACKET) {
                auto crbracketNode = createNode("cRBRACKET", factorNode);
                createNode(tok.value, crbracketNode);
            } else {
                throwError_GetDontExpectedToken(std::array<TokenType, 1>{CRBRACKET});
            }
            break;
        }
        default:
            throwError_GetDontExpectedToken(std::array<TokenType, 3>{ID, CONST,ORBRACKET});

    }
}


//TODO создание узла нетерминала должев нвыполнять функция обрабатывающая нетерминал!

/**
 * <term> := <id><term'>
 *          | <const><term'>
 *          | '('<ar_expr>')'<term'>
 */
void Parser::term(Parser::Graph_t ::iterator node) {
    auto termNode = createNode(NonTerminals::TERM, node);
    Token tok = lexer.next();
    switch(tok.type) {
        case ID : {
            auto idNode = createNode("ID", termNode);
            createNode(tok.value, idNode);
            term_s(termNode);
            break;
        }
        case CONST: {
            auto constNode = createNode("CONST", termNode);
            createNode(tok.value, constNode);
            term_s(termNode);
            break;
        }
        case ORBRACKET: {
            auto orbracketNode = createNode("ORBRACKET", termNode);
            createNode(tok.value, orbracketNode);
            ar_expr(termNode);
            tok = lexer.next();
            if(tok.type == CRBRACKET) {
                auto crbracketNode = createNode("CRBRACKET", termNode);
                createNode(tok.value, crbracketNode);
                term_s(termNode);
            } else {
                throwError_GetDontExpectedToken(std::array<TokenType, 1>{CRBRACKET});
            }
            break;
        }
        default:{
            throwError_GetDontExpectedToken(std::array<TokenType, 3>{ID, CONST, ORBRACKET});
        }
    }
}

/**
 * <term'> := <mul_op><factor><term'>
 *          | <epsilon>
 */
void Parser::term_s(Parser::Graph_t ::iterator node) {
    auto termSNode = createNode(NonTerminals::TERM_S, node);
    Token tok = lexer.next();
    if(tok.type == MUL_OP) {
        auto mulNode = createNode("MUL_OP", termSNode);
        createNode(tok.value, mulNode);
        factor(termSNode);
        term_s(termSNode);
    } else {
        createNode("<EPSILON>", termSNode);
        lexer.back();
    }
}

/**
 * <ar_expr> := <id><term'><ar_expr'>
 *             | <const><term'><ar_expr'>
 *             | '('<ar_expr>')'<term'><ar_expr'>
*/
void Parser::ar_expr(Parser::Graph_t::iterator node) {
    auto arExprNode = createNode(NonTerminals::AR_EXPR ,node);
    Token tok = lexer.next();
    switch(tok.type) {
        case ID: {
            auto idNode = createNode("ID", arExprNode);
            createNode(tok.value, idNode);
            term_s(arExprNode);
            ar_expr_s(arExprNode);
            break;
        }
        case CONST: {
            auto constNode = createNode("CONST", arExprNode);
            createNode(tok.value, constNode);
            term_s(arExprNode);
            ar_expr_s(arExprNode);
            break;
        }
        case ORBRACKET: {
            auto orbracketNode = createNode("ORBRACKET", arExprNode);
            createNode(tok.value, orbracketNode);
            ar_expr(arExprNode);
            tok = lexer.next();
            if(tok.type == CRBRACKET) {
                auto crbracketNode = createNode("CRBRACKET", arExprNode);
                createNode(tok.value, crbracketNode);
             } else {
                throwError_GetDontExpectedToken(std::array<TokenType, 1>{CRBRACKET});
            }
            term_s(arExprNode);
            ar_expr_s(arExprNode);
            break;
        }
        default: {
            throwError_GetDontExpectedToken(std::array<TokenType, 3>{ID, CONST, ORBRACKET});
        }
    }
}

/**
 * <ar_expr'> := <sum_op><term><ar_expr'>
 *              | <epsilon>
 */
void Parser::ar_expr_s(Graph<std::string, Empty>::iterator node) {
    auto arExprSNode = createNode(NonTerminals::AR_EXPR_S, node);
    Token tok = lexer.next();
    if(tok.type == SUM_OP) {
        auto sumOpNode = createNode("SUM_OP", arExprSNode);
        createNode(tok.value, sumOpNode);
        term(arExprSNode);
        ar_expr_s(arExprSNode);
    } else {
        createNode("<EPSILON>", arExprSNode);
        lexer.back();
    }
}

/**
 * <relation> :=  ‘<’|’<=’|’>’|’>=’|’<>’
*/
