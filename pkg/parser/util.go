package parser

import (
	"io"
	"neon/pkg/err"
	"neon/pkg/util"
	"regexp"
	"strings"
)

func precompileRegexes() {
	for i := 0; i < len(TOKENS); i++ {
		if TOKENS[i].Match == "" {
			continue
		}

		if TOKENS[i].IsRegex {
			reg, err := regexp.Compile(TOKENS[i].Match)

			if err != nil {
				panic(err)
			}

			TOKENS[i].CompiledRegex = reg
		}
	}

}

func makeErr(stack *Stack, message string) error {
	return err.BuildError(
		stack.FilePath,
		stack.Get().Position.Line,
		stack.Get().Position.Column,
		message,
	)
}

func readFile(filePath string) string {
	reader := util.ReadFile(filePath)

	buf := new(strings.Builder)
	_, err := io.Copy(buf, reader)

	if err != nil {
		panic(err)
	}

	return buf.String()
}
