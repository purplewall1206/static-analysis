./bin/work1 "namespace n { namespace m { class C {}; } }"

clang -c -Xclang -load -Xclang lib/libWORK1.so -Xclang -plugin -Xclang trigger ../test/a.c 

clang -cc1 -load lib/libWORK1.so -plugin trigger ../test/a.c