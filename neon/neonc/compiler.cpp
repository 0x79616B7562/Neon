#include "compiler.h"

#include "util/measure.h"
#include "util/cwd.h"
#include "util/read_file.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include <neonc.h>
#include "llvm/target.h"

namespace neonc {
    void build(const char * entry) {
        auto measure = Measure();

        auto cwd = get_cwd();

        auto file_path = cwd + "/" + std::string(entry);
        auto file = read_file(file_path);

        auto lexer = Lexer();
        auto tokens = lexer.Tokenize(file_path, file);
        for (auto tok : tokens) tok.dump();
        std::cout << std::endl;

        auto parser = Parser();
        auto ast = parser.parse_ast(file_path, tokens);

        ast.dump();
        std::cout << std::endl;

        auto target = Target();
        auto module = target.create_module(std::string(entry));

        ast.verify();
        ast.build(module);

        module.dump();
        module.verify();

        target.module_to_object_file(module, file_path);

        measure.finish("FINISHED IN:");
    }
}
