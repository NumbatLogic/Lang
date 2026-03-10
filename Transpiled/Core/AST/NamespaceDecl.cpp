#include "NamespaceDecl.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../Validator.hpp"
#include "../OutputBuilder.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class NamespaceDecl;
	class Console;
	class Assert;
	class Validator;
	class OutputBuilder;
	class Util;
	class InternalString;
}
#line 0 "../../../Source/Core/AST/NamespaceDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/NamespaceDecl.nll"
#line 8 "../../../Source/Core/AST/NamespaceDecl.nll"
	NamespaceDecl::NamespaceDecl()
	{
		m_pNameToken = 0;
		m_pNamespaceNode = 0;
#line 10 "../../../Source/Core/AST/NamespaceDecl.nll"
		m_eType = AST::Type::NAMESPACE_DECL;
#line 11 "../../../Source/Core/AST/NamespaceDecl.nll"
		m_bCanDescend = true;
	}

#line 14 "../../../Source/Core/AST/NamespaceDecl.nll"
	NamespaceDecl* NamespaceDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
#line 16 "../../../Source/Core/AST/NamespaceDecl.nll"
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 18 "../../../Source/Core/AST/NamespaceDecl.nll"
		Token* pNamespaceToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_NAMESPACE);
#line 19 "../../../Source/Core/AST/NamespaceDecl.nll"
		if (pNamespaceToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 20 "../../../Source/Core/AST/NamespaceDecl.nll"
			return 0;
		}
#line 21 "../../../Source/Core/AST/NamespaceDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 23 "../../../Source/Core/AST/NamespaceDecl.nll"
		NamespaceDecl* pNamespaceDecl = new NamespaceDecl();
#line 25 "../../../Source/Core/AST/NamespaceDecl.nll"
		Token* pNameToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
#line 26 "../../../Source/Core/AST/NamespaceDecl.nll"
		if (pNameToken == 0)
		{
#line 28 "../../../Source/Core/AST/NamespaceDecl.nll"
			Console::Log("expected namespace name");
#line 29 "../../../Source/Core/AST/NamespaceDecl.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 30 "../../../Source/Core/AST/NamespaceDecl.nll"
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pNamespaceDecl) delete pNamespaceDecl;
#line 31 "../../../Source/Core/AST/NamespaceDecl.nll"
			return 0;
		}
#line 33 "../../../Source/Core/AST/NamespaceDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 35 "../../../Source/Core/AST/NamespaceDecl.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_LEFT) == 0)
		{
#line 37 "../../../Source/Core/AST/NamespaceDecl.nll"
			Console::Log("expected opening curly brace");
#line 38 "../../../Source/Core/AST/NamespaceDecl.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 39 "../../../Source/Core/AST/NamespaceDecl.nll"
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pNamespaceDecl) delete pNamespaceDecl;
#line 40 "../../../Source/Core/AST/NamespaceDecl.nll"
			return 0;
		}
#line 42 "../../../Source/Core/AST/NamespaceDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 44 "../../../Source/Core/AST/NamespaceDecl.nll"
		pNamespaceDecl->m_pFirstToken = pNamespaceToken;
#line 45 "../../../Source/Core/AST/NamespaceDecl.nll"
		pNamespaceDecl->m_pNameToken = pNameToken;
#line 47 "../../../Source/Core/AST/NamespaceDecl.nll"
		while (true)
		{
#line 49 "../../../Source/Core/AST/NamespaceDecl.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_RIGHT) != 0)
			{
#line 51 "../../../Source/Core/AST/NamespaceDecl.nll"
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 52 "../../../Source/Core/AST/NamespaceDecl.nll"
				break;
			}
#line 55 "../../../Source/Core/AST/NamespaceDecl.nll"
			AST* pAST = AST::CreateFromTokenContainer(pTokenContainer, pTempOffset);
#line 56 "../../../Source/Core/AST/NamespaceDecl.nll"
			if (pAST != 0)
			{
				NumbatLogic::AST* __834042965 = pAST;
#line 58 "../../../Source/Core/AST/NamespaceDecl.nll"
				pAST = 0;
#line 58 "../../../Source/Core/AST/NamespaceDecl.nll"
				pNamespaceDecl->AddChild(__834042965);
				if (pAST) delete pAST;
#line 59 "../../../Source/Core/AST/NamespaceDecl.nll"
				continue;
			}
#line 62 "../../../Source/Core/AST/NamespaceDecl.nll"
			Console::Log("expected to parse somethting within namespace...");
#line 63 "../../../Source/Core/AST/NamespaceDecl.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 64 "../../../Source/Core/AST/NamespaceDecl.nll"
			Assert::Plz(false);
			if (pAST) delete pAST;
		}
