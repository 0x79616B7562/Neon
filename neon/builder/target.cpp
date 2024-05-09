#include "target.h"

Target::Target() {
    context = std::make_shared<llvm::LLVMContext>();
    
    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();

    target_triple = llvm::sys::getDefaultTargetTriple();

    std::string error;
    target = llvm::TargetRegistry::lookupTarget(target_triple, error);

    if (!target) {
        llvm::errs() << error;

        return;
    }

    auto cpu = "generic";
    auto features = "";

    llvm::TargetOptions opt;
    auto tm = target->createTargetMachine(
        target_triple,
        cpu,
        features,
        opt,
        llvm::Reloc::PIC_,
        llvm::CodeModel::Medium,
        llvm::CodeGenOptLevel::None
    );

    target_machine = std::unique_ptr<llvm::TargetMachine>(tm);
};

Module Target::create_module(const std::string module_name) const {
    auto llvm_module = std::make_shared<llvm::Module>(module_name, *context);

    llvm_module->setDataLayout(target_machine->createDataLayout());
    llvm_module->setTargetTriple(target_triple);

    return Module(context, llvm_module);
}

void Target::dump_target_triple() const {
    std::cout << "Target Triple: " << target_triple << "\n";
}
