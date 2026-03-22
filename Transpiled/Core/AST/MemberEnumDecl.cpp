#include "MemberEnumDecl.hpp"
#include "../OffsetDatum.hpp"
#include "AccessLevel.hpp"
#include "EnumDecl.hpp"
#include "AST.hpp"
#include "../OutputBuilder.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"

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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/MemberEnumDecl.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/MemberEnumDecl.nll"
#line 8 "/home/cliffya/git/Lang/Source/Core/AST/MemberEnumDecl.nll"
	MemberEnumDecl::MemberEnumDecl()
	{
		m_pAccessLevel = 0;
		m_pEnumDecl = 0;
#line 10 "/home/cliffya/git/Lang/Source/Core/AST/MemberEnumDecl.nll"
		m_bCanDescend = true;
	}

	MemberEnumDecl* MemberEnumDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/MemberEnumDecl.nll"
		AccessLevel* pAccessLevel = AccessLevel::TryCreate(pTokenContainer, pTempOffset);
		if (pAccessLevel == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/MemberEnumDecl.nll"
			return 0;
		}
		EnumDecl* pEnumDecl = EnumDecl::TryCreate(pTokenContainer, pTempOffset);
		if (pEnumDecl == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			if (pEnumDecl) delete pEnumDecl;
#line 23 "/home/cliffya/git/Lang/Source/Core/AST/MemberEnumDecl.nll"
			return 0;
		}
		MemberEnumDecl* pMemberEnumDecl = new MemberEnumDecl();
#line 27 "/home/cliffya/git/Lang/Source/Core/AST/MemberEnumDecl.nll"
		pMemberEnumDecl->m_eType = AST::Type::AST_MEMBER_ENUM_DECL;
		pMemberEnumDecl->m_pAccessLevel = pAccessLevel;
		pMemberEnumDecl->m_pEnumDecl = pEnumDecl;
		pMemberEnumDecl->m_pFirstToken = pMemberEnumDecl->m_pAccessLevel->m_pFirstToken;
		NumbatLogic::AccessLevel* __98877647 = pAccessLevel;
		pAccessLevel = 0;
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/MemberEnumDecl.nll"
		pMemberEnumDecl->AddChild(__98877647);
		NumbatLogic::EnumDecl* __4281946683 = pEnumDecl;
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/MemberEnumDecl.nll"
		pEnumDecl = 0;
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/MemberEnumDecl.nll"
		pMemberEnumDecl->AddChild(__4281946683);
#line 35 "/home/cliffya/git/Lang/Source/Core/AST/MemberEnumDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::MemberEnumDecl* __645533336 = pMemberEnumDecl;
#line 36 "/home/cliffya/git/Lang/Source/Core/AST/MemberEnumDecl.nll"
		pMemberEnumDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pAccessLevel) delete pAccessLevel;
		if (pEnumDecl) delete pEnumDecl;
#line 36 "/home/cliffya/git/Lang/Source/Core/AST/MemberEnumDecl.nll"
		return __645533336;
	}

	void MemberEnumDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
			return;
#line 44 "/home/cliffya/git/Lang/Source/Core/AST/MemberEnumDecl.nll"
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 47 "/home/cliffya/git/Lang/Source/Core/AST/MemberEnumDecl.nll"
		m_pAccessLevel->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		if (eLanguage == AST::Language::CPP)
			pOutputBuilder->m_sOut->AppendChar(':');
		pOutputBuilder->m_sOut->AppendChar(' ');
		m_pEnumDecl->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
		pOutputBuilder->m_sOut->AppendChar('\n');
	}

}

