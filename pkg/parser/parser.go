package parser

import (
	"neon/pkg/ast"
	"neon/pkg/builder"
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

func (p *Parser) addOffset(offset int) int {
	p.index += offset

	return p.index
}

func (p *Parser) findNext(index int, toFind enum.TokenType, ignore util.Option[enum.TokenType]) (util.Option[lexer.Token], int) {
	for i := index; i < len(p.tokens); i++ {
		tok := p.tokens[i]

		if tok.TokenType == toFind {
			return util.Some(tok), i - index + 1
		}

		if ignore.IsSome {
			if ignore.Unwrap() == tok.TokenType {
				continue
			}
		}

		return util.None[lexer.Token](), 0
	}

	return util.None[lexer.Token](), 0
}

func (p *Parser) previousItemIsAny(item *ast.AST, itemarr []enum.Item) bool {
	if len(item.Children) > 0 {
		for _, it := range itemarr {
			if it == item.Children[len(item.Children)-1].Item.AsEnum() {
				return true
			}
		}
	}

	return false
}

func (p *Parser) getFromGrammar(grammar []Grammar) bool {
	found := true

	for _, grammar := range grammar {
		foundtok := true

		if grammar.MatchType == MatchWithAny {
			foundtok = false
		}

		var tokbuf []lexer.Token

		for _, token := range grammar.Tokens {
			if token, offset := p.findNext(p.index, token, grammar.IgnoreToken); token.IsSome {
				p.addOffset(offset)

				tokbuf = append(tokbuf, token.Unwrap())

				if grammar.MatchType == MatchWithAny {
					foundtok = true

					break
				}
			} else {
				if grammar.MatchType == MatchInSequence {
					foundtok = false
				}
			}
		}

		if !foundtok && grammar.Optional == IsRequired {
			found = false

			if grammar.ErrorMessage.IsSome {
				p.errors = append(p.errors, errors.NewSyntaxError(p.fileName, p.getTokenAtCurrentIndex(), grammar.ErrorMessage.Unwrap()))
			}
		} else {
			if grammar.Callback.IsSome {
				grammar.Callback.Unwrap()(tokbuf)
			}
		}
	}

	return found
}

func (p *Parser) getTokenAtCurrentIndex() lexer.Token {
	return p.tokens[p.index]
}

func (p *Parser) analyzeBlock(item *ast.AST) {
loop:
	for {
		if p.index >= len(p.tokens) {
			break
		}

		tok := p.next()

		switch tok.TokenType {
		case enum.EOF:
			break loop
		case enum.NEWLINE:
			// ignore
		case enum.RBRACE:
			p.braceCounter--

			if p.braceCounter < 0 {
				p.errors = append(p.errors, errors.NewSyntaxError(p.fileName, tok, "unexpected closing delimiter"))
			}

			break loop
		case enum.LBRACE:
			p.braceCounter++
			p.lastLBrace = tok

			i := ast.AST{
				Item:     &builder.Block{},
				Position: tok.Position,
				Children: []ast.AST{},
			}

			p.analyzeBlock(&i)

			item.Children = append(item.Children, i)
		case enum.VAR:
			ident := ""
			vtype := ""
			value := ""
			if p.getFromGrammar([]Grammar{
				NewGrammar(
					[]enum.TokenType{enum.IDENT},
					util.Some(enum.NEWLINE),
					NoRepeat, IsRequired, MatchInSequence,
					util.Some("expected identifier"),
					util.Some(Callback(func(toks []lexer.Token) {
						ident = toks[0].Value
					})),
				),
				NewGrammar(
					[]enum.TokenType{enum.IDENT},
					util.Some(enum.NEWLINE),
					NoRepeat, IsRequired, MatchInSequence,
					util.Some("expected type"),
					util.Some(Callback(func(toks []lexer.Token) {
						vtype = toks[0].Value
					})),
				),
				NewGrammar(
					[]enum.TokenType{enum.EQUALS},
					util.Some(enum.NEWLINE),
					NoRepeat, IsRequired, MatchInSequence,
					util.Some("expected '='"),
					util.None[Callback](),
				),
				NewGrammar(
					[]enum.TokenType{enum.NUM},
					util.Some(enum.NEWLINE),
					NoRepeat, IsRequired, MatchInSequence,
					util.Some("expected number"),
					util.Some(Callback(func(toks []lexer.Token) {
						value = toks[0].Value
					})),
				),
			}) {
				item.Children = append(item.Children, ast.AST{
					Item:     &builder.Variable{},
					Position: tok.Position,
					Children: []ast.AST{},
					Data:     []ast.Data{{Id: ast.NAME, Value: ident}, {Id: ast.TYPE, Value: vtype}, {Id: ast.VALUE, Value: value}},
				})
			}
		default:
			p.errors = append(p.errors, errors.NewSyntaxError(p.fileName, tok, "undefined"))
		}
	}
}

func (p *Parser) analyzeHead(item *ast.AST) {
loop:
	for {
		if p.index >= len(p.tokens) {
			break
		}

		tok := p.next()

		switch tok.TokenType {
		case enum.EOF:
			break loop
		case enum.NEWLINE:
			// ignore
		case enum.RBRACE:
			p.braceCounter--

			if p.braceCounter < 0 {
				p.errors = append(p.errors, errors.NewSyntaxError(p.fileName, tok, "unexpected closing delimiter"))
			}

			break loop
		case enum.LBRACE:
			if p.previousItemIsAny(item, []enum.Item{enum.FUNCTION}) {
				p.braceCounter++
				p.lastLBrace = tok

				p.analyzeBlock(&item.Children[len(item.Children)-1])
			} else {
				p.errors = append(p.errors, errors.NewSyntaxError(p.fileName, tok, "expected item"))
			}
		case enum.FN:
			ident := ""
			if p.getFromGrammar([]Grammar{
				NewGrammar(
					[]enum.TokenType{enum.IDENT},
					util.Some(enum.NEWLINE),
					NoRepeat, IsRequired, MatchInSequence,
					util.Some("expected identifier"),
					util.Some(Callback(func(toks []lexer.Token) {
						ident = toks[0].Value
					})),
				),
				NewGrammar(
					[]enum.TokenType{enum.LPAREN},
					util.Some(enum.NEWLINE),
					NoRepeat, IsRequired, MatchInSequence,
					util.Some("expected '('"),
					util.None[Callback](),
				),
				NewGrammar(
					[]enum.TokenType{enum.RPAREN},
					util.Some(enum.NEWLINE),
					NoRepeat, IsRequired, MatchInSequence,
					util.Some("expected ')'"),
					util.None[Callback](),
				),
			}) {
				item.Children = append(item.Children, ast.AST{
					Item:     &builder.Function{},
					Position: tok.Position,
					Children: []ast.AST{},
					Data:     []ast.Data{{Id: ast.NAME, Value: ident}},
				})
			}
		default:
			p.errors = append(p.errors, errors.NewSyntaxError(p.fileName, tok, "undefined"))
		}
	}
}

func (p *Parser) Parse() (ast.AST, error) {
	_, file := filepath.Split(p.fileName)

	head := ast.AST{
		Item: &builder.Head{},
		Data: []ast.Data{{Id: ast.NAME, Value: file}},
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
