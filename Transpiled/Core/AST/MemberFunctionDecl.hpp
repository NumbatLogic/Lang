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
#line 0 "../../../Source/Core/AST/MemberFunctionDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/MemberFunctionDecl.nll"
	class MemberFunctionDecl : public AST
	{
		public: ClassDecl* m_pParentClassDecl;
		public: AccessLevel* m_pAccessLevel;
		public: FunctionDecl* m_pFunctionDecl;
		public: bool m_bStatic;
		public: bool m_bVirtual;
		public: bool m_bOverride;
#line 12 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public: MemberFunctionDecl();
#line 18 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public: static MemberFunctionDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl);
#line 77 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 82 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

