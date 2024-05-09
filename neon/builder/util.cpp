#include "util.h"

llvm::Type * string_to_type(const std::string _type, Module * module) {
    if (_type == "i8") return llvm::Type::getInt8Ty(*module->context);
    if (_type == "i16") return llvm::Type::getInt16Ty(*module->context);
    if (_type == "i32") return llvm::Type::getInt32Ty(*module->context);
    if (_type == "i64") return llvm::Type::getInt64Ty(*module->context);

    if (_type == "f32") return llvm::Type::getFloatTy(*module->context);
    if (_type == "f64") return llvm::Type::getDoubleTy(*module->context);

    throw std::invalid_argument("unknown string_to_type string");
}

llvm::Value * create_constant(llvm::Type * _type, const std::string value, Module * module) {
    if (_type == llvm::Type::getInt8Ty(*module->context)) return module->get_builder()->getInt8(std::stoi(value));
    if (_type == llvm::Type::getInt16Ty(*module->context)) return module->get_builder()->getInt16(std::stoi(value));
    if (_type == llvm::Type::getInt32Ty(*module->context)) return module->get_builder()->getInt32(std::stoi(value));
    if (_type == llvm::Type::getInt64Ty(*module->context)) return module->get_builder()->getInt64(std::stoi(value));
 
    if (_type == llvm::Type::getFloatTy(*module->context)) return llvm::ConstantFP::get(llvm::Type::getFloatTy(*module->context), std::stod(value));
    if (_type == llvm::Type::getDoubleTy(*module->context)) return llvm::ConstantFP::get(llvm::Type::getDoubleTy(*module->context), std::stod(value));

    throw std::invalid_argument("unknown create_constat type");
}
