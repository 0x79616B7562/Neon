#include "lexer/lexer.h"
#include "parser/parser.h"
#include "util/cwd.h"
#include "util/measure.h"
#include "util/read_file.h"
#include "nir/module.h"

auto main() -> int {
    auto whole = Measure();

    std::cout << "RUNNING\n" << std::endl;

    auto cwd = get_cwd();
    auto file_path = cwd + "/main.n";

    auto measure = Measure();
    std::string file = read_file(file_path);
    measure.finish("READING FILE:");

    measure.reset();
    auto lexer = Lexer();
    auto tokens = lexer.Tokenize(file);
    measure.finish("TOKENIZING:");

    std::cout << std::endl;

    std::cout << "Tokens:" << std::endl;
    for (auto tok : tokens)
        tok.dump();
    std::cout << std::endl;

    measure.reset();
    auto parser = Parser();
    auto ast = parser.parse(tokens);
    measure.finish("PARSING:");

    std::cout << std::endl;

    std::cout << "Abstract Syntax Tree:" << std::endl;
    ast.dump();

    std::cout << std::endl;

    std::cout << "NeonIR Module:" << std::endl;

    measure.reset();

    auto module = nir::Module(file_path);
    auto func = module.create_function("main", Type::I32);
    auto block = func->create_block("entry");

    module.dump();

    std::cout << std::endl;

    measure.finish("NeonIR:");

    std::cout << std::endl;

    whole.finish("Done in:");

    return 0;
}
