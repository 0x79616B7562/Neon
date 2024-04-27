package llvm

/*
#include <stdlib.h>
#include <llvm-c/Core.h>
#include <llvm-c/TargetMachine.h>
*/
import "C"
import "unsafe"

func stringCmp(charptr *C.char, str string) bool {
	return C.GoString(charptr) == str
}

func cCharPtrTostring(charptr *C.char) string {
	return C.GoString(charptr)
}

func stringToCCharPtr(str string) *C.char {
	return C.CString(str)
}

func freeCString(str *C.char) {
	C.free(unsafe.Pointer(str))
}

func codeGenLevelNone() C.LLVMCodeGenOptLevel {
	return C.LLVMCodeGenLevelNone
}

func codeGenLevelLess() C.LLVMCodeGenOptLevel {
	return C.LLVMCodeGenLevelLess
}

func codeGenLevelDefault() C.LLVMCodeGenOptLevel {
	return C.LLVMCodeGenLevelDefault
}

func codeGenLevelAggressive() C.LLVMCodeGenOptLevel {
	return C.LLVMCodeGenLevelAggressive
}

func relocDefault() C.LLVMRelocMode {
	return C.LLVMRelocDefault
}

func relocStatic() C.LLVMRelocMode {
	return C.LLVMRelocStatic
}

func relocPIC() C.LLVMRelocMode {
	return C.LLVMRelocPIC
}

func relocDynamicNoPic() C.LLVMRelocMode {
	return C.LLVMRelocDynamicNoPic
}

func relocROPI() C.LLVMRelocMode {
	return C.LLVMRelocROPI
}

func relocRWPI() C.LLVMRelocMode {
	return C.LLVMRelocRWPI
}

func relocROPI_RWPI() C.LLVMRelocMode {
	return C.LLVMRelocROPI_RWPI
}

func codeModelDefault() C.LLVMCodeModel {
	return C.LLVMCodeModelDefault
}

func codeModelJITDefault() C.LLVMCodeModel {
	return C.LLVMCodeModelJITDefault
}

func codeModelTiny() C.LLVMCodeModel {
	return C.LLVMCodeModelTiny
}

func codeModelSmall() C.LLVMCodeModel {
	return C.LLVMCodeModelSmall
}

func codeModelKernel() C.LLVMCodeModel {
	return C.LLVMCodeModelKernel
}

func codeModelMedium() C.LLVMCodeModel {
	return C.LLVMCodeModelMedium
}

func codeModelLarge() C.LLVMCodeModel {
	return C.LLVMCodeModelLarge
}

func intType(numBits uint32) C.LLVMTypeRef {
	return C.LLVMIntType(C.uint(numBits))
}

func voidType() C.LLVMTypeRef {
	return C.LLVMVoidType()
}
