#include "llvm/ADT/MapVector.h"
// #include "llvm/IR/AbstractCallSite.h"
#include "llvm/IR/PassManager.h"

#include "llvm/Support/raw_ostream.h"

#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/InlineAsm.h"

#include "llvm/Pass.h"
#include "llvm/IR/Constants.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/ValueSymbolTable.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

#include <sqlite3.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace llvm;

// 分析当前.o.llvm.bc 使用了哪些1全局变量,2函数和3struct类型
// LLVM 9.x

namespace {
	std::string gvCreateTable = "create table if not exists irglobalvaribles (id integer PRIMARY KEY AUTOINCREMENT, name text, file text, count integer, extra text);";
	std::string fnCreateTable = "create table if not exists irfunctions(id integer PRIMARY KEY AUTOINCREMENT, name text, file text, count integer, extra text);";
	std::string stCreateTable = "create table if not exists irstructs(id integer PRIMARY KEY AUTOINCREMENT, name text, file text, count integer, extra text);";

	std::string insertsql(std::string table, std::string name, std::string file, int count) {
		std::string res = "insert into " + table + "(";
		res = res + "\"" + name 
				  + "\", \"" + file
				  + "\", " + std::to_string(count)
				  + ")";
		return res;
	}

    struct IRUsageModulePass : public llvm::ModulePass {
        static char ID;
		std::unordered_map<std::string, int> globalvaribles;
		std::unordered_map<std::string, int> functions;
		std::unordered_map<std::string, int> structs;

        IRUsageModulePass() : ModulePass(ID) {}
        bool runOnModule(Module &M) override;
    };

    bool IRUsageModulePass::runOnModule(Module &M) {
        LLVMContext& CTX = M.getContext();
		std::string currFile = M.getSourceFileName();
		std::cout << currFile << std::endl;
        // GlobalVariable* tg = M.getGlobalVariable("hg");

        // errs() << *tg << "\n\n";
        // for (auto &F : M) {
        //     errs() << F << "\n";
        // }
		// errs() << "global variables\n";
		// for (GlobalVariable &G : M.getGlobalList()) {
		// 	errs() << "    " << G.getName() << ":" << G.getType()->isPointerTy() << "\n";
		// }
		// errs() << "metadatas\n";
		// for (auto &MD : M.getNamedMDList()) {
		// 	errs() << "    " << MD.getName() << "\n";
		// }		

		// errs() << "Value Symbol Table\n";
		// // M.getValueSymbolTable()
		// ValueSymbolTable& VST = M.getValueSymbolTable();
		// for (auto& vst : VST) {
		// 	errs() << "    " << vst.getKey() << ":" << vst.getValue()->getName() << ":" << *(vst.getValue()->getType()) << "\n";
		// }

		for (auto& F : M) {
			outs() << F.getName() << "\n";
			for (auto& BB : F) {
				for (auto& I : BB) {
					// outs() << "    " << I << "\n";
					// is global
					for (Value *Op : I.operands()) {
						if (GlobalValue* G = dyn_cast<GlobalVariable>(Op)) {
							// outs() << "global " << *G << ":" << *(G->getType()) << "\n";
							++globalvaribles[G->getName().data()];
							// outs() << "        ++ " << G->getName() << "\n";
						}
						
						Type *t = Op->getType();
						std::string type_str;
						raw_string_ostream rso(type_str);
						t->print(rso);
						// outs() << "        ++ " << *t << "\n";
						structs[rso.str()]++;
					}
					
					if (I.getOpcode() == Instruction::Call) {
						// outs() << "        ++ func : " << I.getOpcode() << "\n";
                        auto *CB = dyn_cast<CallBase>(&I);
						Function *F = CB->getCalledFunction();
						if (F) {
							// outs() << "        ++ " << F->getName() << "\n";
							std::string fname = F->getName().data();
							if (fname.find("llvm.dbg") != std::string::npos) {
								continue;
							}
							functions[fname]++;
						}
						
                    }

					// if (I.getOpcode() == Instruction::Store)
					
				}
			}
		}

		sqlite3 *db;
		int res = sqlite3_open("ir-20220301.db", &db);
		int success = 0;
		int failed = 0;
		if (res) {
			std::cout << "    Database failed to open" << std::endl;
		} else {
			std::cout << "    connected ast.db" << std::endl;
			sqlite3_exec(db, gvCreateTable.data(), nullptr, 0, nullptr);
			sqlite3_exec(db, fnCreateTable.data(), nullptr, 0, nullptr);
			sqlite3_exec(db, stCreateTable.data(), nullptr, 0, nullptr);


			// outs() << "global vars \n\n";
			for (auto &gv : globalvaribles) {
				// outs() << "    " << gv.first << ":" << gv.second << "\n";
				std::string sql = insertsql("", gv.first, currFile, gv.second);
				res = sqlite(db, sql , nullptr, 0, nullptr);
				stat(res, success, failed, sql);
			}

			// outs() << "\n\nfunctions \n\n";
			for (auto &func : functions) {
				// outs() << "    " << func.first << ":" << func.second << "\n";
				std::string sql = insertsql("", func.first, currFile, func.second);
				res = sqlite(db, sql , nullptr, 0, nullptr);
				stat(res, success, failed, sql);
			}

			// outs() << "\n\nstructs \n\n";
			for (auto &st : structs) {
				// outs() << "    " << st.first << ":" << st.second << "\n";
				std::string sql = insertsql("", st.first, currFile, st.second);
				res = sqlite(db, sql , nullptr, 0, nullptr);
				stat(res, success, failed, sql);
			}
		}

		llvm::outs() << "    commited \e[32m" << success << " sqls, \e[31m" << failed << " failed\e[0m\n";

        sqlite3_close(db);



        return true;
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
char IRUsageModulePass::ID = 0;

static RegisterPass<IRUsageModulePass> X(
    "irusage",
    "IRUsage Module Pass",
    false,
    true
);
}
