package parser

import (
	"fmt"
	"neon/pkg/ast"
	"neon/pkg/util"
)

var FIRST_FOLLOW = []FirstFollow{
	{First: FN, Follow: parseFunction},
}

//

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

func previousNodeIsAny(node *ast.Node, arr []ast.Id) bool {
	if len(node.Nodes) > 0 {
		for _, id := range arr {
			if node.Nodes[len(node.Nodes)-1].Id == id {
				return true
			}
		}
	}

	return false
}

// IDENT = ident
func parseIdent(stack *Stack, data *Data, ignore util.Option[TokenId]) bool {
	if ident := parseToken(stack, IDENT, ignore); ident.IsSome {
		data.Data = append(data.Data, ast.Data{Id: ast.IDENT, Value: ident.Unwrap().Value})

		return true
	}

	return false
}

// LPAREN = '('
func parseLeftParen(stack *Stack, ignore util.Option[TokenId]) bool {
	return parseToken(stack, LPAREN, ignore).IsSome
}

// RPAREN = ')'
func parseRightParen(stack *Stack, ignore util.Option[TokenId]) bool {
	return parseToken(stack, RPAREN, ignore).IsSome
}

// FUNCTION = 'fn' 'ident' '(' ')'
func parseFunction(stack *Stack, node *ast.Node, data *Data) bool {
	if !parseIdent(stack, data, util.Some(NEWLINE)) {
		return false
	}

	if !parseLeftParen(stack, util.Some(NEWLINE)) {
		return false
	}

	if !parseRightParen(stack, util.Some(NEWLINE)) {
		return false
	}

	node.Nodes = append(node.Nodes, ast.Node{
		Id:   ast.FUNCTION,
		Data: data.Data,
	})

	return true
}

//

func analyze(stack *Stack, node *ast.Node) {
loop:
	for {
		if stack.IsAtEnd() {
			break
		}
		found := false

		tokenId := stack.Get().TokenId

		if tokenId == LBRACE || tokenId == RBRACE || tokenId == NEWLINE {
			stack.AddToIndex(1)

			switch tokenId {
			case LBRACE:
				if previousNodeIsAny(
					node,
					[]ast.Id{
						ast.FUNCTION,
					},
				) {
					analyze(stack, &node.Nodes[len(node.Nodes)-1])
				} else {
					lnode := ast.Node{Id: ast.BLOCK}

					analyze(stack, &lnode)

					node.Nodes = append(node.Nodes, lnode)
				}
			case RBRACE:
				node.Nodes = append(node.Nodes, ast.Node{Id: ast.END})

				break loop
			}

			continue
		}

		for _, ff := range FIRST_FOLLOW {
			if ff.First == tokenId {
				stack.AddToIndex(1)
				result := ff.Follow(stack, node, &Data{})

				if !result {
					fmt.Println(util.ColorYellow + "TODO" + util.ColorReset + ": Error grammar.go")
				}

				found = true
			}
		}

		if !found {
			fmt.Println(util.ColorRed + "Internal Error" + util.ColorReset + ": Unknown FF TokenId: " + stack.Get().String())

			break
		}
	}
}

func parseStack(stack Stack) ast.AST {
	ast := ast.NewAST()

	analyze(&stack, &ast.Head)

	return ast
}
