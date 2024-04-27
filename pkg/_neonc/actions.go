package neonc

import "neon/pkg/util"

func actionInvalid(parser *Parser, grammar []Grammar) NeonError {
	return &ParseError{
		FilePath: parser.sourceFilePath,
		Position: parser.GetToken(parser.index).Position,
		Message:  "invalid character",
	}
}

func actionFnDeclaration(parser *Parser, grammar []Grammar) NeonError {
	ident := parser.GetToken(parser.index + 1)

	if !util.Assert(ident.TokenType, IDENT) {
		return NewParseError(parser.sourceFilePath, parser.GetToken(parser.index).Position, "expected identifier")
	}

	if !util.Assert(parser.GetToken(parser.index+2).TokenType, LPAREN) {
		return NewParseError(parser.sourceFilePath, parser.GetToken(parser.index+1).Position, "expected '('")
	}

	if !util.Assert(parser.GetToken(parser.index+3).TokenType, RPAREN) {
		return NewParseError(parser.sourceFilePath, parser.GetToken(parser.index+2).Position, "expected ')'")
	}

	parser.ast.Items = append(parser.ast.Items, &FnDeclaration{
		name: ident.Value,
	})

	parser.index += 3

	return nil
}
