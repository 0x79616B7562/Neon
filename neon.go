package main

import (
	"fmt"

	"neon/pkg/compiler"
	"neon/pkg/parser"
	"neon/pkg/semantic"
	"neon/pkg/util"
)

func main() {
	whole := util.NewMeasure()

	fmt.Println("RUNNING")
	fmt.Println()

	measure := util.NewMeasure()
	currentDirectory := util.CurrentDirectory()

	fmt.Println("WORKING DIR:", currentDirectory)

	all_files := util.WalkDirectories(currentDirectory)
	files := util.FilterNonNeonFiles(all_files)

	if len(files) < 1 {
		fmt.Println("No neon files found.")

		return
	}

	//

	file := files[0]
	measure.Finish("READING FILES:")

	measure = util.NewMeasure()
	parser := parser.NewParser()
	ast, err := parser.Parse(file)

	if err != nil {
		fmt.Println(err)

		return
	}

	measure.Finish("PARSER:")

	fmt.Println()
	ast.Dump()
	fmt.Println()

	measure = util.NewMeasure()
	err = semantic.Analyze(ast)

	if err != nil {
		fmt.Println(err)
		return
	}

	measure.Finish("Semantic Analysis:")

	measure = util.NewMeasure()
	compiler := compiler.NewCompiler()
	defer compiler.Dispose()
	compiler.Compile(ast)
	measure.Finish("Compiling:")

	fmt.Println()

	whole.Finish("FINISHED IN:")
}
