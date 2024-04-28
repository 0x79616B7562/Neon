package util

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"strings"
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

func ExtractLine(filepath string, line int) string {
	if filepath == "" || line < 0 {
		return ""
	}

	file := ReadFile(filepath)
	sc := bufio.NewScanner(file)

	l := 0

	for sc.Scan() {
		if l == line {
			return sc.Text()
		}

		l++
	}

	return ""
}

func ReaderToString(reader io.Reader) string {
	var sb strings.Builder

	_, err := io.Copy(&sb, reader)

	if err != nil {
		panic(err)
	}

	return sb.String()
}

func ReadFile(filepath string) io.Reader {
	dat, err := os.Open(filepath)

	if err != nil {
		panic(err)
	}

	return dat
}
