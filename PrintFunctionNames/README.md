
clang -cc1 -load lib/libPrintFunctionNames.so -plugin print-fns ../file.cpp 

clang -c -Xclang -load -Xclang lib/libPrintFunctionNames.so -Xclang -plugin -Xclang print-fns ../file.cpp

Linux:
$ clang -cc1 -load ../../Debug+Asserts/lib/libPrintFunctionNames.so -plugin print-fns some-input-file.c
$ clang -cc1 -load ../../Debug+Asserts/lib/libPrintFunctionNames.so -plugin print-fns -plugin-arg-print-fns help -plugin-arg-print-fns --example-argument some-input-file.c
$ clang -cc1 -load ../../Debug+Asserts/lib/libPrintFunctionNames.so -plugin print-fns -plugin-arg-print-fns -an-error some-input-file.c

Mac:
$ clang -cc1 -load ../../Debug+Asserts/lib/libPrintFunctionNames.dylib -plugin print-fns some-input-file.c
$ clang -cc1 -load ../../Debug+Asserts/lib/libPrintFunctionNames.dylib -plugin print-fns -plugin-arg-print-fns help -plugin-arg-print-fns --example-argument some-input-file.c
$ clang -cc1 -load ../../Debug+Asserts/lib/libPrintFunctionNames.dylib -plugin print-fns -plugin-arg-print-fns -an-error some-input-file.c