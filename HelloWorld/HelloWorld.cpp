// #include "clang/AST/ASTConsumer.h"
// #include "clang/AST/RecursiveASTVisitor.h"
// #include "clang/Frontend/CompilerInstance.h"
// #include "clang/Frontend/FrontendAction.h"
// #include "clang/Tooling/Tooling.h"

// using namespace clang;

// class FindNamedClassVisitor
//   : public RecursiveASTVisitor<FindNamedClassVisitor> {
// public:
//   explicit FindNamedClassVisitor(ASTContext *Context)
//     : Context(Context) {}

//   bool VisitCXXRecordDecl(CXXRecordDecl *Declaration) {
//     if (Declaration->getQualifiedNameAsString() == "n::m::C") {
//       FullSourceLoc FullLocation = Context->getFullLoc(Declaration->getBeginLoc());
//       if (FullLocation.isValid())
//         llvm::outs() << "Found declaration at "
//                      << FullLocation.getSpellingLineNumber() << ":"
//                      << FullLocation.getSpellingColumnNumber() << "\n";
//     }
//     return true;
//   }

// private:
//   ASTContext *Context;
// };

// class FindNamedClassConsumer : public clang::ASTConsumer {
// public:
//   explicit FindNamedClassConsumer(ASTContext *Context)
//     : Visitor(Context) {}

//   virtual void HandleTranslationUnit(clang::ASTContext &Context) {
//     Visitor.TraverseDecl(Context.getTranslationUnitDecl());
//   }
// private:
//   FindNamedClassVisitor Visitor;
// };

// class FindNamedClassAction : public clang::ASTFrontendAction {
// public:
//   virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
//     clang::CompilerInstance &Compiler, llvm::StringRef InFile) {
//     return std::make_unique<FindNamedClassConsumer>(&Compiler.getASTContext());
//   }
// };

// int main(int argc, char **argv) {
//   if (argc > 1) {
//     clang::tooling::runToolOnCode(std::make_unique<FindNamedClassAction>(), argv[1]);
//   }
// }

//=============================================================================
// FILE:
//    HelloWorld.cpp
//
// DESCRIPTION:
//    Visits all functions in a module, prints their names and the number of
//    arguments via stderr. Strictly speaking, this is an analysis pass (i.e.
//    the functions are not modified). However, in order to keep things simple
//    there's no 'print' method here (every analysis pass should implement it).
//
// USAGE:
//    1. Legacy PM
//      opt -load libHelloWorld.dylib -legacy-hello-world -disable-output `\`
//        <input-llvm-file>
//    2. New PM
//      opt -load-pass-plugin=libHelloWorld.dylib -passes="hello-world" `\`
//        -disable-output <input-llvm-file>
//
//
// License: MIT
//=============================================================================
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

//-----------------------------------------------------------------------------
// HelloWorld implementation
//-----------------------------------------------------------------------------
// No need to expose the internals of the pass to the outside world - keep
// everything in an anonymous namespace.
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
    visitor(F);
    return PreservedAnalyses::all();
  }
};

// Legacy PM implementation
struct LegacyHelloWorld : public FunctionPass {
  static char ID;
  LegacyHelloWorld() : FunctionPass(ID) {}
  // Main entry point - the name conveys what unit of IR this is to be run on.
  bool runOnFunction(Function &F) override {
    visitor(F);
    // Doesn't modify the input unit of IR, hence 'false'
    return false;
  }
};
} // namespace

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

//-----------------------------------------------------------------------------
// Legacy PM Registration
//-----------------------------------------------------------------------------
// The address of this variable is used to uniquely identify the pass. The
// actual value doesn't matter.
char LegacyHelloWorld::ID = 0;

// This is the core interface for pass plugins. It guarantees that 'opt' will
// recognize LegacyHelloWorld when added to the pass pipeline on the command
// line, i.e.  via '--legacy-hello-world'
static RegisterPass<LegacyHelloWorld>
    X("legacy-hello-world", "Hello World Pass",
      true, // This pass doesn't modify the CFG => true
      false // This pass is not a pure analysis pass => false
    );