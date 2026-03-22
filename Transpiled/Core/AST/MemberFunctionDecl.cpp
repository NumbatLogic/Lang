#include "MemberFunctionDecl.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "AccessLevel.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "ClassDecl.hpp"
#include "FunctionDecl.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "../OutputBuilder.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class AccessLevel;
	class Token;
	class TokenContainer;
	class MemberFunctionDecl;
	class ClassDecl;
	class FunctionDecl;
	template <class T>
	class OwnedVector;
	class OutputBuilder;
	class Util;
	class InternalString;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
#line 12 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
	MemberFunctionDecl::MemberFunctionDecl()
	{
		m_pParentClassDecl = 0;
		m_pAccessLevel = 0;
		m_pFunctionDecl = 0;
		m_bStatic = false;
		m_bVirtual = false;
		m_bOverride = false;
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
		m_eType = AST::Type::AST_MEMBER_FUNCTION_DECL;
		m_bCanDescend = true;
	}

	MemberFunctionDecl* MemberFunctionDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
		AccessLevel* pAccessLevel = AccessLevel::TryCreate(pTokenContainer, pTempOffset);
		if (pAccessLevel == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
#line 24 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
			return 0;
		}
		bool bStatic = false;
		bool bVirtual = false;
		bool bOverride = false;
#line 30 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
		Token* pToken = pTokenContainer->Peek(pTempOffset);
		if (pToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
			return 0;
		}
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
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
#line 43 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
				bVirtual = true;
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				break;
			}

			case Token::Type::TOKEN_KEYWORD_OVERRIDE:
			{
#line 49 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
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
#line 64 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
		FunctionDecl* pFunctionDecl = FunctionDecl::TryCreate(pTokenContainer, pTempOffset, pMemberFunctionDecl);
		if (pFunctionDecl == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			if (pMemberFunctionDecl) delete pMemberFunctionDecl;
			if (pFunctionDecl) delete pFunctionDecl;
#line 66 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
			return 0;
		}
		NumbatLogic::AccessLevel* __99074450 = pAccessLevel;
#line 68 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
		pAccessLevel = 0;
#line 68 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
		pMemberFunctionDecl->AddChild(__99074450);
#line 70 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
		pMemberFunctionDecl->m_pFunctionDecl = pFunctionDecl;
		NumbatLogic::FunctionDecl* __4280026732 = pFunctionDecl;
#line 71 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
		pFunctionDecl = 0;
#line 71 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
		pMemberFunctionDecl->AddChild(__4280026732);
#line 73 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::MemberFunctionDecl* __1564092617 = pMemberFunctionDecl;
#line 74 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
		pMemberFunctionDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pAccessLevel) delete pAccessLevel;
		if (pFunctionDecl) delete pFunctionDecl;
#line 74 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
		return __1564092617;
	}

	void MemberFunctionDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
	}

	void MemberFunctionDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		bool bGeneric = m_pParentClassDecl->m_pGenericTypeDeclVector->GetSize() > 0;
		if (bGeneric && eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
			return;
#line 88 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
		if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
		{
			if (m_pParentClassDecl->m_pGenericTypeDeclVector->GetSize() > 0)
			{
			}
		}
#line 98 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 101 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
		if (!(eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE))
		{
			m_pAccessLevel->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			if (eLanguage == AST::Language::CPP)
				pOutputBuilder->m_sOut->AppendChar(':');
#line 107 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
			if (m_bStatic)
				pOutputBuilder->m_sOut->Append(" static");
#line 110 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
			if (m_bVirtual)
				pOutputBuilder->m_sOut->Append(" virtual");
#line 113 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
			if (m_bOverride)
				if (eLanguage == AST::Language::CPP)
					pOutputBuilder->m_sOut->Append(" virtual");
				else
					pOutputBuilder->m_sOut->Append(" override");
#line 119 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
			pOutputBuilder->m_sOut->AppendChar(' ');
		}
#line 122 "/home/cliffya/git/Lang/Source/Core/AST/MemberFunctionDecl.nll"
		m_pFunctionDecl->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
	}

}

