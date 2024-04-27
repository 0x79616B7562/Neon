package neonc

type Grammar struct {
	fire     TokenType
	action   func(*Parser, []Grammar) NeonError
	contains []Grammar
}

var InvalidGrammar = Grammar{
	INVALID,
	actionInvalid,
	[]Grammar{},
}

var NewLineGrammar = Grammar{
	NEWLINE,
	func(parser *Parser, grammar []Grammar) NeonError { return nil },
	[]Grammar{},
}

var HeadGrammar = []Grammar{
	InvalidGrammar,
	NewLineGrammar,
	{
		FN,
		actionFnDeclaration,
		[]Grammar{},
	},
}
