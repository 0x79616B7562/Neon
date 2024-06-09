#include "err.h"

namespace neonc {
    void throw_error(const std::string absolute_file_path, const std::optional<Position> position, const char * message) {
        if (!position) {
            std::cerr << "ICE: position has no value in analyzer::err" << std::endl;
            exit(0);
        }

        auto src = extract_from_file(absolute_file_path, position->line);

        std::cout << ColorRed << BoldFont << "Error" << ColorCyan << " -> " << ColorReset << absolute_file_path << "\n";
        std::cout << ColorCyan << position->line << " | " << ColorReset << src << "\n";
        std::cout << ColorCyan << std::string(std::to_string(position->line).length(), ' ') << " |";

        std::cout << ColorRed << std::string(position->column, ' ') << "^ " << message << ColorReset << "\n" << std::endl;
    }
}
