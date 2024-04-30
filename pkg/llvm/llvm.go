package llvm

/*
#include <stdlib.h>
#include <llvm-c/Core.h>
#include <llvm-c/TargetMachine.h>
*/
import "C"
import "unsafe"

const CodeGenLevelNone = C.LLVMCodeGenLevelNone
const CodeGenLevelLess = C.LLVMCodeGenLevelLess
const CodeGenLevelDefault = C.LLVMCodeGenLevelDefault
const CodeGenLevelAggressive = C.LLVMCodeGenLevelAggressive

const RelocDefault = C.LLVMRelocDefault
const RelocStatic = C.LLVMRelocStatic
const RelocPIC = C.LLVMRelocPIC
const RelocDynamicNoPIC = C.LLVMRelocDynamicNoPic
const RelocROPI = C.LLVMRelocROPI
const RelocRWPI = C.LLVMRelocRWPI
const RelocROPI_RWPI = C.LLVMRelocROPI_RWPI

const CodeModelDefault = C.LLVMCodeModelDefault
const CodeModelTiny = C.LLVMCodeModelTiny
const CodeModelSmall = C.LLVMCodeModelSmall
const CodeModelKernel = C.LLVMCodeModelKernel
const CodeModelMedium = C.LLVMCodeModelMedium
const CodeModelLarge = C.LLVMCodeModelLarge

const ExternalLinkage = C.LLVMExternalLinkage
const AvailableExternallyLinkage = C.LLVMAvailableExternallyLinkage
const LinkOnceAnyLinkage = C.LLVMLinkOnceAnyLinkage
const LinkOnceODRLinkage = C.LLVMLinkOnceODRLinkage
const LinkOnceODRAutoHideLinkage = C.LLVMLinkOnceODRAutoHideLinkage
const WeakAnyLinkage = C.LLVMWeakAnyLinkage
const WeakODRLinkage = C.LLVMWeakODRLinkage
const AppendingLinkage = C.LLVMAppendingLinkage
const InternalLinkage = C.LLVMInternalLinkage
const PrivateLinkage = C.LLVMPrivateLinkage
const DLLImportLinkage = C.LLVMDLLImportLinkage
const DLLExportLinkage = C.LLVMDLLExportLinkage
const ExternalWeakLinkage = C.LLVMExternalWeakLinkage
const GhostLinkage = C.LLVMGhostLinkage
const CommonLinkage = C.LLVMCommonLinkage
const LinkerPrivateLinkage = C.LLVMLinkerPrivateLinkage
const LinkerPrivateWeakLinkage = C.LLVMLinkerPrivateWeakLinkage

type LLVMBool C.int

const (
	True  LLVMBool = 1
	False LLVMBool = 0
)

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

// llvm data types

func ConstInt(ctype C.LLVMTypeRef, bits uint64, isSigned LLVMBool) C.LLVMValueRef {
	return C.LLVMConstInt(ctype, C.ulonglong(bits), C.int(isSigned))
}

func IntType(numBits uint32) C.LLVMTypeRef {
	return C.LLVMIntType(C.uint(numBits))
}

func VoidType() C.LLVMTypeRef {
	return C.LLVMVoidType()
}
