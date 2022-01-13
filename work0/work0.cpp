#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Frontend/FrontendPluginRegistry.h"

using namespace clang;

class FindNamedClassVisitor : public RecursiveASTVisitor<FindNamedClassVisitor> {
public:
  explicit FindNamedClassVisitor(ASTContext *Context)
    : Context(Context) {}

  bool VisitCXXRecordDecl(CXXRecordDecl *Declaration) {
    Declaration->dump();
    llvm::outs() << Declaration->getQualifiedNameAsString() << "\n";
    if (Declaration->getQualifiedNameAsString() == "n::m::C") {
      FullSourceLoc FullLocation = Context->getFullLoc(Declaration->getBeginLoc());
      if (FullLocation.isValid())
        llvm::outs() << "Found declaration at "
                     << FullLocation.getSpellingLineNumber() << ":"
                     << FullLocation.getSpellingColumnNumber() << "\n";
    }
    return true;
  }

  

private:
  ASTContext *Context;
};

class FindNamedClassConsumer : public clang::ASTConsumer {
public:
  explicit FindNamedClassConsumer(ASTContext *Context)
    : Visitor(Context) {}

  virtual void HandleTranslationUnit(clang::ASTContext &Context) {
    auto Decls = Context.getTranslationUnitDecl()->decls();
    llvm::outs() << "test" << "\n";
    for (auto &Decl : Decls) {
      Decl->dump();
      llvm::outs()  << "\n\n\n";
    }
    Visitor.TraverseDecl(Context.getTranslationUnitDecl());
  }

  bool HandleTopLevelDecl(DeclGroupRef DG) override {
    for (DeclGroupRef::iterator i = DG.begin(), e = DG.end(); i != e; ++i) {
      const Decl *D = *i;
      if (const NamedDecl *ND = dyn_cast<NamedDecl>(D))
        llvm::errs() << "top-level-decl: \"" << ND->getNameAsString() << "\"\n";
    D->dump();
      llvm::outs() << "\n\n\n";
    }

    return true;
  }

private:
  FindNamedClassVisitor Visitor;
};

class FindNamedClassAction : public clang::ASTFrontendAction {
public:
  virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
    clang::CompilerInstance &Compiler, llvm::StringRef InFile) {
    return std::make_unique<FindNamedClassConsumer>(&Compiler.getASTContext());
  }
};


class FindNameClassPluginAction : public PluginASTAction {
public:
std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
    clang::CompilerInstance &Compiler, llvm::StringRef InFile) {
      llvm::outs() << "plugin ast action" << "\n";
    return std::make_unique<FindNamedClassConsumer>(&Compiler.getASTContext());
  }

  bool ParseArgs(const CompilerInstance &CI,
                 const std::vector<std::string> &args) override {
                   llvm::outs() << "parseargs" << "\n";
                   return true;
                 }
};

int main(int argc, char **argv) {
  if (argc > 1) {
    clang::tooling::runToolOnCode(std::make_unique<FindNamedClassAction>(), argv[1]);
  }
}


static FrontendPluginRegistry::Add<FindNameClassPluginAction> X("findname","--");