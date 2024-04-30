package builder

import (
	"neon/pkg/ast"
	"neon/pkg/enum"
)

type Head struct{}

func (f *Head) AsEnum() enum.Item {
	return enum.HEAD
}

func (f *Head) Build(pack *ast.Pack, item ast.AST) ast.Hook {
	return nil
}
