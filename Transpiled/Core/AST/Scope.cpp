#include "Scope.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../Validator.hpp"
#include "TorDecl.hpp"
#include "MemberVarDecl.hpp"
#include "VarDecl.hpp"
#include "TypeRef.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../Semantic/Symbol.hpp"
#include "../Semantic/Resolver.hpp"
#include "../Util.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

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
#line 1 "../../../Source/Core/AST/Scope.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/Scope.nll"
#line 9 "../../../Source/Core/AST/Scope.nll"
	Scope::Scope()
	{
		m_bPseudo = false;
#line 11 "../../../Source/Core/AST/Scope.nll"
		m_eType = AST::Type::AST_SCOPE;
#line 12 "../../../Source/Core/AST/Scope.nll"
		m_bPseudo = false;
	}

#line 15 "../../../Source/Core/AST/Scope.nll"
	Scope* Scope::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, bool bPseudoScope)
	{
		Scope* pScope = 0;
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pOpeningToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_LEFT);
#line 22 "../../../Source/Core/AST/Scope.nll"
		if (pOpeningToken == 0)
		{
#line 24 "../../../Source/Core/AST/Scope.nll"
			if (bPseudoScope)
			{
				AST* pChild = AST::CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
#line 27 "../../../Source/Core/AST/Scope.nll"
				if (pChild != 0)
				{
#line 29 "../../../Source/Core/AST/Scope.nll"
					pScope = new Scope();
#line 30 "../../../Source/Core/AST/Scope.nll"
					pScope->m_pFirstToken = pChild->m_pFirstToken;
#line 31 "../../../Source/Core/AST/Scope.nll"
					pScope->m_bPseudo = true;
					NumbatLogic::AST* __356897802 = pChild;
#line 32 "../../../Source/Core/AST/Scope.nll"
					pChild = 0;
#line 32 "../../../Source/Core/AST/Scope.nll"
					pScope->AddChild(__356897802);
#line 33 "../../../Source/Core/AST/Scope.nll"
					pOffsetDatum->Set(pTempOffset);
					NumbatLogic::Scope* __1530552932 = pScope;
#line 34 "../../../Source/Core/AST/Scope.nll"
					pScope = 0;
					if (pChild) delete pChild;
					if (pTempOffset) delete pTempOffset;
#line 34 "../../../Source/Core/AST/Scope.nll"
					return __1530552932;
				}
				if (pChild) delete pChild;
			}
			if (pScope) delete pScope;
			if (pTempOffset) delete pTempOffset;
#line 38 "../../../Source/Core/AST/Scope.nll"
			return 0;
		}
#line 41 "../../../Source/Core/AST/Scope.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 43 "../../../Source/Core/AST/Scope.nll"
		pScope = new Scope();
#line 44 "../../../Source/Core/AST/Scope.nll"
		pScope->m_pFirstToken = pOpeningToken;
#line 46 "../../../Source/Core/AST/Scope.nll"
		while (true)
		{
			Token* pClosingToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_RIGHT);
#line 49 "../../../Source/Core/AST/Scope.nll"
			if (pClosingToken != 0)
			{
#line 51 "../../../Source/Core/AST/Scope.nll"
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 52 "../../../Source/Core/AST/Scope.nll"
				break;
			}
			AST* pChild = AST::CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
#line 56 "../../../Source/Core/AST/Scope.nll"
			if (pChild == 0)
			{
#line 58 "../../../Source/Core/AST/Scope.nll"
				Console::Log("expected to parse somethting within scope...");
#line 59 "../../../Source/Core/AST/Scope.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 60 "../../../Source/Core/AST/Scope.nll"
				Assert::Plz(false);
				if (pChild) delete pChild;
				if (pScope) delete pScope;
				if (pTempOffset) delete pTempOffset;
#line 61 "../../../Source/Core/AST/Scope.nll"
				return 0;
			}
			NumbatLogic::AST* __357094601 = pChild;
#line 64 "../../../Source/Core/AST/Scope.nll"
			pChild = 0;
#line 64 "../../../Source/Core/AST/Scope.nll"
			pScope->AddChild(__357094601);
			if (pChild) delete pChild;
		}
#line 67 "../../../Source/Core/AST/Scope.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::Scope* __1530749733 = pScope;
#line 68 "../../../Source/Core/AST/Scope.nll"
		pScope = 0;
		if (pTempOffset) delete pTempOffset;
#line 68 "../../../Source/Core/AST/Scope.nll"
		return __1530749733;
	}

#line 71 "../../../Source/Core/AST/Scope.nll"
	void Scope::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 73 "../../../Source/Core/AST/Scope.nll"
		pValidator->BeginScope(this);
