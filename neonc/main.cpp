#include <frontend/lexer/lexer.h>
#include <nir/objects/return.h>
#include <nir/objects/goto.h>
#include <nir/target.h>
#include <frontend/parser/parser.h>
#include <frontend/util/cwd.h>
#include <frontend/util/measure.h>
#include <frontend/util/read_file.h>
#include <nir/module.h>

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

    auto target = nir::Target();

    auto module = nir::Module(file_path);

    auto func = module.create_function("main", nir::Type::I32);
    func->add_block("a");
    func->add_block("b");
   
    func->get("a")->add_object<nir::Goto>(func->get("b"));
    func->get("b")->add_object<nir::Return>(nir::ConstInt(nir::Type::I32, 0));

    module.dump();

    std::cout << "\nLLVMIR:" << std::endl;
    target.nir_module_to_object_file(module, file_path, true);

    std::cout << std::endl;

    measure.finish("NeonIR:");

    std::cout << std::endl;

    whole.finish("Done in:");

    return 0;
}
