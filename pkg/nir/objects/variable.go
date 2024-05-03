package objects

import (
	"fmt"
	"neon/pkg/util"
)

type Variable struct {
	Identifier string
	IsMutable  bool
	Type       Object
}

func (v Variable) String() string {
	isMut := "constant"

	if v.IsMutable {
		isMut = "variable"
	}

	return util.MakeGreen(v.Identifier) + " = " + isMut + "<" + fmt.Sprintf("%s", v.Type) + ">"
}
