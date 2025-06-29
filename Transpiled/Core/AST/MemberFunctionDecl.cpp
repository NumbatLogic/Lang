#include "MemberFunctionDecl.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "AccessLevel.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "ClassDecl.hpp"
#include "FunctionDecl.hpp"
#include "../../LangShared/Vector/OwnedVector.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
	class AccessLevel;
	class Token;
	class MemberFunctionDecl;
	class FunctionDecl;
}
namespace NumbatLogic
{
	MemberFunctionDecl::MemberFunctionDecl()
	{
		m_pParentClassDecl = 0;
		m_pAccessLevel = 0;
		m_pFunctionDecl = 0;
		m_bStatic = false;
		m_bVirtual = false;
		m_bOverride = false;
		m_eType = AST::Type::AST_MEMBER_FUNCTION_DECL;
		m_bCanDescend = true;
	}

	MemberFunctionDecl* MemberFunctionDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		AccessLevel* pAccessLevel = AccessLevel::TryCreate(pTokenContainer, pTempOffset);
		if (pAccessLevel == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			return 0;
		}
		bool bStatic = false;
		bool bVirtual = false;
		bool bOverride = false;
		Token* pToken = pTokenContainer->Peek(pTempOffset);
		if (pToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			return 0;
		}
		switch (pToken->m_eType)
		{
			case Token::Type::TOKEN_KEYWORD_STATIC:
			{
				bStatic = true;
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				break;
			}

			case Token::Type::TOKEN_KEYWORD_VIRTUAL:
			{
				bVirtual = true;
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				break;
			}

			case Token::Type::TOKEN_KEYWORD_OVERRIDE:
			{
				bOverride = true;
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				break;
			}

		}
		MemberFunctionDecl* pMemberFunctionDecl = new MemberFunctionDecl();
		pMemberFunctionDecl->m_pParent = pParentClassDecl;
		pMemberFunctionDecl->m_pParentClassDecl = pParentClassDecl;
		pMemberFunctionDecl->m_pAccessLevel = pAccessLevel;
		pMemberFunctionDecl->m_pFirstToken = pAccessLevel->m_pFirstToken;
		pMemberFunctionDecl->m_bStatic = bStatic;
		pMemberFunctionDecl->m_bVirtual = bVirtual;
		pMemberFunctionDecl->m_bOverride = bOverride;
		FunctionDecl* pFunctionDecl = FunctionDecl::TryCreate(pTokenContainer, pTempOffset, pMemberFunctionDecl);
		if (pFunctionDecl == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			if (pMemberFunctionDecl) delete pMemberFunctionDecl;
			if (pFunctionDecl) delete pFunctionDecl;
			return 0;
		}
		NumbatLogic::AccessLevel* __2194276919 = pAccessLevel;
		pAccessLevel = 0;
		pMemberFunctionDecl->AddChild(__2194276919);
		pMemberFunctionDecl->m_pFunctionDecl = pFunctionDecl;
		NumbatLogic::FunctionDecl* __549451023 = pFunctionDecl;
		pFunctionDecl = 0;
		pMemberFunctionDecl->AddChild(__549451023);
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::MemberFunctionDecl* __635718084 = pMemberFunctionDecl;
		pMemberFunctionDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pAccessLevel) delete pAccessLevel;
		if (pFunctionDecl) delete pFunctionDecl;
		return __635718084;
	}

	void MemberFunctionDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
	}

	void MemberFunctionDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
		{
			if (m_pParentClassDecl->m_pGenericTypeDeclVector->GetSize() > 0)
			{
			}
		}
		Util::Pad(nDepth, sOut);
		if (!(eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE))
		{
			m_pAccessLevel->Stringify(eLanguage, eOutputFile, 0, sOut);
			if (eLanguage == AST::Language::CPP)
				sOut->AppendChar(':');
			if (m_bStatic)
				sOut->Append(" static");
			if (m_bVirtual)
				sOut->Append(" virtual");
			if (m_bOverride)
				if (eLanguage == AST::Language::CPP)
					sOut->Append(" virtual");
				else
					sOut->Append(" override");
			sOut->AppendChar(' ');
		}
		m_pFunctionDecl->Stringify(eLanguage, eOutputFile, nDepth, sOut);
	}

}

