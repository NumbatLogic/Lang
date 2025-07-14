#include "MemberEnumDecl.hpp"
#include "../OffsetDatum.hpp"
#include "AccessLevel.hpp"
#include "EnumDecl.hpp"
#include "AST.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class MemberEnumDecl;
	class OffsetDatum;
	class OffsetDatum;
	class AccessLevel;
	class AccessLevel;
	class EnumDecl;
	class EnumDecl;
	class MemberEnumDecl;
	class AST;
	class Util;
	class InternalString;
}
namespace NumbatLogic
{
	MemberEnumDecl::MemberEnumDecl()
	{
		m_pAccessLevel = 0;
		m_pEnumDecl = 0;
		m_bCanDescend = true;
	}

	MemberEnumDecl* MemberEnumDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		AccessLevel* pAccessLevel = AccessLevel::TryCreate(pTokenContainer, pTempOffset);
		if (pAccessLevel == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			return 0;
		}
		EnumDecl* pEnumDecl = EnumDecl::TryCreate(pTokenContainer, pTempOffset);
		if (pEnumDecl == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			if (pEnumDecl) delete pEnumDecl;
			return 0;
		}
		MemberEnumDecl* pMemberEnumDecl = new MemberEnumDecl();
		pMemberEnumDecl->m_eType = AST::Type::AST_MEMBER_ENUM_DECL;
		pMemberEnumDecl->m_pAccessLevel = pAccessLevel;
		pMemberEnumDecl->m_pEnumDecl = pEnumDecl;
		NumbatLogic::AccessLevel* __257201134 = pAccessLevel;
		pAccessLevel = 0;
		pMemberEnumDecl->AddChild(__257201134);
		NumbatLogic::EnumDecl* __2346898043 = pEnumDecl;
		pEnumDecl = 0;
		pMemberEnumDecl->AddChild(__2346898043);
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::MemberEnumDecl* __1876560565 = pMemberEnumDecl;
		pMemberEnumDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pAccessLevel) delete pAccessLevel;
		if (pEnumDecl) delete pEnumDecl;
		return __1876560565;
	}

	void MemberEnumDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
			return;
		Util::Pad(nDepth, sOut);
		m_pAccessLevel->Stringify(eLanguage, eOutputFile, 0, sOut);
		if (eLanguage == AST::Language::CPP)
			sOut->AppendChar(':');
		sOut->AppendChar(' ');
		m_pEnumDecl->Stringify(eLanguage, eOutputFile, nDepth, sOut);
		sOut->AppendChar('\n');
	}

}

