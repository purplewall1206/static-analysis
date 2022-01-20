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

# 一些统计结果

* 文件数 15235 `make all 统计intel架构所有代码和程序`
* structs: 80294个，匿名2037个 `SELECT count(*) FROM structs WHERE name like ''`
* driver structs: 48606, `SELECT * FROM structs WHERE file like 'drivers%' or file like './drivers%'`
* fs structs : 3038  `SELECT * FROM structs WHERE file like 'fs%' or './fs%`
* 全局变量 10640221 `select DISTINCT * from globalvars `