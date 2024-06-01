#include "err.h"

namespace neonc {
    void throw_parse_error(const Pack * pack, const char * message) {
        auto tok = pack->get();
        auto src = extract_from_file(pack->file_name, tok.position.line);

        std::cout << ColorRed << BoldFont << "Error" << ColorCyan << " -> " << ColorReset << pack->file_name << "\n";
        std::cout << ColorCyan << tok.position.line << " | " << ColorReset << src << "\n";
        std::cout << ColorCyan << std::string(std::to_string(tok.position.line).length(), ' ') << " |";

        if (
            tok.value.empty()
            || tok.token == TokenId::NEWLINE
            || tok.token == TokenId::WHITESPACE
            || tok.token == TokenId::TAB
            || tok.token == TokenId::ENDOFFILE
        ) {
            std::cout << ColorRed << std::string(tok.position.column, ' ') << "^ " << message << ", found '" << tok.token << "'" << ColorReset << "\n" << std::endl;
        } else {
            std::cout << ColorRed << std::string(tok.position.column, ' ') << "^ " << message << ", found '" << tok.value << "'" << ColorReset << "\n" << std::endl;
        }

        exit(0);
    }

    void throw_parse_error_at_position(const Pack * pack, const Position position, const char * message) {
        auto src = extract_from_file(pack->file_name, position.line);

        std::cout << ColorRed << BoldFont << "Error" << ColorCyan << " -> " << ColorReset << pack->file_name << "\n";
        std::cout << ColorCyan << position.line << " | " << ColorReset << src << "\n";
        std::cout << ColorCyan << std::string(std::to_string(position.line).length(), ' ') << " |";

        std::cout << ColorRed << std::string(position.column, ' ') << "^ " << message << ColorReset << "\n" << std::endl;

        exit(0);
    }
}
