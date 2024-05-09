#include <iostream>
#include "util/measure.h"
#include "util/cwd.h"
#include "util/read_file.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

void build(const std::string entry) {
    auto measure = Measure();

    auto cwd = get_cwd();

    auto file_path = cwd + "/" + entry;
    auto file = read_file(file_path);

    auto lexer = Lexer();
    auto tokens = lexer.Tokenize(file);
    for (auto tok : tokens) tok.dump();
    std::cout << std::endl;

    auto parser = Parser();
    auto ast = parser.parse(file_path, tokens);
    ast.dump();
    std::cout << std::endl;

    measure.finish("FINISHED IN:");
}

auto main(int argc, char * argv[]) -> int {
    build(argv[1]);

    return 0;
}
