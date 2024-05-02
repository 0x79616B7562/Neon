package compiler

import (
	"neon/pkg/ast"
	"neon/pkg/llvm"
)

func compileFunction(pack *Pack, node *ast.Node) Hook {
	ident, err := extractDataFromNode(ast.IDENT, node.Data)

	if err != nil {
		panic(err)
	}

	rettype := llvm.NewFunctionType(llvm.VOID)

	if ident.Value == "main" {
		rettype = llvm.NewFunctionType(llvm.I32)
	}

	function := pack.Module.AddFunction(ident.Value, rettype)
	block := function.AppendBlock("entry")
	function.SetBuilderToBlockEnd(block)

	return func(pack *Pack, node *ast.Node) {
		if ident.Value == "main" {
			function.AddRet(llvm.I32, llvm.ConstInt(llvm.IntType(32), 0, llvm.False))
		} else if rettype.Is(llvm.VOID) {
			function.AddRet(llvm.VOID, nil)
		}
	}
}
