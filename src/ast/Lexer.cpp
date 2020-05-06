//
// Created by nrx on 02.05.2020.
//

#include <list>
#include "ast/Lexer.h"
#include "ast/Token.h"
#include "regex/Matcher.h"

bool isSpace(const char &symbol) {
    return (symbol == ' ') || (symbol == '\t') || (symbol == '\r');
}

std::list<std::string> splitBySpace(const std::string &str) {
    std::list<std::string> res;
    std::string tmp;
    for(auto itr = str.cbegin(); itr != str.cend(); itr++) {
        if(isSpace(*itr)) {
            if(tmp.empty()) {
                continue;
            }
            res.push_back(std::move(tmp));
        } else {
            tmp.push_back(*itr);
        }

    }
    if(!tmp.empty()) {
        res.push_back(tmp);
    }
    return res;
}

Lexer::Lexer(const std::string &str) {
    strList = splitBySpace(str);
    itr = strList.begin();
}

Lexer::Lexer(const Lexer &lexer) {
    strList = lexer.strList;
    itr = lexer.itr;
}

bool isRelation(const std::string &str) {
    return (str == "<") || (str == "<=") || (str == "=") || (str == "<>") || (str == ">") || (str == ">=");
}

bool isId(const std::string &str) {
//    Matcher matcher = Matcher::compile("(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|S|Q|W|Y|Z)&(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|S|Q|W|Y|Z)*");
//    return matcher.match(str);
    return str == "$id";
}

bool isConst(const std::string &str) {
   // Matcher matcher = Matcher::compile("(0|1|2|3|4|5|6|7|8|9)&(0|1|2|3|4|5|6|7|8|9)*");
    //return matcher.match(str);
    return str == "@const";
}


Token Lexer::next() {
    TokenType type = TokenType::UNDEFINED;
    for(; itr != strList.end(); ) {
    if (*itr == "{") {
        type = TokenType::OBRACKET;
    } else if(*itr == "}") {
        type = TokenType::CBRACKET;
    } else if(*itr == "+" || *itr == "-") {
            type = TokenType::SUM_OP;
        } else if (*itr == "*" || *itr == "/") {
            type = TokenType::MUL_OP;
        } else if (isRelation(*itr)) {
            type = TokenType::RELATION;
        } else if(isId(*itr)) {
            type = TokenType::ID;
        } else if(isConst(*itr)) {
            type = TokenType::CONST;
        }
        auto tok = itr;
        itr++;
        return {type, *tok};
    }
    return {TokenType::END, std::string("")};
}

