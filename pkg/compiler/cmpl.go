package compiler

import (
	"neon/pkg/ast"
	"neon/pkg/enum"
	"neon/pkg/llvm"
)

func compileFunction(pack *Pack, node *ast.Node) Hook {
	ident, err := extractDataFromNode(ast.IDENT, node.Data)

	if err != nil {
		panic(err)
	}

	rettype := llvm.NewFunctionType(enum.VOID)

	if ident.Value == "main" {
		rettype = llvm.NewFunctionType(enum.I32)
	}

	function := pack.Module.AddFunction(ident.Value, rettype)
	block := function.AppendBlock("entry")
	function.SetBuilderToBlockEnd(block)

	return func(pack *Pack, node *ast.Node) {
		if ident.Value == "main" {
			function.AddRet(enum.I32, llvm.ConstInt(llvm.IntType(32), 0, llvm.False))
		} else if rettype.Is(enum.VOID) {
			function.AddRet(enum.VOID, nil)
		}
	}
}
