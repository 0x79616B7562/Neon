package neonc

import (
	"bufio"
	"fmt"
	"io"
	"strings"
	"unicode"
)

type Lexer struct {
	position Position
	reader   *bufio.Reader
	current  string
	tokens   []Token
}

func NewLexer(reader io.Reader) *Lexer {
	return &Lexer{
		position: Position{
			StartLine:   1,
			StartColumn: 0,
			EndLine:     1,
			EndColumn:   0,
		},
		reader: bufio.NewReader(reader),
	}
}

func (l *Lexer) getToken() TokenType {
	returnVal := INVALID
	compareNonToken := true

	for _, token := range TOKENS {
		if token.Match == "" {
			continue
		}

		if l.current == token.Match {
			return token.TokenType
		} else if strings.Contains(token.Match, l.current) {
			returnVal = UNKNOWN
			compareNonToken = false
		}
	}

	if compareNonToken {
	}

	return returnVal
}

func (l *Lexer) Tokenize() []Token {
	for {
		char, _, err := l.reader.ReadRune()

		if err != nil {
			if err == io.EOF {
				l.tokens = append(l.tokens, Token{
					Position: Position{
						StartLine:   l.position.StartLine,
						StartColumn: l.position.StartColumn,
						EndLine:     l.position.EndLine,
						EndColumn:   l.position.EndColumn + 1,
					},
					TokenType: EOF,
					Value:     "",
				})

				break
			}

			fmt.Println(err)
		}

		switch char {
		case '\n':
			l.tokens = append(l.tokens, Token{
				Position: Position{
					StartLine:   l.position.StartLine,
					StartColumn: l.position.StartColumn,
					EndLine:     l.position.EndLine,
					EndColumn:   l.position.EndColumn + 1,
				},
				TokenType: NEWLINE,
				Value:     "",
			})

			l.position.EndLine++
			l.position.EndColumn = 0
		default:
			l.position.EndColumn++

			if unicode.IsSpace(char) {
				continue
			}

			l.current += string(char)

			token := l.getToken()

			if token != UNKNOWN {
				l.tokens = append(l.tokens, Token{
					Position: Position{
						StartLine:   l.position.StartLine,
						StartColumn: l.position.StartColumn,
						EndLine:     l.position.EndLine,
						EndColumn:   l.position.EndColumn,
					},
					TokenType: l.getToken(),
					Value:     l.current,
				})

				if token != INVALID {
					l.current = ""

					l.position.StartLine = l.position.EndLine
					l.position.StartColumn = l.position.EndColumn
				}
			}
		}
	}

	return l.tokens
}
