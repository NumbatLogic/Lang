#include "DelegateDecl.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "AccessLevel.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "FunctionDecl.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../../../../LangShared/ExternalString/CPP/ExternalString.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "TypeRef.hpp"
#include "ParamDecl.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
	class AccessLevel;
	class Token;
	class DelegateDecl;
	class FunctionDecl;
}
namespace NumbatLogic
{
	DelegateDecl::DelegateDecl()
	{
		m_pAccessLevel = 0;
		m_pFunctionDecl = 0;
		m_eType = AST::Type::DELEGATE_DECL;
	}

	DelegateDecl* DelegateDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		AccessLevel* pAccessLevel = AccessLevel::TryCreate(pTokenContainer, pTempOffset);
		if (pAccessLevel == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			return 0;
		}
		Token* pToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_DELEGATE);
		if (pToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		DelegateDecl* pDelegateDecl = new DelegateDecl();
		pDelegateDecl->m_pFirstToken = pToken;
		pDelegateDecl->m_pAccessLevel = pAccessLevel;
		{
			NumbatLogic::AccessLevel* __2194276919 = pAccessLevel;
			pAccessLevel = 0;
			pDelegateDecl->AddChild(__2194276919);
		}
		FunctionDecl* pFunctionDecl = FunctionDecl::TryCreate(pTokenContainer, pTempOffset, 0);
		if (pFunctionDecl == 0)
		{
			Console::Log("expected function decl");
			NumbatLogic::Assert::Plz(false);
			{
				if (pTempOffset) delete pTempOffset;
				if (pAccessLevel) delete pAccessLevel;
				if (pDelegateDecl) delete pDelegateDecl;
				if (pFunctionDecl) delete pFunctionDecl;
				return 0;
			}
		}
		if (pFunctionDecl->m_pScope != 0)
		{
			Console::Log("function def can't have scope!");
			NumbatLogic::Assert::Plz(false);
			{
				if (pTempOffset) delete pTempOffset;
				if (pAccessLevel) delete pAccessLevel;
				if (pDelegateDecl) delete pDelegateDecl;
				if (pFunctionDecl) delete pFunctionDecl;
				return 0;
			}
		}
		pDelegateDecl->m_pFunctionDecl = pFunctionDecl;
		{
			NumbatLogic::FunctionDecl* __549451023 = pFunctionDecl;
			pFunctionDecl = 0;
			pDelegateDecl->AddChild(__549451023);
		}
		pOffsetDatum->Set(pTempOffset);
		{
			NumbatLogic::DelegateDecl* __2828484651 = pDelegateDecl;
			pDelegateDecl = 0;
			{
				if (pTempOffset) delete pTempOffset;
				if (pAccessLevel) delete pAccessLevel;
				if (pFunctionDecl) delete pFunctionDecl;
				return __2828484651;
			}
		}
	}

	AST* DelegateDecl::FindByName(const char* sxName, AST* pCallingChild)
	{
		if (ExternalString::Equal(sxName, m_pFunctionDecl->m_pNameToken->GetString()))
			return this;
		return AST::FindByName(sxName, pCallingChild);
	}

	void DelegateDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
			return;
		Util::Pad(nDepth, sOut);
		m_pAccessLevel->Stringify(eLanguage, eOutputFile, 0, sOut);
		if (eLanguage == AST::Language::CPP)
			sOut->AppendChar(':');
		sOut->AppendChar(' ');
		switch (eLanguage)
		{
			case AST::Language::CPP:
			{
				sOut->Append("typedef ");
				break;
			}

			case AST::Language::CS:
			case AST::Language::NLL:
			case AST::Language::NLL_DEF:
			{
				sOut->Append("delegate ");
				break;
			}

		}
		m_pFunctionDecl->m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, sOut);
		sOut->AppendChar(' ');
		if (eLanguage == AST::Language::CPP)
			sOut->AppendChar('(');
		sOut->Append(m_pFunctionDecl->m_pNameToken->GetString());
		if (eLanguage == AST::Language::CPP)
			sOut->AppendChar(')');
		m_pFunctionDecl->m_pParamDecl->Stringify(eLanguage, eOutputFile, 0, sOut);
		sOut->Append(";\n");
	}

}

