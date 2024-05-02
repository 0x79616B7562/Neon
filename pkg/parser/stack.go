package parser

type Stack struct {
	FilePath string
	Index    int
	Tokens   []Token
}

func NewStack(filePath string, tokens []Token) Stack {
	return Stack{
		FilePath: filePath,
		Index:    0,
		Tokens:   tokens,
	}
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
