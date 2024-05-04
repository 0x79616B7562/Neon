#include "lexer.h"

Lexer::Lexer() {
    for (int i = 0; i < std::size(TOKENS); i++) {
        auto tok = TokenDef {
            TOKENS[i].token,
            TOKENS[i].match,
            TOKENS[i].do_discard,
            TOKENS[i].is_regex,
        };

        if (tok.is_regex) {
            tok.regex = std::regex(TOKENS[i].match);
        }

        tokens[i] = tok;
    }
}

inline const std::optional<const TokenDef> Lexer::match(const std::string & input) const {
    for (auto tok : tokens) {
        if (tok.is_regex) {
            if (std::regex_match(input, tok.regex)) {
                return tok;
            }
        } else {
            if (input == tok.match) {
                return tok;
            }
        }
    }

    return {};
}

inline bool Lexer::do_discard_token(const TokenId id) const {
    for (auto tok : tokens) {
        if (tok.token == id) {
            return tok.do_discard;
        }
    }

    return false;
}

const std::vector<Token> Lexer::Tokenize(std::string input) const {
    std::string buf;
    std::vector<Token> tokens;
    bool found = false;
    uint32_t line = 1;
    uint32_t column = 0;

    for (int i = 0; i < input.length(); i++) {
        buf += input[i];

        column++;

        auto tok = match(buf);

        if (tok.has_value())
            found = true;
        else if (!tok.has_value() && found) {
            found = false;

            auto tmp = buf.substr(0, buf.size()-1);

            i--;
            column--;

            auto tok = match(tmp);

            if (tok.has_value()) {
                if (!do_discard_token(tok.value().token)) {
                    tokens.push_back(Token {
                        tok.value().token,
                        tmp,
                        line,
                        column,
                    });
                }
            
                if (tok.value().token == TokenId::NEWLINE) {
                    line++;
                    column = 0;
                }
            }

            buf = "";
        }
    }

    tokens.push_back(Token {
        TokenId::ENDOFFILE,
        "",
        line,
        column,
    });

    return tokens;
}
