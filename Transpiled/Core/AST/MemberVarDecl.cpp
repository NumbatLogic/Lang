#include "MemberVarDecl.hpp"
#include "../OffsetDatum.hpp"
#include "AccessLevel.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "VarDecl.hpp"
#include "AST.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
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
#line 1 "../../../Source/Core/AST/MemberVarDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/MemberVarDecl.nll"
#line 10 "../../../Source/Core/AST/MemberVarDecl.nll"
	MemberVarDecl::MemberVarDecl()
	{
		m_pAccessLevel = 0;
		m_bStatic = false;
		m_pVarDecl = 0;
#line 12 "../../../Source/Core/AST/MemberVarDecl.nll"
		m_bCanDescend = true;
	}

#line 15 "../../../Source/Core/AST/MemberVarDecl.nll"
	MemberVarDecl* MemberVarDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		bool bStatic = false;
		AccessLevel* pAccessLevel = AccessLevel::TryCreate(pTokenContainer, pTempOffset);
#line 22 "../../../Source/Core/AST/MemberVarDecl.nll"
		if (pAccessLevel == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
#line 23 "../../../Source/Core/AST/MemberVarDecl.nll"
			return 0;
		}
		Token* pStaticToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_STATIC);
#line 26 "../../../Source/Core/AST/MemberVarDecl.nll"
		if (pStaticToken != 0)
		{
#line 28 "../../../Source/Core/AST/MemberVarDecl.nll"
			bStatic = true;
#line 29 "../../../Source/Core/AST/MemberVarDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		}
		VarDecl* pVarDecl = VarDecl::TryCreate(pTokenContainer, pTempOffset, false);
#line 33 "../../../Source/Core/AST/MemberVarDecl.nll"
		if (pVarDecl == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			if (pVarDecl) delete pVarDecl;
#line 34 "../../../Source/Core/AST/MemberVarDecl.nll"
			return 0;
		}
		MemberVarDecl* pMemberVarDecl = new MemberVarDecl();
#line 38 "../../../Source/Core/AST/MemberVarDecl.nll"
		pMemberVarDecl->m_eType = AST::Type::AST_MEMBER_VAR_DECL;
#line 39 "../../../Source/Core/AST/MemberVarDecl.nll"
		pMemberVarDecl->m_pAccessLevel = pAccessLevel;
#line 40 "../../../Source/Core/AST/MemberVarDecl.nll"
		pMemberVarDecl->m_bStatic = bStatic;
#line 41 "../../../Source/Core/AST/MemberVarDecl.nll"
		pMemberVarDecl->m_pVarDecl = pVarDecl;
		NumbatLogic::AccessLevel* __98943246 = pAccessLevel;
#line 43 "../../../Source/Core/AST/MemberVarDecl.nll"
		pAccessLevel = 0;
#line 43 "../../../Source/Core/AST/MemberVarDecl.nll"
		pMemberVarDecl->AddChild(__98943246);
		NumbatLogic::VarDecl* __2365456416 = pVarDecl;
#line 44 "../../../Source/Core/AST/MemberVarDecl.nll"
		pVarDecl = 0;
#line 44 "../../../Source/Core/AST/MemberVarDecl.nll"
		pMemberVarDecl->AddChild(__2365456416);
#line 46 "../../../Source/Core/AST/MemberVarDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::MemberVarDecl* __4110847305 = pMemberVarDecl;
#line 47 "../../../Source/Core/AST/MemberVarDecl.nll"
		pMemberVarDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pAccessLevel) delete pAccessLevel;
		if (pVarDecl) delete pVarDecl;
#line 47 "../../../Source/Core/AST/MemberVarDecl.nll"
		return __4110847305;
	}

#line 50 "../../../Source/Core/AST/MemberVarDecl.nll"
	void MemberVarDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 52 "../../../Source/Core/AST/MemberVarDecl.nll"
		AST::Validate(pValidator, pParent);
		InternalString* sTemp = new InternalString(m_pVarDecl->m_pNameToken->GetString());
#line 55 "../../../Source/Core/AST/MemberVarDecl.nll"
		if (!(sTemp->StartsWith("m_") || sTemp->StartsWith("__")) && !m_pVarDecl->m_pTypeRef->m_bConst)
		{
#line 57 "../../../Source/Core/AST/MemberVarDecl.nll"
			pValidator->AddError("Member var name does not start with \"m_\"", m_pVarDecl->m_pNameToken->m_sFileName, m_pVarDecl->m_pNameToken->m_nLine, m_pVarDecl->m_pNameToken->m_nColumn);
		}
		if (sTemp) delete sTemp;
	}

#line 61 "../../../Source/Core/AST/MemberVarDecl.nll"
	void MemberVarDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		bool bArrayAssignment = m_pVarDecl->m_pArraySizeVector != 0 && m_pVarDecl->m_pAssignment != 0;
#line 68 "../../../Source/Core/AST/MemberVarDecl.nll"
		if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
		{
			bool bDoIt = false;
#line 71 "../../../Source/Core/AST/MemberVarDecl.nll"
			if (bArrayAssignment)
#line 72 "../../../Source/Core/AST/MemberVarDecl.nll"
				bDoIt = true;
#line 75 "../../../Source/Core/AST/MemberVarDecl.nll"
			if (m_bStatic && !(m_pVarDecl->m_pTypeRef->m_bConst && m_pVarDecl->m_pTypeRef->IsIntegral()))
#line 76 "../../../Source/Core/AST/MemberVarDecl.nll"
				bDoIt = true;
#line 78 "../../../Source/Core/AST/MemberVarDecl.nll"
			if (!bDoIt)
#line 79 "../../../Source/Core/AST/MemberVarDecl.nll"
				return;
		}
#line 83 "../../../Source/Core/AST/MemberVarDecl.nll"
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pVarDecl->m_pFirstToken);
#line 84 "../../../Source/Core/AST/MemberVarDecl.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 86 "../../../Source/Core/AST/MemberVarDecl.nll"
		if (!(eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE))
		{
#line 88 "../../../Source/Core/AST/MemberVarDecl.nll"
			m_pAccessLevel->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 89 "../../../Source/Core/AST/MemberVarDecl.nll"
			if (eLanguage == AST::Language::CPP)
#line 90 "../../../Source/Core/AST/MemberVarDecl.nll"
				pOutputBuilder->m_sOut->AppendChar(':');
#line 91 "../../../Source/Core/AST/MemberVarDecl.nll"
			pOutputBuilder->m_sOut->AppendChar(' ');
#line 93 "../../../Source/Core/AST/MemberVarDecl.nll"
			if (m_bStatic)
			{
#line 95 "../../../Source/Core/AST/MemberVarDecl.nll"
				if (eLanguage == AST::Language::CS)
				{
#line 97 "../../../Source/Core/AST/MemberVarDecl.nll"
					if (m_pVarDecl->m_pTypeRef->m_bConst == false || !m_pVarDecl->m_pTypeRef->IsIntegral() || m_pVarDecl->m_pArraySizeVector != 0)
#line 98 "../../../Source/Core/AST/MemberVarDecl.nll"
						pOutputBuilder->m_sOut->AppendString("static ");
				}
				else
				{
#line 102 "../../../Source/Core/AST/MemberVarDecl.nll"
					pOutputBuilder->m_sOut->AppendString("static ");
				}
			}
		}
#line 108 "../../../Source/Core/AST/MemberVarDecl.nll"
		m_pVarDecl->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
	}

}

