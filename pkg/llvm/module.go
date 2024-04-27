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
	nameptr := stringToCCharPtr(name)
	defer freeCString(nameptr)

	fn := C.LLVMAddFunction(m.Module, nameptr, functionType.resolve())

	function.Function = fn
	function.Builder = C.LLVMCreateBuilder()

	return
}

func (m *Module) Dump() {
	C.LLVMDumpModule(m.Module)
}

func (m *Module) Verify() {
	var errMsg *C.char
	C.LLVMVerifyModule(m.Module, C.LLVMAbortProcessAction, &errMsg)
}

func (m *Module) Dispose() {
	C.LLVMDisposeModule(m.Module)
}
