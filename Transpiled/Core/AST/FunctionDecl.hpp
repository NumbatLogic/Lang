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
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/FunctionDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/FunctionDecl.nll"
	class FunctionDecl : public AST
	{
		public: TypeRef* m_pTypeRef;
		public: Token* m_pNameToken;
		public: const char* m_sMangledName;
		public: ParamDecl* m_pParamDecl;
		public: bool m_bConst;
		public: Scope* m_pScope;
		public: static FunctionDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, AST* pParent);
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
		public: FunctionDecl();
	};
}

