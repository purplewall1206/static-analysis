#pragma once

#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/SourceManager.h"
#include "llvm/Support/raw_ostream.h"

#include <memory>
#include <string>
#include <sstream>
#include <unordered_map>

// The RecursiveASTVisitor provides hooks of the form bool VisitNodeType(NodeType *) for most AST nodes; the exception are TypeLoc nodes, which are passed by-value. We only need to implement the methods for the relevant node types.

class WorkVisitor : public clang::RecursiveASTVisitor<WorkVisitor>
{
private:
	clang::ASTContext *context;
	clang::SourceManager *manager;
	std::unordered_map<std::string, clang::RecordDecl*> alldecls;

	std::string getDeclLocation(clang::SourceLocation Loc) const
	{
		std::ostringstream OSS;
		OSS << (manager->getFilename(Loc)).data() << ":"
			<< manager->getSpellingLineNumber(Loc) << ":"
			<< manager->getSpellingColumnNumber(Loc);
		return OSS.str();
	}

public:
	WorkVisitor(clang::ASTContext *context, clang::SourceManager *manager)
		: context(context), manager(manager) {}

	std::unordered_map<std::string, clang::RecordDecl*> getAlldecls() {
		return alldecls;
	}

	bool VisitNamedDecl(clang::NamedDecl *NamedDecl)
	{
		// llvm::outs() << "Found " << NamedDecl->getQualifiedNameAsString() << " at "
		// 			 << getDeclLocation(NamedDecl->getBeginLoc()) << "\n";
		return true;
	}

	bool VisitDecl(clang::Decl *Decl)
	{
		// llvm::outs() << "Found Decl " << Decl->getDeclKindName() << " at "
		// 			 << getDeclLocation(Decl->getBeginLoc()) << "\n";
		return true;
	}

	bool VisitFunctionDecl(clang::FunctionDecl *FD)
	{
		return true;
	}

	bool VisitCXXRecordDecl(clang::CXXRecordDecl *Declaration)
	{
		// Declaration->dump();
		// llvm::outs() << "\n\n\n";
		// if (Declaration->getQualifiedNameAsString() == "n::m::C")
		// {
		// 	clang::FullSourceLoc FullLocation = context->getFullLoc(Declaration->getBeginLoc());
		// 	if (FullLocation.isValid())
		// 		llvm::outs() << "Found declaration at "
		// 					 << FullLocation.getSpellingLineNumber() << ":"
		// 					 << FullLocation.getSpellingColumnNumber() << "\n";
		// }
		return true;
	}

	bool VisitRecordDecl(clang::RecordDecl *Declaration)
	{
		// Declaration->dump();
		
		clang::FullSourceLoc FullLocation = context->getFullLoc(Declaration->getBeginLoc());
		if (FullLocation.isValid())
			llvm::outs() << "Found declaration at "
						 << Declaration->getQualifiedNameAsString() << ":"
						 << getDeclLocation(Declaration->getBeginLoc()) << ":"
						 << FullLocation.getSpellingLineNumber() << ":"
						 << FullLocation.getSpellingColumnNumber() << "\n";
		llvm::outs() << "\n";
		if (Declaration->getKindName() == "struct") {
			auto Name = Declaration->getName();
			alldecls[Name.data()] = Declaration;
		}
		

		// clang::DeclContext ctx = Declaration->getDeclContext();
		// Declaration->
		return true;
	}

	void print() {
		for (auto xdecl : alldecls) {
			std::string name = xdecl.first;
			clang::RecordDecl *decl = xdecl.second;
			llvm::outs() << name << ":" << decl->getKindName() <<  "---" << getDeclLocation(decl->getBeginLoc()) << "\n";
		}
	}
};