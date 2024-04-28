package parser

import (
	"regexp"
	"strings"
)

func extractTokens(rules []string) []TokenId {
	var tokens []TokenId

	for _, rule := range rules {
		if rule != "" {
			if rule[0] == '@' {
				tokenName := strings.ReplaceAll(strings.ReplaceAll(strings.Split(rule, "=")[0], " ", ""), "@", "")

				reg, err := regexp.Compile("r?\"[^.]*\"")

				if err != nil {
					panic(err)
				}

				value := string(reg.Find([]byte(rule)))

				if len(value) > 0 {
					isReg := false
					ignore := false

					if rule[len(rule)-1] == '!' {
						ignore = true
					}

					if value[0] == 'r' {
						isReg = true

						value = strings.ReplaceAll(value, "r\"", "")
						value = strings.ReplaceAll(value, "\"", "")
					} else {
						value = strings.ReplaceAll(value, "\"", "")
					}

					tokens = append(tokens, TokenId{
						Id:      tokenName,
						Value:   value,
						IsRegex: isReg,
						Ignore:  ignore,
					})
				}
			}
		}
	}

	return tokens
}
