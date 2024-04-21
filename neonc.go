package main

import (
	"fmt"
	"neon/neonc"
)

func main() {
	currentDirectory := neonc.CurrentDirectory()

	all_files := neonc.Walk(currentDirectory)
	files := neonc.Filter(all_files)

	//

	if len(files) < 1 {
		return
	}

	data := string(neonc.ReadFile(currentDirectory + "/" + files[0]))

	fmt.Println(data)
}
