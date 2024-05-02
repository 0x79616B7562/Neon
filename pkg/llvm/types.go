package llvm

/*
#include <llvm-c/Core.h>
*/
import "C"
import (
	"fmt"
	"neon/pkg/util"
)

type DataType uint32

const (
	VOID DataType = iota

	I32
)

func ResolveDataType(t DataType) C.LLVMTypeRef {
	switch t {
	case VOID:
		return VoidType()
	case I32:
		return IntType(32)
	default:
		util.PrintType(t)
		fmt.Println()
		panic("Failed to resolve data type")
	}
}
