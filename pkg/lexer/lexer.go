package lexer

import (
	"bufio"
	"io"
	"neon/pkg/enum"
	"regexp"
	"strings"
)

type Lexer struct {
	position Position
	reader   *bufio.Reader
}

func NewLexer(reader io.Reader) *Lexer {
	return &Lexer{
		position: Position{
			Line:   1,
			Column: 0,
		},
		reader: bufio.NewReader(reader),
	}
}

func splitCharsInclusive(s, chars string) (out []string) {
	for {
		m := strings.IndexAny(s, chars)

		if m < 0 {
			break
		}

		out = append(out, s[:m], s[m:m+1])
		s = s[m+1:]
	}

	out = append(out, s)

	return
}

func (l *Lexer) Tokenize() []Token {
	var tokens []Token

	//
	buf := new(strings.Builder)
	_, err := io.Copy(buf, l.reader)

	if err != nil {
		panic(err)
	}

	// splitting array into smaller pieces
	split := " \n\t"

	for _, token := range TOKENS {
		if token.Match != "" && !token.IsRegex && len([]rune(token.Match)) == 1 {
			split += token.Match
		}
	}

	str := splitCharsInclusive(buf.String(), split)

	// precompile regexes
	for i := 0; i < len(TOKENS); i++ {
		if TOKENS[i].Match == "" {
			continue
		}

		if TOKENS[i].IsRegex {
			reg, err := regexp.Compile(TOKENS[i].Match)

			if err != nil {
				panic(err)
			}

			TOKENS[i].CompiledRegex = reg
		}
	}

	// find toks
	for _, s := range str {
		if s == "" {
			continue
		}

		l.position.Column += len([]rune(s))

		tokenType := enum.INVALID

		for _, token := range TOKENS {
			if token.Match == "" {
				continue
			}

			if !token.IsRegex {
				if token.Match == s {
					tokenType = token.TokenType

					break
				}
			} else {
				if token.CompiledRegex == nil {
					panic("Precompiled Regex is NIL")
				}

				if len(token.CompiledRegex.Find([]byte(s))) > 0 {
					tokenType = token.TokenType

					break
				}
			}
		}

		if tokenType != enum.UNKNOWN {
			if !DoTokenDiscard(tokenType) {
				tokens = append(tokens, Token{
					Position:  l.position,
					TokenType: tokenType,
					Value:     s,
				})
			}
		}

		if s == "\n" {
			l.position.Line++
			l.position.Column = 0
		}
	}

	//
	tokens = append(tokens, Token{
		Position:  l.position,
		TokenType: enum.EOF,
		Value:     "EOF",
	})

	return tokens
}
