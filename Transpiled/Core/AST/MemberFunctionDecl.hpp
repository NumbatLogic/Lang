#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class ClassDecl;
	class AccessLevel;
	class FunctionDecl;
	class MemberFunctionDecl;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/MemberFunctionDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/MemberFunctionDecl.nll"
	class MemberFunctionDecl : public AST
	{
#line 6 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public: ClassDecl* m_pParentClassDecl;
#line 7 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public: AccessLevel* m_pAccessLevel;
#line 8 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public: FunctionDecl* m_pFunctionDecl;
#line 9 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public: bool m_bStatic;
#line 10 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public: bool m_bVirtual;
#line 11 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public: bool m_bOverride;
#line 13 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public: MemberFunctionDecl();
#line 19 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public: static MemberFunctionDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl);
#line 78 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 83 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

