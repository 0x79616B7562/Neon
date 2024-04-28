package lexer

import (
	"fmt"
	"neon/pkg/enum"
)

type Token struct {
	Position  Position
	TokenType enum.TokenType
	Value     string
}

func (t *Token) String() string {
	return fmt.Sprintf("%s %q %s", enum.TokenTypeToString(t.TokenType), t.Value, t.Position.String())
}

type TokenDef struct {
	TokenType enum.TokenType
	Match     string
	IsRegex   bool
	Discard   bool
}

var TOKENS = []TokenDef{
	{enum.WHITESPACE, " ", false, true},
	{enum.TAB, "\t", false, true},
	{enum.NEWLINE, "\n", false, true},

	{enum.VAR, "var", false, false},
	{enum.FN, "fn", false, false},

	{enum.LPAREN, "(", false, false},
	{enum.RPAREN, ")", false, false},

	{enum.LBRACE, "{", false, false},
	{enum.RBRACE, "}", false, false},

	{enum.SEMICOLON, ";", false, false},
	{enum.DOT, ".", false, false},
	{enum.COMMA, ",", false, false},
	{enum.COLON, ":", false, false},
	{enum.EQUALS, "=", false, false},

	{enum.IDENT, "^[a-zA-Z_]+[a-zA-Z0-9_]*$", true, false},
	{enum.NUM, "^[0-9_]+[.]?[0-9_]*?$", true, false},
}

func DoTokenDiscard(tokenType enum.TokenType) bool {
	for _, token := range TOKENS {
		if token.TokenType == tokenType {
			return token.Discard
		}
	}

	return false
}
