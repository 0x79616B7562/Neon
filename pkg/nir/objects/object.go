package objects

import "fmt"

type Object any

func ObjectToString(obj Object) string {
	switch t := obj.(type) {
	case Goto:
		return t.String()
	case Return:
		return t.String()
	case Variable:
		return t.String()
	default:
		panic(fmt.Sprintf("UNKNOWN OBJECT: %v", t))
	}
}
