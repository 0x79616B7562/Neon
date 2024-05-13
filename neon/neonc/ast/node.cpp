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

void Node::add_node(AstId id, const std::optional<std::string> data) {
    nodes.push_back(Node(id, data, std::nullopt));
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

std::vector<Node *> Node::get_all(AstId id, bool recursive) {
    std::vector<Node *> result;

    for (unsigned long int i = 0; i < nodes.size(); i++) {
        if (nodes[i].id == id)
            result.push_back(&nodes[i]);
        
        if (recursive) {
            auto children = nodes[i].get_all(id, true);
            for (auto _a : children) result.push_back(_a);
        }
    }

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
