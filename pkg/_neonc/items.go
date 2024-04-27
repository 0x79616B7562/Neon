package neonc

import (
	"fmt"
	"strings"

	"neon/pkg/enum"
	"neon/pkg/llvm"
)

type Item interface {
	String(indent int) string
	Build(llvm.Module)
}

//

type FnDeclaration struct {
	name string
}

func (f *FnDeclaration) String(indent int) string {
	return strings.Repeat(" ", indent*4) + fmt.Sprintf("FN<Name: %q>", f.name)
}

func (f *FnDeclaration) Build(module llvm.Module) {
	fn_type := llvm.NewFunctionType(enum.VOID)
	fn := module.AddFunction(f.name, fn_type)
	block := fn.AppendBlock("entry")

	fn.SetBuilderToBlockEnd(block)
	fn.AddRet(enum.VOID)
}
