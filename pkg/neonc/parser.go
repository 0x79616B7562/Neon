package neonc

type Parser struct {
	index          int
	sourceFilePath string
	tokens         []Token
	ast            AST

	grammar []struct {
		fire   TokenType
		action func(*Parser) NeonError
	}
}

func NewParser(sourceFilePath string, tokens []Token) *Parser {
	return &Parser{
		tokens:         tokens,
		sourceFilePath: sourceFilePath,

		grammar: []struct {
			fire   TokenType
			action func(*Parser) NeonError
		}{
			{INVALID, actionInvalid},
			{FN, actionFnDeclaration},
		},
	}
}

func (p *Parser) next() {
	p.index++
}

func (p *Parser) GetToken(index int) Token {
	return p.tokens[index]
}

func (p *Parser) analyze(index int) {
	for _, g := range p.grammar {
		if g.fire == p.tokens[index].TokenType {
			if err := g.action(p); err != nil {
				err.Error()
			}
		}
	}
}

func (p *Parser) Parse() AST {
	for {
		p.analyze(p.index)

		p.next()

		if p.index >= len(p.tokens) {
			break
		}
	}

	return p.ast
}
