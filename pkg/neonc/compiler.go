package neonc

import (
	"neon/pkg/enum"
	"neon/pkg/llvm"
)

func Compile(ast AST) {
	target := llvm.NewTarget()
	defer target.Dispose()

	module := target.CreateModule("test.n")
	defer module.Dispose()

	fn_type := llvm.NewFunctionType(enum.VOID)
	fn := module.AddFunction("main", fn_type)
	fn.AddRet(enum.VOID)

	module.Verify()

	module.Dump()
	target.ModuleToObjectFile(module, "out.o")
}
