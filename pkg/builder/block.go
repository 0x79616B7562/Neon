package builder

import (
	"neon/pkg/ast"
	"neon/pkg/enum"
)

type Block struct{}

func (f *Block) AsEnum() enum.Item {
	return enum.BLOCK
}

func (f *Block) Build(pack *ast.Pack, item ast.AST) ast.Hook {
	return nil
}
