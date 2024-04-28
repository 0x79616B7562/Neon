package parser

import "fmt"

type TokenType uint8

const (
	INVALID TokenType = iota
)

type TokenId struct {
	Id      string
	Value   string
	IsRegex bool
	Ignore  bool
}

func (t *TokenId) String() string {
	reg := "false"

	if t.IsRegex {
		reg = "true"
	}

	ignore := "false"

	if t.Ignore {
		ignore = "true"
	}

	return fmt.Sprintf("Id: %s, Value: %q, Is Regex: %s, Do Ignore: %s", t.Id, t.Value, reg, ignore)
}

type Token struct {
	Position Position
	Id       string
	Value    string
}

func (t *Token) String() string {
	return fmt.Sprintf("%s %q %s", t.Id, t.Value, t.Position.String())
}
