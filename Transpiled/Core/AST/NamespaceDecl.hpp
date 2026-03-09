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
#line 1 "../../../Source/Core/AST/NamespaceDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/NamespaceDecl.nll"
	class NamespaceDecl : public AST
	{
#line 6 "../../../Source/Core/AST/NamespaceDecl.nll"
		public: Token* m_pNameToken;
#line 7 "../../../Source/Core/AST/NamespaceDecl.nll"
		public: NamespaceNode* m_pNamespaceNode;
#line 9 "../../../Source/Core/AST/NamespaceDecl.nll"
		public: NamespaceDecl();
#line 15 "../../../Source/Core/AST/NamespaceDecl.nll"
		public: static NamespaceDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 73 "../../../Source/Core/AST/NamespaceDecl.nll"
		public: virtual void PreValidate(Validator* pValidator, OperatorExpr* pParent);
#line 81 "../../../Source/Core/AST/NamespaceDecl.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 89 "../../../Source/Core/AST/NamespaceDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

