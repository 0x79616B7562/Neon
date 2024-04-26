package llvm

/*
#include <llvm-c/Core.h>
*/
import "C"

type Module struct {
	Module C.LLVMModuleRef
}

func (m *Module) AddFunction(name string, functionType FunctionType) (function Function) {
	fn := addFunction(m.Module, name, functionType.resolve())

	appendBlock(fn, "entry")

	function.Function = fn

	return
}

func (m *Module) Dump() {
	dumpModule(m.Module)
}
