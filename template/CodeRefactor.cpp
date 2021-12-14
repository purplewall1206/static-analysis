#include "clang/AST/ASTConsumer.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Rewrite/Frontend/FixItRewriter.h"
#include "clang/Tooling/CommonOptionsParser.h"

#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Refactoring.h"
#include "llvm/Support/CommandLine.h"

#include "clang/AST/Expr.h"
#include "clang/AST/ExprCXX.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/Tooling/Refactoring/Rename/RenamingAction.h"
#include "llvm/Support/raw_ostream.h"
#include <string>



//-----------------------------------------------------------------------------
// ASTFinder callback
//-----------------------------------------------------------------------------
class CodeRefactorMatcher
    : public clang::ast_matchers::MatchFinder::MatchCallback {
public:
  explicit CodeRefactorMatcher(clang::Rewriter &RewriterForCodeRefactor,
                               std::string NewName)
      : CodeRefactorRewriter(RewriterForCodeRefactor), NewName(NewName) {}
  void onEndOfTranslationUnit() override;

  void run(const clang::ast_matchers::MatchFinder::MatchResult &) override;

private:
  clang::Rewriter CodeRefactorRewriter;
  // The new name of the matched member expression.
  // NOTE: This matcher already knows *what* to replace (which method in which
  // class/struct), because it _matched_ a member expression that corresponds to
  // the command line arguments.
  std::string NewName;
};

//-----------------------------------------------------------------------------
// ASTConsumer
//-----------------------------------------------------------------------------
class CodeRefactorASTConsumer : public clang::ASTConsumer {
public:
  CodeRefactorASTConsumer(clang::Rewriter &R, std::string ClassName,
                          std::string OldName, std::string NewName);
  void HandleTranslationUnit(clang::ASTContext &Ctx) override {
    Finder.matchAST(Ctx);
  }

private:
  clang::ast_matchers::MatchFinder Finder;
  CodeRefactorMatcher CodeRefactorHandler;
  // The name of the class to match. Use base class name to rename in all
  // derived classes.
  std::string ClassName;
  // The name of the member method to match
  std::string OldName;
  // The new name of the member method
  std::string NewName;
};

using namespace clang;
using namespace ast_matchers;
using namespace llvm;


//-----------------------------------------------------------------------------
// CodeRefactorMatcher - implementation
//-----------------------------------------------------------------------------
void CodeRefactorMatcher::run(const MatchFinder::MatchResult &Result) {
  const MemberExpr *MemberAccess =
      Result.Nodes.getNodeAs<clang::MemberExpr>("MemberAccess");

  if (MemberAccess) {
    SourceRange CallExprSrcRange = MemberAccess->getMemberLoc();
    CodeRefactorRewriter.ReplaceText(CallExprSrcRange, NewName);
  }

  const NamedDecl *MemberDecl =
      Result.Nodes.getNodeAs<clang::NamedDecl>("MemberDecl");

  if (MemberDecl) {
    SourceRange MemberDeclSrcRange = MemberDecl->getLocation();
    CodeRefactorRewriter.ReplaceText(
        CharSourceRange::getTokenRange(MemberDeclSrcRange), NewName);
  }
}

void CodeRefactorMatcher::onEndOfTranslationUnit() {
  // Output to stdout
  CodeRefactorRewriter
      .getEditBuffer(CodeRefactorRewriter.getSourceMgr().getMainFileID())
      .write(llvm::outs());
}

CodeRefactorASTConsumer::CodeRefactorASTConsumer(Rewriter &R,
                                                 std::string ClassName,
                                                 std::string OldName,
                                                 std::string NewName)
    : CodeRefactorHandler(R, NewName), ClassName(ClassName), OldName(OldName),
      NewName(NewName) {

  const auto MatcherForMemberAccess = cxxMemberCallExpr(
      callee(memberExpr(member(hasName(OldName))).bind("MemberAccess")),
      thisPointerType(cxxRecordDecl(isSameOrDerivedFrom(hasName(ClassName)))));

  Finder.addMatcher(MatcherForMemberAccess, &CodeRefactorHandler);

  const auto MatcherForMemberDecl = cxxRecordDecl(
      allOf(isSameOrDerivedFrom(hasName(ClassName)),
            hasMethod(decl(namedDecl(hasName(OldName))).bind("MemberDecl"))));

  Finder.addMatcher(MatcherForMemberDecl, &CodeRefactorHandler);
}

