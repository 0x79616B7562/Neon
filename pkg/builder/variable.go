package builder

import (
	"log"
	"neon/pkg/ast"
	"neon/pkg/enum"
	"neon/pkg/llvm"
	"strconv"
	"strings"
)

type Variable struct{}

func (f *Variable) AsEnum() enum.Item {
	return enum.VARIABLE
}

func (f *Variable) Build(pack *ast.Pack, item ast.AST) ast.Hook {
	id, name := extractDataFromAST(ast.NAME, item.Data)

	if id != ast.NAME {
		panic("ICE: Variable doesnt have name")
	}

	_, vtype := extractDataFromAST(ast.TYPE, item.Data)
	_, value := extractDataFromAST(ast.VALUE, item.Data)

	_ = vtype

	value = strings.ReplaceAll(value, "_", "")
	ivalue, err := strconv.Atoi(value)

	if err != nil {
		log.Fatal(err)
	}

	val := pack.Function.BuildAlloca(name, llvm.IntType(32))
	pack.Function.BuildStore(llvm.ConstInt(llvm.IntType(32), uint64(ivalue), llvm.False), val)

	return nil
}
