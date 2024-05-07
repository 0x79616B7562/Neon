#include "target.h" 
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/PassManager.h>
#include <llvm/Target/TargetMachine.h>
#include <memory>

namespace nir {
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
    }

    void Target::nir_module_to_object_file(Module & module, const std::string output_file, bool dump_llvm_ir) const {
        auto llvm_module = std::make_shared<llvm::Module>(module.get_module_name(), *context);

        llvm_module->setDataLayout(target_machine->createDataLayout());
        llvm_module->setTargetTriple(target_triple);
   
        //

        auto build_data = BuildData {
            .context = context,
            .module = llvm_module,
        };

        for (auto & func : module.get_functions())
            func.build_function(&build_data);

        //

        if (dump_llvm_ir) {
            llvm_module->print(llvm::errs(), nullptr);
        }

        std::error_code ec;
        llvm::raw_fd_ostream dest(output_file + ".o", ec, llvm::sys::fs::OF_None);

        if (ec) {
            llvm::errs() << "Could not open file: " << ec.message();
            return;
        }

        llvm::legacy::PassManager pass;
        auto file_type = llvm::CodeGenFileType::ObjectFile;

        if (target_machine->addPassesToEmitFile(pass, dest, nullptr, file_type)) {
            llvm::errs() << "TargetMachine can't emit a file of this type";
            return;
        }

        pass.run(*llvm_module);
        dest.flush();
    }
}
