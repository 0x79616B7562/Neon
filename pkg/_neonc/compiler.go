package neonc

import (
	// "neon/pkg/enum"
	"neon/pkg/llvm"
)

func Compile(ast AST) {
	target := llvm.NewTarget()
	defer target.Dispose()

	module := target.CreateModule(ast.Name)
	defer module.Dispose()

	ast.Build(module)

	// fn_type := llvm.NewFunctionType(enum.VOID)
	// fn := module.AddFunction("main", fn_type)
	// block := fn.AppendBlock("entry")
	// fn.SetBuilderToBlockEnd(block)
	// fn.AddRet(enum.VOID)

	module.Verify()

	module.Dump()
	target.ModuleToObjectFile(module, "out.o")
}
