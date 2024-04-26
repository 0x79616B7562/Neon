package llvm

import (
	"fmt"

	"neon/pkg/util"
)

/*
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
	initializeAll()

	targetTriple := getDefaultTargetTriple()
	util.AssertCmpError(!stringCmp(targetTriple, ""), "No Target Triple")

	target := getFirstTarget()
	result, err := getTargetFromTriple(targetTriple, &target)
	util.AssertCmpError(!result, fmt.Sprintf("Error Message: %s", err))

	cpu := stringToCCharPtr("generic")
	features := stringToCCharPtr("")

	targetMachine := createTargetMachine(
		target,
		targetTriple,
		cpu,
		features,
		codeGenLevelNone(),
		relocPIC(),
		codeModelDefault(),
	)

	dataLayout := createDataLayout(targetMachine)

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

func (t *Target) CreateModule(name string) Module {
	module := createModule(name)

	setModuleTargetTriple(module, t.targetTriple)
	setModuleDataLayout(module, t.dataLayout)

	return Module{
		Module: module,
	}
}
