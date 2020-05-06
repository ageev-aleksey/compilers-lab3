

#include "ast/Lexer.h"
#include "ast/Token.h"
#include "ast/Option.h"

Lexer::Lexer(const std::string &text) {
    this->text = text;
    current.start = this->text.begin();
    current.end = current.start;
    before = current;
}

Token Lexer::makeToken(TokenType type) {
    before = current;
    current.step();
    return {type, before.get()};
}

Option<LexerError> Lexer::isToken(const std::string &str) {
    bool isDetected = true;
    auto state = current.end;
    for(size_t i = 0; i < str.size(); i++) {
        if(current.end == text.end() || (++current.end) == text.end()) {
            current.end = state;
            return Option<LexerError>(END_OF_TEXT, true);
        }
        if(*current.end != str[i]) {
            isDetected = false;
            current.end = state;
            break;
        }
    }

    return Option<LexerError>(NOT_ERROR, isDetected);
}



Token Lexer::next() {
    Token token;
    while((current.end != text.end())
        && (*current.end == ' ')) {
        current.step();
    }
    switch (*current.end) {
        case '{':
            token =  makeToken(OBRACKET);
            break;
        case'}':
            token = makeToken(CBRACKET);
            break;
        case '(':
            token =  makeToken(ORBRACKET);
            break;
        case ')':
            token = makeToken(ORBRACKET);
            break;
        case ';':
            token = makeToken(SEMICOLON);
            break;
        case '<':
            if(*(++current.end) != '=' || *current.end != '>')
                --current.end;
            token =  makeToken(RELATION);
            break;
        case '>':
            if(*(++current.end) != '=')
                --current.end;
            token = makeToken(RELATION);
            break;
        case '=':
            token = makeToken(ASSIGN);
            break;
        case '+':
        case '-':
            token = makeToken(SUM_OP);
            break;
        case '*':
        case '/':
            token = makeToken(MUL_OP);
            break;
        case '$': {
            const std::string id("id");
            const std::string _const("const");
            Option<LexerError> res = isToken(id);
            if (res)  {
                token =  makeToken(ID);
                break;
            }
            if(res.get() != NOT_ERROR) {
                //TODO Какое должно быть поведение?
            }
            res = isToken(_const);
            if(res) {
                token =  makeToken(CONST);
                break;
            }
            //TODO какое должно быть поведение если проверки не прошли?
        }

        default:
            token =  {UNDEFINED, ""};
    }

    return token;

}

void Lexer::back() {
    current = before;
}

void Lexer::token_itr::step() {
    end++;
    start = end;
}

std::string Lexer::token_itr::get() {
    std::string res;
    std::string::iterator tmp = end;
    std::copy(start, ++tmp, std::back_inserter(res));
    return res;
}