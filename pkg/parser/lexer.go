package parser

import (
	"regexp"
	"strings"
)

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

func tokenize(source string, tokenIds []TokenId) []Token {
	var tokens []Token

	position := Position{
		Line:   1,
		Column: 0,
	}

	split := " \n\t"

	for _, token := range tokenIds {
		if token.Value != "" && !token.IsRegex && len([]rune(token.Value)) == 1 {
			split += token.Value
		}
	}

	str := splitCharsInclusive(source, split)

	for i := 0; i < len(str); i++ {
		if str[i] == "" {
			continue
		}

		position.Column += len([]rune(str[i]))

		if str[i] == "\n" {
			position.Line++
			position.Column = 0
		}

		tokenType := "INVALID"
		doIgnore := false

		for _, token := range tokenIds {
			if token.Value == "" {
				continue
			}

			if !token.IsRegex {
				if token.Value == str[i] {
					tokenType = token.Id
					doIgnore = token.Ignore

					break
				}
			} else {
				reg, err := regexp.Compile(token.Value)

				if err != nil {
					panic(err)
				}

				if len(reg.Find([]byte(str[i]))) > 0 {
					tokenType = token.Id
					doIgnore = token.Ignore

					break
				}
			}
		}

		if !doIgnore {
			tokens = append(tokens, Token{
				Position: position,
				Id:       tokenType,
				Value:    str[i],
			})
		}
	}

	return tokens
}
