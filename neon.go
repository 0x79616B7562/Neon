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

	parser := neonc.NewParser()

	parser.Parse(neonc.NewLexer(data).Tokenize())
}
