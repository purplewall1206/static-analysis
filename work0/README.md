./bin/work0 "namespace n { namespace m { class C {}; } }"

clang -Xclang -load -Xclang lib/libwork.so -Xclang -plugin -Xclang findname ../a.c 

clang -cc1 -load lib/libwork.so -plugin findname ../a.c 