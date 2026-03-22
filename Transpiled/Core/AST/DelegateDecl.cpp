#include "DelegateDecl.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "AccessLevel.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "FunctionDecl.hpp"
#include "../../../../LangShared/Source/Console/CPP/Console.hpp"
#include "../../../../LangShared/Source/Assert/CPP/Assert.hpp"
#include "../Util.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"
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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
#line 8 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
	DelegateDecl::DelegateDecl()
	{
		m_pAccessLevel = 0;
		m_pFunctionDecl = 0;
#line 10 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		m_eType = AST::Type::DELEGATE_DECL;
	}

	DelegateDecl* DelegateDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, ClassDecl* pParentClassDecl)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		AccessLevel* pAccessLevel = AccessLevel::TryCreate(pTokenContainer, pTempOffset);
		if (pAccessLevel == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			return 0;
		}
		Token* pToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_DELEGATE);
		if (pToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
#line 23 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			return 0;
		}
#line 24 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 26 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		DelegateDecl* pDelegateDecl = new DelegateDecl();
		pDelegateDecl->m_pFirstToken = pToken;
		pDelegateDecl->m_pAccessLevel = pAccessLevel;
		NumbatLogic::AccessLevel* __98812055 = pAccessLevel;
#line 29 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		pAccessLevel = 0;
#line 29 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		pDelegateDecl->AddChild(__98812055);
#line 31 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		FunctionDecl* pFunctionDecl = FunctionDecl::TryCreate(pTokenContainer, pTempOffset, 0);
		if (pFunctionDecl == 0)
		{
			Console::Log("expected function decl");
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			if (pDelegateDecl) delete pDelegateDecl;
			if (pFunctionDecl) delete pFunctionDecl;
#line 36 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			return 0;
		}
#line 39 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		if (pFunctionDecl->m_pScope != 0)
		{
			Console::Log("function def can't have scope!");
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			if (pDelegateDecl) delete pDelegateDecl;
			if (pFunctionDecl) delete pFunctionDecl;
#line 43 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
			return 0;
		}
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		pDelegateDecl->m_pFunctionDecl = pFunctionDecl;
		NumbatLogic::FunctionDecl* __4279829941 = pFunctionDecl;
#line 47 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		pFunctionDecl = 0;
#line 47 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		pDelegateDecl->AddChild(__4279829941);
#line 49 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::DelegateDecl* __305311194 = pDelegateDecl;
#line 50 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		pDelegateDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pAccessLevel) delete pAccessLevel;
		if (pFunctionDecl) delete pFunctionDecl;
#line 50 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		return __305311194;
	}

#line 58 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
	void DelegateDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 63 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
			return;
#line 66 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
		m_pAccessLevel->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		if (eLanguage == AST::Language::CPP)
			pOutputBuilder->m_sOut->AppendChar(':');
		pOutputBuilder->m_sOut->AppendChar(' ');
#line 72 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		switch (eLanguage)
		{
			case AST::Language::CPP:
			{
				pOutputBuilder->m_sOut->Append("typedef ");
				break;
			}

			case AST::Language::CS:
			case AST::Language::NLL:
			case AST::Language::NLL_DEF:
			{
#line 83 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
				pOutputBuilder->m_sOut->Append("delegate ");
				break;
			}

		}
		m_pFunctionDecl->m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		pOutputBuilder->m_sOut->AppendChar(' ');
#line 91 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		if (eLanguage == AST::Language::CPP)
			pOutputBuilder->m_sOut->AppendChar('(');
		pOutputBuilder->m_sOut->Append(m_pFunctionDecl->m_pNameToken->GetString());
		if (eLanguage == AST::Language::CPP)
			pOutputBuilder->m_sOut->AppendChar(')');
#line 97 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		m_pFunctionDecl->m_pParamDecl->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 99 "/home/cliffya/git/Lang/Source/Core/AST/DelegateDecl.nll"
		pOutputBuilder->m_sOut->Append(";\n");
	}

}

