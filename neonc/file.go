package neonc

import (
	"fmt"
	"os"
	"path/filepath"
)

func Filter(list []string) []string {
	var files_ret []string

	for _, file := range list {
		if file[len(file)-2:] == ".n" {
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
	var ret_files []string

	err := filepath.Walk(directory,
		func(path string, info os.FileInfo, err error) error {
			if err != nil {
				return err
			}

			ret_files = append(ret_files, string(path))

			return nil
		})
	if err != nil {
		fmt.Println(err)
	}

	return ret_files
}

func ReadFile(filepath string) string {
	dat, err := os.ReadFile(filepath)

	if err != nil {
		fmt.Println("Filepath: ", filepath)
		panic(err)
	}

	return string(dat)
}
