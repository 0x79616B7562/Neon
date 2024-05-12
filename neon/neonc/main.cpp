#include "util/measure.h"
#include "util/cwd.h"
#include "util/read_file.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "builder/target.h"
#include "analyzer/analyzer.h"
#include <neonc.h>

void build_bodies(Node * node, Module * module) {
    if (node->build.has_value())
        node->build.value()(node, module);

    for (long unsigned int i = 0; i < node->nodes.size(); i++)
        build_bodies(&node->nodes[i], module);
}

void build_ast(Node * node, Module * module) {
    if (node->build.has_value()) {
        node->build.value()(node, module);
    }

    for (long unsigned int i = 0; i < node->nodes.size(); i++)
        if (node->nodes[i].id == AstId::FUNCTION)
            if (node->nodes[i].build)
                node->nodes[i].build.value()(&node->nodes[i], module);

    for (long unsigned int i = 0; i < node->nodes.size(); i++) {
        if (node->nodes[i].id == AstId::FUNCTION) {
            auto name = node->nodes[i].data.value();
            module->pointer = name;

            for (long unsigned int j = 0; j < node->nodes[i].nodes.size(); j++)
                build_bodies(&node->nodes[i].nodes[j], module);
        }
    }
}

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
    auto ast = parser.parse_ast(file_path, tokens);
    ast.dump();
    std::cout << std::endl;

    auto analyzer = Analyzer();
    analyzer.analyze(&ast);

    auto target = Target();
    target.dump_target_triple();

    std::cout << std::endl;

    auto module = target.create_module(entry);

    build_ast(ast.get_root_ptr(), &module);

    // target.optimize(&module);
    module.dump();

    target.module_to_object_file(module, file_path);

    std::cout << std::endl;

    measure.finish("FINISHED IN:");
}

auto main(int argc, char * argv[]) -> int {
    build(argv[1]);

    return 0;
}
