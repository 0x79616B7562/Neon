#include "err.h"

void throw_parse_error(const Pack * pack, const char * message) {
    auto tok = pack->get();
    auto src = extract_from_file(pack->file_name, tok.line);

    std::cout << ColorRed << BoldFont << "Error" << ColorCyan << " -> " << ColorReset << pack->file_name << "\n";
    std::cout << ColorCyan << std::string(std::to_string(tok.line).length(), ' ') << " |" << ColorReset << "\n";
    std::cout << ColorCyan << tok.line << " | " << ColorReset << src << "\n";
    std::cout << ColorCyan << std::string(std::to_string(tok.line).length(), ' ') << " |";
    std::cout << ColorRed << std::string(tok.column, ' ') << "^ " << message << ", found " << tok.token << ColorReset << "\n" << std::endl;

    exit(0);
}
