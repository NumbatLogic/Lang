#include "MemberEnumDecl.hpp"
#include "../OffsetDatum.hpp"
#include "AccessLevel.hpp"
#include "EnumDecl.hpp"
#include "AST.hpp"
#include "../Util.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class AccessLevel;
	class EnumDecl;
	class MemberEnumDecl;
	class Util;
	class OutputBuilder;
	class InternalString;
}
#line 0 "../../../Source/Core/AST/MemberEnumDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/MemberEnumDecl.nll"
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
		NumbatLogic::AccessLevel* __98877646 = pAccessLevel;
		pAccessLevel = 0;
		pMemberEnumDecl->AddChild(__98877646);
		NumbatLogic::EnumDecl* __4281946682 = pEnumDecl;
		pEnumDecl = 0;
		pMemberEnumDecl->AddChild(__4281946682);
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::MemberEnumDecl* __645533335 = pMemberEnumDecl;
		pMemberEnumDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pAccessLevel) delete pAccessLevel;
		if (pEnumDecl) delete pEnumDecl;
		return __645533335;
	}

	void MemberEnumDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out)
	{
		if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
			return;
		Util::Pad(nDepth, out->m_sOut);
		m_pAccessLevel->Stringify(eLanguage, eOutputFile, 0, out);
		if (eLanguage == AST::Language::CPP)
			out->m_sOut->AppendChar(':');
		out->m_sOut->AppendChar(' ');
		m_pEnumDecl->Stringify(eLanguage, eOutputFile, nDepth, out);
		out->m_sOut->AppendChar('\n');
	}

}

