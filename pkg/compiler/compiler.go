package compiler

import (
	"neon/pkg/enum"
	"neon/pkg/llvm"
	"neon/pkg/parser"
)

type Compiler struct {
	target llvm.Target
}

func NewCompiler() Compiler {
	return Compiler{
		target: llvm.NewTarget(),
	}
}

func (c *Compiler) Dispose() {
	c.target.Dispose()
}

func (c *Compiler) Compile(item parser.Item, output string) {
	if item.Item == enum.HEAD {
		module := c.target.CreateModule(item.Data)
		defer module.Dispose()

		buildHead(&module, item.Children)

		module.Dump()
		module.Verify()

		c.target.ModuleToObjectFile(module, output+".o")
	}
}
