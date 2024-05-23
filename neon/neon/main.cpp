#include <neonc/compiler.h>

auto main(int argc, char * argv[]) -> int {
    neonc::build(argv[1]);

    return 0;
}
