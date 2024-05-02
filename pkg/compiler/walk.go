package compiler

import "neon/pkg/ast"

type Hook func(*Pack, *ast.Node)

var TRIGGERS = []Trigger{
	{Id: ast.FUNCTION, Action: compileFunction},
}

func walk(pack *Pack, node ast.Node) {
	var hook Hook

	for _, trigger := range TRIGGERS {
		if node.Id == trigger.Id {
			hook = trigger.Action(pack, &node)

			break
		}
	}

	for _, node := range node.Nodes {
		walk(pack, node)
	}

	if hook != nil {
		hook(pack, &node)
	}
}
