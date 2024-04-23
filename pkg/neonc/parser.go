package neonc

import "fmt"

type Parser struct {
}

func NewParser() *Parser {
	return &Parser{}
}

func (p *Parser) Parse(tokens []Token) {
	for _, toks := range tokens {
		fmt.Println(toks.String())
	}
}
