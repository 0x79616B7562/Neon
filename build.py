import sys
import platform
import os
import multiprocessing

def build_linux():
    os.system("mkdir -p build/debug")

    if not os.path.isdir("build/debug/llvm"):
        print("Building llvm")
        os.system("mkdir -p build/debug/llvm")
        os.system(
            "cd build/debug/llvm "
            + "&& cmake "
            + "-DCMAKE_BUILD_TYPE=Release "
            + "-DLLVM_TARGETS_TO_BUILD=X86 "
            + "-DCMAKE_INSTALL_PREFIX=build/debug/llvm/installed "
            + "-DLLVM_ENABLE_TERMINFO=OFF "
            + "-DLLVM_ENABLE_RTTI=ON "
            + "../../../llvm/llvm "
            + "&& make -j " + str(multiprocessing.cpu_count()) + " "
            + "&& make install"
        )

    print("Building neon")
    os.system("mkdir -p build/debug/neon")
    os.system("cd build/debug/neon && cmake -DCMAKE_BUILD_TYPE=Debug ../../.. && make -j " + str(multiprocessing.cpu_count()))

if __name__ == "__main__":
    if platform.system() == "Linux":
        build_linux()
    else:
        print("Unsupported build os")
