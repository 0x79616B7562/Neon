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
	fmt.Printf("AST<Name: %q>\n", ast.Name)

	for _, item := range ast.Items {
		fmt.Println(item.String(1))
	}
}

func (ast *AST) Build(module llvm.Module) {
	for _, item := range ast.Items {
		item.Build(module)
	}
}
