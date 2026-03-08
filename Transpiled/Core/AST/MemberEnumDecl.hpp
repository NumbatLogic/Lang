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
		public: AccessLevel* m_pAccessLevel;
		public: EnumDecl* m_pEnumDecl;
		public: MemberEnumDecl();
		public: static MemberEnumDecl* TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum);
		public: virtual void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out);
	};
}

