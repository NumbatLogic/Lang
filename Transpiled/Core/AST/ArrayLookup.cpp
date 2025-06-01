#include "ArrayLookup.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "Identifier.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../Shared/CPP/Console.hpp"
#include "../../../Shared/CPP/Assert.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "../../../Shared/CPP/InternalString.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class OffsetDatum;
		class AST;
		class ArrayLookup;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		ArrayLookup::ArrayLookup()
		{
			m_pExpression = 0;
			m_pIndexExpression = 0;
			m_eType = AST::Type::AST_ARRAY_LOOKUP;
		}

		ArrayLookup* ArrayLookup::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
		{
			OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
			AST* pExpression = Identifier::TryCreate(pTokenContainer, pTempOffset);
			if (pExpression == 0)
			{
				if (pTempOffset) delete pTempOffset;
				if (pExpression) delete pExpression;
				return 0;
			}
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_LEFT) == 0)
			{
				if (pTempOffset) delete pTempOffset;
				if (pExpression) delete pExpression;
				return 0;
			}
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			AST* pIndexExpression = AST::TryCreateExpression(pTokenContainer, pTempOffset);
			if (pIndexExpression == 0)
			{
				Console::Log("expected index expression");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				nbAssert::Assert(false);
				{
					if (pTempOffset) delete pTempOffset;
					if (pExpression) delete pExpression;
					if (pIndexExpression) delete pIndexExpression;
					return 0;
				}
			}
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_RIGHT) == 0)
			{
				Console::Log("expected right bracket");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				nbAssert::Assert(false);
				{
					if (pTempOffset) delete pTempOffset;
					if (pExpression) delete pExpression;
					if (pIndexExpression) delete pIndexExpression;
					return 0;
				}
			}
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			ArrayLookup* pArrayLookup = new ArrayLookup();
			pArrayLookup->m_pFirstToken = pExpression->m_pFirstToken;
			pArrayLookup->m_pExpression = pExpression;
			pArrayLookup->m_pIndexExpression = pIndexExpression;
			{
				NumberDuck::Secret::AST* __1067118945 = pExpression;
				pExpression = 0;
				pArrayLookup->AddChild(__1067118945);
			}
			{
				NumberDuck::Secret::AST* __2256997130 = pIndexExpression;
				pIndexExpression = 0;
				pArrayLookup->AddChild(__2256997130);
			}
			pOffsetDatum->Set(pTempOffset);
			{
				NumberDuck::Secret::ArrayLookup* __487846044 = pArrayLookup;
				pArrayLookup = 0;
				{
					if (pTempOffset) delete pTempOffset;
					if (pExpression) delete pExpression;
					if (pIndexExpression) delete pIndexExpression;
					return __487846044;
				}
			}
		}

		AST* ArrayLookup::BaseClone()
		{
			AST* pExpression = m_pExpression->BaseClone();
			AST* pIndexExpression = m_pIndexExpression->BaseClone();
			ArrayLookup* pArrayLookup = new ArrayLookup();
			pArrayLookup->m_pFirstToken = pExpression->m_pFirstToken;
			pArrayLookup->m_pExpression = pExpression;
			pArrayLookup->m_pIndexExpression = pIndexExpression;
			{
				NumberDuck::Secret::AST* __1067118945 = pExpression;
				pExpression = 0;
				pArrayLookup->AddChild(__1067118945);
			}
			{
				NumberDuck::Secret::AST* __2256997130 = pIndexExpression;
				pIndexExpression = 0;
				pArrayLookup->AddChild(__2256997130);
			}
			{
				NumberDuck::Secret::ArrayLookup* __487846044 = pArrayLookup;
				pArrayLookup = 0;
				{
					if (pExpression) delete pExpression;
					if (pIndexExpression) delete pIndexExpression;
					return __487846044;
				}
			}
		}

		void ArrayLookup::Validate(Validator* pValidator, OperatorExpr* pParent)
		{
			AST::Validate(pValidator, pParent);
			if (m_pExpression->m_pValueType == 0)
			{
				pValidator->AddError("Unknown ValueType of m_pExpression", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				return;
			}
			m_pValueType = m_pExpression->m_pValueType->Clone();
		}

		void ArrayLookup::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
		{
			m_pExpression->Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut->AppendChar('[');
			m_pIndexExpression->Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut->AppendChar(']');
		}

	}
}

