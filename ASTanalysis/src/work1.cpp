// #include "clang/AST/ASTConsumer.h"
// #include "clang/AST/RecursiveASTVisitor.h"
// #include "clang/Frontend/CompilerInstance.h"
// #include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/FrontendPluginRegistry.h"

#include "Work1Action.h"
// int main(int argc, char **argv)
// {
//     if (argc > 1)
//     {
//         clang::tooling::runToolOnCode(std::make_unique<WorkAction>(), argv[1]);
//     }
// }

// static FrontendPluginRegistry::Add<WorkAction> X("work", "--");

static clang::FrontendPluginRegistry::Add<WorkAction> X("ASTparser", "collect all structs declarations and global variables declarations & definitions");
