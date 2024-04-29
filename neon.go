package main

import (
	"fmt"

	"neon/pkg/clang"
	"neon/pkg/compiler"
	"neon/pkg/lexer"
	"neon/pkg/parser"
	"neon/pkg/util"
)

func main() {
	fmt.Println("RUNNING")

	clang.Invoke()

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

	tokens := lexer.NewLexer(data).Tokenize()

	for _, token := range tokens {
		fmt.Println(token.String())
	}

	fmt.Println()

	parser := parser.NewParser(file, tokens)
	head, err := parser.Parse()

	fmt.Println(head.String(1))

	if err != nil {
		fmt.Println(err)

		return
	}

	fmt.Println()

	compiler := compiler.NewCompiler()
	defer compiler.Dispose()

	compiler.Compile(head, file)
}
