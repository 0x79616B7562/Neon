package llvm

/*
#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>
*/
import "C"

type Module struct {
	Module C.LLVMModuleRef
}

func (m *Module) AddFunction(name string, functionType FunctionType) (function Function) {
	fn := addFunction(m.Module, name, functionType.resolve())

	function.Function = fn
	function.Builder = C.LLVMCreateBuilder()

	blockRef := appendBlock(fn, "entry")
	C.LLVMPositionBuilderAtEnd(function.Builder, blockRef)

	return
}

func (m *Module) Dump() {
	dumpModule(m.Module)
}

func (m *Module) Verify() {
	var errMsg *C.char
	C.LLVMVerifyModule(m.Module, C.LLVMAbortProcessAction, &errMsg)
}

func (m *Module) Dispose() {
	C.LLVMDisposeModule(m.Module)
}
