package ast

import (
	"fmt"
	"neon/pkg/util"
)

type Data struct {
	Id    Id
	Value string
}

func (d *Data) String() string {
	if d.Value == "" {
		return fmt.Sprintf(util.ColorBlue+"%s"+util.ColorReset, d.Id)
	}

	return fmt.Sprintf(util.ColorYellow+"%s"+util.ColorReset+"("+util.ColorGreen+"%s"+util.ColorReset+")", d.Id, d.Value)
}
