package nir

import "neon/pkg/ast"

type Hook func()

type Trigger struct {
	Trigger ast.Id
	Action  func(ir *NeonIR, node *ast.Node) Hook
}

var TRIGGERS = []Trigger{
	{Trigger: ast.FUNCTION, Action: buildFunction},
	{Trigger: ast.BLOCK, Action: buildBlock},
	{Trigger: ast.END, Action: buildEnd},
	{Trigger: ast.VARIABLE, Action: buildVariable},
}
