#include "NamespaceDecl.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Source/Console/CPP/Console.hpp"
#include "../../../../LangShared/Source/Assert/CPP/Assert.hpp"
#include "../Validator.hpp"
#include "../OutputBuilder.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"

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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
#line 8 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
	NamespaceDecl::NamespaceDecl()
	{
		m_pNameToken = 0;
		m_pNamespaceNode = 0;
#line 10 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
		m_eType = AST::Type::NAMESPACE_DECL;
		m_bCanDescend = true;
	}

	NamespaceDecl* NamespaceDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 18 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
		Token* pNamespaceToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_NAMESPACE);
		if (pNamespaceToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
			return 0;
		}
#line 21 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 23 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
		NamespaceDecl* pNamespaceDecl = new NamespaceDecl();
#line 25 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
		Token* pNameToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
		if (pNameToken == 0)
		{
			Console::Log("expected namespace name");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pNamespaceDecl) delete pNamespaceDecl;
#line 31 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 35 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_LEFT) == 0)
		{
			Console::Log("expected opening curly brace");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pNamespaceDecl) delete pNamespaceDecl;
#line 40 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 44 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
		pNamespaceDecl->m_pFirstToken = pNamespaceToken;
		pNamespaceDecl->m_pNameToken = pNameToken;
#line 47 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
		while (true)
		{
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_RIGHT) != 0)
			{
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				break;
			}
#line 55 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
			AST* pAST = AST::CreateFromTokenContainer(pTokenContainer, pTempOffset);
			if (pAST != 0)
			{
				NumbatLogic::AST* __834042965 = pAST;
#line 58 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
				pAST = 0;
#line 58 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
				pNamespaceDecl->AddChild(__834042965);
				if (pAST) delete pAST;
#line 59 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
				continue;
			}
#line 62 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
			Console::Log("expected to parse somethting within namespace...");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			Assert::Plz(false);
			if (pAST) delete pAST;
		}
#line 68 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::NamespaceDecl* __1424002840 = pNamespaceDecl;
#line 69 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
		pNamespaceDecl = 0;
		if (pTempOffset) delete pTempOffset;
#line 69 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
		return __1424002840;
	}

	void NamespaceDecl::PreValidate(Validator* pValidator, OperatorExpr* pParent)
	{
		const char* sxName = m_pNameToken->GetString();
		pValidator->BeginNamespace(sxName);
		AST::PreValidate(pValidator, pParent);
		pValidator->EndNamespace(sxName);
	}

	void NamespaceDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		const char* sxName = m_pNameToken->GetString();
		pValidator->BeginNamespace(sxName);
		AST::Validate(pValidator, pParent);
		pValidator->EndNamespace(sxName);
	}

	void NamespaceDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 92 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
		pOutputBuilder->m_sOut->Append("namespace ");
		m_pNameToken->Stringify(pOutputBuilder->m_sOut);
		pOutputBuilder->m_sOut->Append("\n");
#line 97 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
		pOutputBuilder->m_sOut->Append("{\n");
		nDepth++;
#line 101 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
		AST* pChild = m_pFirstChild;
		while (pChild != 0)
		{
			pChild->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
			pChild = pChild->m_pNextSibling;
		}
#line 108 "/home/cliffya/git/Lang/Source/Core/AST/NamespaceDecl.nll"
		nDepth--;
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
		pOutputBuilder->m_sOut->Append("}\n");
	}

}

