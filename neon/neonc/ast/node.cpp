#include "node.h"

#define INDENT_MULTIPLIER 4

void Node::dump(const int indent) const {
    constexpr char * array[5] = {
        (char *)ColorCyan,
        (char *)ColorYellow,
        (char *)ColorBlue,
        (char *)ColorGreen,
        (char *)ColorMagenta,
    };

    std::cout << ColorGray << std::string(indent * INDENT_MULTIPLIER, ' ') << BoldFont << array[indent % (std::end(array) - std::begin(array))] << id << " " << ColorReset;

    if (data)
        std::cout << "\"" << data.value() << "\" ";

    if (position)
        std::cout << "<" << std::get<0>(position.value()) << ":" << std::get<1>(position.value()) << "> ";

    if (build)
        std::cout << ColorRed << BoldFont << "B " << ColorReset;

    if (nodes.size() > 0) {
        std::cout << "{" << std::endl;

        for (Node child : nodes)
            child.dump(indent + 1);

        std::cout << std::string(indent * INDENT_MULTIPLIER, ' ') << "}" << std::endl;
    } else {
        std::cout << std::endl;
    }
}

bool Node::has_any(AstId id) const {
    for (auto node : nodes) {
        if (node.id == id)
            return true;

        if (node.has_any(id))
            return true;
    }

    return false;
}

bool Node::contains(AstId id) const {
    for (auto node : nodes)
        if (node.id == id)
            return true;

    return false;
}

std::vector<Node> Node::get_all(AstId id) const {
    std::vector<Node> result;

    for (auto node : nodes)
        if (node.id == id)
            result.push_back(node);

    return result;
}

std::optional<Node *> Node::get_node(AstId id) {
    auto it = std::find_if(std::begin(nodes), std::end(nodes), [id](const Node & node) {
        return node.id == id;
    });

    if (it == std::end(nodes))
        return std::nullopt;

    return &*it;
}

Node * Node::get_last_node() {
    if (nodes.empty())
        return this;

    return nodes.back().get_last_node();
}
