package nir

import (
	"neon/pkg/ast"
	"neon/pkg/nir/objects"
	"neon/pkg/nir/types"
)

func buildEnd(n *NeonIR, node *ast.Node) Hook {
	return nil
}

func buildBlock(n *NeonIR, node *ast.Node) Hook {
	nb := n.module.Pointer.AddBlock("")
	n.module.Pointer.AddToBlock(objects.Goto{Into: nb.Identifier}, -1)

	return nil
}

func buildFunction(n *NeonIR, node *ast.Node) Hook {
	fn := Node{Id: FUNCTION, Data: node.Data}

	ident := extractData(ast.IDENT, node.Data)

	if ident.Unwrap().Value == "main" {
		fn.Type = types.I32
	}

	fn.AddBlock("entry")

	n.module.Nodes = append(n.module.Nodes, fn)
	n.module.Pointer = &n.module.Nodes[len(n.module.Nodes)-1]

	return func() {
		if ident.Unwrap().Value == "main" {
			n.module.Pointer.AddToBlock(objects.Return{Object: objects.Const{Type: types.I32, Value: 0}}, 0)
			return
		}

		n.module.Pointer.AddToBlock(objects.Return{}, 0)
	}
}

func buildVariable(n *NeonIR, node *ast.Node) Hook {
	ident := extractData(ast.IDENT, node.Data)
	mut := extractData(ast.MUT, node.Data)

	vtype := types.TYPECHECK

	if etype := extractData(ast.TYPE, node.Data); etype.IsSome {
		vtype = resolveAstType(etype.Unwrap().Value)
	}

	object := objects.Variable{Identifier: ident.Unwrap().Value, Type: vtype, IsMutable: mut.IsSome}

	n.module.Pointer.AddToBlock(object, 0)

	return nil
}
