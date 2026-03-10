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
#line 5 "../../../Source/Core/AST/FunctionDecl.nll"
		public: TypeRef* m_pTypeRef;
#line 6 "../../../Source/Core/AST/FunctionDecl.nll"
		public: Token* m_pNameToken;
#line 7 "../../../Source/Core/AST/FunctionDecl.nll"
		public: const char* m_sMangledName;
#line 8 "../../../Source/Core/AST/FunctionDecl.nll"
		public: ParamDecl* m_pParamDecl;
#line 9 "../../../Source/Core/AST/FunctionDecl.nll"
		public: bool m_bConst;
#line 10 "../../../Source/Core/AST/FunctionDecl.nll"
		public: Scope* m_pScope;
#line 12 "../../../Source/Core/AST/FunctionDecl.nll"
		public: static FunctionDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, AST* pParent);
#line 83 "../../../Source/Core/AST/FunctionDecl.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 108 "../../../Source/Core/AST/FunctionDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
#line 3 "../../../Source/Core/AST/FunctionDecl.nll"
		public: FunctionDecl();
	};
}

