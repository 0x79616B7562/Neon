package nir

import (
	"neon/pkg/ast"
	"neon/pkg/nir/objects"
	"neon/pkg/nir/types"
	"neon/pkg/util"
	"strconv"
	"strings"
)

type Node struct {
	Id     Id
	Data   []ast.Data
	Type   types.Type
	Blocks []Block
}

func (n *Node) AddBlock(identifier string) *Block {
	id := identifier

	if id == "" {
		id = strconv.Itoa(len(n.Blocks))
	}

	n.Blocks = append(n.Blocks, Block{Identifier: id})

	return &n.Blocks[len(n.Blocks)-1]
}

func (n *Node) AddToBlock(obj objects.Object, offset int) {
	n.Blocks[len(n.Blocks)+(offset-1)].AddObject(obj)
}

func (n Node) String() string {
	str := util.MakeGreen(n.Id.String())

	if len(n.Data) > 0 {
		ident := extractData(ast.IDENT, n.Data)

		if !ident.IsSome {
			goto cont
		}

		str += " " + ident.Unwrap().Value + "()"

		if n.Type != types.VOID {
			str += " " + n.Type.String()
		}
	}

cont:

	str += " {\n"

	for _, block := range n.Blocks {
		str += util.MakeCyan(block.String()) + ":\n"

		for _, object := range block.Objects {
			str += strings.Repeat(" ", 4) + objects.ObjectToString(object) + "\n"
		}
	}

	str += "}\n"

	return str
}
