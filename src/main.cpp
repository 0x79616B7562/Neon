#include "lexer/lexer.h"
#include "util/cwd.h"
#include "util/read_file.h"
#include <iostream>

int main() {
    std::cout << "RUNNING" << std::endl;

    auto cwd = get_cwd();

    std::string file = read_file(cwd + "/main.n");

    auto lexer = Lexer();
    lexer.Tokenize(file);

    return 0;
}
