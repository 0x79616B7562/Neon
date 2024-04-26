package llvm

/*
#include <llvm-c/Core.h>
*/
import "C"
import (
	"neon/pkg/enum"
)

type Function struct {
	Function C.LLVMValueRef
	Builder  C.LLVMBuilderRef
}

func (f *Function) AddRet(returnType enum.DataType) {
	if returnType == enum.VOID {
		C.LLVMBuildRetVoid(f.Builder)
	} else {
		panic("uninplemented")
	}
}
