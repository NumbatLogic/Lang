#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class TypeRef;
	class Token;
	class ParamDecl;
	class Scope;
	class FunctionDecl;
	class TokenContainer;
	class OffsetDatum;
	class AST;
	class Validator;
	class OperatorExpr;
	class InternalString;
}
namespace NumbatLogic
{
	class FunctionDecl : public AST
	{
		public: TypeRef* m_pTypeRef;
		public: Token* m_pNameToken;
		public: const char* m_sMangledName;
		public: ParamDecl* m_pParamDecl;
		public: bool m_bConst;
		public: Scope* m_pScope;
		public: static FunctionDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, AST* pParent);
		public: virtual AST* FindByName(const char* sxName, AST* pCallingChild);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut);
		public: FunctionDecl();
	};
}

