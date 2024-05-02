package parser

import "neon/pkg/ast"

//

type Parser struct{}

func NewParser() Parser {
	precompileRegexes()

	return Parser{}
}

func (p *Parser) Parse(filePath string) ast.AST {
	data := readDataFromFile(filePath)

	stack := NewStack(nil)
	lex(data, &stack)

	ast := parseStack(stack)

	ast.FilePath = filePath

	return ast
}
