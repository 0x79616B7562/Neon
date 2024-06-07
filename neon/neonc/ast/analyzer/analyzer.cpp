#include "analyzer.h"

#include "analyzers/type_inference.h"

namespace neonc {
    void Analyzer::analyze(std::shared_ptr<Node> root) {
        type_inference(root);
    }
}
