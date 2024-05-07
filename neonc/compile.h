#pragma once

#include <iostream>
#include <frontend/util/cwd.h>
#include <frontend/util/read_file.h>
#include <frontend/lexer/lexer.h>
#include <frontend/parser/parser.h>
#include <frontend/util/measure.h>
#include <nir/target.h>
#include "builder.h"

void compile(int argc, char * argv[]);
