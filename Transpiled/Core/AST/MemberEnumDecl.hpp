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
#line 0 "../../../Source/Core/AST/MemberEnumDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/MemberEnumDecl.nll"
	class MemberEnumDecl : public AST
	{
#line 5 "../../../Source/Core/AST/MemberEnumDecl.nll"
		public: AccessLevel* m_pAccessLevel;
#line 6 "../../../Source/Core/AST/MemberEnumDecl.nll"
		public: EnumDecl* m_pEnumDecl;
#line 8 "../../../Source/Core/AST/MemberEnumDecl.nll"
		public: MemberEnumDecl();
#line 13 "../../../Source/Core/AST/MemberEnumDecl.nll"
		public: static MemberEnumDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 39 "../../../Source/Core/AST/MemberEnumDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

