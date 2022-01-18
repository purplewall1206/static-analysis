cmds = []

with open('compile-output', 'r') as f:
    cmds = f.readlines()

with open('ast-parser.sh', 'w') as f:
    for cmd in cmds:
        if cmd.find('.S') != -1:
            continue
        posstart = cmd.find('-o ')
        posend = cmd.find('.o ')
        prefix = cmd[:posstart]
        objectfile = cmd[posstart+2:posend]
        res = prefix
        res = res + ' -emit-llvm -S -o ' + objectfile + '.ll ' + objectfile + '.c '
        res = res + '-Xclang -load -Xclang ../static-analysis/ASTanalysis/build/lib/libASTPARSER.so -Xclang -plugin -Xclang ASTparser;\n'
        f.write(res)



# ../static-analysis/ASTanalysis/build/lib/libASTPARSER.so 

# 'clang -Wp,-MMD,scripts/mod/.empty.o.d -nostdinc -isystem /home/wangzc/Documents/llvm-project/install/lib/clang/13.0.0/include -I./arch/x86/include -I./arch/x86/include/generated  -I./include -I./arch/x86/include/uapi -I./arch/x86/include/generated/uapi -I./include/uapi -I./include/generated/uapi -include ./include/linux/kconfig.h -include ./include/linux/compiler_types.h -D__KERNEL__ -Qunused-arguments -fmacro-prefix-map=./= -Wall -Wundef -Werror=strict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -fshort-wchar -fno-PIE -Werror=implicit-function-declaration -Werror=implicit-int -Werror=return-type -Wno-format-security -std=gnu89 -no-integrated-as -Werror=unknown-warning-option -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -mno-avx -fcf-protection=none -m64 -mno-80387 -mstack-alignment=8 -mtune=generic -mno-red-zone -mcmodel=kernel -DCONFIG_X86_X32_ABI -Wno-sign-compare -fno-asynchronous-unwind-tables -fno-delete-null-pointer-checks -Wno-frame-address -Wno-address-of-packed-member -O2 -Wframe-larger-than=1024 -fstack-protector-strong -Wno-format-invalid-specifier -Wno-gnu -mno-global-merge -Wno-unused-const-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -gdwarf-4 -pg -mfentry -DCC_USING_FENTRY -Wdeclaration-after-statement -Wvla -Wno-pointer-sign -Wno-array-bounds -fno-strict-overflow -fno-stack-check -Werror=date-time -Werror=incompatible-pointer-types -Wno-initializer-overrides -Wno-format -Wno-sign-compare -Wno-format-zero-length -Wno-pointer-to-enum-cast -Wno-tautological-constant-out-of-range-compare    -DKBUILD_MODFILE=\'"scripts/mod/empty"\' -DKBUILD_BASENAME=\'"empty"\' -DKBUILD_MODNAME=\'"empty"\' -c -o scripts/mod/empty.o scripts/mod/empty.c\n'