#include "Scope.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../Shared/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../Validator.hpp"
#include "TorDecl.hpp"
#include "MemberVarDecl.hpp"
#include "VarDecl.hpp"
#include "TypeRef.hpp"
#include "../Util.hpp"
#include "../../../Shared/CPP/InternalString.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class OffsetDatum;
		class Token;
		class Scope;
		class AST;
		class TorDecl;
		class MemberVarDecl;
		class ClassDecl;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		Scope::Scope()
		{
			m_eType = AST::Type::AST_SCOPE;
		}

		Scope* Scope::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
		{
			OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
			Token* pOpeningToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_LEFT);
			if (pOpeningToken == 0)
			{
				if (pTempOffset) delete pTempOffset;
				return 0;
			}
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			Scope* pScope = new Scope();
			pScope->m_pFirstToken = pOpeningToken;
			while (true)
			{
				Token* pClosingToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_RIGHT);
				if (pClosingToken != 0)
				{
					pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
					break;
				}
				AST* pChild = AST::CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
				if (pChild == 0)
				{
					Console::Log("expected to parse somethting within scope...");
					Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
					NumbatLogic::Assert::Plz(false);
					{
						if (pChild) delete pChild;
						if (pTempOffset) delete pTempOffset;
						if (pScope) delete pScope;
						return 0;
					}
				}
				{
					NumberDuck::Secret::AST* __4076228335 = pChild;
					pChild = 0;
					pScope->AddChild(__4076228335);
				}
				if (pChild) delete pChild;
			}
			pOffsetDatum->Set(pTempOffset);
			{
				NumberDuck::Secret::Scope* __693694853 = pScope;
				pScope = 0;
				{
					if (pTempOffset) delete pTempOffset;
					return __693694853;
				}
			}
		}

		void Scope::Validate(Validator* pValidator, OperatorExpr* pParent)
		{
			pValidator->BeginScope(this);
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
					AST* pChild = pTorDecl->m_pParent->m_pFirstChild;
					while (pChild != 0)
					{
						if (pChild->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
						{
							MemberVarDecl* pMemberVarDecl = (MemberVarDecl*)(pChild);
							pValidator->AddVarDecl(pMemberVarDecl->m_pVarDecl);
							if (pMemberVarDecl->m_pVarDecl->m_pTypeRef->m_pTypeToken->m_eType == Token::Type::TOKEN_IDENTIFIER)
							{
								const char* sTypeName = pMemberVarDecl->m_pVarDecl->m_pTypeRef->m_pTypeToken->GetString();
								AST* pType = FindByName(sTypeName, this);
								if (pType != 0 && pType->m_eType == AST::Type::AST_CLASS_DECL)
								{
									ClassDecl* pClassDecl = (ClassDecl*)(pType);
									AddClassDeclReference(pClassDecl, AST::OutputFile::SOURCE, false);
								}
							}
						}
						pChild = pChild->m_pNextSibling;
					}
				}
			}
			AST::Validate(pValidator, pParent);
			pValidator->EndScope(this);
		}

		void Scope::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
		{
			Util::Pad(nDepth, sOut);
			sOut->Append("{\n");
			AST* pChild = m_pFirstChild;
			while (pChild != 0)
			{
				pChild->Stringify(eLanguage, eOutputFile, nDepth + 1, sOut);
				pChild = pChild->m_pNextSibling;
			}
			Util::Pad(nDepth, sOut);
			sOut->Append("}\n");
		}

	}
}

