package compiler

import "neon/pkg/ast"

type Trigger struct {
	Id     ast.Id
	Action func(*Pack, *ast.Node) Hook
}
