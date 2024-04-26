package main

import (
	"fmt"
	"neon/pkg/neonc"
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

	ast := neonc.NewParser(file, neonc.NewLexer(data).Tokenize()).Parse()

	ast.Dump()

	neonc.Compile(ast)
}
