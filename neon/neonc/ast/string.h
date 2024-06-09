#pragma once

#include "node.h"
#include <neonc.h>

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

    struct String : public Node {
        String(const std::string string, const std::optional<Position> position): string(string), Node(position) {}

        virtual NodeId id() const {
            return NodeId::String;
        }
        
        virtual void dump(const uint32_t indentation) const {
            (void)indentation;

            std::cout << "\"" << escape_string(string) << "\"";
        }

        void * build(Module & module) {
            return module.get_builder()->CreateGlobalString(string);
        }

        std::string string;
    };
}
