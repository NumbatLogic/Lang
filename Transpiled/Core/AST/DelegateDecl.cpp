#include "DelegateDecl.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "AccessLevel.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "FunctionDecl.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../Util.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "TypeRef.hpp"
#include "ParamDecl.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class AccessLevel;
	class Token;
	class TokenContainer;
	class DelegateDecl;
	class FunctionDecl;
	class Console;
	class Assert;
	class Util;
	class OutputBuilder;
	class InternalString;
	class TypeRef;
	class ParamDecl;
}
#line 1 "../../../Source/Core/AST/DelegateDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/DelegateDecl.nll"
#line 9 "../../../Source/Core/AST/DelegateDecl.nll"
	DelegateDecl::DelegateDecl()
	{
		m_pAccessLevel = 0;
		m_pFunctionDecl = 0;
#line 11 "../../../Source/Core/AST/DelegateDecl.nll"
		m_eType = AST::Type::DELEGATE_DECL;
	}

#line 14 "../../../Source/Core/AST/DelegateDecl.nll"
	DelegateDecl* DelegateDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		AccessLevel* pAccessLevel = AccessLevel::TryCreate(pTokenContainer, pTempOffset);
#line 19 "../../../Source/Core/AST/DelegateDecl.nll"
		if (pAccessLevel == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
#line 20 "../../../Source/Core/AST/DelegateDecl.nll"
			return 0;
		}
		Token* pToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_DELEGATE);
#line 23 "../../../Source/Core/AST/DelegateDecl.nll"
		if (pToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
#line 24 "../../../Source/Core/AST/DelegateDecl.nll"
			return 0;
		}
#line 25 "../../../Source/Core/AST/DelegateDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		DelegateDecl* pDelegateDecl = new DelegateDecl();
#line 28 "../../../Source/Core/AST/DelegateDecl.nll"
		pDelegateDecl->m_pFirstToken = pToken;
#line 29 "../../../Source/Core/AST/DelegateDecl.nll"
		pDelegateDecl->m_pAccessLevel = pAccessLevel;
		NumbatLogic::AccessLevel* __98812055 = pAccessLevel;
#line 30 "../../../Source/Core/AST/DelegateDecl.nll"
		pAccessLevel = 0;
#line 30 "../../../Source/Core/AST/DelegateDecl.nll"
		pDelegateDecl->AddChild(__98812055);
		FunctionDecl* pFunctionDecl = FunctionDecl::TryCreate(pTokenContainer, pTempOffset, 0);
#line 33 "../../../Source/Core/AST/DelegateDecl.nll"
		if (pFunctionDecl == 0)
		{
#line 35 "../../../Source/Core/AST/DelegateDecl.nll"
			Console::Log("expected function decl");
#line 36 "../../../Source/Core/AST/DelegateDecl.nll"
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			if (pDelegateDecl) delete pDelegateDecl;
			if (pFunctionDecl) delete pFunctionDecl;
#line 37 "../../../Source/Core/AST/DelegateDecl.nll"
			return 0;
		}
#line 40 "../../../Source/Core/AST/DelegateDecl.nll"
		if (pFunctionDecl->m_pScope != 0)
		{
#line 42 "../../../Source/Core/AST/DelegateDecl.nll"
			Console::Log("function def can't have scope!");
#line 43 "../../../Source/Core/AST/DelegateDecl.nll"
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			if (pDelegateDecl) delete pDelegateDecl;
			if (pFunctionDecl) delete pFunctionDecl;
#line 44 "../../../Source/Core/AST/DelegateDecl.nll"
			return 0;
		}
#line 47 "../../../Source/Core/AST/DelegateDecl.nll"
		pDelegateDecl->m_pFunctionDecl = pFunctionDecl;
		NumbatLogic::FunctionDecl* __4279829941 = pFunctionDecl;
#line 48 "../../../Source/Core/AST/DelegateDecl.nll"
		pFunctionDecl = 0;
#line 48 "../../../Source/Core/AST/DelegateDecl.nll"
		pDelegateDecl->AddChild(__4279829941);
#line 50 "../../../Source/Core/AST/DelegateDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::DelegateDecl* __305311194 = pDelegateDecl;
#line 51 "../../../Source/Core/AST/DelegateDecl.nll"
		pDelegateDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pAccessLevel) delete pAccessLevel;
		if (pFunctionDecl) delete pFunctionDecl;
#line 51 "../../../Source/Core/AST/DelegateDecl.nll"
		return __305311194;
	}

#line 59 "../../../Source/Core/AST/DelegateDecl.nll"
	void DelegateDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 64 "../../../Source/Core/AST/DelegateDecl.nll"
		if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
#line 65 "../../../Source/Core/AST/DelegateDecl.nll"
			return;
#line 67 "../../../Source/Core/AST/DelegateDecl.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 68 "../../../Source/Core/AST/DelegateDecl.nll"
		m_pAccessLevel->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 69 "../../../Source/Core/AST/DelegateDecl.nll"
		if (eLanguage == AST::Language::CPP)
#line 70 "../../../Source/Core/AST/DelegateDecl.nll"
			pOutputBuilder->m_sOut->AppendChar(':');
#line 71 "../../../Source/Core/AST/DelegateDecl.nll"
		pOutputBuilder->m_sOut->AppendChar(' ');
#line 73 "../../../Source/Core/AST/DelegateDecl.nll"
		switch (eLanguage)
		{
			case AST::Language::CPP:
			{
#line 77 "../../../Source/Core/AST/DelegateDecl.nll"
				pOutputBuilder->m_sOut->Append("typedef ");
#line 78 "../../../Source/Core/AST/DelegateDecl.nll"
				break;
			}

			case AST::Language::CS:
			case AST::Language::NLL:
			case AST::Language::NLL_DEF:
			{
#line 84 "../../../Source/Core/AST/DelegateDecl.nll"
				pOutputBuilder->m_sOut->Append("delegate ");
#line 85 "../../../Source/Core/AST/DelegateDecl.nll"
				break;
			}

		}
#line 89 "../../../Source/Core/AST/DelegateDecl.nll"
		m_pFunctionDecl->m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 90 "../../../Source/Core/AST/DelegateDecl.nll"
		pOutputBuilder->m_sOut->AppendChar(' ');
#line 92 "../../../Source/Core/AST/DelegateDecl.nll"
		if (eLanguage == AST::Language::CPP)
#line 93 "../../../Source/Core/AST/DelegateDecl.nll"
			pOutputBuilder->m_sOut->AppendChar('(');
#line 94 "../../../Source/Core/AST/DelegateDecl.nll"
		pOutputBuilder->m_sOut->Append(m_pFunctionDecl->m_pNameToken->GetString());
#line 95 "../../../Source/Core/AST/DelegateDecl.nll"
		if (eLanguage == AST::Language::CPP)
#line 96 "../../../Source/Core/AST/DelegateDecl.nll"
			pOutputBuilder->m_sOut->AppendChar(')');
#line 98 "../../../Source/Core/AST/DelegateDecl.nll"
		m_pFunctionDecl->m_pParamDecl->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 100 "../../../Source/Core/AST/DelegateDecl.nll"
		pOutputBuilder->m_sOut->Append(";\n");
	}

}

