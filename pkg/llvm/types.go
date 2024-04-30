package llvm

/*
#include <llvm-c/Core.h>
*/
import "C"
import (
	"fmt"
	"neon/pkg/enum"
	"neon/pkg/util"
)

func ResolveDataType(t enum.DataType) C.LLVMTypeRef {
	switch t {
	case enum.VOID:
		return VoidType()
	case enum.I32:
		return IntType(32)
	default:
		util.PrintType(t)
		fmt.Println()
		panic("Failed to resolve data type")
	}
}
