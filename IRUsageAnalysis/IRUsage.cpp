#include "llvm/ADT/MapVector.h"
#include "llvm/IR/AbstractCallSite.h"
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

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"


#include <vector>
#include <algorithm>

// using namespace llvm;

// 分析当前.o.llvm.bc 使用了哪些全局变量和struct类型

namespace {
    struct IRUsageModulePass : public llvm::ModulePass {
        static char ID;

        Inst2ModulePass() : ModulePass(ID) {}
        bool runOnModule(Module &M) override;
    };

    bool IRUsageModulePass::runOnModule(Module &M) {
        auto& CTX = M.getContext();

        return true;
    }
}