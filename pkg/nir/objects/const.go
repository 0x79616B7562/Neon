package objects

import (
	"fmt"
	"neon/pkg/nir/types"
	"neon/pkg/util"
)

type Const struct {
	Type  types.Type
	Value int64
}

func (c Const) String() string {
	return fmt.Sprintf(util.MakeGreen("Const")+"(type: %s, val: %d)", c.Type, c.Value)
}
