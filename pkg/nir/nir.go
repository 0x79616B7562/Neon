package nir

import (
	"fmt"
	"neon/pkg/ast"
	"neon/pkg/util"
)

type NeonIR struct {
	module Module
}

func NewNeonIR(filePath string) NeonIR {
	return NeonIR{
		module: NewModule(filePath),
	}
}

func (n *NeonIR) walk(node ast.Node) {
	found := false
	var hook Hook

	for _, t := range TRIGGERS {
		if node.Id == t.Trigger {
			if t.Action != nil {
				hook = t.Action(n, &node)
			}

			found = true
		}
	}

	if !found && node.Id != ast.ROOT {
		fmt.Println(util.MakeRed(util.MakeBold("NeonIR Error")) + ": " + "Unknown ID: " + util.MakeCyan(node.Id.String()))
	}

	for _, node := range node.Nodes {
		n.walk(node)
	}

	if hook != nil {
		hook()
	}
}

func (n *NeonIR) Generate(ast ast.AST) Module {
	n.walk(ast.Root)

	return n.module
}

func (n *NeonIR) Dump() {
	n.module.Dump()
}
