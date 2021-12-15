# out-of-source clang AST及前端编译目标

如果直接用 `clang++ x.cpp -I$LLVM_DIR/include -lclang` 这种编译方法会出现非常复杂的链接问题

因此为了避免复杂的编译依赖，还是直接使用cmake

template 给出的例子是coderefactor，把file.cpp文件中的foo函数全部变成bar函数（来自clang-tutor）

```
mkdir build && cd build

cmake ..

make

clang -cc1 -load <build_dir>/lib/libCodeRefactor.dylib -plugin CodeRefactor -plugin-arg-CodeRefactor -class-name -plugin-arg-CodeRefactor Base  -plugin-arg-CodeRefactor -old-name -plugin-arg-CodeRefactor foo  -plugin-arg-CodeRefactor -new-name -plugin-arg-CodeRefactor bar file.cpp
# 或者
./bin/ct-code-refactor --class-name=Base --new-name=bar --old-name=foo ../file.cpp  --
```

主要借鉴了

[llvm-cmake-embedding-llvm-in-your-project]('https://llvm.org/docs/CMake.html#embedding-llvm-in-your-project')   
[banach-space clang-tutor](https://github.com/banach-space/clang-tutor)  