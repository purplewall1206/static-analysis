cmds = []

with open('clangs-llvm-10.txt', 'r') as f:
    cmds = f.readlines()

count = 0

opts = []

with open('ir-perfile-usage.sh', 'w') as f:
    for cmd in cmds:
        if cmd == '\n':
            continue        
        if cmd.find('.S') != -1:
            continue
        posstart = cmd.find('-o ')
        posend = cmd.find('.o ')
        prefix = cmd[:posstart]
        objectfile = cmd[posstart+2:posend]
        res = 'echo ' + str(count) + ';\n'
        count = count + 1
        res = res + prefix
        res = res + ' -emit-llvm  -o ' + objectfile + '.bc ' + cmd[cmd.rfind(' '):-1] + ';\n'
        res = res +  '  opt -load ~/static-analysis/IRUsageAnalysis/build/libIRUsage.so -irusage ' + objectfile + '.bc -disable-output;\n'
        # res = res + '  -o  ' + objectfile + '.o  ' + objectfile + '.c '
        # res = res + '-Xclang -load -Xclang ../static-analysis/ASTanalysis/build/lib/libASTPARSER.so -Xclang -plugin -Xclang ASTparser;\n'
        # res = res + cmd[:-1] + ' -Xclang -load -Xclang /home/wangzc/Documents/static-analysis/ASTFuncAnalysis/build/lib/libASTFuncPARSER.so -Xclang -plugin -Xclang ASTFuncparser;\n'
        f.write(res)

