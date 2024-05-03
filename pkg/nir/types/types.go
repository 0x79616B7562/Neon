package types

import "fmt"

type Type uint32

const (
	VOID Type = iota

	TYPECHECK

	I32
)

func (t Type) String() string {
	switch t {
	case VOID:
		return "void"

	case TYPECHECK:
		return "TYPECHECK"

	case I32:
		return "i32"
	default:
		panic(fmt.Sprintf("UNKNOWN TYPE: %d", t))
	}
}
