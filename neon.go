package main

import (
	"fmt"

	"neon/pkg/lexer"
	"neon/pkg/util"
)

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
	data := util.ReadFile(file)

	//

	measure := util.NewMeasure()
	tokens := lexer.NewLexer(data).Tokenize()
	measure.Finish("Lexer:")

	fmt.Println()

	for _, token := range tokens {
		fmt.Println(token.String())
	}

	// fmt.Println()
	// ast.Dump()

	// neonc.Compile(ast)
}
