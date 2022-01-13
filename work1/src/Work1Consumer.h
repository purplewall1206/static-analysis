#pragma once

#include "Work1Visitor.h"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/Basic/SourceManager.h"

class WorkConsumer : public clang::ASTConsumer {
private:
    clang::SourceManager *manager;
    WorkVisitor visitor;

public:
    WorkConsumer(clang::ASTContext *context, clang::SourceManager *manager) 
        : manager(manager), visitor(context, manager) {}

    void HandleTranslationUnit(clang::ASTContext &Context) {
        auto Decls = Context.getTranslationUnitDecl()->decls();
        for (auto &Decl : Decls) {
            // const auto& FileID = manager->getFileID(Decl->getLocation());
            // if (FileID != manager->getMainFileID())
            //     continue;
            visitor.TraverseDecl(Decl);
        }
    }
};