#include "NamespaceDecl.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../Validator.hpp"
#include "../../../../LangShared/ExternalString/CPP/ExternalString.hpp"
#include "../NamespaceNode.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "ClassDecl.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class NamespaceDecl;
	class Console;
	class Assert;
	class AST;
	class Validator;
	class ExternalString;
	class NamespaceNode;
	template <class T>
	class Vector;
	class ClassDecl;
	class Util;
	class InternalString;
}
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
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pNamespaceDecl) delete pNamespaceDecl;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_LEFT) == 0)
		{
			Console::Log("expected opening curly brace");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
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
				NumbatLogic::AST* __2537202 = pAST;
				pAST = 0;
				pNamespaceDecl->AddChild(__2537202);
				if (pAST) delete pAST;
				continue;
			}
			Console::Log("expected to parse somethting within namespace...");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pAST) delete pAST;
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::NamespaceDecl* __2611787265 = pNamespaceDecl;
		pNamespaceDecl = 0;
		if (pTempOffset) delete pTempOffset;
		return __2611787265;
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

	AST* NamespaceDecl::SubFindByName(const char* sxName, AST* pCallingChild)
	{
		return AST::FindByName(sxName, pCallingChild);
	}

	AST* NamespaceDecl::FindByName(const char* sxName, AST* pCallingChild)
	{
		if (ExternalString::Equal(sxName, m_pNameToken->GetString()))
			return this;
		AST* pFound = SubFindByName(sxName, pCallingChild);
		if (pFound != 0)
			return pFound;
		NamespaceNode* pFoundNamespace = m_pNamespaceNode->FindByName(sxName, pCallingChild == 0);
		if (pFoundNamespace != 0)
			return pFoundNamespace->m_pNamespaceDeclVector->Get(0);
		for (int i = 0; i < m_pNamespaceNode->m_pNamespaceDeclVector->GetSize(); i++)
		{
			NamespaceDecl* pNamespaceDecl = m_pNamespaceNode->m_pNamespaceDeclVector->Get(i);
			if (pNamespaceDecl != this)
			{
				ClassDecl* pClassDecl = pNamespaceDecl->FindClassDecl(sxName, 0);
				if (pClassDecl != 0)
				{
					if (pClassDecl->m_pNameToken != 0)
						return pClassDecl;
					return pClassDecl;
				}
			}
		}
		return 0;
	}

	void NamespaceDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		Util::Pad(nDepth, sOut);
		sOut->Append("namespace ");
		m_pNameToken->Stringify(sOut);
		sOut->Append("\n");
		Util::Pad(nDepth, sOut);
		sOut->Append("{\n");
		nDepth++;
		AST* pChild = m_pFirstChild;
		while (pChild != 0)
		{
			pChild->Stringify(eLanguage, eOutputFile, nDepth, sOut);
			pChild = pChild->m_pNextSibling;
		}
		nDepth--;
		Util::Pad(nDepth, sOut);
		sOut->Append("}\n");
	}

}