#line 76 "../../../Source/Core/AST/Scope.nll"
		if (m_pParent->m_eType == AST::Type::AST_TOR_DECL)
		{
			TorDecl* pTorDecl = (TorDecl*)(m_pParent);
#line 79 "../../../Source/Core/AST/Scope.nll"
			if (pTorDecl->m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DESTRUCT)
			{
#line 81 "../../../Source/Core/AST/Scope.nll"
				if (pTorDecl->m_pParent->m_eType != AST::Type::AST_CLASS_DECL)
				{
#line 83 "../../../Source/Core/AST/Scope.nll"
					pValidator->AddError("Expected parent TorDecl to be child of AST_CLASS_DECL", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
#line 84 "../../../Source/Core/AST/Scope.nll"
					return;
				}
				AST* pChild = pTorDecl->m_pParent->m_pFirstChild;
#line 88 "../../../Source/Core/AST/Scope.nll"
				while (pChild != 0)
				{
#line 90 "../../../Source/Core/AST/Scope.nll"
					if (pChild->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
					{
						MemberVarDecl* pMemberVarDecl = (MemberVarDecl*)(pChild);
#line 94 "../../../Source/Core/AST/Scope.nll"
						if (!pMemberVarDecl->m_bStatic)
						{
#line 96 "../../../Source/Core/AST/Scope.nll"
							pValidator->AddVarDecl(pMemberVarDecl->m_pVarDecl);
#line 98 "../../../Source/Core/AST/Scope.nll"
							if (pMemberVarDecl->m_pVarDecl->m_pTypeRef->m_pTypeToken->m_eType == Token::Type::TOKEN_IDENTIFIER)
							{
								AST* pType = 0;
								Vector<Symbol*>* pCandidates = new Vector<Symbol*>();
#line 103 "../../../Source/Core/AST/Scope.nll"
								pValidator->m_pResolver->ResolveFromNode(this, pMemberVarDecl->m_pVarDecl->m_pTypeRef->m_pTypeToken->GetString(), pCandidates);
#line 104 "../../../Source/Core/AST/Scope.nll"
								if (pCandidates->GetSize() == 1 && pCandidates->Get(0)->m_pDeclAST != 0 && pCandidates->Get(0)->m_pDeclAST->m_eType == AST::Type::AST_CLASS_DECL)
#line 105 "../../../Source/Core/AST/Scope.nll"
									pType = pCandidates->Get(0)->m_pDeclAST;
#line 107 "../../../Source/Core/AST/Scope.nll"
								if (pType != 0 && pType->m_eType == AST::Type::AST_CLASS_DECL)
								{
									ClassDecl* pClassDecl = (ClassDecl*)(pType);
#line 110 "../../../Source/Core/AST/Scope.nll"
									AddClassDeclReference(pClassDecl, AST::OutputFile::SOURCE, false);
								}
								if (pCandidates) delete pCandidates;
							}
						}
					}
#line 116 "../../../Source/Core/AST/Scope.nll"
					pChild = pChild->m_pNextSibling;
				}
			}
		}
#line 121 "../../../Source/Core/AST/Scope.nll"
		AST::Validate(pValidator, pParent);
#line 123 "../../../Source/Core/AST/Scope.nll"
		pValidator->EndScope(this);
	}

#line 126 "../../../Source/Core/AST/Scope.nll"
	void Scope::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 128 "../../../Source/Core/AST/Scope.nll"
		if (!m_bPseudo || m_pFirstChild == 0 || m_pFirstChild != m_pLastChild)
		{
#line 130 "../../../Source/Core/AST/Scope.nll"
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 131 "../../../Source/Core/AST/Scope.nll"
			pOutputBuilder->m_sOut->Append("{\n");
		}
		AST* pChild = m_pFirstChild;
#line 135 "../../../Source/Core/AST/Scope.nll"
		while (pChild != 0)
		{
#line 137 "../../../Source/Core/AST/Scope.nll"
			pChild->Stringify(eLanguage, eOutputFile, nDepth + 1, pOutputBuilder);
#line 138 "../../../Source/Core/AST/Scope.nll"
			pChild = pChild->m_pNextSibling;
		}
#line 141 "../../../Source/Core/AST/Scope.nll"
		if (!m_bPseudo || m_pFirstChild == 0 || m_pFirstChild != m_pLastChild)
		{
#line 143 "../../../Source/Core/AST/Scope.nll"
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 144 "../../../Source/Core/AST/Scope.nll"
			pOutputBuilder->m_sOut->Append("}\n");
		}
	}

}

