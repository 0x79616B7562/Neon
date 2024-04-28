package parser

import (
	"fmt"
	"neon/pkg/enum"
	"neon/pkg/lexer"
	"strings"
)

type Item struct {
	Item     enum.Item
	Position lexer.Position
	Data     string
	Children []Item
}

func NewItem(item enum.Item, position lexer.Position, data string, children []Item) Item {
	return Item{
		Item:     item,
		Position: position,
		Data:     data,
		Children: children,
	}
}

func (i *Item) String(indent int) string {
	str := fmt.Sprintf("%s %q %d:%d", enum.ItemToString(i.Item), i.Data, i.Position.Line, i.Position.Column)

	for _, child := range i.Children {
		indentstr := strings.Repeat(" ", indent*4)
		str += fmt.Sprintf("\n"+indentstr+"%s", child.String(indent+1))
	}

	return str
}
