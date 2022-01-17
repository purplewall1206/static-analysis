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
    std::vector<Structs*> allSTs;
    std::vector<Relates*> allREs;
public:
    WorkConsumer(clang::ASTContext *context, clang::SourceManager *manager)
        : manager(manager), visitor(context, manager) {}

    void HandleTranslationUnit(clang::ASTContext &Context)
    {
        auto Decls = Context.getTranslationUnitDecl()->decls();

        llvm::outs() << "In file : " << manager->getFilename(manager->getLocForStartOfFile(manager->getMainFileID())) << "\n";
        llvm::outs() << "    get " << allGVs.size() << " global variables\n";

        for (auto &Decl : Decls)
        {
            visitor.TraverseDecl(Decl);
        }

        alldecls = visitor.getRecorddecls();
        for (auto decls : alldecls)
        {
            std::string Name = decls.first;
            clang::RecordDecl *decl = decls.second;
            std::string file = manager->getFilename(decl->getBeginLoc()).data();
            Structs *curr = new Structs(Name, file);
            for (clang::RecordDecl::field_iterator i = decl->field_begin(), e = decl->field_end();
                 i != e; i++)
            {
                clang::FieldDecl *field = *i;
                std::string gettype = field->getType().getAsString();
              
                if (gettype.find("struct ") != std::string::npos)
                {
                    std::string nameb = field->getNameAsString();
                    int type = 1;
                    if (gettype.find(" *") != std::string::npos) {
                        type = 2;
                    }
                    allREs.push_back(new Relates(Name, nameb, type));
                }
            }

            allSTs.push_back(curr);
        }
        llvm::outs() << "    get " << allSTs.size() << " structures\n";
        llvm::outs() << "    get " << allREs.size() << " relations\n";

        insertDB();
    }

    bool HandleTopLevelDecl(clang::DeclGroupRef DG) override
    {
        for (clang::DeclGroupRef::iterator i = DG.begin(), e = DG.end(); i != e; ++i)
        {
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
        }

        
        return true;
    }


    void insertDB() {
        for (auto x : allGVs) {
            llvm::outs() << x->genDB() << "\n";
        }

        for (auto x : allSTs) {
            llvm::outs() << x->genStructsDB() << "\n";
        }

        for (auto x : allREs) {
            llvm::outs() << x->genRelatedDB() << "\n";
        }
    }
};