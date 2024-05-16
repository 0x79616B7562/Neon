#include "parser.h"

const AbstractSyntaxTree Parser::parse_ast(const std::string file_name, std::vector<Token> tokens) const {
    auto pack = Pack(file_name, tokens);
    auto ast = AbstractSyntaxTree(Node(AstId::ROOT, get_root() + "/" + std::filesystem::path(file_name).filename().string(), {}));

    parse(&pack, ast.get_root_ptr());

    return ast;
}
