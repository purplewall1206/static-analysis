# 标准模板，有AST静态分析按照这个写就行

./bin/work1 "namespace n { namespace m { class C {}; } }"

clang -c -Xclang -load -Xclang lib/libWORK1.so -Xclang -plugin -Xclang trigger ../test/a.c 

clang -cc1 -load lib/libWORK1.so -plugin trigger ../test/a.c

目标：
* struct声明
* 全局变量声明
* struct之间依赖关系