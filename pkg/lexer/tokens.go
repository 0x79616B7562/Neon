package lexer

import (
	"fmt"
	"neon/pkg/enum"
	"regexp"
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
	TokenType     enum.TokenType
	Match         string
	IsRegex       bool
	Discard       bool
	CompiledRegex *regexp.Regexp
}

var TOKENS = []TokenDef{
	{enum.WHITESPACE, " ", false, true, nil},
	{enum.TAB, "\t", false, true, nil},
	{enum.NEWLINE, "\n", false, false, nil},

	{enum.VAR, "var", false, false, nil},
	{enum.FN, "fn", false, false, nil},

	{enum.LPAREN, "(", false, false, nil},
	{enum.RPAREN, ")", false, false, nil},

	{enum.LBRACE, "{", false, false, nil},
	{enum.RBRACE, "}", false, false, nil},

	{enum.SEMICOLON, ";", false, false, nil},
	{enum.DOT, ".", false, false, nil},
	{enum.COMMA, ",", false, false, nil},
	{enum.COLON, ":", false, false, nil},
	{enum.EQUALS, "=", false, false, nil},

	{enum.IDENT, "^[a-zA-Z_]+[a-zA-Z0-9_]*$", true, false, nil},
	{enum.NUM, "^[-]?[0-9_]+[.]?[0-9_]*?$", true, false, nil},
}

func DoTokenDiscard(tokenType enum.TokenType) bool {
	for _, token := range TOKENS {
		if token.TokenType == tokenType {
			return token.Discard
		}
	}

	return false
}
