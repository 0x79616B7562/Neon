package ast

type AST struct {
	FilePath string
	Head     Node
}

func NewAST() AST {
	return AST{
		Head: Node{
			Id: HEAD,
		},
	}
}

func (a *AST) Dump() {
	a.Head.Dump(0)
}
