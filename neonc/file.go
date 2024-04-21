package neonc

import (
	"fmt"
	"io/ioutil"
	"os"
)

func Filter(list []string) []string {
	var files_ret []string

	for _, file := range list {
		if file[len(file)-1:] == "n" {
			files_ret = append(files_ret, file)
		}
	}

	return files_ret
}

func CurrentDirectory() string {
	path, err := os.Getwd()

	if err != nil {
		panic(err)
	}

	return path
}

func Walk(directory string) []string {
	files, err := ioutil.ReadDir(directory)

	if err != nil {
		panic(err)
	}

	var files_ret []string

	for _, file := range files {
		files_ret = append(files_ret, file.Name())
	}

	return files_ret
}

func ReadFile(filepath string) string {
	dat, err := os.ReadFile(filepath)

	if err != nil {
		fmt.Println("Filepath: ", filepath)
		panic(err)
	}

	return string(dat)
}
