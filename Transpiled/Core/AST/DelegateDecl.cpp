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
#line 0 "../../../Source/Core/AST/DelegateDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/DelegateDecl.nll"
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
		NumbatLogic::AccessLevel* __98812055 = pAccessLevel;
		pAccessLevel = 0;
		pDelegateDecl->AddChild(__98812055);
		FunctionDecl* pFunctionDecl = FunctionDecl::TryCreate(pTokenContainer, pTempOffset, 0);
		if (pFunctionDecl == 0)
		{
			Console::Log("expected function decl");
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			if (pDelegateDecl) delete pDelegateDecl;
			if (pFunctionDecl) delete pFunctionDecl;
			return 0;
		}
		if (pFunctionDecl->m_pScope != 0)
		{
			Console::Log("function def can't have scope!");
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pAccessLevel) delete pAccessLevel;
			if (pDelegateDecl) delete pDelegateDecl;
			if (pFunctionDecl) delete pFunctionDecl;
			return 0;
		}
		pDelegateDecl->m_pFunctionDecl = pFunctionDecl;
		NumbatLogic::FunctionDecl* __4279829941 = pFunctionDecl;
		pFunctionDecl = 0;
		pDelegateDecl->AddChild(__4279829941);
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::DelegateDecl* __305311194 = pDelegateDecl;
		pDelegateDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pAccessLevel) delete pAccessLevel;
		if (pFunctionDecl) delete pFunctionDecl;
		return __305311194;
	}

	void DelegateDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out)
	{
		if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
			return;
		Util::Pad(nDepth, out->m_sOut);
		m_pAccessLevel->Stringify(eLanguage, eOutputFile, 0, out);
		if (eLanguage == AST::Language::CPP)
			out->m_sOut->AppendChar(':');
		out->m_sOut->AppendChar(' ');
		switch (eLanguage)
		{
			case AST::Language::CPP:
			{
				out->m_sOut->Append("typedef ");
#line 77 "../../../Source/Core/AST/DelegateDecl.nll"
				break;
			}

			case AST::Language::CS:
			case AST::Language::NLL:
			case AST::Language::NLL_DEF:
			{
				out->m_sOut->Append("delegate ");
#line 84 "../../../Source/Core/AST/DelegateDecl.nll"
				break;
			}

		}
		m_pFunctionDecl->m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, out);
		out->m_sOut->AppendChar(' ');
		if (eLanguage == AST::Language::CPP)
			out->m_sOut->AppendChar('(');
		out->m_sOut->Append(m_pFunctionDecl->m_pNameToken->GetString());
		if (eLanguage == AST::Language::CPP)
			out->m_sOut->AppendChar(')');
		m_pFunctionDecl->m_pParamDecl->Stringify(eLanguage, eOutputFile, 0, out);
		out->m_sOut->Append(";\n");
	}

}

