package neonc

import (
	"bufio"
	"io"
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

func (l *Lexer) Tokenize() []Token {
	var tokens []Token
	var current string

	for {
		char, _, err := l.reader.ReadRune()

		if err != nil {
			if err == io.EOF {
				break
			}

			panic(err)
		}

		current += string(char)

		l.position.Column++

		tokenType := INVALID

		for _, token := range TOKENS {
			if token.Match == "" || current == "" {
				continue
			}

			if token.IsRegex {
				reg, err := regexp.Compile(token.Match)

				if err != nil {
					panic(err)
				}

				if len(reg.Find([]byte(current))) == 0 {
					loccurrent := current[:len(current)-1]

					if len(reg.Find([]byte(loccurrent))) > 0 {
						l.reader.UnreadRune()

						tokenType = token.TokenType
						current = loccurrent

						break
					}
				} else {
					tokenType = UNKNOWN
				}
			} else {
				if current == token.Match {
					tokenType = token.TokenType
					break
				} else if strings.Contains(token.Match, current) {
					tokenType = UNKNOWN
				}
			}
		}

		if tokenType != UNKNOWN {
			if !DoTokenDiscard(tokenType) {
				tokens = append(tokens, Token{
					Position:  l.position,
					TokenType: tokenType,
					Value:     current,
				})
			}

			current = ""
		}

		if char == '\n' {
			l.position.Line++
			l.position.Column = 0
		}
	}

	return tokens
}
