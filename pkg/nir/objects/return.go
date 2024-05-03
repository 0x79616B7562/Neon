package objects

import (
	"fmt"
	"neon/pkg/util"
)

type Return struct {
	Object any
}

func (r *Return) String() string {
	if r.Object == nil {
		return util.MakeYellow("return")
	}

	return util.MakeYellow("return") + fmt.Sprintf(" %s", r.Object)
}
