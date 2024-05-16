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
        llvm::CodeGenOpt::None
    );

    target_machine = std::unique_ptr<llvm::TargetMachine>(tm);

    pass = std::make_shared<Pass>();

    pass->fpm = std::make_shared<llvm::FunctionPassManager>();
    pass->lam = std::make_shared<llvm::LoopAnalysisManager>();
    pass->fam = std::make_shared<llvm::FunctionAnalysisManager>();
    pass->cgam = std::make_shared<llvm::CGSCCAnalysisManager>();
    pass->mam = std::make_shared<llvm::ModuleAnalysisManager>();
    pass->pic = std::make_shared<llvm::PassInstrumentationCallbacks>();
    pass->si = std::make_shared<llvm::StandardInstrumentations>(
        *context,
#ifdef NDEBUG
        true
#else
        false
#endif
    );

    pass->si->registerCallbacks(*pass->pic, pass->mam.get());

    //

    pass->fpm->addPass(llvm::InstCombinePass());
    pass->fpm->addPass(llvm::ReassociatePass());
    pass->fpm->addPass(llvm::GVNPass());
    pass->fpm->addPass(llvm::SimplifyCFGPass());
    pass->fpm->addPass(llvm::DSEPass());
    pass->fpm->addPass(llvm::DCEPass());
    pass->fpm->addPass(llvm::ADCEPass());
    pass->fpm->addPass(llvm::SCCPPass());
    pass->fpm->addPass(llvm::CorrelatedValuePropagationPass());

    pass->pb.registerModuleAnalyses(*pass->mam);
    pass->pb.registerFunctionAnalyses(*pass->fam);
    pass->pb.crossRegisterProxies(*pass->lam, *pass->fam, *pass->cgam, *pass->mam);
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

void Target::optimize(Module * module) const {
    for (auto t : module->functions) {
        pass->fpm->run(*std::get<0>(t.second), *pass->fam);
    }
}

void Target::module_to_object_file(Module module, const std::string out) const {
    std::error_code e;
    llvm::raw_fd_ostream dest(out + ".o", e, llvm::sys::fs::OF_None);

    if (e) {
        llvm::errs() << "Could not open file: " << e.message();
        return;
    }

    llvm::legacy::PassManager pass;
    auto ft = llvm::CodeGenFileType::CGFT_ObjectFile;

    if (target_machine->addPassesToEmitFile(pass, dest, nullptr, ft)) {
        llvm::errs() << "TargetMachine can't emit a file of this type";
        return;
    }

    pass.run(*module.module);
    dest.flush();
}
