#include "ExpressionStmt.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../Util.hpp"
#include "../../../Shared/CPP/InternalString.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class OffsetDatum;
		class AST;
		class ExpressionStmt;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		ExpressionStmt::ExpressionStmt()
		{
			m_pExpression = 0;
			m_eType = AST::Type::AST_EXPRESSION_STMT;
			m_bStatement = true;
		}

		ExpressionStmt* ExpressionStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
		{
			OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
			AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
			if (pExpression == 0)
			{
				if (pTempOffset) delete pTempOffset;
				if (pExpression) delete pExpression;
				return 0;
			}
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
			{
				if (pTempOffset) delete pTempOffset;
				if (pExpression) delete pExpression;
				return 0;
			}
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			ExpressionStmt* pExpressionStmt = new ExpressionStmt();
			pExpressionStmt->m_pFirstToken = pExpression->m_pFirstToken;
			pExpressionStmt->m_pExpression = pExpression;
			{
				NumberDuck::Secret::AST* __1067118945 = pExpression;
				pExpression = 0;
				pExpressionStmt->AddChild(__1067118945);
			}
			pOffsetDatum->Set(pTempOffset);
			{
				NumberDuck::Secret::ExpressionStmt* __817911874 = pExpressionStmt;
				pExpressionStmt = 0;
				{
					if (pTempOffset) delete pTempOffset;
					if (pExpression) delete pExpression;
					return __817911874;
				}
			}
		}

		void ExpressionStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
		{
			Util::Pad(nDepth, sOut);
			m_pExpression->Stringify(eLanguage, eOutputFile, nDepth, sOut);
			sOut->Append(";\n");
		}

	}
}

