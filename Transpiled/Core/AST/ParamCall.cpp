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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/ParamCall.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/ParamCall.nll"
#line 5 "/home/cliffya/git/Lang/Source/Core/AST/ParamCall.nll"
	ParamCall* ParamCall::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 9 "/home/cliffya/git/Lang/Source/Core/AST/ParamCall.nll"
		Token* m_pFirstToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT);
		if (m_pFirstToken == 0)
		{
			Console::Log("expected '(' ");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
#line 15 "/home/cliffya/git/Lang/Source/Core/AST/ParamCall.nll"
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/ParamCall.nll"
		ParamCall* pParamCall = new ParamCall();
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/ParamCall.nll"
		pParamCall->m_eType = AST::Type::AST_PARAM_CALL;
		pParamCall->m_pFirstToken = m_pFirstToken;
#line 25 "/home/cliffya/git/Lang/Source/Core/AST/ParamCall.nll"
		while (true)
		{
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) != 0)
			{
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				break;
			}
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/ParamCall.nll"
			AST* pParam = AST::TryCreateExpression(pTokenContainer, pTempOffset);
			if (pParam == 0)
			{
				Console::Log("expected param");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
			}
			NumbatLogic::AST* __3258004090 = pParam;
			pParam = 0;
#line 41 "/home/cliffya/git/Lang/Source/Core/AST/ParamCall.nll"
			pParamCall->AddChild(__3258004090);
#line 43 "/home/cliffya/git/Lang/Source/Core/AST/ParamCall.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) != 0)
			{
				if (pParam) delete pParam;
#line 44 "/home/cliffya/git/Lang/Source/Core/AST/ParamCall.nll"
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
		NumbatLogic::ParamCall* __1502847900 = pParamCall;
#line 56 "/home/cliffya/git/Lang/Source/Core/AST/ParamCall.nll"
		pParamCall = 0;
		if (pTempOffset) delete pTempOffset;
#line 56 "/home/cliffya/git/Lang/Source/Core/AST/ParamCall.nll"
		return __1502847900;
	}

	void ParamCall::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		pOutputBuilder->m_sOut->AppendChar('(');
		AST* pParam = m_pFirstChild;
		while (pParam != 0)
		{
			if (pParam != m_pFirstChild)
				pOutputBuilder->m_sOut->Append(", ");
			pParam->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			pParam = pParam->m_pNextSibling;
		}
		pOutputBuilder->m_sOut->AppendChar(')');
	}

}

