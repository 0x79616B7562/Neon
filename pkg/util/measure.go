package util

import (
	"fmt"
	"time"
)

type Measure struct {
	time time.Time
}

func NewMeasure() Measure {
	return Measure{time.Now()}
}

func (m *Measure) Finish(msg string) {
	now := time.Now()
	fmt.Println(msg, now.Sub(m.time))
}
