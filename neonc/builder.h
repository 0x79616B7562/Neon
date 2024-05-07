#pragma once

#include <frontend/ast/ast.h>
#include <nir/module.h>
#include <nir/objects.h>
#include <string>
#include <optional>

nir::Module build_nir_from_ast(const std::string file_path, Ast ast);
