#include "Scope.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Source/Console/CPP/Console.hpp"
#include "../../../../LangShared/Source/Assert/CPP/Assert.hpp"
#include "../Validator.hpp"
#include "TorDecl.hpp"
#include "MemberVarDecl.hpp"
#include "VarDecl.hpp"
#include "TypeRef.hpp"
#include "../../../../LangShared/Source/Vector/CPP/Vector.hpp"
#include "../Semantic/Symbol.hpp"
#include "../Semantic/Resolver.hpp"
#include "../Util.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class Scope;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class Console;
	class Assert;
	class Validator;
	class TorDecl;
	class MemberVarDecl;
	class VarDecl;
	class TypeRef;
	template <class T>
	class Vector;
	class Symbol;
	class Resolver;
	class ClassDecl;
	class Util;
	class OutputBuilder;
	class InternalString;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
#line 8 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
	Scope::Scope()
	{
		m_bPseudo = false;
#line 10 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
		m_eType = AST::Type::AST_SCOPE;
		m_bPseudo = false;
	}

	Scope* Scope::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, bool bPseudoScope)
	{
		Scope* pScope = 0;
#line 18 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
		Token* pOpeningToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_LEFT);
		if (pOpeningToken == 0)
		{
			if (bPseudoScope)
			{
				AST* pChild = AST::CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
				if (pChild != 0)
				{
					pScope = new Scope();
					pScope->m_pFirstToken = pChild->m_pFirstToken;
					pScope->m_bPseudo = true;
					NumbatLogic::AST* __356897802 = pChild;
#line 31 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
					pChild = 0;
#line 31 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
					pScope->AddChild(__356897802);
					pOffsetDatum->Set(pTempOffset);
					NumbatLogic::Scope* __1530552932 = pScope;
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
					pScope = 0;
					if (pChild) delete pChild;
					if (pTempOffset) delete pTempOffset;
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
					return __1530552932;
				}
				if (pChild) delete pChild;
			}
			if (pScope) delete pScope;
			if (pTempOffset) delete pTempOffset;
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
			return 0;
		}
#line 40 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 42 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
		pScope = new Scope();
		pScope->m_pFirstToken = pOpeningToken;
#line 45 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
		while (true)
		{
			Token* pClosingToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_RIGHT);
			if (pClosingToken != 0)
			{
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				break;
			}
#line 54 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
			AST* pChild = AST::CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
			if (pChild == 0)
			{
				Console::Log("expected to parse somethting within scope...");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				Assert::Plz(false);
				if (pChild) delete pChild;
				if (pScope) delete pScope;
				if (pTempOffset) delete pTempOffset;
#line 60 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
				return 0;
			}
			NumbatLogic::AST* __357094601 = pChild;
			pChild = 0;
#line 63 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
			pScope->AddChild(__357094601);
			if (pChild) delete pChild;
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::Scope* __1530749733 = pScope;
#line 67 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
		pScope = 0;
		if (pTempOffset) delete pTempOffset;
#line 67 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
		return __1530749733;
	}

	void Scope::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		pValidator->BeginScope(this);
#line 75 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
		if (m_pParent->m_eType == AST::Type::AST_TOR_DECL)
		{
			TorDecl* pTorDecl = (TorDecl*)(m_pParent);
			if (pTorDecl->m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DESTRUCT)
			{
				if (pTorDecl->m_pParent->m_eType != AST::Type::AST_CLASS_DECL)
				{
					pValidator->AddError("Expected parent TorDecl to be child of AST_CLASS_DECL", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
					return;
				}
#line 86 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
				AST* pChild = pTorDecl->m_pParent->m_pFirstChild;
				while (pChild != 0)
				{
					if (pChild->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
					{
						MemberVarDecl* pMemberVarDecl = (MemberVarDecl*)(pChild);
#line 93 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
						if (!pMemberVarDecl->m_bStatic)
						{
							pValidator->AddVarDecl(pMemberVarDecl->m_pVarDecl);
#line 97 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
							if (pMemberVarDecl->m_pVarDecl->m_pTypeRef->m_pTypeToken->m_eType == Token::Type::TOKEN_IDENTIFIER)
							{
#line 100 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
								AST* pType = 0;
								Vector<Symbol*>* pCandidates = new Vector<Symbol*>();
								pValidator->m_pResolver->ResolveFromNode(this, pMemberVarDecl->m_pVarDecl->m_pTypeRef->m_pTypeToken->GetString(), pCandidates);
								if (pCandidates->GetSize() == 1 && pCandidates->Get(0)->m_pDeclAST != 0 && pCandidates->Get(0)->m_pDeclAST->m_eType == AST::Type::AST_CLASS_DECL)
									pType = pCandidates->Get(0)->m_pDeclAST;
#line 106 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
								if (pType != 0 && pType->m_eType == AST::Type::AST_CLASS_DECL)
								{
									ClassDecl* pClassDecl = (ClassDecl*)(pType);
									AddClassDeclReference(pClassDecl, AST::OutputFile::SOURCE, false);
								}
								if (pCandidates) delete pCandidates;
							}
						}
					}
					pChild = pChild->m_pNextSibling;
				}
			}
		}
#line 120 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
		AST::Validate(pValidator, pParent);
#line 122 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
		pValidator->EndScope(this);
	}

	void Scope::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		if (!m_bPseudo || m_pFirstChild == 0 || m_pFirstChild != m_pLastChild)
		{
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
			pOutputBuilder->m_sOut->Append("{\n");
		}
#line 133 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
		AST* pChild = m_pFirstChild;
		while (pChild != 0)
		{
			pChild->Stringify(eLanguage, eOutputFile, nDepth + 1, pOutputBuilder);
			pChild = pChild->m_pNextSibling;
		}
#line 140 "/home/cliffya/git/Lang/Source/Core/AST/Scope.nll"
		if (!m_bPseudo || m_pFirstChild == 0 || m_pFirstChild != m_pLastChild)
		{
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
			pOutputBuilder->m_sOut->Append("}\n");
		}
	}

}

