package neonc

import (
	"fmt"
	"neon/pkg/util"
	"strings"
)

type NeonError interface {
	Error()
}

type ParseError struct {
	FilePath string
	Position Position
	Message  string
}

func NewParseError(filePath string, position Position, message string) *ParseError {
	return &ParseError{
		FilePath: filePath,
		Position: position,
		Message:  message,
	}
}

func (err *ParseError) Error() {
	fmt.Print(util.ColorRed + "Error " + util.ColorReset)
	fmt.Printf(util.ColorBlue+"->"+util.ColorReset+" %s\n", err.FilePath)

	line := fmt.Sprintf("%d", err.Position.Line)
	columns := ""

	if err.Position.Column > 0 {
		columns = strings.Repeat(" ", err.Position.Column-1)
	}

	fmt.Println(util.ColorBlue + strings.Repeat(" ", len([]rune(line))+1) + "|" + util.ColorReset)
	fmt.Println(util.ColorBlue + line + " | " + util.ColorReset + util.ExtractLine(err.FilePath, err.Position.Line-1))
	fmt.Println(
		util.ColorBlue +
			strings.Repeat(" ", len([]rune(line))+1) +
			"| " +
			util.ColorReset +
			columns +
			util.ColorRed +
			"^ " +
			err.Message +
			util.ColorReset,
	)
	fmt.Println()
}
