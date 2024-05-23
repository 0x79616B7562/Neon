#include "lexer.h"

#define cmp(s, t) if (ident == s) return t;

namespace neonc {
    inline void throw_error(const std::string file_path, uint32_t line, uint32_t column, const char * value, const char * message) {
        auto src = extract_from_file(file_path, line);

        std::cout << ColorRed << BoldFont << "Error" << ColorCyan << " -> " << ColorReset << file_path << "\n";
        std::cout << ColorCyan << line << " | " << ColorReset << src << "\n";
        std::cout << ColorCyan << std::string(std::to_string(line).length(), ' ') << " |";

        std::cout << ColorRed << std::string(column, ' ') << "^ " << message << ", found '" << value << "'" << ColorReset << "\n" << std::endl;

        exit(0);
    }

    inline void add_token(std::vector<Token> & tokens, TokenId token, std::string value, uint64_t & line, uint64_t & column) {
        tokens.push_back(Token {
            token,
            value,
            line,
            column - uint64_t(value.size()) + 2
        });

        if (token == TokenId::NEWLINE) {
            line++;
            column = 0;
        }
    }

    constexpr inline bool is_ident(char ch, bool include_nums = true) {
        return include_nums ? (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '_'
            : (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
    }

    constexpr inline bool is_number(char ch, bool include_underscore = true) {
        return include_underscore ? (ch >= '0' && ch <= '9') || ch == '_' : ch >= '0' && ch <= '9';
    }

    constexpr inline TokenId resolve_ident(std::string ident) {
        cmp("fn", TokenId::FN)
        cmp("let", TokenId::LET)
        cmp("mut", TokenId::MUT)
        cmp("true", TokenId::TRUE)
        cmp("false", TokenId::FALSE)
        cmp("return", TokenId::RET)

        return TokenId::IDENT;
    }

    constexpr inline bool is_single(char ch) {
        return ch == '('
            || ch == ')'
            || ch == '{'
            || ch == '}'
            || ch == ':'
            || ch == '='
            || ch == ','
            || ch == ';'
            || ch == '.'
            || ch == '*'
            || ch == '+'
            || ch == '-'
            || ch == '/'
            || ch == '%'
            || ch == '!'
            || ch == '&'
            || ch == '|'
            || ch == '>'
            || ch == '<'
            || ch == '^';
    }

    constexpr inline TokenId resolve_single(char ch) {
        switch (ch) {
        case '(': return TokenId::LPAREN;
        case ')': return TokenId::RPAREN;
        case '{': return TokenId::LBRACE;
        case '}': return TokenId::RBRACE;
        case ':': return TokenId::COLON;
        case '=': return TokenId::EQUALS;
        case ',': return TokenId::COMMA;
        case ';': return TokenId::SEMICOLON;
        case '.': return TokenId::DOT;
        case '*': return TokenId::ASTERISK;
        case '+': return TokenId::PLUS;
        case '-': return TokenId::MINUS;
        case '/': return TokenId::SLASH;
        case '%': return TokenId::PERCENT;
        case '!': return TokenId::EXCLAMATION;
        case '&': return TokenId::AND;
        case '|': return TokenId::OR;
        case '<': return TokenId::LESS_THAN;
        case '>': return TokenId::GREATER_THAN;
        case '^': return TokenId::CIRC;
        }

        return TokenId::INVALID;
    }

    constexpr inline bool is_whitespace(char ch) {
        return ch == ' ' || ch == '\t';
    }

    const std::vector<Token> Lexer::Tokenize(const std::string file_path, std::string _input) const {
        std::vector<Token> tokens;
        std::string input = _input + " ";
        long long cursor = 0;
        std::string buffer = "";

        uint64_t line = 1, column = 0;
        bool in_string = false;
        int32_t indentation = 0;
        uint32_t last_l_brace_l = 0, last_l_brace_c = 0;

        long long __size = input.size();
        while (1) {
            if (__size <= cursor)
                break;

            if (in_string)
                goto in_string_block;

            if (input[cursor] == '\n') {
                add_token(tokens, TokenId::NEWLINE, "\n", line, column);
                cursor++;

                continue;
            }

            if (input[cursor] == '\"') {
                in_string = true;
                cursor++;
                column++;

                continue;
            }

            if (is_ident(input[cursor], false)) {
                while (buffer.length() < 1 ? is_ident(input[cursor], false) : is_ident(input[cursor])) {
                    buffer += input[cursor];
                    column++;
                    cursor++;
                }

                add_token(tokens, resolve_ident(buffer), buffer, line, column);

                buffer.clear();

                cursor--;
            } else if (is_number(input[cursor], false)) {
                bool is_floating_point = false;
    num:
                while (buffer.length() < 1 ? is_number(input[cursor], false) : is_number(input[cursor])) {
                    buffer += input[cursor];
                    column++;
                    cursor++;
                }

                if (input[cursor] == '.' && is_number(input[cursor + 1])) {
                    buffer += input[cursor];

                    cursor++;
                    column++;
                    is_floating_point = true;

                    goto num;
                }

                add_token(tokens, is_floating_point ? TokenId::FLOATING_NUMBER : TokenId::NUMBER, buffer, line, column);

                buffer.clear();

                cursor--;
            } else if (is_single(input[cursor])) {
                add_token(tokens, resolve_single(input[cursor]), std::string(1, input[cursor]), line, column);

                if (input[cursor] == '{') {
                    last_l_brace_l = line;
                    last_l_brace_c = column;

                    indentation++;
                } else if (input[cursor] == '}') {
                    indentation--;

                    if (indentation < 0) {
                        throw_error(file_path, line, column + 1, "}", "unexpected closing delimiter");
                    }
                }
                
                column++;

                buffer.clear();
            } else if (is_whitespace(input[cursor])) { // ignore
                column++;
            } else {
                add_token(tokens, TokenId::INVALID, std::string(1, input[cursor]), line, column);

                column++;

                buffer.clear();
            }

            cursor++;
            continue;
    in_string_block:
            if (input[cursor] == '\"') {
                in_string = false;

                add_token(tokens, TokenId::STRING, buffer, line, column);

                buffer = "";

                cursor++;
                column++;
            } else {
                buffer += input[cursor];
                cursor++;
                column++;
            }
        }

        if (indentation > 0) {
            throw_error(file_path, last_l_brace_l, last_l_brace_c + 1, "{", "unclosed delimiter");
        }

        tokens.push_back(Token {
            TokenId::ENDOFFILE,
            "",
            line,
            1
        });

        return tokens;
    }
}
