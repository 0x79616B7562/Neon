#pragma once

#include <neonc.h>

struct Pass {
    llvm::PassBuilder pb;

    std::shared_ptr<llvm::FunctionPassManager> fpm;
    std::shared_ptr<llvm::LoopAnalysisManager> lam;
    std::shared_ptr<llvm::FunctionAnalysisManager> fam;
    std::shared_ptr<llvm::CGSCCAnalysisManager> cgam;
    std::shared_ptr<llvm::ModuleAnalysisManager> mam;
    std::shared_ptr<llvm::PassInstrumentationCallbacks> pic;
    std::shared_ptr<llvm::StandardInstrumentations> si;
};
