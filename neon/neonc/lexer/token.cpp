#include "token.h"

namespace neonc {
    namespace {
        static const std::string escape_string(const std::string & input_string) {
            std::ostringstream escaped_string;
            for (char current_char : input_string) {
                switch (current_char) {
                    case '\n':
                        escaped_string << "\\n";
                        break;
                    case '\t':
                        escaped_string << "\\t";
                        break;
                    case '\r':
                        escaped_string << "\\r";
                        break;
                    case '\\':
                        escaped_string << "\\\\";
                        break;
                    case '\"':
                        escaped_string << "\\\"";
                        break;
                    default:
                        escaped_string << current_char;
                        break;
                }
            }

            return escaped_string.str();
        }
    }

    void Token::dump() const {
        auto v = value;

        if (v.empty()) {
            std::cout << ColorRed << token << ColorReset << std::endl;

            return;
        }

        std::cout << ColorCyan << token << ColorReset << " \"" << escape_string(v) << "\" " << position.string() << std::endl;
    }
}
