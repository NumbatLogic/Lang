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
#include "../Util.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
	class AccessLevel;
	class Token;
	class TokenContainer;
	class VarDecl;
	class MemberVarDecl;
	class AST;
	class InternalString;
	class TypeRef;
	class Validator;
	class Util;
}
namespace NumbatLogic
{
	MemberVarDecl::MemberVarDecl()
	{
		m_pAccessLevel = 0;
		m_bStatic = false;
		m_pVarDecl = 0;
		m_bCanDescend = true;
	}

	MemberVarDecl* MemberVarDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		bool bStatic = false;
		AccessLevel* pAccessLevel = AccessLevel::TryCreate(pTokenContainer, pTempOffset);
		if (pAccessLevel == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			return 0;
		}
		Token* pStaticToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_STATIC);
		if (pStaticToken != 0)
		{
			bStatic = true;
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		}
		VarDecl* pVarDecl = VarDecl::TryCreate(pTokenContainer, pTempOffset, false);
		if (pVarDecl == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			if (pVarDecl) delete pVarDecl;
			return 0;
		}
		MemberVarDecl* pMemberVarDecl = new MemberVarDecl();
		pMemberVarDecl->m_eType = AST::Type::AST_MEMBER_VAR_DECL;
		pMemberVarDecl->m_pAccessLevel = pAccessLevel;
		pMemberVarDecl->m_bStatic = bStatic;
		pMemberVarDecl->m_pVarDecl = pVarDecl;
		NumbatLogic::AccessLevel* __1431588250 = pAccessLevel;
		pAccessLevel = 0;
		pMemberVarDecl->AddChild(__1431588250);
		NumbatLogic::VarDecl* __1710550748 = pVarDecl;
		pVarDecl = 0;
		pMemberVarDecl->AddChild(__1710550748);
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::MemberVarDecl* __3049868366 = pMemberVarDecl;
		pMemberVarDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pAccessLevel) delete pAccessLevel;
		if (pVarDecl) delete pVarDecl;
		return __3049868366;
	}

	void MemberVarDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		InternalString* sTemp = new InternalString(m_pVarDecl->m_pNameToken->GetString());
		if (!sTemp->StartsWith("m_") && !m_pVarDecl->m_pTypeRef->m_bConst)
		{
			pValidator->AddError("Member var name does not start with \"m_\"", m_pVarDecl->m_pNameToken->m_sFileName, m_pVarDecl->m_pNameToken->m_nLine, m_pVarDecl->m_pNameToken->m_nColumn);
		}
		if (sTemp) delete sTemp;
	}

	void MemberVarDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		bool bArrayAssignment = m_pVarDecl->m_pArraySize != 0 && m_pVarDecl->m_pAssignment != 0;
		if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
		{
			bool bDoIt = false;
			if (bArrayAssignment)
				bDoIt = true;
			if (m_bStatic && !m_pVarDecl->m_pTypeRef->IsIntegral())
				bDoIt = true;
			if (!bDoIt)
				return;
		}
		Util::Pad(nDepth, sOut);
		if (!(eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE))
		{
			m_pAccessLevel->Stringify(eLanguage, eOutputFile, 0, sOut);
			if (eLanguage == AST::Language::CPP)
				sOut->AppendChar(':');
			sOut->AppendChar(' ');
			if (m_bStatic)
			{
				if (eLanguage == AST::Language::CS)
				{
					if (m_pVarDecl->m_pTypeRef->m_bConst == false || m_pVarDecl->m_pArraySize != 0)
						sOut->AppendString("static ");
				}
				else
				{
					sOut->AppendString("static ");
				}
			}
		}
		m_pVarDecl->Stringify(eLanguage, eOutputFile, 0, sOut);
	}

}

