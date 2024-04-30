package llvm

import (
	"neon/pkg/enum"
	"unsafe"
)

/*
#include <llvm-c/Core.h>
*/
import "C"

type FunctionType struct {
	returnType enum.DataType
	params     []enum.DataType
}

func NewFunctionType(returnType enum.DataType, params ...enum.DataType) FunctionType {
	var _params []enum.DataType

	for _, param := range params {
		_params = append(_params, param)
	}

	return FunctionType{
		returnType: returnType,
		params:     _params,
	}
}

func (fnt *FunctionType) resolve() C.LLVMTypeRef {
	returnType := ResolveDataType(fnt.returnType)

	var paramTypes []C.LLVMTypeRef

	for _, param := range fnt.params {
		paramTypes = append(paramTypes, ResolveDataType(param))
	}

	isVarArg := false
	_isVarArg := 0

	if isVarArg {
		_isVarArg = 1
	}

	if len(paramTypes) > 0 {
		return C.LLVMFunctionType(returnType, (*C.LLVMTypeRef)(unsafe.Pointer(&paramTypes[0])), C.uint(len(paramTypes)), C.int(_isVarArg))
	} else {
		return C.LLVMFunctionType(returnType, nil, C.uint(len(paramTypes)), C.int(_isVarArg))
	}

}
