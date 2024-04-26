package util

func AssertCmpError(a bool, msg string) {
	if !a {
		panic(msg)
	}
}

func Assert(a any, b any) bool {
	return a == b
}
