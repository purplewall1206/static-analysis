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
    std::unordered_map<std::string, clang::RecordDecl *> alldecls;

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

        alldecls = visitor.getAlldecls();
        for (auto decls : alldecls)
        {
            std::string Name = decls.first;
            clang::RecordDecl *decl = decls.second;
            auto rtype = decl->getTypeForDecl();
            llvm::outs() << decl->getName() << "---" << decl->getKindName() << "---\n";

            for (clang::RecordDecl::field_iterator i = decl->field_begin(), e = decl->field_end();
                 i != e; i++)
            {
                clang::FieldDecl *field = *i;
                auto gettype = field->getType().getAsString();
                // 此处还需要想办法匹配一个“struct x *” 与 “struct x”的情况
                if (alldecls.count(gettype) != 0)
                {
                    llvm::outs() << "GET field: " << field->getName()
                                 << ":" << gettype
                                 << ": declarated in the " << decl->getName()
                                 << "\n";
                }
            }
        }
    }

    bool HandleTopLevelDecl(clang::DeclGroupRef DG) override
    {
        // visitor.TraverseDecl(Decl);
        for (clang::DeclGroupRef::iterator i = DG.begin(), e = DG.end(); i != e; ++i)
        {
            const clang::Decl *D = *i;
            // clang::RecordDecl *RD;
            if (const clang::NamedDecl *ND = llvm::dyn_cast<clang::NamedDecl>(D))
            {
                llvm::errs() << "top-level-decl: " << ND->getNameAsString()
                             << ":" << ND->getDeclKindName()
                             << ":" << manager->getFilename(ND->getBeginLoc())
                             << "\n";
                // cast to RecordDecl
                // if (ND->getDeclKindName() == "Record") {
                //     if (RD = llvm::dyn_cast<clang::RecordDecl>(D->getDeclContext())) {
                //         llvm::outs() << "   recordDecl- " << RD->getName() << ":";
                //         // for (clang::FieldDeclarator start = RD->field_begin(), end = RD->field_end();
                //         //     start != end; ++start) {
                //         //         clang::FieldDecl *FD = *start;
                //         //         llvm::outs() << FD->getType()->getTypeClassName() << "\n";
                //         //     }
                //     }
                // }
                // llvm::outs() << "\n\n";
            }
        }

        return true;
    }
};