package parser

import (
	"io"
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

func splitCharsInclusive(s, chars string) (out []string) {
	for {
		m := strings.IndexAny(s, chars)

		if m < 0 {
			break
		}

		out = append(out, s[:m], s[m:m+1])
		s = s[m+1:]
	}

	out = append(out, s)

	return
}

func readDataFromFile(filePath string) []string {
	reader := util.ReadFile(filePath)

	buf := new(strings.Builder)
	_, err := io.Copy(buf, reader)

	if err != nil {
		panic(err)
	}

	split := " \n\t"

	for _, token := range TOKENS {
		if token.Match != "" && !token.IsRegex && len([]rune(token.Match)) == 1 {
			split += token.Match
		}
	}

	str := splitCharsInclusive(buf.String(), split)

	return str
}
