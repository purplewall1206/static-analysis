<!-- 

# 一些统计结果

* 文件数 15235 `make all 统计intel架构所有代码和程序`
* structs: 80294个，匿名2037个 `SELECT count(*) FROM structs WHERE name like ''`
* driver structs: 48606, `SELECT * FROM structs WHERE file like 'drivers%' or file like './drivers%'`
* fs structs : 3038  `SELECT * FROM structs WHERE file like 'fs%' or './fs%`
* 全局变量 10640221 `select DISTINCT * from globalvars ` -->

# function统计

AST分析

function 类型，param，文件位置

关于文件位置：如果是当前文件，那么显然是定义，如果在其他文件，那么应该就是声明，是否可以被记录为在这个文件使用？

`clang -Xclang -ast-dump -fsyntax-only -fno-color-diagnostics -Wno-visibility a.c`

测试命令
```
clang -Wp,-MD,arch/x86/lib/.usercopy_64.o.d -nostdinc -isystem /usr/lib/llvm-13/lib/clang/13.0.0/include -I../arch/x86/include -I./arch/x86/include/generated  -I../include -I./include -I../arch/x86/include/uapi -I./arch/x86/include/generated/uapi -I../include/uapi -I./include/generated/uapi -include ../include/linux/kconfig.h -include ../include/linux/compiler_types.h  -I../arch/x86/lib -Iarch/x86/lib -D__KERNEL__ -Qunused-arguments -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -fshort-wchar -Werror-implicit-function-declaration -Werror=return-type -Wno-format-security -std=gnu89 -no-integrated-as -Werror=unknown-warning-option -fno-PIE -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -mno-avx -fcf-protection=none -m64 -mno-80387 -mstack-alignment=8 -mtune=generic -mno-red-zone -mcmodel=kernel -funit-at-a-time -DCONFIG_X86_X32_ABI -DCONFIG_AS_CFI=1 -DCONFIG_AS_CFI_SIGNAL_FRAME=1 -DCONFIG_AS_CFI_SECTIONS=1 -DCONFIG_AS_FXSAVEQ=1 -DCONFIG_AS_SSSE3=1 -DCONFIG_AS_CRC32=1 -DCONFIG_AS_AVX=1 -DCONFIG_AS_AVX2=1 -DCONFIG_AS_AVX512=1 -DCONFIG_AS_SHA1_NI=1 -DCONFIG_AS_SHA256_NI=1 -pipe -Wno-sign-compare -fno-asynchronous-unwind-tables -mretpoline-external-thunk -fno-delete-null-pointer-checks -Wno-frame-address -Wno-int-in-bool-context -Wno-address-of-packed-member -O2 -Wframe-larger-than=2048 -fstack-protector-strong -Wno-format-invalid-specifier -Wno-gnu -Wno-tautological-compare -mno-global-merge -Wno-unused-but-set-variable -Wno-unused-const-variable -pg -mfentry -DCC_USING_FENTRY -Wdeclaration-after-statement -Wno-pointer-sign -Wno-array-bounds -fno-strict-overflow -fno-merge-all-constants -fno-stack-check -Werror=implicit-int -Werror=strict-prototypes -Werror=date-time -Werror=incompatible-pointer-types -fmacro-prefix-map=../= -Wno-initializer-overrides -Wno-unused-value -Wno-format -Wno-sign-compare -Wno-format-zero-length -Wno-uninitialized -Wno-pointer-to-enum-cast     -DKBUILD_BASENAME='"usercopy_64"' -DKBUILD_MODNAME='"usercopy_64"'  -g -emit-llvm -c -o arch/x86/lib/.tmp_usercopy_64.o.bc ../arch/x86/lib/usercopy_64.c -Xclang -load -Xclang /home/wangzc/Documents/static-analysis/ASTFuncAnalysis/build/lib/libASTFuncPARSER.so -Xclang -plugin -Xclang ASTFuncparser
```