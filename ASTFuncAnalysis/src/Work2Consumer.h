#pragma once

#include "Work2Visitor.h"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/Basic/SourceManager.h"
#include "clang/AST/AST.h"
#include "llvm/Support/raw_ostream.h"
#include "entity.h"
#include <sqlite3.h>

class WorkConsumer : public clang::ASTConsumer
{
private:
    clang::SourceManager *manager;
    WorkVisitor visitor;
    // std::unordered_map<std::string, clang::RecordDecl *> alldecls;
    std::vector<std::pair<std::string, clang::RecordDecl *>> alldecls;
    // std::unordered_map<std::string, GlobalVaribles*> allGlobalVariables;
    std::vector<GlobalVaribles *> allGVs;
    std::vector<Structs *> allSTs;
    std::vector<Relates *> allREs;

    std::vector<FunctionUse*> allFuncUses;
    std::vector<FunctionDeclaration*> allFuncDeclarations;
    std::vector<Param*> allFuncParams;

public:
    WorkConsumer(clang::ASTContext *context, clang::SourceManager *manager)
        : manager(manager), visitor(context, manager) {}

    void HandleTranslationUnit(clang::ASTContext &Context)
    {
        // auto Decls = Context.getTranslationUnitDecl()->decls();

        std::cout << "\e[1;32mfile : " << manager->getFilename(manager->getLocForStartOfFile(manager->getMainFileID())).data() << "\e[0m\n";
        std::cout << "    get " << allFuncDeclarations.size() << " function decls\n";
        // std::cout << "    get " << allFuncUses.size() << " function uses\n";
        std::cout << "    get " << allFuncParams.size() << " function paramters\n";
        // std::cout << "    get " << allGVs.size() << " global variables\n";

        // for (auto &Decl : Decls)
        // {
        //     visitor.TraverseDecl(Decl);
        // }

        // alldecls = visitor.getRecorddecls();
        // for (auto decls : alldecls)
        // {
        //     std::string Name = decls.first;
        //     clang::RecordDecl *decl = decls.second;
        //     llvm::StringRef fileRef = manager->getFilename(decl->getBeginLoc());
        //     std::string file = fileRef.empty() ? "" : fileRef.data();
        //     Structs *curr = new Structs(Name, file);
        //     for (clang::RecordDecl::field_iterator i = decl->field_begin(), e = decl->field_end();
        //          i != e; i++)
        //     {
        //         clang::FieldDecl *field = *i;
        //         std::string gettype = field->getType().getAsString();
        //         int type = 1;
        //         if (gettype.find("struct") != std::string::npos)
        //         {
        //             std::string nameb = field->getType().getAsString();

        //             if (gettype.find(" *") != std::string::npos)
        //             {
        //                 type = 2;
        //             }
        //             allREs.push_back(new Relates(Name, nameb, type));
        //         }
        //         if (field->getType()->isFunctionPointerType())
        //         {
        //             type = 3;
        //             std::string nameb = field->getNameAsString();
        //             allREs.push_back(new Relates(Name, nameb, type));
        //         }
                
        //     }

        //     allSTs.push_back(curr);
        // }
        // llvm::outs() << "    get " << allSTs.size() << " structures\n";
        // llvm::outs() << "    get " << allREs.size() << " relations\n";

        insertDB();
    }

