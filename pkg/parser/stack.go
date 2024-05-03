package parser

import "fmt"

type Stack struct {
	FilePath      string
	Index         int
	Tokens        []Token
	LastLeftBrace Token
}

func NewStack(filePath string, tokens []Token) Stack {
	return Stack{
		FilePath: filePath,
		Index:    0,
		Tokens:   tokens,
	}
}

func (s *Stack) Dump() {
	for _, tok := range s.Tokens {
		fmt.Println(tok.String())
	}
}

func (s *Stack) Pop() {
	if len(s.Tokens) == 0 {
		return
	}

	s.Index--
	s.Tokens = s.Tokens[:len(s.Tokens)-1]
}

func (s *Stack) Push(tok Token) {
	s.Tokens = append(s.Tokens, tok)
}

func (s *Stack) Get() Token {
	return s.Tokens[s.Index]
}

func (s *Stack) AddToIndex(add int) {
	s.Index += add
}

func (s *Stack) IsAtEnd() bool {
	return s.Index >= len(s.Tokens)-1
}
