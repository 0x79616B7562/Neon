package parser

import "neon/pkg/ast"

type FirstFollow struct {
	First  TokenId
	Follow func(*Stack, *ast.Node, *Data) error
}
