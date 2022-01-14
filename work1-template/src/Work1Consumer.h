#pragma once

#include "Work1Visitor.h"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/Basic/SourceManager.h"
#include "clang/AST/AST.h"
#include "llvm/Support/raw_ostream.h"

class WorkConsumer : public clang::ASTConsumer
{
private:
    clang::SourceManager *manager;
    WorkVisitor visitor;

public:
    WorkConsumer(clang::ASTContext *context, clang::SourceManager *manager)
        : manager(manager), visitor(context, manager) {}

    void HandleTranslationUnit(clang::ASTContext &Context)
    {
        auto Decls = Context.getTranslationUnitDecl()->decls();
        for (auto &Decl : Decls)
        {
            // const auto& FileID = manager->getFileID(Decl->getLocation());
            // if (FileID != manager->getMainFileID())
            //     continue;
            visitor.TraverseDecl(Decl);
        }
        visitor.print();
    }

    bool HandleTopLevelDecl(clang::DeclGroupRef DG) override
    {
        for (clang::DeclGroupRef::iterator i = DG.begin(), e = DG.end(); i != e; ++i)
        {
            const clang::Decl *D = *i;
            if (const clang::NamedDecl *ND = llvm::dyn_cast<clang::NamedDecl>(D)) {

                llvm::errs() << "top-level-decl: " << ND->getNameAsString() 
                             << ":" << ND->getDeclKindName() 
                             << "\n";
            }
                
        }

        return true;
    }
};