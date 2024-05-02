package parser

import (
	"fmt"
	"regexp"
)

type TokenId uint8

const (
	INVALID TokenId = iota
	EOF
	UNKNOWN
	WHITESPACE
	TAB
	NEWLINE

	VAR
	MUT
	FN

	LPAREN
	RPAREN

	LBRACE
	RBRACE

	SEMICOLON
	DOT
	COMMA
	COLON
	EQUALS

	IDENT
	NUM
	STRING
)

func TokenIdToString(tokenId TokenId) string {
	switch tokenId {
	case INVALID:
		return "INVALID"
	case EOF:
		return "EOF"
	case UNKNOWN:
		return "UNKNOWN"
	case WHITESPACE:
		return "WHITESPACE"
	case TAB:
		return "TAB"
	case NEWLINE:
		return "NEWLINE"

	case VAR:
		return "VAR"
	case MUT:
		return "MUT"
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
	case COLON:
		return "COLON"
	case EQUALS:
		return "EQUALS"

	case IDENT:
		return "IDENT"
	case NUM:
		return "NUM"
	case STRING:
		return "STRING"

	default:
		return fmt.Sprintf("UNKNOWN TOKEN STRING: %d", tokenId)
	}
}

type Token struct {
	Position Position
	TokenId  TokenId
	Value    string
}

func (t Token) String() string {
	return fmt.Sprintf("%s %q %s", TokenIdToString(t.TokenId), t.Value, t.Position.String())
}

type TokenDef struct {
	TokenId       TokenId
	Match         string
	IsRegex       bool
	Discard       bool
	CompiledRegex *regexp.Regexp
}

var TOKENS = []TokenDef{
	{WHITESPACE, " ", false, true, nil},
	{TAB, "\t", false, true, nil},
	{NEWLINE, "\n", false, false, nil},

	{VAR, "var", false, false, nil},
	{MUT, "mut", false, false, nil},
	{FN, "fn", false, false, nil},

	{LPAREN, "(", false, false, nil},
	{RPAREN, ")", false, false, nil},

	{LBRACE, "{", false, false, nil},
	{RBRACE, "}", false, false, nil},

	{SEMICOLON, ";", false, false, nil},
	{DOT, ".", false, false, nil},
	{COMMA, ",", false, false, nil},
	{COLON, ":", false, false, nil},
	{EQUALS, "=", false, false, nil},

	{IDENT, "^[a-zA-Z_]+[a-zA-Z0-9_]*$", true, false, nil},
	{NUM, "^[-]?[0-9_]+[.]?[0-9_]*?$", true, false, nil},
	{STRING, "^\"(?:\\\\.|[^\"\\\\])*\"$", true, false, nil},
}

func DoTokenDiscard(tokenId TokenId) bool {
	for _, token := range TOKENS {
		if token.TokenId == tokenId {
			return token.Discard
		}
	}

	return false
}
