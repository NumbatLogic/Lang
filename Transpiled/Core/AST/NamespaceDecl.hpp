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
#line 0 "../../../Source/Core/AST/NamespaceDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/NamespaceDecl.nll"
	class NamespaceDecl : public AST
	{
#line 5 "../../../Source/Core/AST/NamespaceDecl.nll"
		public: Token* m_pNameToken;
#line 6 "../../../Source/Core/AST/NamespaceDecl.nll"
		public: NamespaceNode* m_pNamespaceNode;
#line 8 "../../../Source/Core/AST/NamespaceDecl.nll"
		public: NamespaceDecl();
#line 14 "../../../Source/Core/AST/NamespaceDecl.nll"
		public: static NamespaceDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 72 "../../../Source/Core/AST/NamespaceDecl.nll"
		public: virtual void PreValidate(Validator* pValidator, OperatorExpr* pParent);
#line 80 "../../../Source/Core/AST/NamespaceDecl.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 88 "../../../Source/Core/AST/NamespaceDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

