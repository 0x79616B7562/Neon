package neonc

import (
	"fmt"
	"neon/pkg/enum"
	"neon/pkg/llvm"
)

func Compile(ast AST) {
	target := llvm.NewTarget()
	defer target.Dispose()

	module := target.CreateModule("test.n")
	fmt.Printf("\nMODULE:\n\n")

	fn_type := llvm.NewFunctionType(enum.VOID)
	fn := module.AddFunction("main", fn_type)
	_ = fn

	module.Dump()
}
