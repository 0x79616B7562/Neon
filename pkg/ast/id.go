package ast

import "fmt"

type Id uint32

//

const (
	INVALID Id = iota

	ROOT

	BLOCK
	END

	IDENT
	TYPE

	EXPRESSION
	VALUE
	NUMBER

	MUT
	VARIABLE
	FUNCTION
)

func (id Id) String() string {
	switch id {
	case INVALID:
		return "Invalid"

	case ROOT:
		return "Root"

	case BLOCK:
		return "Block"
	case END:
		return "End"

	case IDENT:
		return "Ident"
	case TYPE:
		return "Type"

	case EXPRESSION:
		return "Expression"
	case VALUE:
		return "Value"
	case NUMBER:
		return "Number"

	case MUT:
		return "Mut"
	case VARIABLE:
		return "Variable"
	case FUNCTION:
		return "Function"

	default:
		return fmt.Sprintf("INVALID ID: %d", id)
	}
}
