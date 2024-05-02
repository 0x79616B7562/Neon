package llvm

/*
#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>
*/
import "C"
import "neon/pkg/enum"

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

func (f *Function) SetLinkage(linkage C.LLVMLinkage) {
	C.LLVMSetLinkage(f.Function, linkage)
}

func (f *Function) SetBuilderToBlockEnd(blockRef C.LLVMBasicBlockRef) {
	C.LLVMPositionBuilderAtEnd(f.Builder, blockRef)
}

func (f *Function) SetBr(blockRef C.LLVMBasicBlockRef) {
	C.LLVMBuildBr(f.Builder, blockRef)
}

func (f *Function) BuildAlloca(name string, typeRef C.LLVMTypeRef) (valueref C.LLVMValueRef) {
	nameptr := stringToCCharPtr(name)
	defer freeCString(nameptr)

	valueref = C.LLVMBuildAlloca(f.Builder, typeRef, nameptr)

	return
}

func (f *Function) BuildStore(value C.LLVMValueRef, ptr C.LLVMValueRef) (valueref C.LLVMValueRef) {
	valueref = C.LLVMBuildStore(f.Builder, value, ptr)
	return
}

func (f *Function) AddRet(returnType enum.DataType, valueref C.LLVMValueRef) {
	if returnType == enum.VOID {
		C.LLVMBuildRetVoid(f.Builder)
	} else {
		C.LLVMBuildRet(f.Builder, valueref)
	}
}

func (f *Function) Verify() {
	C.LLVMVerifyFunction(f.Function, C.LLVMAbortProcessAction)
}

func (f *Function) Dispose() {
	C.LLVMDisposeBuilder(f.Builder)
}
