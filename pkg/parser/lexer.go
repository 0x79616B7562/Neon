package parser

import "errors"

func lex(data []string, stack *Stack) {
	position := Position{
		Line:   1,
		Column: 0,
	}

	for _, str := range data {
		tok, err := tok(str, &position)

		if err != nil {
			continue
		}

		stack.Push(tok)
	}
}

func tok(s string, position *Position) (Token, error) {
	if s == "" {
		return Token{}, errors.New("INPUT IS EMPTY")
	}

	var token Token

	position.Column += len([]rune(s))

	tokenId := INVALID

	for _, token := range TOKENS {
		if token.Match == "" {
			continue
		}

		if !token.IsRegex {
			if token.Match == s {
				tokenId = token.TokenId

				break
			}
		} else {
			if token.CompiledRegex == nil {
				panic("Precompiled Regex is NIL")
			}

			if len(token.CompiledRegex.Find([]byte(s))) > 0 {
				tokenId = token.TokenId

				break
			}
		}
	}

	if tokenId != UNKNOWN {
		if !DoTokenDiscard(tokenId) {
			token = Token{
				Position: *position,
				TokenId:  tokenId,
				Value:    s,
			}
		} else {
			return Token{}, errors.New("TOKEN IS UNKNOWN")
		}
	}

	if s == "\n" {
		position.Line++
		position.Column = 0
	}

	return token, nil
}
