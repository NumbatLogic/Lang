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
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

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
#line 1 "../../../Source/Core/AST/MemberFunctionDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/MemberFunctionDecl.nll"
#line 13 "../../../Source/Core/AST/MemberFunctionDecl.nll"
	MemberFunctionDecl::MemberFunctionDecl()
	{
		m_pParentClassDecl = 0;
		m_pAccessLevel = 0;
		m_pFunctionDecl = 0;
		m_bStatic = false;
		m_bVirtual = false;
		m_bOverride = false;
#line 15 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		m_eType = AST::Type::AST_MEMBER_FUNCTION_DECL;
#line 16 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		m_bCanDescend = true;
	}

#line 19 "../../../Source/Core/AST/MemberFunctionDecl.nll"
	MemberFunctionDecl* MemberFunctionDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		AccessLevel* pAccessLevel = AccessLevel::TryCreate(pTokenContainer, pTempOffset);
#line 24 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		if (pAccessLevel == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
#line 25 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			return 0;
		}
		bool bStatic = false;
		bool bVirtual = false;
		bool bOverride = false;
		Token* pToken = pTokenContainer->Peek(pTempOffset);
#line 32 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		if (pToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
#line 33 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			return 0;
		}
#line 34 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		switch (pToken->m_eType)
		{
			case Token::Type::TOKEN_KEYWORD_STATIC:
			{
#line 38 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				bStatic = true;
#line 39 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 40 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				break;
			}

			case Token::Type::TOKEN_KEYWORD_VIRTUAL:
			{
#line 44 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				bVirtual = true;
#line 45 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 46 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				break;
			}

			case Token::Type::TOKEN_KEYWORD_OVERRIDE:
			{
#line 50 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				bOverride = true;
#line 51 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 52 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				break;
			}

		}
		MemberFunctionDecl* pMemberFunctionDecl = new MemberFunctionDecl();
#line 57 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		pMemberFunctionDecl->m_pParent = pParentClassDecl;
#line 58 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		pMemberFunctionDecl->m_pParentClassDecl = pParentClassDecl;
#line 59 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		pMemberFunctionDecl->m_pAccessLevel = pAccessLevel;
#line 60 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		pMemberFunctionDecl->m_pFirstToken = pAccessLevel->m_pFirstToken;
#line 61 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		pMemberFunctionDecl->m_bStatic = bStatic;
#line 62 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		pMemberFunctionDecl->m_bVirtual = bVirtual;
#line 63 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		pMemberFunctionDecl->m_bOverride = bOverride;
		FunctionDecl* pFunctionDecl = FunctionDecl::TryCreate(pTokenContainer, pTempOffset, pMemberFunctionDecl);
#line 66 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		if (pFunctionDecl == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			if (pMemberFunctionDecl) delete pMemberFunctionDecl;
			if (pFunctionDecl) delete pFunctionDecl;
#line 67 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			return 0;
		}
		NumbatLogic::AccessLevel* __99074450 = pAccessLevel;
#line 69 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		pAccessLevel = 0;
#line 69 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		pMemberFunctionDecl->AddChild(__99074450);
#line 71 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		pMemberFunctionDecl->m_pFunctionDecl = pFunctionDecl;
		NumbatLogic::FunctionDecl* __4280026732 = pFunctionDecl;
#line 72 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		pFunctionDecl = 0;
#line 72 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		pMemberFunctionDecl->AddChild(__4280026732);
#line 74 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::MemberFunctionDecl* __1564092617 = pMemberFunctionDecl;
#line 75 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		pMemberFunctionDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pAccessLevel) delete pAccessLevel;
		if (pFunctionDecl) delete pFunctionDecl;
#line 75 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		return __1564092617;
	}

#line 78 "../../../Source/Core/AST/MemberFunctionDecl.nll"
	void MemberFunctionDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 80 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		AST::Validate(pValidator, pParent);
	}

#line 83 "../../../Source/Core/AST/MemberFunctionDecl.nll"
	void MemberFunctionDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		bool bGeneric = m_pParentClassDecl->m_pGenericTypeDeclVector->GetSize() > 0;
#line 86 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		if (bGeneric && eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
#line 87 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			return;
#line 89 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
		{
#line 91 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			if (m_pParentClassDecl->m_pGenericTypeDeclVector->GetSize() > 0)
			{
			}
		}
#line 99 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 100 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 102 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		if (!(eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE))
		{
#line 104 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			m_pAccessLevel->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 105 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			if (eLanguage == AST::Language::CPP)
#line 106 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				pOutputBuilder->m_sOut->AppendChar(':');
#line 108 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			if (m_bStatic)
#line 109 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				pOutputBuilder->m_sOut->Append(" static");
#line 111 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			if (m_bVirtual)
#line 112 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				pOutputBuilder->m_sOut->Append(" virtual");
#line 114 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			if (m_bOverride)
#line 115 "../../../Source/Core/AST/MemberFunctionDecl.nll"
				if (eLanguage == AST::Language::CPP)
#line 116 "../../../Source/Core/AST/MemberFunctionDecl.nll"
					pOutputBuilder->m_sOut->Append(" virtual");
				else
#line 118 "../../../Source/Core/AST/MemberFunctionDecl.nll"
					pOutputBuilder->m_sOut->Append(" override");
#line 120 "../../../Source/Core/AST/MemberFunctionDecl.nll"
			pOutputBuilder->m_sOut->AppendChar(' ');
		}
#line 123 "../../../Source/Core/AST/MemberFunctionDecl.nll"
		m_pFunctionDecl->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
	}

}

