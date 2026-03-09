#include "ParamCall.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "AST.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class Console;
	class Assert;
	class ParamCall;
	class OutputBuilder;
	class InternalString;
}
#line 1 "../../../Source/Core/AST/ParamCall.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/ParamCall.nll"
#line 6 "../../../Source/Core/AST/ParamCall.nll"
	ParamCall* ParamCall::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* m_pFirstToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT);
#line 11 "../../../Source/Core/AST/ParamCall.nll"
		if (m_pFirstToken == 0)
		{
#line 13 "../../../Source/Core/AST/ParamCall.nll"
			Console::Log("expected '(' ");
#line 14 "../../../Source/Core/AST/ParamCall.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 15 "../../../Source/Core/AST/ParamCall.nll"
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
#line 16 "../../../Source/Core/AST/ParamCall.nll"
			return 0;
		}
#line 18 "../../../Source/Core/AST/ParamCall.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		ParamCall* pParamCall = new ParamCall();
#line 23 "../../../Source/Core/AST/ParamCall.nll"
		pParamCall->m_eType = AST::Type::AST_PARAM_CALL;
#line 24 "../../../Source/Core/AST/ParamCall.nll"
		pParamCall->m_pFirstToken = m_pFirstToken;
#line 26 "../../../Source/Core/AST/ParamCall.nll"
		while (true)
		{
#line 28 "../../../Source/Core/AST/ParamCall.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) != 0)
			{
#line 30 "../../../Source/Core/AST/ParamCall.nll"
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 31 "../../../Source/Core/AST/ParamCall.nll"
				break;
			}
			AST* pParam = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 35 "../../../Source/Core/AST/ParamCall.nll"
			if (pParam == 0)
			{
#line 37 "../../../Source/Core/AST/ParamCall.nll"
				Console::Log("expected param");
#line 38 "../../../Source/Core/AST/ParamCall.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 39 "../../../Source/Core/AST/ParamCall.nll"
				NumbatLogic::Assert::Plz(false);
			}
			NumbatLogic::AST* __3258004090 = pParam;
#line 42 "../../../Source/Core/AST/ParamCall.nll"
			pParam = 0;
#line 42 "../../../Source/Core/AST/ParamCall.nll"
			pParamCall->AddChild(__3258004090);
#line 44 "../../../Source/Core/AST/ParamCall.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) != 0)
			{
				if (pParam) delete pParam;
#line 45 "../../../Source/Core/AST/ParamCall.nll"
				continue;
			}
#line 47 "../../../Source/Core/AST/ParamCall.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COMMA) == 0)
			{
#line 49 "../../../Source/Core/AST/ParamCall.nll"
				Console::Log("expected comma");
#line 50 "../../../Source/Core/AST/ParamCall.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 51 "../../../Source/Core/AST/ParamCall.nll"
				NumbatLogic::Assert::Plz(false);
			}
#line 53 "../../../Source/Core/AST/ParamCall.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			if (pParam) delete pParam;
		}
#line 56 "../../../Source/Core/AST/ParamCall.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ParamCall* __1502847900 = pParamCall;
#line 57 "../../../Source/Core/AST/ParamCall.nll"
		pParamCall = 0;
		if (pTempOffset) delete pTempOffset;
#line 57 "../../../Source/Core/AST/ParamCall.nll"
		return __1502847900;
	}

#line 60 "../../../Source/Core/AST/ParamCall.nll"
	void ParamCall::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 62 "../../../Source/Core/AST/ParamCall.nll"
		pOutputBuilder->m_sOut->AppendChar('(');
		AST* pParam = m_pFirstChild;
#line 64 "../../../Source/Core/AST/ParamCall.nll"
		while (pParam != 0)
		{
#line 66 "../../../Source/Core/AST/ParamCall.nll"
			if (pParam != m_pFirstChild)
#line 67 "../../../Source/Core/AST/ParamCall.nll"
				pOutputBuilder->m_sOut->Append(", ");
#line 68 "../../../Source/Core/AST/ParamCall.nll"
			pParam->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 69 "../../../Source/Core/AST/ParamCall.nll"
			pParam = pParam->m_pNextSibling;
		}
#line 71 "../../../Source/Core/AST/ParamCall.nll"
		pOutputBuilder->m_sOut->AppendChar(')');
	}

}

