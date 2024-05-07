#include "parser.h"

Parser::Parser() {
}

void Parser::walk(Pack * pack, Node * node) const {
    while (true) {
        if (pack->is_at_end()) {
            break;
        }
    
        bool found = false;

        for (auto ff : FIRST_FOLLOW) {
            if (ff.first == pack->get().token) {
                if (ff.follow != nullptr) {
                    auto result = ff.follow(pack, node);
                
                    if (!result) {
                        return;
                    }
                }

                found = true;
            
                break;
            }
        }

        if (!found) {
            std::cout << ColorRed << "Parser > Unknown TokenId" << ColorReset << ": " << pack->get().token << std::endl;
        }

        pack->next();
    }
}

const Ast Parser::parse(std::vector<Token> tokens) const {
    auto pack = Pack(tokens);
    auto ast = Ast(Node(Data(AstId::ROOT)));

    walk(&pack, ast.get_root_ptr());

    return ast;
}
