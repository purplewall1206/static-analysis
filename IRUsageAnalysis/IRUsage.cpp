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


// #include <vector>
// #include <algorithm>

// using namespace llvm;

// // 分析当前.o.llvm.bc 使用了哪些全局变量和struct类型

// namespace {
//     struct IRUsageModulePass : public llvm::ModulePass {
//         static char ID;

//         IRUsageModulePass() : ModulePass(ID) {}
//         bool runOnModule(Module &M) override;
//     };

//     bool IRUsageModulePass::runOnModule(Module &M) {
//         LLVMContext& CTX = M.getContext();
//         errs() << "hello\n";
//         for (auto &F : M) {
//             errs() << F << "\n";
//         }
//         return true;
//     }
// char IRUsageModulePass::ID = 0;

// static RegisterPass<IRUsageModulePass> X(
//     "IRUsage",
//     "IRUsage Module Pass",
//     false,
//     true
// );

// // static void loadPass(const PassManagerBuilder &Builder, llvm::legacy::PassManagerBase &PM) {
// //     PM.add(new IRUsageModulePass());
// // }

// static RegisterStandardPasses Y(
//                                 PassManagerBuilder::EP_EarlyAsPossible, 
//                                 [](const PassManagerBuilder &Builder, legacy::PassManagerBase &PM) {
//                                     PM.add(new IRUsageModulePass());
//                                 });
// }

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"


using namespace llvm;
namespace {
// This method implements what the pass does
void visitor(Function &F) {
    errs() << "(llvm-tutor) Hello from: "<< F.getName() << "\n";
    errs() << "(llvm-tutor)   number of arguments: " << F.arg_size() << "\n";
}
// New PM implementation
struct HelloWorld : PassInfoMixin<HelloWorld> {
  // Main entry point, takes IR unit to run the pass on (&F) and the
  // corresponding pass manager (to be queried if need be)
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
      errs() << "111111111111111111111111111111111\n";
    visitor(F);
    return PreservedAnalyses::all();
  }
};

} // namespace llvm

//-----------------------------------------------------------------------------
// New PM Registration
//-----------------------------------------------------------------------------
llvm::PassPluginLibraryInfo getHelloWorldPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "HelloWorld", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "hello-world") {
                    FPM.addPass(HelloWorld());
                    return true;
                  }
                  return false;
                });
          }};
}

// This is the core interface for pass plugins. It guarantees that 'opt' will
// be able to recognize HelloWorld when added to the pass pipeline on the
// command line, i.e. via '-passes=hello-world'
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getHelloWorldPluginInfo();
}