# 标准模板，有AST静态分析按照这个写就行

./bin/work1 "namespace n { namespace m { class C {}; } }"

clang -c -Xclang -load -Xclang lib/libASTPARSER.so -Xclang -plugin -Xclang ASTparser ../test/a.c 

clang -cc1 -load lib/libASTPARSER.so -plugin ASTparser ../test/a.c

目标：
* struct声明:`HandleTranslationUnit`
* 全局变量声明:`HandleTopLevelDecl`
* struct之间依赖关系:`HandleTopLevelDecl->RecordDecl->fieldDecls`

1. 收集struct里面的具体定义
2. 收集全局变量 `HandleTopLevelDecl`