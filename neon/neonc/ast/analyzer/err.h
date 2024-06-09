#pragma once

#include <neonc.h>
#include "../../types/position.h"
#include "../../util/clicolor.h"
#include "../../util/extract_from_file.h"

namespace neonc {
    void throw_error(const std::string absolute_file_path, const std::optional<Position> position, const char * message);
}
