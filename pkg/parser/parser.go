package parser

import (
	"fmt"
	"neon/pkg/util"
	"strings"
)

type Parser struct {
	tokens []TokenId
}

func NewParser(grammar string) Parser {
	rules := strings.Split(strings.Replace(grammar, "\n", "", -1), ";")

	tokens := extractTokens(rules)

	return Parser{
		tokens: tokens,
	}
}

func (p *Parser) PrintTokenIds() {
	for _, token := range p.tokens {
		fmt.Println(token.String())
	}
}

func (p *Parser) Parse(filename string) {
	data := util.ReaderToString(util.ReadFile(filename))

	tokens := tokenize(data, p.tokens)

	fmt.Println("TOKENS:")
	for _, token := range tokens {
		fmt.Println(token.String())
	}
}
