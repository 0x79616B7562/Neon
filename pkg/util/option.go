package util

type Option[T any] struct {
	Some   T
	IsSome bool
}

func Some[T any](option T) Option[T] {
	return Option[T]{
		Some:   option,
		IsSome: true,
	}
}

func None[T any]() Option[T] {
	return Option[T]{
		IsSome: false,
	}
}

func (o *Option[T]) Unwrap() T {
	if o.IsSome {
		return o.Some
	}

	panic("option has no value")
}
