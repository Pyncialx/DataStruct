MD bin
clang.exe -Iinclude -o bin\doublyList.lib src\doublyLinkedList.c -fuse-ld=llvm-lib
clang.exe -Iinclude -o bin\doublyList.exe src\doublyLinkedList.c -Lbin -l doublyList