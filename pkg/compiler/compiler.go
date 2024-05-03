package compiler

import (
	"fmt"
	"neon/pkg/llvm"
	"neon/pkg/nir"
)

type Compiler struct {
	target llvm.Target
}

func NewCompiler() Compiler {
	return Compiler{
		target: llvm.NewTarget(),
	}
}

func (c *Compiler) Compile(nir nir.Module) {
	module := c.target.CreateModule(nir.Name)
	defer module.Dispose()

	fmt.Println("LLVMIR:")
	module.Dump()
}

func (c *Compiler) Dispose() {
	c.target.Dispose()
}
