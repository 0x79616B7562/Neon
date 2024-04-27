package neonc

import (
	"fmt"
	"neon/pkg/llvm"
)

type AST struct {
	Name  string
	Items []Item
}

func (ast *AST) Dump() {
	for _, item := range ast.Items {
		fmt.Println(item.String())
	}
}

func (ast *AST) Build(module llvm.Module) {
	for _, item := range ast.Items {
		item.Build(module)
	}
}
