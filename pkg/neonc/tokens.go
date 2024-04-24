package neonc

import "fmt"

type TokenType int

const (
	EOF TokenType = iota
	UNKNOWN
	INVALID
	NEWLINE
	WHITESPACE
	TAB

	FN

	LPAREN
	RPAREN

	LBRACE
	RBRACE

	SEMICOLON
	DOT
	COMMA

	IDENT
)

type Token struct {
	Position  Position
	TokenType TokenType
	Value     string
}

func (t *Token) String() string {
	return fmt.Sprintf("%s %q %s", TokenTypeToString(t.TokenType), t.Value, t.Position.String())
}

type TokenDef struct {
	TokenType TokenType
	Match     string
	IsRegex   bool
	Discard   bool
}

var TOKENS = []TokenDef{
	{NEWLINE, "\n", false, false},
	{FN, "fn", false, false},
	{LPAREN, "(", false, false},
	{RPAREN, ")", false, false},
	{LBRACE, "{", false, false},
	{RBRACE, "}", false, false},
	{SEMICOLON, ";", false, false},
	{DOT, ".", false, false},
	{COMMA, ",", false, false},
	{WHITESPACE, " ", false, true},
	{TAB, "\t", false, true},
	{IDENT, "^[a-zA-Z_]+[a-zA-Z0-9_]*$", true, false},
}

func DoTokenDiscard(tokenType TokenType) bool {
	for _, token := range TOKENS {
		if token.TokenType == tokenType {
			return token.Discard
		}
	}

	return false
}

func TokenTypeToString(tokenType TokenType) string {
	switch tokenType {
	case EOF:
		return "EOF"
	case UNKNOWN:
		return "UNKNOWN"
	case INVALID:
		return "INVALID"
	case NEWLINE:
		return "NEWLINE"
	case WHITESPACE:
		return "WHITESPACE"
	case FN:
		return "FN"
	case LPAREN:
		return "LPAREN"
	case RPAREN:
		return "RPAREN"
	case LBRACE:
		return "LBRACE"
	case RBRACE:
		return "RBRACE"
	case SEMICOLON:
		return "SEMICOLON"
	case DOT:
		return "DOT"
	case COMMA:
		return "COMMA"
	case IDENT:
		return "IDENT"
	default:
		return "UNKNOWN"
	}
}
