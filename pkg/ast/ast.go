package ast

import (
	"fmt"
	"neon/pkg/enum"
	"neon/pkg/lexer"
	"neon/pkg/target"
	"path/filepath"
	"strings"
)

type Id string

const UNKNOWN Id = "UNKNOWN"

const NAME Id = "Name"
const TYPE Id = "Type"
const VALUE Id = "Value"

type Data struct {
	Id    Id
	Value string
}

type AST struct {
	Item     Item
	Position lexer.Position
	Data     []Data
	Children []AST
}

func (a *AST) String(indent int) string {
	str := fmt.Sprintf("%s %q %d:%d", enum.ItemToString(a.Item.AsEnum()), a.Data, a.Position.Line, a.Position.Column)

	for _, child := range a.Children {
		indentstr := strings.Repeat(" ", indent*4)
		str += fmt.Sprintf("\n"+indentstr+"%s", child.String(indent+1))
	}

	return str
}

func (a *AST) build(pack *Pack, ast AST) {
	hook := ast.Item.Build(pack, ast)

	for _, child := range ast.Children {
		a.build(pack, child)
	}

	if hook != nil {
		hook(pack, ast)
	}
}

func (a *AST) Build(filePath string, target *target.Target) {
	_, file := filepath.Split(filePath)
	pack := Pack{Module: target.Target.CreateModule(file)}
	defer pack.Dispose()

	for _, child := range a.Children {
		a.build(&pack, child)
	}

	pack.Module.Dump()
	pack.Module.Verify()

	target.Target.ModuleToObjectFile(pack.Module, filePath+".o")
}
