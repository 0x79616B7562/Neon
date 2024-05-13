#pragma once

// precompiled header file

#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/ADT/ArrayRef.h>

#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/PassManager.h>

#include <llvm/MC/TargetRegistry.h>

#include <llvm/Support/FileSystem.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>

#include <llvm/TargetParser/Host.h>

#include <llvm/Passes/PassBuilder.h>
#include <llvm/Passes/StandardInstrumentations.h>

#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Scalar/Reassociate.h>
#include <llvm/Transforms/Scalar/SimplifyCFG.h>
#include <llvm/Transforms/Scalar/DeadStoreElimination.h>
#include <llvm/Transforms/Scalar/DCE.h>
#include <llvm/Transforms/Scalar/ADCE.h>
#include <llvm/Transforms/Scalar/SCCP.h>

#include <numeric>
#include <chrono>
#include <stdio.h>
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <optional>
#include <tuple>
#include <fstream>
#include <ostream>
#include <sstream>
#include <cstddef>
#include <regex>
#include <cstdint>
#include <map>
#include <algorithm>

#define NPRINT std::cout << "NPRINT" << std::endl;
