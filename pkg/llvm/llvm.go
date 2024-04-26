package llvm

/*
#include <stdlib.h>
#include <llvm-c/Core.h>
#include <llvm-c/TargetMachine.h>
*/
import "C"
import "unsafe"

func initializeAllTargetInfos() {
	C.LLVMInitializeAllTargetInfos()
}

func initializeAllTargets() {
	C.LLVMInitializeAllTargets()
}

func initializeAllTargetMCs() {
	C.LLVMInitializeAllTargetMCs()
}

func initializeAllAsmParsers() {
	C.LLVMInitializeAllAsmParsers()
}

func initializeAllAsmPrinters() {
	C.LLVMInitializeAllAsmPrinters()
}

func initializeAll() {
	initializeAllTargetInfos()
	initializeAllTargets()
	initializeAllTargetMCs()
	initializeAllAsmParsers()
	initializeAllAsmPrinters()
}

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

func getDefaultTargetTriple() *C.char {
	return C.LLVMGetDefaultTargetTriple()
}

func getFirstTarget() C.LLVMTargetRef {
	return C.LLVMGetFirstTarget()
}

func getTargetFromTriple(str *C.char, targetRef *C.LLVMTargetRef) (bool, string) {
	var msg *C.char

	result := C.LLVMGetTargetFromTriple(str, targetRef, &msg)

	return result != 0, C.GoString(msg)
}

func createTargetMachine(
	targetRef C.LLVMTargetRef,
	triple *C.char,
	cpu *C.char,
	features *C.char,
	optLevel C.LLVMCodeGenOptLevel,
	reloc C.LLVMRelocMode,
	codeModel C.LLVMCodeModel,
) C.LLVMTargetMachineRef {
	return C.LLVMCreateTargetMachine(targetRef, triple, cpu, features, optLevel, reloc, codeModel)
}

func createDataLayout(targetMachine C.LLVMTargetMachineRef) C.LLVMTargetDataRef {
	return C.LLVMCreateTargetDataLayout(targetMachine)
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

func createModule(name string) (module C.LLVMModuleRef) {
	nameptr := stringToCCharPtr(name)
	defer freeCString(nameptr)

	module = C.LLVMModuleCreateWithName(nameptr)

	return
}

func dumpModule(module C.LLVMModuleRef) {
	C.LLVMDumpModule(module)
}

func setModuleTargetTriple(module C.LLVMModuleRef, triple *C.char) {
	C.LLVMSetTarget(module, triple)
}

func setModuleDataLayout(module C.LLVMModuleRef, dataLayout C.LLVMTargetDataRef) {
	C.LLVMSetModuleDataLayout(module, dataLayout)
}

func addFunction(module C.LLVMModuleRef, name string, vType C.LLVMTypeRef) (value C.LLVMValueRef) {
	nameptr := stringToCCharPtr(name)
	defer freeCString(nameptr)

	value = C.LLVMAddFunction(module, nameptr, vType)

	return
}

func functionType(returnType C.LLVMTypeRef, paramTypes []C.LLVMTypeRef, paramCount int, isVarArg bool) C.LLVMTypeRef {
	_isVarArg := 0

	if isVarArg {
		_isVarArg = 1
	}

	if len(paramTypes) > 0 {
		return C.LLVMFunctionType(returnType, (*C.LLVMTypeRef)(unsafe.Pointer(&paramTypes[0])), C.uint(paramCount), C.int(_isVarArg))
	} else {
		return C.LLVMFunctionType(returnType, nil, C.uint(paramCount), C.int(_isVarArg))
	}
}

func appendBlock(function C.LLVMValueRef, name string) {
	nameptr := stringToCCharPtr(name)
	defer freeCString(nameptr)

	C.LLVMAppendBasicBlock(function, nameptr)
}

func intType(numBits uint32) C.LLVMTypeRef {
	return C.LLVMIntType(C.uint(numBits))
}

func voidType() C.LLVMTypeRef {
	return C.LLVMVoidType()
}
