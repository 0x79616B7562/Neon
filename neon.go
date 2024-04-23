package main

import (
	"fmt"
	"neon/pkg/neonc"
)

func main() {
	currentDirectory := neonc.CurrentDirectory()

	all_files := neonc.WalkDirectories(currentDirectory)
	files := neonc.FilterNonNeonFiles(all_files)

	if len(files) < 1 {
		fmt.Println("No neon files found.")

		return
	}

	//

	file := files[0]
	data := neonc.ReadFile(file)

	//

	lexer := neonc.NewLexer(data)
	tokens := lexer.Tokenize()

	for _, token := range tokens {
		fmt.Printf("TOKENTYPE: %s, POSITION: %q, VALUE: %s\n", neonc.TokenTypeToString(token.TokenType), token.Position.String(), token.Value)
	}
}
