#include "util.h"

std::string double_backslash_to_single(std::string input) {
    std::string output = "";
    size_t start_pos = 0;
    size_t found_pos = input.find("\\", start_pos);

    while (found_pos != std::string::npos) {
        output += input.substr(start_pos, found_pos - start_pos);
        
        if (found_pos + 1 < input.size()) {
            char escaped_char = input[found_pos + 1];

            switch (escaped_char) {
                case 'n':
                    output += "\n"; break;
                case 't':
                    output += "\t"; break;
                case '\"':
                    output += "\""; break;
                default:
                    output += "\\";
                    output += escaped_char;
            }

            start_pos = found_pos + 2;
        } else {
            output += "\\";
            start_pos = found_pos + 1;
        }

        found_pos = input.find("\\", start_pos);
    }

    return output + input.substr(start_pos);
}

llvm::Type * string_to_type(const std::string _type, Module * module) {
    // simple
    if (_type == "bool") return llvm::Type::getInt1Ty(*module->context);

    if (_type == "i8") return llvm::Type::getInt8Ty(*module->context);
    if (_type == "i16") return llvm::Type::getInt16Ty(*module->context);
    if (_type == "i32") return llvm::Type::getInt32Ty(*module->context);
    if (_type == "i64") return llvm::Type::getInt64Ty(*module->context);

    if (_type == "f32") return llvm::Type::getFloatTy(*module->context);
    if (_type == "f64") return llvm::Type::getDoubleTy(*module->context);

    // ptr
    if (_type == "str") return llvm::Type::getInt8PtrTy(*module->context);

    throw std::invalid_argument("unknown string_to_type string");
}

llvm::Value * create_constant(llvm::Type * _type, std::string value, Module * module) {
    if (_type == llvm::Type::getInt8PtrTy(*module->context)) return module->get_builder()->CreateGlobalStringPtr(llvm::StringRef(double_backslash_to_single(value)));

    auto _value = value == "" ? "0" : value;

    if (_type == llvm::Type::getInt1Ty(*module->context)) return module->get_builder()->getInt1(std::stoi(_value));

    if (_type == llvm::Type::getInt8Ty(*module->context)) return module->get_builder()->getInt8(std::stoll(_value));
    if (_type == llvm::Type::getInt16Ty(*module->context)) return module->get_builder()->getInt16(std::stoll(_value));
    if (_type == llvm::Type::getInt32Ty(*module->context)) return module->get_builder()->getInt32(std::stoll(_value));
    if (_type == llvm::Type::getInt64Ty(*module->context)) return module->get_builder()->getInt64(std::stoll(_value));
 
    if (_type == llvm::Type::getFloatTy(*module->context)) return llvm::ConstantFP::get(llvm::Type::getFloatTy(*module->context), std::stod(_value));
    if (_type == llvm::Type::getDoubleTy(*module->context)) return llvm::ConstantFP::get(llvm::Type::getDoubleTy(*module->context), std::stod(value));

    throw std::invalid_argument("unknown create_constat type");
}