    bool HandleTopLevelDecl(clang::DeclGroupRef DG) override
    {
        llvm::StringRef currFile = manager->getFilename(manager->getLocForStartOfFile(manager->getMainFileID()));
        for (clang::DeclGroupRef::iterator i = DG.begin(), e = DG.end(); i != e; ++i)
        {
            const clang::FunctionDecl *FD = llvm::dyn_cast<clang::FunctionDecl>(*i);
            if (FD) {
                std::string name = FD->getNameAsString();
                llvm::StringRef fileRef = manager->getFilename(FD->getBeginLoc());
                std::string file = fileRef.empty() ? "" : fileRef.data();
                clang::QualType retType = FD->getReturnType();
                // std::cout << name << ":" << retType.getAsString() << " " << file << ":" << (fileRef == currFile) << std::endl;
                
                
                
                allFuncUses.push_back(new FunctionUse(name, currFile.data()));

                bool isDecl = (fileRef == currFile);
                // std::cout << name << ":" << retType.getAsString() << ":" << currFile.data() << ":" << file << ":" << isDecl << ":" << FD->isImplicit() << "\n" << std::endl;

                if (isDecl) {
                    // std::cout << name << ":" << retType.getAsString() << std::endl;
                    allFuncDeclarations.push_back(new FunctionDeclaration(name, retType.getAsString(), file));
                    if (FD->param_empty()) {
                        continue;
                    }
                    for (auto *i = FD->param_begin(); i != FD->param_end(); i++) {
                        const clang::ParmVarDecl *PVD = *i;
                        llvm::StringRef pvdnameRef = PVD->getName();
                        std::string pvdname = pvdnameRef.data();
                        clang::QualType pvdType = PVD->getType();
                        // std::cout << "    " << pvdname << ":" << pvdType.getAsString() << std::endl;
                        allFuncParams.push_back(new Param(pvdname, pvdType.getAsString(), name));
                    }
                }
            }
        }
        // for (clang::DeclGroupRef::iterator i = DG.begin(), e = DG.end(); i != e; ++i)
        // {
        //     const clang::VarDecl *VD = llvm::dyn_cast<clang::VarDecl>(*i);
        //     if (VD)
        //     {
        //         std::string name = VD->getNameAsString();
        //         std::string type = VD->getType().getAsString();
        //         // llvm::outs() << "\e[32m" << name << "\e[0m:" << manager->getFilename(VD->getBeginLoc()) << "|\n";
        //         llvm::StringRef fileRef = manager->getFilename(VD->getBeginLoc());
        //         std::string file = fileRef.empty() ? "" : fileRef.data();
        //         llvm::StringRef currFileRef = manager->getFilename(manager->getLocForStartOfFile(manager->getMainFileID()));
        //         std::string currFile = currFileRef.empty() ? "" : currFileRef.data();
        //         int extrainfo = 0;
        //         if (VD->getType()->isPointerType())
        //         {
        //             extrainfo = 1;
        //         }
        //         else if (VD->getType()->isRecordType())
        //         {
        //             extrainfo = 2;
        //         }
        //         else if (VD->getType()->isArrayType())
        //         {
        //             extrainfo = 3;
        //         }
        //         else if (VD->getType()->isFunctionPointerType())
        //         {
        //             extrainfo = 4;
        //         }
        //         allGVs.push_back(new GlobalVaribles(name, type, file, extrainfo, currFile));
        //     }
        // }

        return true;
    }

    void insertDB()
    {
        sqlite3 *db;
        int res = sqlite3_open("ast-20220228.db", &db);
        int success = 0;
        int failed = 0;
        if (res)
        {
            //database failed to open
            std::cout << "    Database failed to open" << std::endl;
        }
        else
        {
            //your database code here
            std::cout << "    connected ast.db" << std::endl;

            // res = sqlite3_exec(db, StructscreateTable.data(), nullptr, 0, nullptr);
            // res = sqlite3_exec(db, GlobalVariblescreateTable.data(), nullptr, 0, nullptr);
            // res = sqlite3_exec(db, RelatescreateTable.data(), nullptr, 0, nullptr);
            sqlite3_exec(db, FunctionUsescreateTable.data(), nullptr, 0, nullptr);
            sqlite3_exec(db, FunctionDeclarationscreateTable.data(), nullptr, 0, nullptr);
            sqlite3_exec(db, ParamscreateTable.data(), nullptr, 0, nullptr);

            
            for (auto &x : allFuncDeclarations) {
                res = sqlite3_exec(db, x->genDB().data(), nullptr, 0, nullptr);
                // x->print();
                stat(res, success, failed, x->genDB());
            }

            // for (auto &x : allFuncUses) {
            //     res = sqlite3_exec(db, x->genDB().data(), nullptr, 0, nullptr);
            //     stat(res, success, failed, x->genDB());
            // }

            for (auto &x : allFuncParams) {
                res = sqlite3_exec(db, x->genDB().data(), nullptr, 0, nullptr);
                stat(res, success, failed, x->genDB());
            }

            // for (auto x : allGVs)
            // {
            //     // llvm::outs() << x->genDB().data() << "\n";
            //     res = sqlite3_exec(db, x->genDB().data(), nullptr, 0, nullptr);
            //     // llvm::outs() << "executed " << (res == SQLITE_OK) << "\n";
            //     stat(res, success, failed, x->genDB());
            // }

            // for (auto x : allSTs)
            // {
            //     res = sqlite3_exec(db, x->genStructsDB().data(), nullptr, 0, nullptr);
            //     stat(res, success, failed, x->genStructsDB().data());
            // }

            // for (auto x : allREs)
            // {
            //     // llvm::outs() << x->genRelatedDB().data() << "\n";
            //     res = sqlite3_exec(db, x->genRelatedDB().data(), nullptr, 0, nullptr);
            //     // llvm::outs() << "executed " << (res == SQLITE_OK) << "\n";
            //     stat(res, success, failed, x->genRelatedDB());
            // }
        }
        llvm::outs() << "    commited \e[32m" << success << " sqls, \e[31m" << failed << " failed\e[0m\n";

        sqlite3_close(db);
    }

    void stat(int res, int &success, int &failed, std::string sql)
    {
        if (res != SQLITE_OK)
        {
            failed++;
            // std::cout << "    failed :" << sql << std::endl;
        }
        else
        {
            success++;
        }
    }
};