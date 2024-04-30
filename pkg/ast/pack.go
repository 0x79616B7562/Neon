package ast

import (
	"neon/pkg/enum"
	"neon/pkg/llvm"
)

type Pack struct {
	Module llvm.Module

	Function        llvm.Function
	FunctionRetType enum.DataType
}

func NewPack(module llvm.Module) Pack {
	return Pack{
		Module: module,

		FunctionRetType: enum.VOID,
	}
}

func (p *Pack) Dispose() {
	p.Module.Dispose()
}
