package llvm

/*
#include <llvm-c/Core.h>
*/
import "C"

type Function struct {
	Function C.LLVMValueRef
}
