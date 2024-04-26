package neonc

import "neon/pkg/util"

func actionInvalid(parser *Parser) NeonError {
	return &ParseError{
		FilePath: parser.sourceFilePath,
		Position: parser.GetToken(parser.index).Position,
		Message:  "invalid character",
	}
}

func actionFnDeclaration(parser *Parser) NeonError {
	ident := parser.GetToken(parser.index + 1)

	if !util.Assert(ident.TokenType, IDENT) {
		return &ParseError{
			FilePath: parser.sourceFilePath,
			Position: parser.GetToken(parser.index).Position,
			Message:  "expected identifier",
		}
	}

	if !util.Assert(parser.GetToken(parser.index+2).TokenType, LPAREN) {
		return &ParseError{
			FilePath: parser.sourceFilePath,
			Position: parser.GetToken(parser.index + 1).Position,
			Message:  "expected '('",
		}
	}

	if !util.Assert(parser.GetToken(parser.index+3).TokenType, RPAREN) {
		return &ParseError{
			FilePath: parser.sourceFilePath,
			Position: parser.GetToken(parser.index + 2).Position,
			Message:  "expected ')'",
		}
	}

	parser.ast.Items = append(parser.ast.Items, &FnDeclaration{
		name: ident.Value,
	})

	parser.index += 3

	return nil
}
