package neonc

import (
	"fmt"
	"neon/pkg/util"
)

type NeonError interface {
	Error()
}

type ParseError struct {
	FilePath string
	Position Position
	Message  string
}

func (err *ParseError) Error() {
	fmt.Println("File Path:", err.FilePath)
	fmt.Println("Line:", util.ExtractLine(err.FilePath, err.Position.Line-1))
	fmt.Println("Position:", err.Position.String())
	fmt.Println(err.Message)
}
