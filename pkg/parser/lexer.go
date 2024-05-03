package parser

func findTok(current string) TokenId {
	id := INVALID

	for _, token := range TOKENS {
		if token.Match == "" {
			continue
		}

		if !token.IsRegex {
			if token.Match == current {
				id = token.TokenId

				break
			}
		} else {
			if token.CompiledRegex == nil {
				panic("Precompiled Regex is NIL")
			}

			if len(token.CompiledRegex.Find([]byte(current))) > 0 {
				id = token.TokenId

				break
			}
		}
	}

	return id
}

func lex(data string, stack *Stack) {
	position := Position{
		Line:   1,
		Column: 0,
	}

	current := ""
	found := false

	for i := 0; i < len(data); i++ {
		current += string(data[i])

		position.Column++

		tokenId := findTok(current)

		if tokenId != INVALID {
			found = true
		} else if tokenId == INVALID && found {
			found = false

			ncur := current[:len(current)-1]

			position.Column--

			current = ""

			i--

			tokenId = findTok(ncur)

			if tokenId != UNKNOWN {
				if !DoTokenDiscard(tokenId) {
					stack.Push(Token{
						Position: position,
						TokenId:  tokenId,
						Value:    ncur,
					})
				}
			}

			if tokenId == NEWLINE {
				position.Line++
				position.Column = 0
			}
		}
	}

	stack.Push(Token{
		Position: position,
		TokenId:  EOF,
		Value:    "EOF",
	})
}
