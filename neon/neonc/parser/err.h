#pragma once

#include "pack.h"
#include "../util/clicolor.h"
#include "../util/extract_from_file.h"

namespace neonc {
    void throw_parse_error(const Pack * pack, const char * message);
}
