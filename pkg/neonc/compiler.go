package neonc

import (
	"fmt"

	"neon/pkg/llvm"
)

func Compile(ast AST) {
	fmt.Println("LLVM VERSION:", llvm.Version)

	for _, item := range ast.Items {
		item.Build()
	}
}
