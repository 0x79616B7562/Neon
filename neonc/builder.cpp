#include "builder.h"

#define EXTRACT_DATA_AND_SOURCE(data_id, result_data, result_source) std::string result_data = ""; std::optional<nir::Source> result_source = {}; { \
    auto data = node.get_data_by_id(data_id); if (!data) return; auto __i = std::get<0>(data.value()).data; if (!__i) return; \
    result_data = __i.value(); if (!std::get<1>(data.value())) return; result_source = std::get<1>(data.value()).value(); }
#define HAS_DATA(data_id) node.get_data_by_id(data_id).has_value()
#define GET_DATA(data_id) node.get_data_by_id(data_id) ? std::get<0>(node.get_data_by_id(data_id).value()).data : std::nullopt

inline void build(nir::Module * module, Node node) {
    switch (node.id) {
    case AstId::FUNCTION:
        {
            EXTRACT_DATA_AND_SOURCE(DataId::IDENTIFIER, ident, source) 
            module->create_function(ident, nir::Type::VOID, source);
        }
        break;
    case AstId::VARIABLE:
        {
            EXTRACT_DATA_AND_SOURCE(DataId::IDENTIFIER, ident, source)
            module->get_last_function()->add_object<nir::Variable>(ident, HAS_DATA(DataId::MUTABLE), GET_DATA(DataId::TYPE), source);
        }
        break;
    default:
        std::cerr << "Unknown id to build: " << node.id << std::endl;
        exit(1);
    }

    for (auto & n : node.nodes)
        build(module, n);
}

inline void walk(nir::Module * module, const Node * node) {
    for (auto & node : node->nodes)
        build(module, node);
}

nir::Module build_nir_from_ast(const std::string file_path, Ast ast) {
    auto module = nir::Module(file_path);

    walk(&module, ast.get_root_ptr());
    
    return module;
}
