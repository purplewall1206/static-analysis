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
	std::unordered_map<std::string, clang::RecordDecl*> recorddecls;
	std::unordered_map<std::string, clang::VarDecl*> vardecls;

public:
	WorkVisitor(clang::ASTContext *context, clang::SourceManager *manager)
		: context(context), manager(manager) {}

	std::unordered_map<std::string, clang::RecordDecl*> getRecorddecls() {
		return recorddecls;
	}

	std::unordered_map<std::string, clang::VarDecl*> getVardecls() {
		return vardecls;
	}



	bool VisitVarDecl(clang::VarDecl *decl) {

	}

	bool VisitRecordDecl(clang::RecordDecl *decl)
	{
		// Declaration->dump();		
		// clang::FullSourceLoc FullLocation = context->getFullLoc(Declaration->getBeginLoc());
		// if (FullLocation.isValid())
		// 	llvm::outs() << "Found declaration at "
		// 				 << Declaration->getQualifiedNameAsString() << ":"
		// 				 << getDeclLocation(Declaration->getBeginLoc()) << ":"
		// 				 << FullLocation.getSpellingLineNumber() << ":"
		// 				 << FullLocation.getSpellingColumnNumber() << "\n";
		// llvm::outs() << "\n";
		// if (Declaration->getKindName() == "struct") {
		// 	auto Name = Declaration->getName();
		// 	std::string key = Name.data();
		// 	key = "struct " + key;
		// 	alldecls[key] = Declaration;
		// }
		// clang::DeclContext ctx = Declaration->getDeclContext();
		// Declaration->
		if (decl->getKindName() == "struct") {
			std::string Name = decl->getNameAsString();
			recorddecls[Name] = decl;
		}
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