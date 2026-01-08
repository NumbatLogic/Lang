#include "MemberClassDecl.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "AccessLevel.hpp"
#include "ClassDecl.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class AccessLevel;
	class MemberClassDecl;
	class ClassDecl;
	class Util;
	class InternalString;
}
namespace NumbatLogic
{
	MemberClassDecl::MemberClassDecl()
	{
		m_pParentClassDecl = 0;
		m_pAccessLevel = 0;
		m_pClassDecl = 0;
		m_eType = AST::Type::AST_MEMBER_CLASS_DECL;
		m_bCanDescend = true;
	}

	MemberClassDecl* MemberClassDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		AccessLevel* pAccessLevel = AccessLevel::TryCreate(pTokenContainer, pTempOffset);
		if (pAccessLevel == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			return 0;
		}
		MemberClassDecl* pMemberClassDecl = new MemberClassDecl();
		pMemberClassDecl->m_pParentClassDecl = pParentClassDecl;
		pMemberClassDecl->m_pAccessLevel = pAccessLevel;
		pMemberClassDecl->m_pFirstToken = pAccessLevel->m_pFirstToken;
		ClassDecl* pClassDecl = ClassDecl::TryCreate(pTokenContainer, pTempOffset, pMemberClassDecl);
		if (pClassDecl == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			if (pMemberClassDecl) delete pMemberClassDecl;
			if (pClassDecl) delete pClassDecl;
			return 0;
		}
		NumbatLogic::AccessLevel* __98877649 = pAccessLevel;
		pAccessLevel = 0;
		pMemberClassDecl->AddChild(__98877649);
		pMemberClassDecl->m_pClassDecl = pClassDecl;
		NumbatLogic::ClassDecl* __3174337334 = pClassDecl;
		pClassDecl = 0;
		pMemberClassDecl->AddChild(__3174337334);
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::MemberClassDecl* __578676116 = pMemberClassDecl;
		pMemberClassDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pAccessLevel) delete pAccessLevel;
		if (pClassDecl) delete pClassDecl;
		return __578676116;
	}

	void MemberClassDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
	}

	void MemberClassDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		Util::Pad(nDepth, sOut);
		if (!(eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE))
		{
			m_pAccessLevel->Stringify(eLanguage, eOutputFile, 0, sOut);
			if (eLanguage == AST::Language::CPP)
				sOut->AppendChar(':');
			sOut->AppendChar(' ');
		}
		m_pClassDecl->Stringify(eLanguage, eOutputFile, nDepth, sOut);
	}

}

