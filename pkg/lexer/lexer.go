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

	buf := new(strings.Builder)
	_, err := io.Copy(buf, l.reader)

	if err != nil {
		panic(err)
	}

	split := " \n\t"

	for _, token := range TOKENS {
		if token.Match != "" && !token.IsRegex && len([]rune(token.Match)) == 1 {
			split += token.Match
		}
	}

	str := splitCharsInclusive(buf.String(), split)

	for i := 0; i < len(str); i++ {
		if str[i] == "" {
			continue
		}

		tokenType := enum.INVALID

		for _, token := range TOKENS {
			if token.Match == "" {
				continue
			}

			if !token.IsRegex {
				if token.Match == str[i] {
					tokenType = token.TokenType

					break
				}
			} else {
				reg, err := regexp.Compile(token.Match)

				if err != nil {
					panic(err)
				}

				if len(reg.Find([]byte(str[i]))) > 0 {
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
					Value:     str[i],
				})
			}
		}
	}

	return tokens
}
