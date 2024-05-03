package nir

import "neon/pkg/nir/objects"

type Block struct {
	Identifier string
	Objects    []objects.Object
}

func (b *Block) AddObject(obj objects.Object) {
	b.Objects = append(b.Objects, obj)
}

func (b Block) String() string {
	return b.Identifier
}
