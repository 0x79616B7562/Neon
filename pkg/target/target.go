package target

import "neon/pkg/llvm"

type Target struct {
	Target llvm.Target
}

func NewTarget() Target {
	return Target{
		Target: llvm.NewTarget(),
	}
}

func (t *Target) Dispose() {
	t.Target.Dispose()
}
