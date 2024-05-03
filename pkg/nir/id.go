package nir

import "fmt"

type Id uint32

const (
	FUNCTION Id = iota
)

func (id Id) String() string {
	switch id {
	case FUNCTION:
		return "fn"
	default:
		panic(fmt.Sprintf("UNKNOWN ID: %d", id))
	}
}
