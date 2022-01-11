MD bin
clang.exe -Iinclude -o bin\linkedList.lib src\linkedList.c -fuse-ld=llvm-lib
clang.exe -Iinclude -o bin\linkedList.exe src\linkedList.c -Lbin -l linkedList