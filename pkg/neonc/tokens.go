package neonc

type TokenType int

const (
	EOF TokenType = iota
	UNKNOWN
	INVALID
	NEWLINE

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

type TokenDef struct {
	TokenType TokenType
	Match     string
}

var TOKENS = []TokenDef{
	{NEWLINE, "\n"},
	{FN, "fn"},
	{LPAREN, "("},
	{RPAREN, ")"},
	{LBRACE, "{"},
	{RBRACE, "}"},
	{SEMICOLON, ";"},
	{DOT, "."},
	{COMMA, ","},
}

var REGS = []TokenDef{
	{IDENT, "^[a-zA-Z_]*[a-zA-Z0-9_]+$"},
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
