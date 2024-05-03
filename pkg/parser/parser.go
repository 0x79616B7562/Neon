package parser

import "neon/pkg/ast"

//

type Parser struct{}

func NewParser() Parser {
	precompileRegexes()

	return Parser{}
}

func (p *Parser) Parse(filePath string) (ast.AST, error) {
	data := readFile(filePath) + "\n"

	stack := NewStack(filePath, nil)

	lex(data, &stack)

	stack.Dump()

	ast, err := parseStack(stack)

	ast.FilePath = filePath

	return ast, err
}
