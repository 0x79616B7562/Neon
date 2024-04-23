package neonc

import (
	"fmt"
	"io"
	"os"
	"path/filepath"
)

func FilterNonNeonFiles(list []string) []string {
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

func WalkDirectories(directory string) []string {
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

func ReadFile(filepath string) io.Reader {
	dat, err := os.Open(filepath)

	if err != nil {
		panic(err)
	}

	return dat
}
