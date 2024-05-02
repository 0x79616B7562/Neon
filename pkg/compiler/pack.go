package compiler

import "neon/pkg/llvm"

type Pack struct {
	Module   llvm.Module
	Function llvm.Function
}
