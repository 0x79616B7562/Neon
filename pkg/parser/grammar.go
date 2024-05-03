package parser

import (
	"neon/pkg/ast"
	"neon/pkg/util"
)

func parseToken(stack *Stack, toFind TokenId, ignore util.Option[TokenId]) util.Option[Token] {
	for i := stack.Index; i < len(stack.Tokens); i++ {
		tok := stack.Tokens[i]

		if tok.TokenId == toFind {
			stack.AddToIndex(i - stack.Index + 1)
			return util.Some(tok)
		}

		if ignore.IsSome {
			if ignore.Unwrap() == tok.TokenId {
				continue
			}
		}

		return util.None[Token]()
	}

	return util.None[Token]()
}

// IDENT = ident -> bool
func parseIdent(stack *Stack, data *Data, ignore util.Option[TokenId], saveAs util.Option[ast.Id]) bool {
	if ident := parseToken(stack, IDENT, ignore); ident.IsSome {
		if saveAs.IsSome {
			data.Data = append(data.Data, ast.Data{Id: saveAs.Unwrap(), Value: ident.Unwrap().Value})
		}

		return true
	}

	return false
}

// LPAREN = '(' -> bool
func parseLeftParen(stack *Stack, ignore util.Option[TokenId]) bool {
	return parseToken(stack, LPAREN, ignore).IsSome
}

// RPAREN = ')' -> bool
func parseRightParen(stack *Stack, ignore util.Option[TokenId]) bool {
	return parseToken(stack, RPAREN, ignore).IsSome
}

// COMMENT
func parseComment(stack *Stack, node *ast.Node, data *Data) error {
	_ = node
	_ = data

	stack.AddToIndex(1)

	return nil
}

// FUNCTION = fn' 'ident' '(' ')' -> error
func parseFunction(stack *Stack, node *ast.Node, data *Data) error {
	parseToken(stack, FN, util.None[TokenId]())

	if !parseIdent(stack, data, util.Some(NEWLINE), util.Some(ast.IDENT)) {
		return makeErr(stack, "expected identifier")
	}

	if !parseLeftParen(stack, util.Some(NEWLINE)) {
		return makeErr(stack, "expected '('")
	}

	if !parseRightParen(stack, util.Some(NEWLINE)) {
		return makeErr(stack, "expected ')'")
	}

	node.Nodes = append(node.Nodes, ast.Node{
		Id:   ast.FUNCTION,
		Data: data.Data,
	})

	return nil
}

// EXPRESSION = 'num' -> error
func parseExpression(stack *Stack, node *ast.Node) error {
	num := parseToken(stack, NUM, util.Some(NEWLINE))

	if !num.IsSome {
		return makeErr(stack, "expected number")
	}

	node.Nodes = append(node.Nodes, ast.Node{
		Id: ast.EXPRESSION,
		Nodes: []ast.Node{
			{
				Id:   ast.NUMBER,
				Data: []ast.Data{{Id: ast.VALUE, Value: num.Unwrap().Value}},
			},
		},
	})

	return nil
}

// VAR = 'var' 'mut'? 'ident' ('type' (= EXPRESSION)? | (= EXPRESSION)) -> error
func parseVariable(stack *Stack, node *ast.Node, data *Data) error {
	parseToken(stack, VAR, util.None[TokenId]())

	if parseToken(stack, MUT, util.Some(NEWLINE)).IsSome {
		data.Data = append(data.Data, ast.Data{Id: ast.MUT, Value: ""})
	}

	if !parseIdent(stack, data, util.Some(NEWLINE), util.Some(ast.IDENT)) {
		return makeErr(stack, "expected identifier")
	}

	variableNode := ast.Node{
		Id: ast.VARIABLE,
	}

	identResult := parseIdent(stack, data, util.Some(NEWLINE), util.Some(ast.TYPE))

	if parseToken(stack, EQUALS, util.Some(NEWLINE)).IsSome {
		if err := parseExpression(stack, &variableNode); err != nil {
			return err
		}
	} else if !identResult {
		return makeErr(stack, "expected '=' or "+ast.TYPE.String())
	}

	variableNode.Data = data.Data
	node.Nodes = append(node.Nodes, variableNode)

	return nil
}
