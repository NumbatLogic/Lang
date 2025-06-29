#include "ParamCall.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "AST.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
	class Token;
	class ParamCall;
	class AST;
}
namespace NumbatLogic
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
			if (pTempOffset) delete pTempOffset;
			return 0;
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
			NumbatLogic::AST* __876224153 = pParam;
			pParam = 0;
			pParamCall->AddChild(__876224153);
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
		NumbatLogic::ParamCall* __474271540 = pParamCall;
		pParamCall = 0;
		if (pTempOffset) delete pTempOffset;
		return __474271540;
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

