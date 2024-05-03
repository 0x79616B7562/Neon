package parser

import (
	"errors"
	"fmt"
	"neon/pkg/ast"
	"neon/pkg/err"
	"neon/pkg/util"
)

var FIRST_FOLLOW = []FirstFollow{
	{First: SINGLELINECOMMENT, Follow: parseComment},

	{First: FN, Follow: parseFunction},
	{First: VAR, Follow: parseVariable},
}

func analyze(stack *Stack, node *ast.Node, depth *int) error {
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
				(*depth)++

				stack.LastLeftBrace = stack.Get()

				if previousNodeIsAny(
					node,
					[]ast.Id{
						ast.FUNCTION,
					},
				) {
					err := analyze(stack, &node.Nodes[len(node.Nodes)-1], depth)

					if err != nil {
						return err
					}
				} else {
					lnode := ast.Node{Id: ast.BLOCK}

					err := analyze(stack, &lnode, depth)

					if err != nil {
						return err
					}

					node.Nodes = append(node.Nodes, lnode)
				}
			case RBRACE:
				(*depth)--

				if *depth < 0 {
					stack.Pop()
					return makeErr(stack, "unexpected closing delimiter")
				}

				node.Nodes = append(node.Nodes, ast.Node{Id: ast.END})

				break loop
			}

			continue
		}

		for _, ff := range FIRST_FOLLOW {
			if ff.First == tokenId {
				result := ff.Follow(stack, node, &Data{})

				if result != nil {
					fmt.Println(result)

					return errors.New(util.MakeRed("Syntax Error"))
				}

				found = true
			}
		}

		if !found {
			fmt.Println(makeErr(stack, "undefined").Error())

			return errors.New(util.MakeRed("Syntax Error"))
		}
	}

	return nil
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

func parseStack(stack Stack) (ast.AST, error) {
	ast := ast.NewAST()

	depth := 0
	error := analyze(&stack, &ast.Root, &depth)

	if depth != 0 && error == nil {
		return ast, err.BuildError(
			stack.FilePath,
			stack.LastLeftBrace.Position.Line,
			stack.LastLeftBrace.Position.Column-1,
			"unclosed delimiter",
		)

	}

	if error != nil {
		return ast, error
	}

	return ast, nil
}
