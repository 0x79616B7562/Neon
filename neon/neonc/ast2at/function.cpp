#include "build.h"

namespace neonc {
    void build_function(Node * node, ActionTree * at) {
        if (!node->data.has_value()) {
            std::cerr << "function has no value" << std::endl;
            exit(0);
        }

        auto _type = node->get_node(AstId::TYPE);

        std::vector<Argument> args = {};

        for (auto & arg : node->get_all(AstId::ARGUMENT)) {
            args.push_back(Argument(
                arg->data.value(),
                arg->get_node(AstId::TYPE).value()->data.value()
            ));
        }

        at->add_function(
            node->data.value(),
            node->has_any(AstId::BODY),
            _type.has_value() ? _type.value()->data.value() : "void",
            args,
            node->has_any(AstId::VARIADIC) ? node->get_node(AstId::VARIADIC).value()->data : std::nullopt
        );
    }
}
