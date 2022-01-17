#pragma once

#include "Work1Visitor.h"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/Basic/SourceManager.h"
#include "clang/AST/AST.h"
#include "llvm/Support/raw_ostream.h"
#include "entity.h"

class WorkConsumer : public clang::ASTConsumer
{
private:
    clang::SourceManager *manager;
    WorkVisitor visitor;
    std::unordered_map<std::string, clang::RecordDecl *> alldecls;
    // std::unordered_map<std::string, GlobalVaribles*> allGlobalVariables;
    std::vector<GlobalVaribles*> allGVs;
public:
    WorkConsumer(clang::ASTContext *context, clang::SourceManager *manager)
        : manager(manager), visitor(context, manager) {}

    void HandleTranslationUnit(clang::ASTContext &Context)
    {
        auto Decls = Context.getTranslationUnitDecl()->decls();
        // manager->getFilename()

        
        llvm::outs() << "In file : " << manager->getFilename(manager->getLocForStartOfFile(manager->getMainFileID())) << "\n";
        llvm::outs() << "get " << allGVs.size() << " global variables\n\n";
        for (auto g : allGVs) {
            llvm::outs() << g->genDB() + "\n";
        }
        // for (auto &Decl : Decls)
        // {
            // visitor.TraverseDecl(Decl);
        // }
        // visitor.print();

        // alldecls = visitor.getRecorddecls();
        // for (auto decls : alldecls)
        // {
        //     std::string Name = decls.first;
        //     clang::RecordDecl *decl = decls.second;
        //     // auto rtype = decl->getTypeForDecl();
        //     llvm::outs() << decl->getName() << "---" 
        //                  << ":" << manager->getFilename(decl->getBeginLoc())
        //                  << ":" << decl->getKindName() << "---\n";

        //     for (clang::RecordDecl::field_iterator i = decl->field_begin(), e = decl->field_end();
        //          i != e; i++)
        //     {
        //         clang::FieldDecl *field = *i;
        //         auto gettype = field->getType().getAsString();
        //         // 此处还需要想办法匹配一个“struct x *” 与 “struct x”的情况
        //         if (alldecls.count(gettype) != 0)
        //         {
        //             llvm::outs() << "GET field: " << field->getName()
        //                          << ":" << gettype
        //                          << ": declarated in the " << decl->getName()
        //                          << "\n";
        //         }
        //     }
        // }
    }

    bool HandleTopLevelDecl(clang::DeclGroupRef DG) override
    {
        // visitor.TraverseDecl(Decl);
        for (clang::DeclGroupRef::iterator i = DG.begin(), e = DG.end(); i != e; ++i)
        {
            // const clang::Decl *D = *i;
            const clang::VarDecl *VD =  llvm::dyn_cast<clang::VarDecl>(*i);
            if (VD) {
                std::string name = VD->getNameAsString();
                std::string type = VD->getType().getAsString();
                std::string file = manager->getFilename(VD->getBeginLoc()).data();
                int extrainfo = 0;
                if (VD->getType()->isPointerType()) {
                    extrainfo = 1;
                } else if (VD->getType()->isRecordType()) {
                    extrainfo = 2;
                } else if (VD->getType()->isArrayType()) {
                    extrainfo = 3;
                }
                allGVs.push_back(new GlobalVaribles(name, type, file, extrainfo));
            }
            // clang::QualType qtype = VD->getType();
            // qtype.dump();
            
            // if (VD) {
            //     VD->getType().dump();
            //     llvm::outs() << VD->getNameAsString() 
            //                  << ":" << VD->getType().getAsString() 
            //                  << ":ispointerType:" << VD->getType()->isPointerType()
            //                  << ":isarrytype" << VD->getType()->isArrayType()
            //                  << ":" << manager->getFilename(VD->getBeginLoc())
            //                  << "\n\n";
            // }
            
            // if (const clang::NamedDecl *ND = llvm::dyn_cast<clang::NamedDecl>(D))
            // {
            //     llvm::errs() << "top-level-decl: " << ND->getNameAsString()
            //                  << ":" << ND->getDeclKindName()
            //                  << ":" << manager->getFilename(ND->getBeginLoc())
            //                  << "\n";
            //     std::string vartype = ND->getDeclKindName();
            //     if (vartype == "Var") {
            //         const clang::VarDecl *VD = llvm::dyn_cast<clang::VarDecl>(D);
            //         llvm::outs() << "VD : " << VD->getType().getAsString() << "\n";
            //     }
                
            // }
        }

        
        return true;
    }
};