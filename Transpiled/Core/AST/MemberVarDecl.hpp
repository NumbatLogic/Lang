#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class AccessLevel;
	class VarDecl;
	class MemberVarDecl;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/MemberVarDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/MemberVarDecl.nll"
	class MemberVarDecl : public AST
	{
#line 6 "../../../Source/Core/AST/MemberVarDecl.nll"
		public: AccessLevel* m_pAccessLevel;
#line 7 "../../../Source/Core/AST/MemberVarDecl.nll"
		public: bool m_bStatic;
#line 8 "../../../Source/Core/AST/MemberVarDecl.nll"
		public: VarDecl* m_pVarDecl;
#line 10 "../../../Source/Core/AST/MemberVarDecl.nll"
		public: MemberVarDecl();
#line 15 "../../../Source/Core/AST/MemberVarDecl.nll"
		public: static MemberVarDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 50 "../../../Source/Core/AST/MemberVarDecl.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 61 "../../../Source/Core/AST/MemberVarDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

