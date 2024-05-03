package nir

import (
	"neon/pkg/ast"
	"neon/pkg/nir/types"
	"neon/pkg/util"
)

func resolveAstType(asttype string) types.Type {
	switch asttype {
	case "i32":
		return types.I32
	default:
		return types.TYPECHECK
	}
}

func extractData(id ast.Id, data []ast.Data) util.Option[ast.Data] {
	for _, d := range data {
		if d.Id == id {
			return util.Some(d)
		}
	}

	return util.None[ast.Data]()
}
