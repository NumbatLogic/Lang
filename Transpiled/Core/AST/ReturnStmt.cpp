#include "ReturnStmt.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../Validator.hpp"
#include "../Util.hpp"
#include "../../../Shared/CPP/InternalString.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class OffsetDatum;
		class Token;
		class AST;
		class ReturnStmt;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		ReturnStmt::ReturnStmt()
		{
			m_pExpression = 0;
			m_eType = AST::Type::AST_RETURN_STMT;
			m_bStatement = true;
		}

		ReturnStmt* ReturnStmt::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
		{
			OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
			Token* pReturnToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_RETURN);
			if (pReturnToken == 0)
			{
				if (pTempOffset) delete pTempOffset;
				return 0;
			}
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			AST* pExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
			{
				if (pTempOffset) delete pTempOffset;
				if (pExpression) delete pExpression;
				return 0;
			}
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			ReturnStmt* pReturnStmt = new ReturnStmt();
			pReturnStmt->m_pFirstToken = pReturnToken;
			pReturnStmt->m_pExpression = pExpression;
			if (pExpression != 0)
			{
				NumberDuck::Secret::AST* __1067118945 = pExpression;
				pExpression = 0;
				pReturnStmt->AddChild(__1067118945);
			}
			pOffsetDatum->Set(pTempOffset);
			{
				NumberDuck::Secret::ReturnStmt* __3384094912 = pReturnStmt;
				pReturnStmt = 0;
				{
					if (pTempOffset) delete pTempOffset;
					if (pExpression) delete pExpression;
					return __3384094912;
				}
			}
		}

		void ReturnStmt::Validate(Validator* pValidator, OperatorExpr* pParent)
		{
			AST::Validate(pValidator, pParent);
			pValidator->InjectCleanup(this);
		}

		void ReturnStmt::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
		{
			Util::Pad(nDepth, sOut);
			sOut->AppendString("return");
			if (m_pExpression != 0)
			{
				sOut->AppendChar(' ');
				m_pExpression->Stringify(eLanguage, eOutputFile, 0, sOut);
			}
			sOut->AppendString(";\n");
		}

	}
}

