package parser

import "neon/pkg/ast"

//

type Parser struct{}

func NewParser() Parser {
	precompileRegexes()

	return Parser{}
}

func (p *Parser) Parse(filePath string) (ast.AST, error) {
	data := readFile(filePath)

	stack := NewStack(filePath, nil)

	lex(data, &stack)

	ast, err := parseStack(stack)

	ast.FilePath = filePath

	return ast, err
}
