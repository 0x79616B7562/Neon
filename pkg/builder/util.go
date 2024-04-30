package builder

import "neon/pkg/ast"

func extractDataFromAST(id ast.Id, data []ast.Data) (ast.Id, string) {
	for _, d := range data {
		if d.Id == id {
			return d.Id, d.Value
		}
	}

	return ast.UNKNOWN, ""
}
