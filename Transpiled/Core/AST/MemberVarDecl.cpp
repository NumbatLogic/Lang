#include "MemberVarDecl.hpp"
#include "../OffsetDatum.hpp"
#include "AccessLevel.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "VarDecl.hpp"
#include "AST.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"
#include "TypeRef.hpp"
#include "../Validator.hpp"
#include "../OutputBuilder.hpp"
#include "../Util.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class AccessLevel;
	class Token;
	class TokenContainer;
	class VarDecl;
	class MemberVarDecl;
	class InternalString;
	class TypeRef;
	class Validator;
	class OutputBuilder;
	class Util;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
#line 9 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
	MemberVarDecl::MemberVarDecl()
	{
		m_pAccessLevel = 0;
		m_bStatic = false;
		m_pVarDecl = 0;
#line 11 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
		m_bCanDescend = true;
	}

	MemberVarDecl* MemberVarDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 18 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
		bool bStatic = false;
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
		AccessLevel* pAccessLevel = AccessLevel::TryCreate(pTokenContainer, pTempOffset);
		if (pAccessLevel == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
			return 0;
		}
		Token* pStaticToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_STATIC);
		if (pStaticToken != 0)
		{
			bStatic = true;
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		}
#line 31 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
		VarDecl* pVarDecl = VarDecl::TryCreate(pTokenContainer, pTempOffset, false);
		if (pVarDecl == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			if (pVarDecl) delete pVarDecl;
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
			return 0;
		}
		MemberVarDecl* pMemberVarDecl = new MemberVarDecl();
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
		pMemberVarDecl->m_eType = AST::Type::AST_MEMBER_VAR_DECL;
		pMemberVarDecl->m_pAccessLevel = pAccessLevel;
		pMemberVarDecl->m_bStatic = bStatic;
		pMemberVarDecl->m_pVarDecl = pVarDecl;
		NumbatLogic::AccessLevel* __98943246 = pAccessLevel;
		pAccessLevel = 0;
#line 42 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
		pMemberVarDecl->AddChild(__98943246);
		NumbatLogic::VarDecl* __2365456416 = pVarDecl;
#line 43 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
		pVarDecl = 0;
#line 43 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
		pMemberVarDecl->AddChild(__2365456416);
#line 45 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::MemberVarDecl* __4110847305 = pMemberVarDecl;
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
		pMemberVarDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pAccessLevel) delete pAccessLevel;
		if (pVarDecl) delete pVarDecl;
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
		return __4110847305;
	}

	void MemberVarDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
#line 53 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
		InternalString* sTemp = new InternalString(m_pVarDecl->m_pNameToken->GetString());
		if (!(sTemp->StartsWith("m_") || sTemp->StartsWith("__")) && !m_pVarDecl->m_pTypeRef->m_bConst)
		{
			pValidator->AddError("Member var name does not start with \"m_\"", m_pVarDecl->m_pNameToken->m_sFileName, m_pVarDecl->m_pNameToken->m_nLine, m_pVarDecl->m_pNameToken->m_nColumn);
		}
		if (sTemp) delete sTemp;
	}

#line 60 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
	void MemberVarDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		bool bArrayAssignment = m_pVarDecl->m_pArraySizeVector != 0 && m_pVarDecl->m_pAssignment != 0;
#line 67 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
		if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
		{
			bool bDoIt = false;
			if (bArrayAssignment)
				bDoIt = true;
#line 74 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
			if (m_bStatic && !(m_pVarDecl->m_pTypeRef->m_bConst && m_pVarDecl->m_pTypeRef->IsIntegral()))
				bDoIt = true;
#line 77 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
			if (!bDoIt)
				return;
		}
#line 82 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pVarDecl->m_pFirstToken);
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 85 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
		if (!(eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE))
		{
			m_pAccessLevel->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			if (eLanguage == AST::Language::CPP)
				pOutputBuilder->m_sOut->AppendChar(':');
			pOutputBuilder->m_sOut->AppendChar(' ');
#line 92 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
			if (m_bStatic)
			{
				if (eLanguage == AST::Language::CS)
				{
					if (m_pVarDecl->m_pTypeRef->m_bConst == false || !m_pVarDecl->m_pTypeRef->IsIntegral() || m_pVarDecl->m_pArraySizeVector != 0)
						pOutputBuilder->m_sOut->AppendString("static ");
				}
				else
				{
					pOutputBuilder->m_sOut->AppendString("static ");
				}
			}
		}
#line 107 "/home/cliffya/git/Lang/Source/Core/AST/MemberVarDecl.nll"
		m_pVarDecl->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
	}

}

