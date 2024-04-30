package ast

import "neon/pkg/enum"

type Hook func(pack *Pack, ast AST)

type Item interface {
	AsEnum() enum.Item
	Build(pack *Pack, ast AST) Hook
}
