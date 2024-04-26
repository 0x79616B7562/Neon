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

func resolveDataType(t enum.DataType) C.LLVMTypeRef {
	switch t {
	case enum.VOID:
		return voidType()
	case enum.I32:
		return intType(32)
	default:
		util.PrintType(t)
		fmt.Println()
		panic("Failed to resolve data type")
	}
}
