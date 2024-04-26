package neonc

import "fmt"

type AST struct {
	Items []Item
}

func (ast *AST) Dump() {
	for _, item := range ast.Items {
		fmt.Println(item.String())
	}
}
