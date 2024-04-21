package main

import (
	"fmt"
	"neon/neonc"
)

func main() {
	currentDirectory := neonc.CurrentDirectory()

	all_files := neonc.Walk(currentDirectory)
	files := neonc.Filter(all_files)

	if len(files) < 1 {
		fmt.Println("No neon files found.")

		return
	}

	file := files[0]

	//

	data := neonc.ReadFile(file)

	_ = data
}
