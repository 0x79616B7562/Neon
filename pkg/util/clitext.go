package util

var ColorReset = "\033[0m"
var ColorRed = "\033[31m"
var ColorGreen = "\033[32m"
var ColorYellow = "\033[33m"
var ColorBlue = "\033[34m"
var ColorMagenta = "\033[35m"
var ColorCyan = "\033[36m"
var ColorGray = "\033[37m"
var ColorWhite = "\033[97m"
var Bold = "\033[1m"

func MakeRed(str string) string {
	return ColorRed + str + ColorReset
}

func MakeCyan(str string) string {
	return ColorCyan + str + ColorReset
}

func MakeBold(str string) string {
	return Bold + str + ColorReset
}

func MakeYellow(str string) string {
	return ColorYellow + str + ColorReset
}

func MakeGreen(str string) string {
	return ColorGreen + str + ColorReset
}
