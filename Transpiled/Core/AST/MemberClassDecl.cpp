#include "MemberClassDecl.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "AccessLevel.hpp"
#include "ClassDecl.hpp"
#include "../OutputBuilder.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class AccessLevel;
	class MemberClassDecl;
	class ClassDecl;
	class OutputBuilder;
	class Util;
	class InternalString;
}
#line 0 "../../../Source/Core/AST/MemberClassDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/MemberClassDecl.nll"
#line 9 "../../../Source/Core/AST/MemberClassDecl.nll"
	MemberClassDecl::MemberClassDecl()
	{
		m_pParentClassDecl = 0;
		m_pAccessLevel = 0;
		m_pClassDecl = 0;
#line 11 "../../../Source/Core/AST/MemberClassDecl.nll"
		m_eType = AST::Type::AST_MEMBER_CLASS_DECL;
#line 12 "../../../Source/Core/AST/MemberClassDecl.nll"
		m_bCanDescend = true;
	}

#line 15 "../../../Source/Core/AST/MemberClassDecl.nll"
	MemberClassDecl* MemberClassDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl)
	{
#line 17 "../../../Source/Core/AST/MemberClassDecl.nll"
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 19 "../../../Source/Core/AST/MemberClassDecl.nll"
		AccessLevel* pAccessLevel = AccessLevel::TryCreate(pTokenContainer, pTempOffset);
#line 20 "../../../Source/Core/AST/MemberClassDecl.nll"
		if (pAccessLevel == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
#line 21 "../../../Source/Core/AST/MemberClassDecl.nll"
			return 0;
		}
#line 23 "../../../Source/Core/AST/MemberClassDecl.nll"
		MemberClassDecl* pMemberClassDecl = new MemberClassDecl();
#line 25 "../../../Source/Core/AST/MemberClassDecl.nll"
		pMemberClassDecl->m_pParentClassDecl = pParentClassDecl;
#line 26 "../../../Source/Core/AST/MemberClassDecl.nll"
		pMemberClassDecl->m_pAccessLevel = pAccessLevel;
#line 27 "../../../Source/Core/AST/MemberClassDecl.nll"
		pMemberClassDecl->m_pFirstToken = pAccessLevel->m_pFirstToken;
#line 30 "../../../Source/Core/AST/MemberClassDecl.nll"
		ClassDecl* pClassDecl = ClassDecl::TryCreate(pTokenContainer, pTempOffset, pMemberClassDecl);
#line 31 "../../../Source/Core/AST/MemberClassDecl.nll"
		if (pClassDecl == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			if (pMemberClassDecl) delete pMemberClassDecl;
			if (pClassDecl) delete pClassDecl;
#line 32 "../../../Source/Core/AST/MemberClassDecl.nll"
			return 0;
		}
		NumbatLogic::AccessLevel* __98877649 = pAccessLevel;
#line 34 "../../../Source/Core/AST/MemberClassDecl.nll"
		pAccessLevel = 0;
#line 34 "../../../Source/Core/AST/MemberClassDecl.nll"
		pMemberClassDecl->AddChild(__98877649);
#line 36 "../../../Source/Core/AST/MemberClassDecl.nll"
		pMemberClassDecl->m_pClassDecl = pClassDecl;
		NumbatLogic::ClassDecl* __3174337334 = pClassDecl;
#line 37 "../../../Source/Core/AST/MemberClassDecl.nll"
		pClassDecl = 0;
#line 37 "../../../Source/Core/AST/MemberClassDecl.nll"
		pMemberClassDecl->AddChild(__3174337334);
#line 39 "../../../Source/Core/AST/MemberClassDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::MemberClassDecl* __578676116 = pMemberClassDecl;
#line 40 "../../../Source/Core/AST/MemberClassDecl.nll"
		pMemberClassDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pAccessLevel) delete pAccessLevel;
		if (pClassDecl) delete pClassDecl;
#line 40 "../../../Source/Core/AST/MemberClassDecl.nll"
		return __578676116;
	}

#line 43 "../../../Source/Core/AST/MemberClassDecl.nll"
	void MemberClassDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 45 "../../../Source/Core/AST/MemberClassDecl.nll"
		AST::Validate(pValidator, pParent);
	}

#line 48 "../../../Source/Core/AST/MemberClassDecl.nll"
	void MemberClassDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 62 "../../../Source/Core/AST/MemberClassDecl.nll"
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 63 "../../../Source/Core/AST/MemberClassDecl.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 65 "../../../Source/Core/AST/MemberClassDecl.nll"
		if (!(eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE))
		{
#line 67 "../../../Source/Core/AST/MemberClassDecl.nll"
			m_pAccessLevel->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 69 "../../../Source/Core/AST/MemberClassDecl.nll"
			if (eLanguage == AST::Language::CPP)
#line 70 "../../../Source/Core/AST/MemberClassDecl.nll"
				pOutputBuilder->m_sOut->AppendChar(':');
#line 72 "../../../Source/Core/AST/MemberClassDecl.nll"
			pOutputBuilder->m_sOut->AppendChar(' ');
		}
#line 75 "../../../Source/Core/AST/MemberClassDecl.nll"
		m_pClassDecl->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
	}

}

