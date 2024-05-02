package ast

import "fmt"

type Data struct {
	Id    Id
	Value string
}

func (d *Data) String() string {
	return fmt.Sprintf("%s(%s)", d.Id, d.Value)
}
