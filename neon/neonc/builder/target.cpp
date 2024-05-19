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

    auto cpu = llvm::sys::getHostCPUName();
    constexpr auto features = "";

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

    target_cpu = target_machine->getTargetCPU();

    switch (target_machine->getTargetTriple().getArch()) {
    case llvm::Triple::arm:
        target_cpu = "arm";
        break;
    case llvm::Triple::armeb:
        target_cpu = "armeb";
        break;
    case llvm::Triple::aarch64:
        target_cpu = "aarch64";
        break;
    case llvm::Triple::aarch64_be:
        target_cpu = "aarch64-be";
        break;
    case llvm::Triple::aarch64_32:
        target_cpu = "aarch64-32";
        break;
    case llvm::Triple::arc:
        target_cpu = "arc";
        break;
    case llvm::Triple::avr:
        target_cpu = "avr";
        break;
    case llvm::Triple::bpfel:
        target_cpu = "bpfel";
        break;
    case llvm::Triple::bpfeb:
        target_cpu = "bpfeb";
        break;
    case llvm::Triple::csky:
        target_cpu = "csky";
        break;
    case llvm::Triple::dxil:
        target_cpu = "dxil";
        break;
    case llvm::Triple::hexagon:
        target_cpu = "hexagon";
        break;
    case llvm::Triple::loongarch32:
        target_cpu = "loongarch32";
        break;
    case llvm::Triple::loongarch64:
        target_cpu = "loongarch64";
        break;
    case llvm::Triple::m68k:
        target_cpu = "m68k";
        break;
    case llvm::Triple::mips:
        target_cpu = "mips";
        break;
    case llvm::Triple::mipsel:
        target_cpu = "mipsel";
        break;
    case llvm::Triple::mips64:
        target_cpu = "mips64";
        break;
    case llvm::Triple::mips64el:
        target_cpu = "mips64el";
        break;
    case llvm::Triple::msp430:
        target_cpu = "msp430";
        break;
    case llvm::Triple::ppc:
        target_cpu = "ppc";
        break;
    case llvm::Triple::ppcle:
        target_cpu = "ppcle";
        break;
    case llvm::Triple::ppc64:
        target_cpu = "ppc64";
        break;
    case llvm::Triple::ppc64le:
        target_cpu = "ppc64le";
        break;
    case llvm::Triple::r600:
        target_cpu = "r600";
        break;
    case llvm::Triple::amdgcn:
        target_cpu = "amdgcn";
        break;
    case llvm::Triple::riscv32:
        target_cpu = "riscv32";
        break;
    case llvm::Triple::riscv64:
        target_cpu = "riscv64";
        break;
    case llvm::Triple::sparc:
        target_cpu = "sparc";
        break;
    case llvm::Triple::sparcv9:
        target_cpu = "sparcv9";
        break;
    case llvm::Triple::sparcel:
        target_cpu = "sparcel";
        break;
    case llvm::Triple::systemz:
        target_cpu = "systemz";
        break;
    case llvm::Triple::tce:
        target_cpu = "tce";
        break;
    case llvm::Triple::tcele:
        target_cpu = "tcele";
        break;
    case llvm::Triple::thumb:
        target_cpu = "thumb";
        break;
    case llvm::Triple::thumbeb:
        target_cpu = "thumbeb";
        break;
    case llvm::Triple::x86:
        target_cpu = "x86";
        break;
    case llvm::Triple::x86_64:
        target_cpu = "x86-64";
        break;
    case llvm::Triple::xcore:
        target_cpu = "xcore";
        break;
    case llvm::Triple::xtensa:
        target_cpu = "xtensa";
        break;
    case llvm::Triple::nvptx:
        target_cpu = "nvptx";
        break;
    case llvm::Triple::nvptx64:
        target_cpu = "nvptx64";
        break;
    case llvm::Triple::le32:
        target_cpu = "le32";
        break;
    case llvm::Triple::le64:
        target_cpu = "le64";
        break;
    case llvm::Triple::amdil:
        target_cpu = "amdil";
        break;
    case llvm::Triple::amdil64:
        target_cpu = "amdil64";
        break;
    case llvm::Triple::hsail:
        target_cpu = "hsail";
        break;
    case llvm::Triple::hsail64:
        target_cpu = "hsail64";
        break;
    case llvm::Triple::spir:
        target_cpu = "spir";
        break;
    case llvm::Triple::spir64:
        target_cpu = "spir64";
        break;
    case llvm::Triple::spirv32:
        target_cpu = "spirv32";
        break;
    case llvm::Triple::spirv64:
        target_cpu = "spirv64";
        break;
    case llvm::Triple::kalimba:
        target_cpu = "kalimba";
        break;
    case llvm::Triple::shave:
        target_cpu = "shave";
        break;
    case llvm::Triple::lanai:
        target_cpu = "lanai";
        break;
    case llvm::Triple::wasm32:
        target_cpu = "wasm32";
        break;
    case llvm::Triple::wasm64:
        target_cpu = "wasm64";
        break;
    case llvm::Triple::renderscript32:
        target_cpu = "renderscript32";
        break;
    case llvm::Triple::renderscript64:
        target_cpu = "renderscript64";
        break;
    case llvm::Triple::ve:
        target_cpu = "ve";
        break;
    case llvm::Triple::UnknownArch:
        std::cout << "ICE: unknown arch" << std::endl;
        exit(0);
        break;
    }

    auto * sti = target_machine->getMCSubtargetInfo();
    target_features = sti->getFeatureString();

    //

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
    llvm_module->setUwtable(llvm::UWTableKind::Default);
    llvm_module->setFramePointer(llvm::FramePointerKind::All);

    return Module(context, llvm_module, target_features, target_cpu);
}

void Target::dump_target_triple() const {
    std::cout << "Target Triple: " << target_triple << "\n";
}

void Target::optimize(Module * module) const {
    for (auto t : module->functions) {
        pass->fpm->run(*std::get<0>(t.second), *pass->fam);
    }
}

std::string Target::get_target_features() const {
    return target_features;
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
