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
#line 0 "../../../Source/Core/AST/MemberVarDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/MemberVarDecl.nll"
	class MemberVarDecl : public AST
	{
#line 5 "../../../Source/Core/AST/MemberVarDecl.nll"
		public: AccessLevel* m_pAccessLevel;
#line 6 "../../../Source/Core/AST/MemberVarDecl.nll"
		public: bool m_bStatic;
#line 7 "../../../Source/Core/AST/MemberVarDecl.nll"
		public: VarDecl* m_pVarDecl;
#line 9 "../../../Source/Core/AST/MemberVarDecl.nll"
		public: MemberVarDecl();
#line 14 "../../../Source/Core/AST/MemberVarDecl.nll"
		public: static MemberVarDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 49 "../../../Source/Core/AST/MemberVarDecl.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 60 "../../../Source/Core/AST/MemberVarDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

