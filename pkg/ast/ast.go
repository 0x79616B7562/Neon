package ast

type AST struct {
	FilePath string
	Root     Node
}

func NewAST() AST {
	return AST{
		Root: Node{
			Id: ROOT,
		},
	}
}

func (a *AST) Dump() {
	a.Root.Dump(0)
}
