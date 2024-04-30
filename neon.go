package main

import (
	"fmt"

	"neon/pkg/lexer"
	"neon/pkg/llvm"
	"neon/pkg/parser"
	"neon/pkg/target"
	"neon/pkg/util"
)

func main() {
	whole := util.NewMeasure()

	fmt.Println("RUNNING")
	fmt.Println()

	fmt.Println("LLVM VERSION:", llvm.Version)
	fmt.Println()

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

	measure := util.NewMeasure()
	tokens := lexer.NewLexer(data).Tokenize()
	measure.Finish("LEXER:")
	_ = tokens

	for _, token := range tokens {
		fmt.Println(token.String())
	}

	fmt.Println()

	measure = util.NewMeasure()
	parser := parser.NewParser(file, tokens)
	ast, err := parser.Parse()
	measure.Finish("PARSER:")

	fmt.Println(ast.String(1))
	fmt.Println()

	if err != nil {
		fmt.Println(err)

		return
	}

	target := target.NewTarget()
	defer target.Dispose()

	ast.Build(file, &target)

	fmt.Println()

	whole.Finish("FINISHED IN:")
}
