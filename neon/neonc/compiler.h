#pragma once

#include "util/measure.h"
#include "util/cwd.h"
#include "util/read_file.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "builder/target.h"
#include <neonc.h>

void build(const std::string entry);
