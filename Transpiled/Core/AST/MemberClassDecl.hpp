#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class ClassDecl;
	class AccessLevel;
	class MemberClassDecl;
	class TokenContainer;
	class OffsetDatum;
	class Validator;
	class OperatorExpr;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/MemberClassDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/MemberClassDecl.nll"
	class MemberClassDecl : public AST
	{
#line 6 "../../../Source/Core/AST/MemberClassDecl.nll"
		public: ClassDecl* m_pParentClassDecl;
#line 7 "../../../Source/Core/AST/MemberClassDecl.nll"
		public: AccessLevel* m_pAccessLevel;
#line 8 "../../../Source/Core/AST/MemberClassDecl.nll"
		public: ClassDecl* m_pClassDecl;
#line 10 "../../../Source/Core/AST/MemberClassDecl.nll"
		public: MemberClassDecl();
#line 16 "../../../Source/Core/AST/MemberClassDecl.nll"
		public: static MemberClassDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl);
#line 44 "../../../Source/Core/AST/MemberClassDecl.nll"
		public: virtual void Validate(Validator* pValidator, OperatorExpr* pParent);
#line 49 "../../../Source/Core/AST/MemberClassDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

