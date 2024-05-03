package objects

import "neon/pkg/util"

type Goto struct {
	Into string
}

func (j *Goto) String() string {
	return util.MakeYellow("goto") + ": " + j.Into
}
