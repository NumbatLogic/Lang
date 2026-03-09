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
#line 1 "../../../Source/Core/AST/FunctionDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/FunctionDecl.nll"
	class FunctionDecl : public AST
	{
#line 6 "../../../Source/Core/AST/FunctionDecl.nll"
		public: TypeRef* m_pTypeRef;
#line 7 "../../../Source/Core/AST/FunctionDecl.nll"
		public: Token* m_pNameToken;
#line 8 "../../../Source/Core/AST/FunctionDecl.nll"
		public: const char* m_sMangledName;
#line 9 "../../../Source/Core/AST/FunctionDecl.nll"
		public: ParamDecl* m_pParamDecl;
#line 10 "../../../Source/Core/AST/FunctionDecl.nll"
		public: bool m_bConst;
#line 11 "../../../Source/Core/AST/FunctionDecl.nll"
		public: Scope* m_pScope;
#line 13 "../../../Source/Core/AST/FunctionDecl.nll"
		public: static FunctionDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, AST* pParent);
#line 84 "../../../Source/Core/AST/FunctionDecl.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 109 "../../../Source/Core/AST/FunctionDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 4 "../../../Source/Core/AST/FunctionDecl.nll"
		public: FunctionDecl();
	};
}

