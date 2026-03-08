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
#line 1 "../../../Source/Core/AST/NamespaceDecl.nll"
namespace NumbatLogic
{
	NamespaceDecl::NamespaceDecl()
	{
		m_pNameToken = 0;
		m_pNamespaceNode = 0;
		m_eType = AST::Type::NAMESPACE_DECL;
		m_bCanDescend = true;
	}

	NamespaceDecl* NamespaceDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pNamespaceToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_NAMESPACE);
		if (pNamespaceToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		NamespaceDecl* pNamespaceDecl = new NamespaceDecl();
		Token* pNameToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
		if (pNameToken == 0)
		{
			Console::Log("expected namespace name");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pNamespaceDecl) delete pNamespaceDecl;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_LEFT) == 0)
		{
			Console::Log("expected opening curly brace");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pNamespaceDecl) delete pNamespaceDecl;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		pNamespaceDecl->m_pFirstToken = pNamespaceToken;
		pNamespaceDecl->m_pNameToken = pNameToken;
		while (true)
		{
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_RIGHT) != 0)
			{
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				break;
			}
			AST* pAST = AST::CreateFromTokenContainer(pTokenContainer, pTempOffset);
			if (pAST != 0)
			{
				NumbatLogic::AST* __834042965 = pAST;
				pAST = 0;
				pNamespaceDecl->AddChild(__834042965);
				if (pAST) delete pAST;
				continue;
			}
			Console::Log("expected to parse somethting within namespace...");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			Assert::Plz(false);
			if (pAST) delete pAST;
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::NamespaceDecl* __1424002840 = pNamespaceDecl;
		pNamespaceDecl = 0;
		if (pTempOffset) delete pTempOffset;
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
		pOutputBuilder->OutputSourceLocation(eLanguage, m_pNameToken);
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
		pOutputBuilder->m_sOut->Append("namespace ");
		m_pNameToken->Stringify(pOutputBuilder->m_sOut);
		pOutputBuilder->m_sOut->Append("\n");
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
		pOutputBuilder->m_sOut->Append("{\n");
		nDepth++;
		AST* pChild = m_pFirstChild;
		while (pChild != 0)
		{
			pChild->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
			pChild = pChild->m_pNextSibling;
		}
		nDepth--;
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
		pOutputBuilder->m_sOut->Append("}\n");
	}

}