//-----------------------------------------------------------------------------
// FrontendAction
//-----------------------------------------------------------------------------
class CodeRefactorAddPluginAction : public PluginASTAction {
public:
  bool ParseArgs(const CompilerInstance &CI,
                 const std::vector<std::string> &Args) override {
    // Example error handling.
    DiagnosticsEngine &D = CI.getDiagnostics();
    for (size_t I = 0, E = Args.size(); I != E; ++I) {
      llvm::errs() << "CodeRefactor arg = " << Args[I] << "\n";

      if (Args[I] == "-class-name") {
        if (I + 1 >= E) {
          D.Report(D.getCustomDiagID(DiagnosticsEngine::Error,
                                     "missing -class-name argument"));
          return false;
        }
        ++I;
        ClassName = Args[I];
      } else if (Args[I] == "-old-name") {
        if (I + 1 >= E) {
          D.Report(D.getCustomDiagID(DiagnosticsEngine::Error,
                                     "missing -old-name argument"));
          return false;
        }
        ++I;
        OldName = Args[I];
      } else if (Args[I] == "-new-name") {
        if (I + 1 >= E) {
          D.Report(D.getCustomDiagID(DiagnosticsEngine::Error,
                                     "missing -new-name argument"));
          return false;
        }
        ++I;
        NewName = Args[I];
      }
      if (!Args.empty() && Args[0] == "help")
        PrintHelp(llvm::errs());
    }

    if (NewName.empty()) {
      D.Report(D.getCustomDiagID(DiagnosticsEngine::Error,
                                 "missing -new-name argument"));
      return false;
    }
    if (OldName.empty()) {
      D.Report(D.getCustomDiagID(DiagnosticsEngine::Error,
                                 "missing -old-name argument"));
      return false;
    }
    if (ClassName.empty()) {
      D.Report(D.getCustomDiagID(DiagnosticsEngine::Error,
                                 "missing -class-name argument"));
      return false;
    }

    return true;
  }
  static void PrintHelp(llvm::raw_ostream &ros) {
    ros << "Help for CodeRefactor plugin goes here\n";
  }

  // Returns our ASTConsumer per translation unit.
  std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI,
                                                 StringRef file) override {
    RewriterForCodeRefactor.setSourceMgr(CI.getSourceManager(),
                                         CI.getLangOpts());
    return std::make_unique<CodeRefactorASTConsumer>(
        RewriterForCodeRefactor, ClassName, OldName, NewName);
  }

private:
  Rewriter RewriterForCodeRefactor;
  std::string ClassName;
  std::string OldName;
  std::string NewName;
};

//-----------------------------------------------------------------------------
// Registration
//-----------------------------------------------------------------------------
static FrontendPluginRegistry::Add<CodeRefactorAddPluginAction>
    X(/*Name=*/"CodeRefactor",
      /*Desc=*/"Change the name of a class method");



//===----------------------------------------------------------------------===//
// Command line options
//===----------------------------------------------------------------------===//
static cl::OptionCategory CodeRefactorCategory("ct-code-refactor options");

static cl::opt<std::string> ClassNameOpt{
    "class-name",
    cl::desc("The name of the class/struct that the method to be renamed "
             "belongs to"),
    cl::Required, cl::init(""), cl::cat(CodeRefactorCategory)};
static cl::opt<std::string> OldNameOpt{
    "old-name", cl::desc("The current name of the method to be renamed"),
    cl::Required, cl::init(""), cl::cat(CodeRefactorCategory)};
static cl::opt<std::string> NewNameOpt{
    "new-name", cl::desc("The new name of the method to be renamed"),
    cl::Required, cl::init(""), cl::cat(CodeRefactorCategory)};

//===----------------------------------------------------------------------===//
// PluginASTAction
//===----------------------------------------------------------------------===//
class CodeRefactorPluginAction : public PluginASTAction {
public:
  explicit CodeRefactorPluginAction(){};
  // Not used
  bool ParseArgs(const CompilerInstance &CI,
                 const std::vector<std::string> &args) override {
    return true;
  }

  // Output the edit buffer for this translation unit
  // void EndSourceFileAction() override {
  //   RewriterForCodeRefactor
  //       .getEditBuffer(RewriterForCodeRefactor.getSourceMgr().getMainFileID())
  //       .write(llvm::outs());
  // }

  std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI,
                                                 StringRef file) override {
    RewriterForCodeRefactor.setSourceMgr(CI.getSourceManager(),
                                         CI.getLangOpts());
    return std::make_unique<CodeRefactorASTConsumer>(
        RewriterForCodeRefactor, ClassNameOpt, OldNameOpt, NewNameOpt);
  }

private:
  Rewriter RewriterForCodeRefactor;
};

//===----------------------------------------------------------------------===//
// Main driver code.
//===----------------------------------------------------------------------===//
int main(int Argc, const char **Argv) {
  Expected<tooling::CommonOptionsParser> eOptParser =
      clang::tooling::CommonOptionsParser::create(Argc, Argv,
                                                  CodeRefactorCategory);
  if (auto E = eOptParser.takeError()) {
    errs() << "Problem constructing CommonOptionsParser "
           << toString(std::move(E)) << '\n';
    return EXIT_FAILURE;
  }
  clang::tooling::RefactoringTool Tool(eOptParser->getCompilations(),
                                       eOptParser->getSourcePathList());

  return Tool.runAndSave(
      clang::tooling::newFrontendActionFactory<CodeRefactorPluginAction>()
          .get());
}
