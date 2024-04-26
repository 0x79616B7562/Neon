package llvm

/*
#include "llvm/Config/llvm-config.h"
*/
import "C"

const Version = C.LLVM_VERSION_STRING
