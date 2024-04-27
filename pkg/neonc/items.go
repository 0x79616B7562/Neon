package neonc

import (
	"fmt"

	"neon/pkg/enum"
	"neon/pkg/llvm"
)

type Item interface {
	String() string
	Build(llvm.Module)
}

//

type FnDeclaration struct {
	name string
}

func (f *FnDeclaration) String() string {
	return fmt.Sprintf("FN<%s>", f.name)
}

func (f *FnDeclaration) Build(module llvm.Module) {
	fn_type := llvm.NewFunctionType(enum.VOID)
	fn := module.AddFunction(f.name, fn_type)
	block := fn.AppendBlock("entry")
	fn.SetBuilderToBlockEnd(block)
	fn.AddRet(enum.VOID)
}
