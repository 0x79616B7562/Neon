package neonc

import "fmt"

type Item interface {
	String() string
	Build()
}

//

type FnDeclaration struct {
	name string
}

func (fn *FnDeclaration) String() string {
	return fmt.Sprintf("FN<%s>", fn.name)
}

func (fn *FnDeclaration) Build() {
}
