package err

import (
	"errors"
	"fmt"
	"neon/pkg/util"
	"strconv"
	"strings"
)

func BuildError(filePath string, line, column int, message string) error {
	linestr := util.ExtractLine(filePath, line-1)

	err := util.MakeBold(util.MakeRed("Error")) +
		util.MakeCyan(" -> ") + fmt.Sprintf("%s:%d:%d", filePath, line, column) +
		"\n"

	linenum := strconv.Itoa(line)
	pred := strings.Repeat(" ", len([]rune(linenum))+1)

	err += pred + util.MakeCyan("|\n")
	err += util.MakeCyan(linenum+" | ") + linestr + "\n"
	err += pred + util.MakeCyan("|")

	col := strings.Repeat(" ", column)

	err += col + util.MakeRed("^ "+message) + "\n"

	return errors.New(err)
}
