package llvm

import (
	"fmt"

	"neon/pkg/util"
)

/*
#include <llvm-c/Core.h>
#include <llvm-c/TargetMachine.h>
*/
import "C"

type Target struct {
	targetTriple  *C.char
	target        C.LLVMTargetRef
	cpu           *C.char
	features      *C.char
	targetMachine C.LLVMTargetMachineRef
	dataLayout    C.LLVMTargetDataRef
}

func NewTarget() Target {
	C.LLVMInitializeAllTargetInfos()
	C.LLVMInitializeAllTargets()
	C.LLVMInitializeAllTargetMCs()
	C.LLVMInitializeAllAsmParsers()
	C.LLVMInitializeAllAsmPrinters()

	targetTriple := C.LLVMGetDefaultTargetTriple()
	util.AssertCmpError(!stringCmp(targetTriple, ""), "No Target Triple")

	target := C.LLVMGetFirstTarget()
	var msg *C.char
	result := C.LLVMGetTargetFromTriple(targetTriple, &target, &msg)
	util.AssertCmpError(result == 0, fmt.Sprintf("Error Message: %s", C.GoString(msg)))

	cpu := stringToCCharPtr("generic")
	features := stringToCCharPtr("")

	targetMachine := C.LLVMCreateTargetMachine(
		target,
		targetTriple,
		cpu,
		features,
		CodeGenLevelNone,
		RelocPIC,
		CodeModelDefault,
	)

	dataLayout := C.LLVMCreateTargetDataLayout(targetMachine)

	return Target{
		targetTriple:  targetTriple,
		target:        target,
		cpu:           cpu,
		features:      features,
		targetMachine: targetMachine,
		dataLayout:    dataLayout,
	}
}

func (t *Target) Dispose() {
	freeCString(t.cpu)
	freeCString(t.features)
	C.LLVMDisposeTargetMachine(t.targetMachine)
	C.LLVMDisposeTargetData(t.dataLayout)
}

func (t *Target) CreateModule(name string) (module Module) {
	nameptr := stringToCCharPtr(name)
	defer freeCString(nameptr)

	mod := C.LLVMModuleCreateWithName(nameptr)

	C.LLVMSetTarget(mod, t.targetTriple)
	C.LLVMSetModuleDataLayout(mod, t.dataLayout)

	module.Module = mod

	return
}

func (t *Target) ModuleToObjectFile(module Module, output string) {
	outputptr := stringToCCharPtr(output)
	defer freeCString(outputptr)

	var errorMsg *C.char

	if C.LLVMTargetMachineEmitToFile(t.targetMachine, module.Module, outputptr, C.LLVMObjectFile, &errorMsg) != 0 {
		panic(C.GoString(errorMsg))
	}
}
