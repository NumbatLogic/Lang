#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class Token;
	class NamespaceNode;
	class NamespaceDecl;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class AST;
	class InternalString;
}
namespace NumbatLogic
{
	class NamespaceDecl : public AST
	{
		public: Token* m_pNameToken;
		public: NamespaceNode* m_pNamespaceNode;
		public: NamespaceDecl();
		public: static NamespaceDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void PreValidate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		protected: AST* SubFindByName(const char* sxName, AST* pCallingChild);
		public: virtual AST* FindByName(const char* sxName, AST* pCallingChild);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
	};
}

