#include "MemberEnumDecl.hpp"
#include "../OffsetDatum.hpp"
#include "AccessLevel.hpp"
#include "EnumDecl.hpp"
#include "AST.hpp"
#include "../OutputBuilder.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class AccessLevel;
	class EnumDecl;
	class MemberEnumDecl;
	class OutputBuilder;
	class Util;
	class InternalString;
}
#line 1 "../../../Source/Core/AST/MemberEnumDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/MemberEnumDecl.nll"
#line 9 "../../../Source/Core/AST/MemberEnumDecl.nll"
	MemberEnumDecl::MemberEnumDecl()
	{
		m_pAccessLevel = 0;
		m_pEnumDecl = 0;
#line 11 "../../../Source/Core/AST/MemberEnumDecl.nll"
		m_bCanDescend = true;
	}

#line 14 "../../../Source/Core/AST/MemberEnumDecl.nll"
	MemberEnumDecl* MemberEnumDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		AccessLevel* pAccessLevel = AccessLevel::TryCreate(pTokenContainer, pTempOffset);
#line 19 "../../../Source/Core/AST/MemberEnumDecl.nll"
		if (pAccessLevel == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
#line 20 "../../../Source/Core/AST/MemberEnumDecl.nll"
			return 0;
		}
		EnumDecl* pEnumDecl = EnumDecl::TryCreate(pTokenContainer, pTempOffset);
#line 23 "../../../Source/Core/AST/MemberEnumDecl.nll"
		if (pEnumDecl == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			if (pEnumDecl) delete pEnumDecl;
#line 24 "../../../Source/Core/AST/MemberEnumDecl.nll"
			return 0;
		}
		MemberEnumDecl* pMemberEnumDecl = new MemberEnumDecl();
#line 28 "../../../Source/Core/AST/MemberEnumDecl.nll"
		pMemberEnumDecl->m_eType = AST::Type::AST_MEMBER_ENUM_DECL;
#line 29 "../../../Source/Core/AST/MemberEnumDecl.nll"
		pMemberEnumDecl->m_pAccessLevel = pAccessLevel;
#line 30 "../../../Source/Core/AST/MemberEnumDecl.nll"
		pMemberEnumDecl->m_pEnumDecl = pEnumDecl;
#line 31 "../../../Source/Core/AST/MemberEnumDecl.nll"
		pMemberEnumDecl->m_pFirstToken = pMemberEnumDecl->m_pAccessLevel->m_pFirstToken;
		NumbatLogic::AccessLevel* __98877647 = pAccessLevel;
#line 33 "../../../Source/Core/AST/MemberEnumDecl.nll"
		pAccessLevel = 0;
#line 33 "../../../Source/Core/AST/MemberEnumDecl.nll"
		pMemberEnumDecl->AddChild(__98877647);
		NumbatLogic::EnumDecl* __4281946683 = pEnumDecl;
#line 34 "../../../Source/Core/AST/MemberEnumDecl.nll"
		pEnumDecl = 0;
#line 34 "../../../Source/Core/AST/MemberEnumDecl.nll"
		pMemberEnumDecl->AddChild(__4281946683);
#line 36 "../../../Source/Core/AST/MemberEnumDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::MemberEnumDecl* __645533336 = pMemberEnumDecl;
#line 37 "../../../Source/Core/AST/MemberEnumDecl.nll"
		pMemberEnumDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pAccessLevel) delete pAccessLevel;
		if (pEnumDecl) delete pEnumDecl;
#line 37 "../../../Source/Core/AST/MemberEnumDecl.nll"
		return __645533336;
	}

#line 40 "../../../Source/Core/AST/MemberEnumDecl.nll"
	void MemberEnumDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 42 "../../../Source/Core/AST/MemberEnumDecl.nll"
		if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
#line 43 "../../../Source/Core/AST/MemberEnumDecl.nll"
			return;
#line 45 "../../../Source/Core/AST/MemberEnumDecl.nll"
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 46 "../../../Source/Core/AST/MemberEnumDecl.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 48 "../../../Source/Core/AST/MemberEnumDecl.nll"
		m_pAccessLevel->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 49 "../../../Source/Core/AST/MemberEnumDecl.nll"
		if (eLanguage == AST::Language::CPP)
#line 50 "../../../Source/Core/AST/MemberEnumDecl.nll"
			pOutputBuilder->m_sOut->AppendChar(':');
#line 51 "../../../Source/Core/AST/MemberEnumDecl.nll"
		pOutputBuilder->m_sOut->AppendChar(' ');
#line 52 "../../../Source/Core/AST/MemberEnumDecl.nll"
		m_pEnumDecl->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 53 "../../../Source/Core/AST/MemberEnumDecl.nll"
		pOutputBuilder->m_sOut->AppendChar('\n');
	}

}

