#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/SourceManager.h"
#include "llvm/Support/raw_ostream.h"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/Basic/SourceManager.h"

#include "clang/Frontend/FrontendAction.h"
#include "clang/Frontend/CompilerInstance.h"

#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"

#include <memory>
#include <string>
#include <sstream>

using namespace clang::tooling;
using namespace llvm;

class DeclVisitor : public clang::RecursiveASTVisitor<DeclVisitor> {
  clang::SourceManager &SourceManager;

public:
  DeclVisitor(clang::SourceManager &SourceManager)
      : SourceManager(SourceManager) {}

  bool VisitNamedDecl(clang::NamedDecl *NamedDecl) {
    llvm::outs() << "Found " << NamedDecl->getQualifiedNameAsString() << " at "
                 << getDeclLocation(NamedDecl->getBeginLoc()) << "\n";
    return true;
  }

private:
  std::string getDeclLocation(clang::SourceLocation Loc) const {
    std::ostringstream OSS;
    OSS << SourceManager.getFilename(Loc).str() << ":"
        << SourceManager.getSpellingLineNumber(Loc) << ":"
        << SourceManager.getSpellingColumnNumber(Loc);
    return OSS.str();
  }
};


class DeclFinder : public clang::ASTConsumer {
  clang::SourceManager &SourceManager;
  DeclVisitor Visitor;
public:
  DeclFinder(clang::SourceManager &SM) : SourceManager(SM), Visitor(SM) {}

  void HandleTranslationUnit(clang::ASTContext &Context) final {
    auto Decls = Context.getTranslationUnitDecl()->decls();
    for (auto &Decl : Decls) {
      const auto& FileID = SourceManager.getFileID(Decl->getLocation());
      if (FileID != SourceManager.getMainFileID())
        continue;
      Visitor.TraverseDecl(Decl);
    }
  }
};



class DeclFindingAction : public clang::ASTFrontendAction {
public:
  std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &CI, clang::StringRef) final {
    return std::unique_ptr<clang::ASTConsumer>(
        new DeclFinder(CI.getSourceManager()));
  }
};

static llvm::cl::extrahelp
    CommonHelp(clang::tooling::CommonOptionsParser::HelpMessage);
llvm::cl::OptionCategory FindDeclCategory("find-decl options");

#define FIND_DECL_VERSION "0.0.1"

static void PrintVersion() {
  llvm::outs() << "find-decl version: " << FIND_DECL_VERSION << "\n";
}

static char FindDeclUsage[] = "find-decl <source file>";


int main(int argc, const char **argv) {
//   llvm::cl::SetVersionPrinter(PrintVersion);
//   clang::tooling::CommonOptionsParser option(argc, argv);
//   , FindDeclCategory);
                                            //  FindDeclUsage);
    // clang::tooling::CommonOptionsParser option(argc, argv, FindDeclCategory, llvm::cl::OneOrMore, FindDeclUsage);
    auto option = CommonOptionsParser::create(argc, argv, FindDeclCategory, llvm::cl::OneOrMore, FindDeclUsage);
    auto files = option->getSourcePathList();
  clang::tooling::ClangTool tool(option->getCompilations(), files);

  return tool.run(clang::tooling::newFrontendActionFactory<DeclFindingAction>().get());
}
