package nir

import (
	"fmt"
	"neon/pkg/util"
	"path/filepath"
)

type Module struct {
	Name    string
	Nodes   []Node
	Pointer *Node
}

func NewModule(filePath string) Module {
	_, file := filepath.Split(filePath)

	return Module{
		Name:    file,
		Pointer: nil,
	}
}

func (m *Module) Dump() {
	fmt.Println(util.MakeBold(util.MakeCyan("Module")) + ": " + util.MakeYellow(m.Name))

	for _, node := range m.Nodes {
		fmt.Println(node)
	}
}
