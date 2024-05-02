package compiler

import (
	"neon/pkg/ast"
	"neon/pkg/llvm"
	"path/filepath"
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

func (c *Compiler) Compile(ast ast.AST) {
	_, file := filepath.Split(ast.FilePath)

	pack := Pack{Module: c.target.CreateModule(file)}
	defer pack.Module.Dispose()

	walk(&pack, ast.Head)

	pack.Module.Dump()
	pack.Module.Verify()
}
