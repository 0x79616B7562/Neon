#include "parser.h"

namespace neonc {
    const AbstractSyntaxTree Parser::parse_ast(const std::string absolute_file_path, std::vector<Token> tokens) const {
        auto pack = Pack(absolute_file_path, tokens);

        auto ast = AbstractSyntaxTree(
            std::make_shared<Root>(get_root() + "/" + std::filesystem::path(absolute_file_path).filename().string()),
            absolute_file_path
        );

        parse(&pack, ast.get_root_ptr());

        return ast;
    }
}
