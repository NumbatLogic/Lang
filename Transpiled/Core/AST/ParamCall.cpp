#include "ParamCall.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../Shared/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "AST.hpp"
#include "../../../Shared/CPP/InternalString.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class OffsetDatum;
		class Token;
		class ParamCall;
		class AST;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		ParamCall* ParamCall::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
		{
			OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
			Token* m_pFirstToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT);
			if (m_pFirstToken == 0)
			{
				Console::Log("expected '(' ");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				{
					if (pTempOffset) delete pTempOffset;
					return 0;
				}
			}
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			ParamCall* pParamCall = new ParamCall();
			pParamCall->m_eType = AST::Type::AST_PARAM_CALL;
			pParamCall->m_pFirstToken = m_pFirstToken;
			while (true)
			{
				if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) != 0)
				{
					pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
					break;
				}
				AST* pParam = AST::TryCreateExpression(pTokenContainer, pTempOffset);
				if (pParam == 0)
				{
					Console::Log("expected param");
					Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
					NumbatLogic::Assert::Plz(false);
				}
				{
					NumberDuck::Secret::AST* __3343749822 = pParam;
					pParam = 0;
					pParamCall->AddChild(__3343749822);
				}
				if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) != 0)
				{
					if (pParam) delete pParam;
					continue;
				}
				if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COMMA) == 0)
				{
					Console::Log("expected comma");
					Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
					NumbatLogic::Assert::Plz(false);
				}
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				if (pParam) delete pParam;
			}
			pOffsetDatum->Set(pTempOffset);
			{
				NumberDuck::Secret::ParamCall* __3062759993 = pParamCall;
				pParamCall = 0;
				{
					if (pTempOffset) delete pTempOffset;
					return __3062759993;
				}
			}
		}

		void ParamCall::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
		{
			sOut->AppendChar('(');
			AST* pParam = m_pFirstChild;
			while (pParam != 0)
			{
				if (pParam != m_pFirstChild)
					sOut->Append(", ");
				pParam->Stringify(eLanguage, eOutputFile, 0, sOut);
				pParam = pParam->m_pNextSibling;
			}
			sOut->AppendChar(')');
		}

	}
}

