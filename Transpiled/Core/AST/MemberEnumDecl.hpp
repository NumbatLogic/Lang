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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/MemberEnumDecl.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/MemberEnumDecl.nll"
	class MemberEnumDecl : public AST
	{
		public: AccessLevel* m_pAccessLevel;
		public: EnumDecl* m_pEnumDecl;
#line 8 "/home/cliffya/git/Lang/Source/Core/AST/MemberEnumDecl.nll"
		public: MemberEnumDecl();
#line 13 "/home/cliffya/git/Lang/Source/Core/AST/MemberEnumDecl.nll"
		public: static MemberEnumDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
#line 39 "/home/cliffya/git/Lang/Source/Core/AST/MemberEnumDecl.nll"
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder);
	};
}

