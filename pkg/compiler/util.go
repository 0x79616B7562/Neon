package compiler

import (
	"errors"
	"neon/pkg/ast"
)

func extractDataFromNode(id ast.Id, data []ast.Data) (ast.Data, error) {
	for _, d := range data {
		if d.Id == id {
			return d, nil
		}
	}

	return ast.Data{Id: ast.INVALID}, errors.New("Data Not Found")
}
