package compiler

import (
	"fmt"
	"neon/pkg/enum"
	"neon/pkg/llvm"
	"neon/pkg/parser"
)

func getNext(items []parser.Item, index int) parser.Item {
	if index >= len(items) {
		return parser.Item{
			Item: enum.INVALIDITEM,
		}
	} else {
		return items[index]
	}
}

func buildFunction(module *llvm.Module, name string) (function llvm.Function) {
	function = module.AddFunction(name, llvm.NewFunctionType(enum.VOID))
	return
}

func buildFunctionBody(function *llvm.Function, items []parser.Item) {
	entry := function.AppendBlock("entry")
	function.SetBuilderToBlockEnd(entry)

	for itemIndex := 0; itemIndex < len(items); itemIndex++ {
		item := items[itemIndex]

		switch item.Item {
		default:
			fmt.Printf("UNKNOWN FUNCTION BODY ITEM: %s\n", item.String(0))
		}
	}

	function.AddRet(enum.VOID)
}

func buildHead(module *llvm.Module, items []parser.Item) {
	for itemIndex := 0; itemIndex < len(items); itemIndex++ {
		item := items[itemIndex]

		switch item.Item {
		case enum.FUNCTION:
			function := buildFunction(module, item.Data)

			if getNext(items, itemIndex+1).Item == enum.BLOCK {
				itemIndex++

				buildFunctionBody(&function, item.Children)
			}

			function.Verify()
		default:
			fmt.Printf("UNKNOWN HEAD ITEM: %s\n", item.String(0))
		}
	}
}
