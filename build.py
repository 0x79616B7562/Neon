import sys
import platform
import os

def build_linux():
    os.system("mkdir -p build/debug")

    if not os.path.isdir("build/debug/llvm"):
        os.system("mkdir -p build/debug/llvm")
        os.system("cd build/debug/llvm && cmake -DCMAKE_BUILD_TYPE=Debug ../../../llvm/llvm && make -j 8")

    os.system("mkdir -p build/debug/neon")
    os.system("cd build/debug/neon && cmake -DCMAKE_BUILD_TYPE=Debug ../../.. && make -j 8")

if __name__ == "__main__":
    if platform.system() == "Linux":
        build_linux()
    else:
        print("Unsupported build os")
