package parser

import (
	"neon/pkg/enum"
	"neon/pkg/errors"
	"neon/pkg/lexer"
	"neon/pkg/util"
	"path/filepath"
)

type Parser struct {
	fileName string
	index    int
	tokens   []lexer.Token

	braceCounter int
	lastLBrace   lexer.Token

	errors []errors.Error
}

func NewParser(fileName string, tokens []lexer.Token) Parser {
	return Parser{
		fileName: fileName,
		index:    0,
		tokens:   tokens,
	}
}

func (p *Parser) next() lexer.Token {
	tok := p.tokens[len(p.tokens)-1]

	if p.index < len(p.tokens) {
		tok = p.tokens[p.index]
		p.index++
	}

	return tok
}

func (p *Parser) analyzeBlock(item *Item) {
loop:
	for {
		if p.index >= len(p.tokens) {
			break
		}

		tok := p.next()

		switch tok.TokenType {
		case enum.EOF:
			break loop
		case enum.RBRACE:
			p.braceCounter--

			if p.braceCounter < 0 {
				p.errors = append(p.errors, errors.NewSyntaxError(p.fileName, tok, "unexpected closing delimiter"))
			}

			break loop
		case enum.LBRACE:
			p.braceCounter++
			p.lastLBrace = tok

			i := Item{
				Item:     enum.BLOCK,
				Position: tok.Position,
				Data:     "",
				Children: []Item{},
			}

			p.analyzeBlock(&i)

			item.Children = append(item.Children, i)
		default:
			p.errors = append(p.errors, errors.NewSyntaxError(p.fileName, tok, "undefined"))
		}
	}
}

func (p *Parser) analyzeHead(item *Item) {
loop:
	for {
		if p.index >= len(p.tokens) {
			break
		}

		tok := p.next()

		switch tok.TokenType {
		case enum.EOF:
			break loop
		case enum.RBRACE:
			p.braceCounter--

			if p.braceCounter < 0 {
				p.errors = append(p.errors, errors.NewSyntaxError(p.fileName, tok, "unexpected closing delimiter"))
			}

			break loop
		case enum.LBRACE:
			if len(item.Children) > 0 {
				if item.Children[len(item.Children)-1].Item == enum.FUNCTION {
					p.braceCounter++
					p.lastLBrace = tok

					i := Item{
						Item:     enum.BLOCK,
						Position: tok.Position,
						Data:     "",
						Children: []Item{},
					}

					p.analyzeBlock(&i)

					item.Children = append(item.Children, i)
				} else {
					p.errors = append(p.errors, errors.NewSyntaxError(p.fileName, tok, "expected item"))
					p.next()
				}
			} else {
				p.errors = append(p.errors, errors.NewSyntaxError(p.fileName, tok, "expected item"))
				p.next()
			}
		case enum.FN:
			ident := p.next()

			if !util.Assert(ident.TokenType, enum.IDENT) {
				p.errors = append(p.errors, errors.NewSyntaxError(p.fileName, ident, "expected identifier"))
				p.next()
			} else {
				lparen := p.next()

				if !util.Assert(lparen.TokenType, enum.LPAREN) {
					p.errors = append(p.errors, errors.NewSyntaxError(p.fileName, lparen, "expected '('"))
					p.next()
				} else {
					rparen := p.next()

					if !util.Assert(rparen.TokenType, enum.RPAREN) {
						p.errors = append(p.errors, errors.NewSyntaxError(p.fileName, rparen, "expected ')'"))
						p.next()
					} else {
						item.Children = append(item.Children, Item{
							Item:     enum.FUNCTION,
							Position: tok.Position,
							Data:     ident.Value,
							Children: []Item{},
						})
					}
				}
			}
		default:
			p.errors = append(p.errors, errors.NewSyntaxError(p.fileName, tok, "undefined"))
		}
	}
}

func (p *Parser) Parse() (Item, error) {
	_, file := filepath.Split(p.fileName)

	head := Item{
		Item: enum.HEAD,
		Data: file,
	}

	p.analyzeHead(&head)

	if p.braceCounter > 0 {
		p.errors = append(p.errors, errors.NewSyntaxError(p.fileName, p.lastLBrace, "unclosed delimiter"))
	}

	if len(p.errors) > 0 {
		for _, error := range p.errors {
			error.Error()
		}

		return head, errors.New(util.ColorRed + "Syntax Error" + util.ColorReset + ": Could not compile due to error/s above")
	}

	return head, nil
}
