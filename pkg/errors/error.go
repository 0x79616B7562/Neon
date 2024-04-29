package errors

import "errors"

type Error interface {
	Error()
}

func New(msg string) error {
	return errors.New(msg)
}
