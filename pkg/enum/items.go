package enum

import "fmt"

type Item uint8

const (
	INVALIDITEM Item = iota

	HEAD

	BLOCK

	VARIABLE
	FUNCTION
)

func ItemToString(item Item) string {
	switch item {
	case INVALIDITEM:
		return "INVALIDITEM"
	case HEAD:
		return "HEAD"
	case BLOCK:
		return "BLOCK"
	case VARIABLE:
		return "VARIABLE"
	case FUNCTION:
		return "FUNCTION"
	default:
		return fmt.Sprintf("UNKNOWN ITEM STRING: %d", item)
	}
}
