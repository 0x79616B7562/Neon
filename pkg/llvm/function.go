package llvm

/*
#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>
*/
import "C"
import (
	"neon/pkg/enum"
)

type Function struct {
	Function C.LLVMValueRef
	Builder  C.LLVMBuilderRef
}

func (f *Function) AppendBlock(name string) (blockRef C.LLVMBasicBlockRef) {
	nameptr := stringToCCharPtr(name)
	defer freeCString(nameptr)

	blockRef = C.LLVMAppendBasicBlock(f.Function, nameptr)

	return
}

func (f *Function) SetBuilderToBlockEnd(blockRef C.LLVMBasicBlockRef) {
	C.LLVMPositionBuilderAtEnd(f.Builder, blockRef)
}

func (f *Function) AddRet(returnType enum.DataType) {
	if returnType == enum.VOID {
		C.LLVMBuildRetVoid(f.Builder)
	} else {
		panic("uninplemented")
	}
}

func (f *Function) Verify() {
	C.LLVMVerifyFunction(f.Function, C.LLVMAbortProcessAction)
}
