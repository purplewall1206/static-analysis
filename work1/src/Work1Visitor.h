#pragma once

#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/SourceManager.h"
#include "llvm/Support/raw_ostream.h"

#include <memory>
#include <string>
#include <sstream>

class WorkVisitor : public clang::RecursiveASTVisitor<WorkVisitor> {
private:
	clang::ASTContext *context;
	clang::SourceManager *manager;

	std::string getDeclLocation(clang::SourceLocation Loc) const {
		std::ostringstream OSS;
		OSS << (manager->getFilename(Loc)).data() << ":"
			<< manager->getSpellingLineNumber(Loc) << ":"
			<< manager->getSpellingColumnNumber(Loc);
		return OSS.str();
	}

public:
	WorkVisitor(clang::ASTContext *context, clang::SourceManager *manager)
		: context(context), manager(manager) {}
	
	bool VisitNamedDecl(clang::NamedDecl *NamedDecl) {
		llvm::outs() << "Found " << NamedDecl->getQualifiedNameAsString() << " at "
                 << getDeclLocation(NamedDecl->getBeginLoc()) << "\n";
    	return true;
	}
};