#pragma once

#include "AST.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class TypeRef;
		class Token;
		class AST;
		class VarDecl;
		class TokenContainer;
		class OffsetDatum;
		class Validator;
		class OperatorExpr;
		class InternalString;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		class VarDecl : public AST
		{
			public: TypeRef* m_pTypeRef;
			public: Token* m_pNameToken;
			public: AST* m_pAssignment;
			public: bool m_bInline;
			public: AST* m_pArraySize;
			public: Token* m_pOwnedNameToken;
			public: VarDecl();
			public: static VarDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, bool bInline);
			public: virtual AST* FindByName(const char* sxName, AST* pCallingChild);
			public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
			public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
			public: virtual ~VarDecl();
		};
	}
}

