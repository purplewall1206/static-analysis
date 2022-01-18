#pragma once

#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/SourceManager.h"
#include "llvm/Support/raw_ostream.h"

#include <memory>
#include <string>
#include <sstream>
#include <unordered_map>
#include <iostream>

// The RecursiveASTVisitor provides hooks of the form bool VisitNodeType(NodeType *) for most AST nodes; the exception are TypeLoc nodes, which are passed by-value. We only need to implement the methods for the relevant node types.


class WorkVisitor : public clang::RecursiveASTVisitor<WorkVisitor>
{
private:
	clang::ASTContext *context;
	clang::SourceManager *manager;
	std::unordered_map<std::string, clang::RecordDecl *> recorddecls;
	std::unordered_map<std::string, clang::VarDecl *> vardecls;

public:
	WorkVisitor(clang::ASTContext *context, clang::SourceManager *manager)
		: context(context), manager(manager) {}

	std::unordered_map<std::string, clang::RecordDecl *> getRecorddecls()
	{
		return recorddecls;
	}

	std::unordered_map<std::string, clang::VarDecl *> getVardecls()
	{
		return vardecls;
	}

	

	bool VisitRecordDecl(clang::RecordDecl *decl)
	{
		llvm::outs() << "-------------visit record decl\n";
		if (decl->getKindName() == "struct")
		{
			
			std::string Name = decl->getNameAsString();
			recorddecls[Name] = decl;
		}
		return true;
	}

};