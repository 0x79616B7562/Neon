package parser

import "fmt"

type Position struct {
	Line   int
	Column int
}

func (pos *Position) String() string {
	return fmt.Sprintf("%d:%d", pos.Line, pos.Column)
}
