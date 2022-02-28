#pragma once

#include "clang/Frontend/FrontendAction.h"
#include "clang/Frontend/CompilerInstance.h"
#include "Work2Consumer.h"

#include <memory>

class WorkAction : public clang::PluginASTAction {
public:
    std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &CI, clang::StringRef) final {
        return std::unique_ptr<clang::ASTConsumer>(new WorkConsumer(&CI.getASTContext(), &CI.getSourceManager()));
    }

    bool ParseArgs(const clang::CompilerInstance &CI, const std::vector<std::string> &args) override{
        // llvm::outs() << "parseargs" << "\n";
        return true;
    }
};