#line 68 "../../../Source/Core/AST/NamespaceDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::NamespaceDecl* __1424002840 = pNamespaceDecl;
#line 69 "../../../Source/Core/AST/NamespaceDecl.nll"
		pNamespaceDecl = 0;
		if (pTempOffset) delete pTempOffset;
#line 69 "../../../Source/Core/AST/NamespaceDecl.nll"
		return __1424002840;
	}

#line 72 "../../../Source/Core/AST/NamespaceDecl.nll"
	void NamespaceDecl::PreValidate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 74 "../../../Source/Core/AST/NamespaceDecl.nll"
		const char* sxName = m_pNameToken->GetString();
#line 75 "../../../Source/Core/AST/NamespaceDecl.nll"
		pValidator->BeginNamespace(sxName);
#line 76 "../../../Source/Core/AST/NamespaceDecl.nll"
		AST::PreValidate(pValidator, pParent);
#line 77 "../../../Source/Core/AST/NamespaceDecl.nll"
		pValidator->EndNamespace(sxName);
	}

#line 80 "../../../Source/Core/AST/NamespaceDecl.nll"
	void NamespaceDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 82 "../../../Source/Core/AST/NamespaceDecl.nll"
		const char* sxName = m_pNameToken->GetString();
#line 83 "../../../Source/Core/AST/NamespaceDecl.nll"
		pValidator->BeginNamespace(sxName);
#line 84 "../../../Source/Core/AST/NamespaceDecl.nll"
		AST::Validate(pValidator, pParent);
#line 85 "../../../Source/Core/AST/NamespaceDecl.nll"
		pValidator->EndNamespace(sxName);
	}

#line 88 "../../../Source/Core/AST/NamespaceDecl.nll"
	void NamespaceDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 90 "../../../Source/Core/AST/NamespaceDecl.nll"
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 92 "../../../Source/Core/AST/NamespaceDecl.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 93 "../../../Source/Core/AST/NamespaceDecl.nll"
		pOutputBuilder->m_sOut->Append("namespace ");
#line 94 "../../../Source/Core/AST/NamespaceDecl.nll"
		m_pNameToken->Stringify(pOutputBuilder->m_sOut);
#line 95 "../../../Source/Core/AST/NamespaceDecl.nll"
		pOutputBuilder->m_sOut->Append("\n");
#line 97 "../../../Source/Core/AST/NamespaceDecl.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 98 "../../../Source/Core/AST/NamespaceDecl.nll"
		pOutputBuilder->m_sOut->Append("{\n");
#line 99 "../../../Source/Core/AST/NamespaceDecl.nll"
		nDepth++;
#line 101 "../../../Source/Core/AST/NamespaceDecl.nll"
		AST* pChild = m_pFirstChild;
#line 102 "../../../Source/Core/AST/NamespaceDecl.nll"
		while (pChild != 0)
		{
#line 104 "../../../Source/Core/AST/NamespaceDecl.nll"
			pChild->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 105 "../../../Source/Core/AST/NamespaceDecl.nll"
			pChild = pChild->m_pNextSibling;
		}
#line 108 "../../../Source/Core/AST/NamespaceDecl.nll"
		nDepth--;
#line 109 "../../../Source/Core/AST/NamespaceDecl.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 110 "../../../Source/Core/AST/NamespaceDecl.nll"
		pOutputBuilder->m_sOut->Append("}\n");
	}

}

