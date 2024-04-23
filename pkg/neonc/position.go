package neonc

import "fmt"

type Position struct {
	StartLine   int
	StartColumn int

	EndLine   int
	EndColumn int
}

func (pos *Position) String() string {
	return fmt.Sprintf("%d:%d-%d:%d", pos.StartLine, pos.StartColumn, pos.EndLine, pos.EndColumn)
}
