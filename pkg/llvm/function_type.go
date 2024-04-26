package llvm

import (
	"neon/pkg/enum"
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
	returnType := resolveDataType(fnt.returnType)

	var paramTypes []C.LLVMTypeRef

	for _, param := range fnt.params {
		paramTypes = append(paramTypes, resolveDataType(param))
	}

	return functionType(returnType, paramTypes, len(paramTypes), false)
}
