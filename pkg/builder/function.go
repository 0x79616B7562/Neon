package builder

import (
	"neon/pkg/ast"
	"neon/pkg/enum"
	"neon/pkg/llvm"
)

type Function struct{}

func (f *Function) AsEnum() enum.Item {
	return enum.FUNCTION
}

func (f *Function) Build(pack *ast.Pack, item ast.AST) ast.Hook {
	id, name := extractDataFromAST(ast.NAME, item.Data)

	if id != ast.NAME {
		panic("ICE: Function doesnt have name")
	}

	vtype := enum.VOID

	if name == "main" {
		vtype = enum.I32
	}

	pack.Function = pack.Module.AddFunction(name, llvm.NewFunctionType(vtype))
	block := pack.Function.AppendBlock("entry")
	pack.Function.SetBuilderToBlockEnd(block)

	if name == "main" {
		return func(pack *ast.Pack, item ast.AST) {
			pack.Function.AddRet(enum.I32, llvm.ConstInt(llvm.IntType(32), 0, llvm.False))
		}
	}

	return nil
}
