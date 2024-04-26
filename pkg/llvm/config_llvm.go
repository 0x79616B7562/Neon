package llvm

// #cgo CPPFLAGS: -I/usr/include -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS
// #cgo CXXFLAGS: -std=c++14
// #cgo LDFLAGS: -L/usr/lib64  -lLLVM
import "C"
