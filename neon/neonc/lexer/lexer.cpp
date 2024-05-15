#include "lexer.h"

#define cmp(str, id) if (buffer == str) { add_token(tokens, id, buffer, line, column); buffer.clear(); }

inline void add_token(std::vector<Token> & tokens, TokenId token, std::string value, uint32_t & line, uint32_t & column) {
    tokens.push_back(Token {
        token,
        value,
        line,
        column - uint32_t(value.size()) + 1
    });

    if (token == TokenId::NEWLINE) {
        line++;
        column = 0;
    }
}

const std::vector<Token> Lexer::Tokenize(std::string _input) const {
    std::vector<Token> tokens;
    std::string buffer = "";
    std::string input = _input + "\n";

    uint32_t line = 1, column = 0;
    bool in_string = false;

    const auto IDENTIFIER = std::regex((char*)"^[a-zA-Z_]+[a-zA-Z0-9_]*$");
    const auto NUMBER = std::regex((char*)"^[-]?[0-9]+[0-9_]*$");
    const auto FLOATING_NUMBER = std::regex((char*)"^[-]?[0-9]+[0-9_]*[.][0-9_]+$");
    const auto STRING = std::regex((char*)"^\"(?:\\\\.|[^\"\\\\])*\"$");

    for (long unsigned int i = 0; i < input.length(); i++) {
        buffer += input[i];

        column++;

        if (in_string)
            goto in_string_block;

toks:
        cmp("fn",          TokenId::FN)
        else cmp("mut",    TokenId::MUT)
        else cmp("return", TokenId::RET)
        else cmp("let",    TokenId::LET)
        else cmp("true",   TokenId::TRUE)
        else cmp("false",  TokenId::FALSE)
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
        else cmp("+",      TokenId::PLUS)
        else cmp("-",      TokenId::MINUS)
        else cmp("/",      TokenId::SLASH)
        else cmp("%",      TokenId::PERCENT)
        else cmp("!",      TokenId::EXCLAMATION)
        else cmp("&",      TokenId::AND)
        else cmp("|",      TokenId::OR)
        else cmp(">",      TokenId::GREATER_THAN)
        else cmp("<",      TokenId::LESS_THAN)
        else cmp("^",      TokenId::CIRC)
        else cmp("\n",     TokenId::NEWLINE)
        else {
            if (buffer == "\"") {
                in_string = true;
    
                continue;
            }

            if (buffer == " " || buffer == "\t") {
                buffer.pop_back();

                goto toks;
            }

            auto tmp = buffer;
            tmp.pop_back();

            if (!std::regex_match(buffer, IDENTIFIER) && std::regex_match(tmp, IDENTIFIER)) {
                add_token(tokens, TokenId::IDENT, tmp, line, column);
                buffer = buffer.back();
            
                goto toks;
            } else if (!std::regex_match(buffer, NUMBER) && std::regex_match(tmp, NUMBER)) {
                if (input[i + 1] != '.' && input[i] != '.') {
                    add_token(tokens, TokenId::NUMBER, tmp, line, column);
                    buffer = buffer.back();

                    goto toks;
                }
            } else if (!std::regex_match(buffer, FLOATING_NUMBER) && std::regex_match(tmp, FLOATING_NUMBER)) {
                add_token(tokens, TokenId::FLOATING_NUMBER, tmp, line, column);
                buffer = buffer.back();
            
                goto toks;
            }
        }

        continue;
in_string_block:
        if (buffer.back() == '\"') {
            in_string = false;
           
            add_token(tokens, TokenId::STRING, buffer, line, column);
           
            line += std::accumulate(buffer.cbegin(), buffer.cend(), 0, [](int prev, char c) { return c != '\n' ? prev : prev + 1; });

            buffer = "";
        }
    }

    tokens.push_back(Token {
        TokenId::ENDOFFILE,
        "",
        line,
        1
    });

    return tokens;
}
