#include "ast.h"

#include "analyzer/analyzer.h"

namespace neonc {
    std::shared_ptr<Node> AbstractSyntaxTree::get_root_ptr() {
        return root;
    }

    void AbstractSyntaxTree::dump() const {
        root->dump(0);
    }

    void AbstractSyntaxTree::verify() {
        auto analyzer = Analyzer(absolute_file_path);

        analyzer.analyze(get_root_ptr());

        verified = true;
    }

    void AbstractSyntaxTree::build(Module & module) {
        if (!verified) {
            std::cerr << "ICE: unable to build unverified ast, call verify()" << std::endl;
            exit(0);
        }

        root->build(module);

        built = true;
    }

    void AbstractSyntaxTree::finalize(Module & module) {
        if (!built) {
            std::cerr << "ICE: unable to finalize unbuilt ast, call build()" << std::endl;
            exit(0);
        }
        
        root->finalize(module);
    }
}
