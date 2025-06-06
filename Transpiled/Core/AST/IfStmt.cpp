#include "IfStmt.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "AST.hpp"
#include "../../../Shared/CPP/InternalString.hpp"
#include "../Util.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class OffsetDatum;
		class Token;
		class AST;
		class IfStmt;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		IfStmt::IfStmt()
		{
			m_bStatement = true;
		}

		IfStmt* IfStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
		{
			OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
			Token* pIfToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_IF);
			if (pIfToken == 0)
			{
				if (pTempOffset) delete pTempOffset;
				return 0;
			}
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT) == 0)
			{
				Console::Log("expected left paren");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				{
					if (pTempOffset) delete pTempOffset;
					return 0;
				}
			}
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			AST* pCondition = AST::TryCreateExpression(pTokenContainer, pTempOffset);
			if (pCondition == 0)
			{
				Console::Log("expected condition");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				{
					if (pTempOffset) delete pTempOffset;
					if (pCondition) delete pCondition;
					return 0;
				}
			}
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) == 0)
			{
				Console::Log("expected right paren");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				{
					if (pTempOffset) delete pTempOffset;
					if (pCondition) delete pCondition;
					return 0;
				}
			}
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			AST* pThen = AST::CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
			if (pThen == 0)
			{
				Console::Log("expected statement");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				{
					if (pTempOffset) delete pTempOffset;
					if (pCondition) delete pCondition;
					if (pThen) delete pThen;
					return 0;
				}
			}
			AST* pElse = 0;
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_ELSE) != 0)
			{
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				pElse = AST::CreateStatementFromTokenContainer(pTokenContainer, pTempOffset);
				if (pElse == 0)
				{
					Console::Log("expected else statement");
					Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
					NumbatLogic::Assert::Plz(false);
					{
						if (pTempOffset) delete pTempOffset;
						if (pCondition) delete pCondition;
						if (pThen) delete pThen;
						if (pElse) delete pElse;
						return 0;
					}
				}
			}
			IfStmt* pIfStmt = new IfStmt();
			pIfStmt->m_eType = AST::Type::AST_IF_STMT;
			pIfStmt->m_pFirstToken = pIfToken;
			{
				NumberDuck::Secret::AST* __3534699931 = pCondition;
				pCondition = 0;
				pIfStmt->AddChild(__3534699931);
			}
			{
				NumberDuck::Secret::AST* __1813633903 = pThen;
				pThen = 0;
				pIfStmt->AddChild(__1813633903);
			}
			if (pElse != 0)
			{
				NumberDuck::Secret::AST* __1661904051 = pElse;
				pElse = 0;
				pIfStmt->AddChild(__1661904051);
			}
			pOffsetDatum->Set(pTempOffset);
			{
				NumberDuck::Secret::IfStmt* __2301836827 = pIfStmt;
				pIfStmt = 0;
				{
					if (pTempOffset) delete pTempOffset;
					if (pCondition) delete pCondition;
					if (pThen) delete pThen;
					if (pElse) delete pElse;
					return __2301836827;
				}
			}
		}

		void IfStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
		{
			AST* pCondition = m_pFirstChild;
			AST* pThen = pCondition->m_pNextSibling;
			AST* pElse = pThen->m_pNextSibling;
			IfStmt* pParentIfStmt = 0;
			if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_IF_STMT)
				pParentIfStmt = (IfStmt*)(m_pParent);
			if (pParentIfStmt != 0 && pParentIfStmt->m_pFirstChild->m_pNextSibling->m_pNextSibling == this)
				sOut->Append(" ");
			else
				Util::Pad(nDepth, sOut);
			sOut->Append("if (");
			pCondition->Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut->Append(")\n");
			if (pThen->m_eType == AST::Type::AST_SCOPE)
				pThen->Stringify(eLanguage, eOutputFile, nDepth, sOut);
			else
				pThen->Stringify(eLanguage, eOutputFile, nDepth + 1, sOut);
			if (pElse != 0)
			{
				Util::Pad(nDepth, sOut);
				if (pElse->m_eType == AST::Type::AST_IF_STMT)
				{
					sOut->Append("else");
					pElse->Stringify(eLanguage, eOutputFile, nDepth, sOut);
				}
				else
				{
					sOut->Append("else\n");
					if (pElse->m_eType == AST::Type::AST_SCOPE)
						pElse->Stringify(eLanguage, eOutputFile, nDepth, sOut);
					else
						pElse->Stringify(eLanguage, eOutputFile, nDepth + 1, sOut);
				}
			}
		}

	}
}

