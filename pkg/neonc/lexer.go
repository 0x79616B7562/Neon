package neonc

import (
	"bufio"
	"fmt"
	"io"
	"regexp"
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
		for _, reg := range REGS {
			reg, err := regexp.Compile(reg.Match)

			if err != nil {
				panic(err)
			}

			comp := reg.Find([]byte(l.current))

			if len(comp) == 0 && l.current != "" {
				comp := string(reg.Find([]byte(l.current[:len(l.current)-1])))

				if len(comp) != 0 {
					l.addIdent(comp)

					l.current = ""
					l.reader.UnreadRune()

					break
				}
			} else if len(comp) > 0 {
				returnVal = UNKNOWN
			}
		}
	}

	return returnVal
}

func (l *Lexer) addIdent(value string) {
	l.tokens = append(l.tokens, Token{
		Position: Position{
			StartLine:   l.position.StartLine,
			StartColumn: l.position.StartColumn,
			EndLine:     l.position.EndLine,
			EndColumn:   l.position.EndColumn,
		},
		TokenType: IDENT,
		Value:     value,
	})
}

func (l *Lexer) addEof() {
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
}

func (l *Lexer) addNewLine() {
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
}

func (l *Lexer) Tokenize() []Token {
	for {
		char, _, err := l.reader.ReadRune()

		if err != nil {
			if err == io.EOF {
				l.addEof()

				break
			}

			fmt.Println(err)
		}

		switch char {
		case '\n':
			l.addNewLine()

			l.position.EndLine++
			l.position.EndColumn = 0
		default:
			l.position.EndColumn++

			if unicode.IsSpace(char) {
				continue
			}

			l.current += string(char)

			token := l.getToken()

			if token != UNKNOWN && l.current != "" {
				l.tokens = append(l.tokens, Token{
					Position: Position{
						StartLine:   l.position.StartLine,
						StartColumn: l.position.StartColumn,
						EndLine:     l.position.EndLine,
						EndColumn:   l.position.EndColumn,
					},
					TokenType: token,
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
