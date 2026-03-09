#pragma once

#include "AST.hpp"

namespace NumbatLogic
{
	class AST;
	class AccessLevel;
	class EnumDecl;
	class MemberEnumDecl;
	class TokenContainer;
	class OffsetDatum;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/MemberEnumDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/MemberEnumDecl.nll"
	class MemberEnumDecl : public AST
	{
#line 6 "../../../Source/Core/AST/MemberEnumDecl.nll"
		public: AccessLevel* m_pAccessLevel;
#line 7 "../../../Source/Core/AST/MemberEnumDecl.nll"
		public: EnumDecl* m_pEnumDecl;
#line 9 "../../../Source/Core/AST/MemberEnumDecl.nll"
		public: MemberEnumDecl();
#line 14 "../../../Source/Core/AST/MemberEnumDecl.nll"
		public: static MemberEnumDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 40 "../../../Source/Core/AST/MemberEnumDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

