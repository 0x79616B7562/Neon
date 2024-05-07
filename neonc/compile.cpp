#include "compile.h"

void compile(int argc, char * argv[]) {
    auto measure = Measure();

    auto cwd = get_cwd();

    if (argc < 1) return;
    auto file_path = cwd + "/" + argv[1]; // fix
    auto file = read_file(file_path);

    auto lexer = Lexer();
    auto tokens = lexer.Tokenize(file);
    for (auto tok : tokens) tok.dump();
    std::cout << std::endl;

    auto parser = Parser();
    auto ast = parser.parse(file_path, tokens);
    ast.dump();
    std::cout << std::endl;

    auto target = nir::Target();

    auto module = build_nir_from_ast(file_path, ast);

    module.dump();
    std::cout << std::endl;

    target.nir_module_to_object_file(module, file_path, true);
    std::cout << std::endl;

    measure.finish("FINISHED IN:");
}

   //  std::cout << "RUNNING\n" << std::endl;
   //
   //  auto cwd = get_cwd();
   //  auto file_path = cwd + "/main.n";
   //
   //  auto measure = Measure();
   //  std::string file = read_file(file_path);
   //  measure.finish("READING FILE:");
   //
   //  measure.reset();
   //  auto lexer = Lexer();
   //  auto tokens = lexer.Tokenize(file);
   //  measure.finish("TOKENIZING:");
   //
   //  std::cout << std::endl;
   //
   //  std::cout << "Tokens:" << std::endl;
   //  for (auto tok : tokens)
   //      tok.dump();
   //  std::cout << std::endl;
   //
   //  measure.reset();
   //  auto parser = Parser();
   //  auto ast = parser.parse(file_path, tokens);
   //  measure.finish("PARSING:");
   //
   //  std::cout << std::endl;
   //
   //  std::cout << "Abstract Syntax Tree:" << std::endl;
   //  ast.dump();
   //
   //  return 0;
   //
   //  std::cout << std::endl;
   //
   //  std::cout << "NeonIR Module:" << std::endl;
   //
   //  measure.reset();
   //
   //  auto target = nir::Target();
   //
   //  auto module = nir::Module(file_path);
   //
   //  auto func = module.create_function("main", nir::Type::I32);
   //  func->add_block("a");
   //  func->add_block("b");
   // 
   //  func->get("a")->add_object<nir::Goto>(func->get("b"));
   //  func->get("b")->add_object<nir::Return>(nir::ConstInt(nir::Type::I32, 0));
   //
   //  module.dump();
   //
   //  std::cout << "\nLLVMIR:" << std::endl;
   //  target.nir_module_to_object_file(module, file_path, true);
   //
   //  std::cout << std::endl;
   //
   //  measure.finish("NeonIR:");
   //
   //  std::cout << std::endl;
   //
   //  whole.finish("Done in:");


