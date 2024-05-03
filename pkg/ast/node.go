package ast

import (
	"fmt"
	"neon/pkg/util"
	"strings"
)

type Node struct {
	Id    Id
	Data  []Data
	Nodes []Node
}

func (n *Node) Dump(indent int) {
	spaces := strings.Repeat(" ", indent*4)
	fmt.Printf(spaces+"Id: "+util.ColorCyan+util.Bold+"%s"+util.ColorReset, n.Id)

	if len(n.Data) > 0 {
		fmt.Print(" > ")
		for i, d := range n.Data {
			if i > 0 {
				fmt.Print(", ")
			}

			fmt.Printf("%s", d.String())
		}
	}

	fmt.Println()

	for _, n := range n.Nodes {
		n.Dump(indent + 1)
	}
}
