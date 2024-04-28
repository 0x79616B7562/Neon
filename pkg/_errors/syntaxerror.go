package errors

import (
	"fmt"
	"neon/pkg/lexer"
	"neon/pkg/util"
	"strings"
)

type SyntaxError struct {
	FileName string
	Token    lexer.Token
	Message  string
}

func NewSyntaxError(fileName string, token lexer.Token, message string) *SyntaxError {
	return &SyntaxError{
		FileName: fileName,
		Token:    token,
		Message:  message,
	}
}

func (err *SyntaxError) Error() {
	fmt.Print(util.ColorRed + "Error " + util.ColorReset)
	fmt.Printf(util.ColorBlue+"->"+util.ColorReset+" %s\n", err.FileName)

	line := fmt.Sprintf("%d", err.Token.Position.Line)

	columns := ""

	if err.Token.Position.Column > 0 {
		columns = strings.Repeat(" ", err.Token.Position.Column-1)
	}

	fmt.Println(util.ColorBlue + strings.Repeat(" ", len([]rune(line))+1) + "|" + util.ColorReset)
	fmt.Println(util.ColorBlue + line + " | " + util.ColorReset + util.ExtractLine(err.FileName, err.Token.Position.Line-1))

	errvalue := "found " + fmt.Sprintf("%q", err.Token.Value)

	fmt.Println(
		util.ColorBlue +
			strings.Repeat(" ", len([]rune(line))+1) +
			"| " +
			util.ColorReset +
			columns +
			util.ColorRed +
			"^ " +
			err.Message +
			": " +
			errvalue +
			util.ColorReset,
	)
	fmt.Println()

}
