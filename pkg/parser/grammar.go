package parser

import (
	"neon/pkg/enum"
	"neon/pkg/lexer"
	"neon/pkg/util"
)

type Repeat uint8

const (
	NoRepeat Repeat = iota
	CanRepeat
)

type Optional uint8

const (
	IsOptional Optional = iota
	IsRequired
)

type MatchType bool

const MatchInSequence MatchType = true
const MatchWithAny MatchType = false

type Callback func([]lexer.Token)

type Grammar struct {
	Tokens       []enum.TokenType
	IgnoreToken  util.Option[enum.TokenType]
	Repeat       Repeat
	Optional     Optional
	MatchType    MatchType
	ErrorMessage util.Option[string]
	Callback     util.Option[Callback]
}

func NewGrammar(
	tokens []enum.TokenType,
	ignoreToken util.Option[enum.TokenType],
	repeat Repeat,
	optional Optional,
	matchType MatchType,
	errorMessage util.Option[string],
	callback util.Option[Callback],
) Grammar {
	return Grammar{
		Tokens:       tokens,
		IgnoreToken:  ignoreToken,
		Repeat:       repeat,
		Optional:     optional,
		MatchType:    matchType,
		ErrorMessage: errorMessage,
		Callback:     callback,
	}
}
