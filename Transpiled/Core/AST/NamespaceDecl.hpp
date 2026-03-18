#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class Token;
	class NamespaceNode;
	class NamespaceDecl;
	class TokenContainer;
	class OffsetDatum;
	class AST;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
	class NamespaceDecl : public AST
	{
		public: Token* m_pNameToken;
		public: NamespaceNode* m_pNamespaceNode;
#line 8 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
		public: NamespaceDecl();
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
		public: static NamespaceDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 72 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
		public: virtual void PreValidate(Validator* pValidator, OperatorExpr* pParent);
#line 80 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 88 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

