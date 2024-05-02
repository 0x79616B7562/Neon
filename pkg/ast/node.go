package ast

import (
	"fmt"
	"strings"
)

type Node struct {
	Id    Id
	Data  []Data
	Nodes []Node
}

func (n *Node) Dump(indent int) {
	spaces := strings.Repeat(" ", indent*4)
	fmt.Printf(spaces+"Id: %s", n.Id)

	if len(n.Data) > 0 {
		fmt.Printf(", Data: %v", n.Data)
	}

	fmt.Println()

	for _, n := range n.Nodes {
		n.Dump(indent + 1)
	}
}
