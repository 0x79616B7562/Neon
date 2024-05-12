#include "lexer.h"

#define cmp(str, id) if (buffer == str) { add_token(tokens, id, buffer, line, column); buffer.clear(); }

inline void add_token(std::vector<Token> & tokens, TokenId token, std::string value, uint32_t & line, uint32_t & column) {
    tokens.push_back(Token {
        token,
        value,
        line,
        column
    });

    if (token == TokenId::NEWLINE) {
        line++;
        column = 0;
    }
}

const std::vector<Token> Lexer::Tokenize(std::string input) const {
    std::vector<Token> tokens;
    std::string buffer = "";

    uint32_t line = 1, column = 0;

    for (long unsigned int i = 0; i < input.length(); i++) {
        buffer += input[i];

        column++;

        cmp("fn",          TokenId::FN)
        else cmp("mut",    TokenId::MUT)
        else cmp("return", TokenId::RET)
        else cmp("let",    TokenId::LET)
        else cmp("(",      TokenId::LPAREN)
        else cmp(")",      TokenId::RPAREN)
        else cmp("{",      TokenId::LBRACE)
        else cmp("}",      TokenId::RBRACE)
        else cmp(":",      TokenId::COLON)
        else cmp("=",      TokenId::EQUALS)
        else cmp(",",      TokenId::COMMA)
        else cmp(";",      TokenId::SEMICOLON)
        else cmp(".",      TokenId::DOT)
        else cmp("*",      TokenId::ASTERISK)
        else cmp("\n",     TokenId::NEWLINE)
        else {
            if (buffer == " " || buffer == "\t") {
                buffer.clear();
                
                continue;
            }

            // ident, num, string, singleline comment
        }
    }

    std::cout << buffer << std::endl;

    return tokens;
}
