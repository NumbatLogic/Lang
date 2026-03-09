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
#line 1 "../../../Source/Core/AST/MemberClassDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/MemberClassDecl.nll"
#line 10 "../../../Source/Core/AST/MemberClassDecl.nll"
	MemberClassDecl::MemberClassDecl()
	{
		m_pParentClassDecl = 0;
		m_pAccessLevel = 0;
		m_pClassDecl = 0;
#line 12 "../../../Source/Core/AST/MemberClassDecl.nll"
		m_eType = AST::Type::AST_MEMBER_CLASS_DECL;
#line 13 "../../../Source/Core/AST/MemberClassDecl.nll"
		m_bCanDescend = true;
	}

#line 16 "../../../Source/Core/AST/MemberClassDecl.nll"
	MemberClassDecl* MemberClassDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		AccessLevel* pAccessLevel = AccessLevel::TryCreate(pTokenContainer, pTempOffset);
#line 21 "../../../Source/Core/AST/MemberClassDecl.nll"
		if (pAccessLevel == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
#line 22 "../../../Source/Core/AST/MemberClassDecl.nll"
			return 0;
		}
		MemberClassDecl* pMemberClassDecl = new MemberClassDecl();
#line 26 "../../../Source/Core/AST/MemberClassDecl.nll"
		pMemberClassDecl->m_pParentClassDecl = pParentClassDecl;
#line 27 "../../../Source/Core/AST/MemberClassDecl.nll"
		pMemberClassDecl->m_pAccessLevel = pAccessLevel;
#line 28 "../../../Source/Core/AST/MemberClassDecl.nll"
		pMemberClassDecl->m_pFirstToken = pAccessLevel->m_pFirstToken;
		ClassDecl* pClassDecl = ClassDecl::TryCreate(pTokenContainer, pTempOffset, pMemberClassDecl);
#line 32 "../../../Source/Core/AST/MemberClassDecl.nll"
		if (pClassDecl == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			if (pMemberClassDecl) delete pMemberClassDecl;
			if (pClassDecl) delete pClassDecl;
#line 33 "../../../Source/Core/AST/MemberClassDecl.nll"
			return 0;
		}
		NumbatLogic::AccessLevel* __98877649 = pAccessLevel;
#line 35 "../../../Source/Core/AST/MemberClassDecl.nll"
		pAccessLevel = 0;
#line 35 "../../../Source/Core/AST/MemberClassDecl.nll"
		pMemberClassDecl->AddChild(__98877649);
#line 37 "../../../Source/Core/AST/MemberClassDecl.nll"
		pMemberClassDecl->m_pClassDecl = pClassDecl;
		NumbatLogic::ClassDecl* __3174337334 = pClassDecl;
#line 38 "../../../Source/Core/AST/MemberClassDecl.nll"
		pClassDecl = 0;
#line 38 "../../../Source/Core/AST/MemberClassDecl.nll"
		pMemberClassDecl->AddChild(__3174337334);
#line 40 "../../../Source/Core/AST/MemberClassDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::MemberClassDecl* __578676116 = pMemberClassDecl;
#line 41 "../../../Source/Core/AST/MemberClassDecl.nll"
		pMemberClassDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pAccessLevel) delete pAccessLevel;
		if (pClassDecl) delete pClassDecl;
#line 41 "../../../Source/Core/AST/MemberClassDecl.nll"
		return __578676116;
	}

#line 44 "../../../Source/Core/AST/MemberClassDecl.nll"
	void MemberClassDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 46 "../../../Source/Core/AST/MemberClassDecl.nll"
		AST::Validate(pValidator, pParent);
	}

#line 49 "../../../Source/Core/AST/MemberClassDecl.nll"
	void MemberClassDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 63 "../../../Source/Core/AST/MemberClassDecl.nll"
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 64 "../../../Source/Core/AST/MemberClassDecl.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 66 "../../../Source/Core/AST/MemberClassDecl.nll"
		if (!(eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE))
		{
#line 68 "../../../Source/Core/AST/MemberClassDecl.nll"
			m_pAccessLevel->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 70 "../../../Source/Core/AST/MemberClassDecl.nll"
			if (eLanguage == AST::Language::CPP)
#line 71 "../../../Source/Core/AST/MemberClassDecl.nll"
				pOutputBuilder->m_sOut->AppendChar(':');
#line 73 "../../../Source/Core/AST/MemberClassDecl.nll"
			pOutputBuilder->m_sOut->AppendChar(' ');
		}
#line 76 "../../../Source/Core/AST/MemberClassDecl.nll"
		m_pClassDecl->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
	}

}

