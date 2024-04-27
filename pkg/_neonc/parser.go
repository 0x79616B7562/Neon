package neonc

import (
	"fmt"
	"path/filepath"
)

type Parser struct {
	index          int
	sourceFilePath string
	tokens         []Token
	ast            AST

	grammar []Grammar
}

func NewParser(sourceFilePath string, tokens []Token) *Parser {
	return &Parser{
		tokens:         tokens,
		sourceFilePath: sourceFilePath,

		grammar: HeadGrammar,
	}
}

func (p *Parser) next() Token {
	tok := p.tokens[p.index]
	p.index++

	return tok
}

func (p *Parser) GetToken(index int) Token {
	return p.tokens[index]
}

func (p *Parser) analyze(index int) NeonError {
	valid := false

	for _, g := range p.grammar {
		if g.fire == p.tokens[index].TokenType {
			if err := g.action(p, g.contains); err != nil {
				err.Error()
			}

			valid = true
		}
	}

	if !valid {
		return &ParseError{
			FilePath: p.sourceFilePath,
			Position: p.GetToken(p.index).Position,
			Message:  fmt.Sprintf("expected declaration, found: %q", p.GetToken(p.index).Value),
		}
	}

	return nil
}

func (p *Parser) Parse() (AST, error) {
	_, file := filepath.Split(p.sourceFilePath)
	p.ast.Name = file

	errors := 0

	for {
		err := p.analyze(p.index)

		if err != nil {
			err.Error()

			errors++
		}

		p.next()

		if p.index >= len(p.tokens) {
			break
		}
	}

	if errors > 0 {
		if errors == 1 {
			return p.ast, fmt.Errorf("Could not compile due to error above")
		} else {
			return p.ast, fmt.Errorf("Could not compile due to %d errors above", errors)
		}
	}

	return p.ast, nil
}
