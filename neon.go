package main

import (
	_ "embed"
	"fmt"

	"neon/pkg/parser"
	"neon/pkg/util"
)

//go:embed grammar/grammar
var grammar string

func main() {
	currentDirectory := util.CurrentDirectory()

	all_files := util.WalkDirectories(currentDirectory)
	files := util.FilterNonNeonFiles(all_files)

	if len(files) < 1 {
		fmt.Println("No neon files found.")

		return
	}

	//

	file := files[0]

	parser := parser.NewParser(grammar)

	fmt.Println("IDS:")
	parser.PrintTokenIds()
	fmt.Println()

	parser.Parse(file)

	//

	// tokens := lexer.NewLexer(data).Tokenize()
	//
	// for _, token := range tokens {
	// 	fmt.Println(token.String())
	// }
	//
	// fmt.Println()
	//
	// parser := parser.NewParser(file, tokens)
	// head, err := parser.Parse()
	//
	// fmt.Println(head.String(1))
	//
	// if err != nil {
	// 	fmt.Println(err)
	//
	// 	return
	// }
	//
	// fmt.Println()
}
