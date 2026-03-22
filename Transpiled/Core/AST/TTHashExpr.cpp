#include "TTHashExpr.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Source/Console/CPP/Console.hpp"
#include "../../../../LangShared/Source/Assert/CPP/Assert.hpp"
#include "StringExpr.hpp"
#include "../ValueType.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"
#include "../../../../LangShared/Source/ExternalString/CPP/ExternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class Console;
	class Assert;
	class StringExpr;
	class TTHashExpr;
	class ValueType;
	class OutputBuilder;
	class InternalString;
	class ExternalString;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
#line 7 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
	TTHashExpr::TTHashExpr()
	{
		m_pStringExpr = 0;
#line 9 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
		m_eType = AST::Type::AST_TTHASH_EXP;
	}

	TTHashExpr* TTHashExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
		Token* pTTHashToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_TTHASH);
		if (pTTHashToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 18 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
			return 0;
		}
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 21 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
		Token* pOpenToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT);
		if (pOpenToken == 0)
		{
			Console::Log("expected '(' ");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
#line 27 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 31 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
		StringExpr* pStringExpr = StringExpr::TryCreate(pTokenContainer, pTempOffset);
		if (pStringExpr == 0)
		{
			Console::Log("expected a string to tthash");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pStringExpr) delete pStringExpr;
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
			return 0;
		}
#line 40 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
		Token* pCloseToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT);
		if (pCloseToken == 0)
		{
			Console::Log("expected ')' ");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pStringExpr) delete pStringExpr;
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 51 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
		TTHashExpr* pTTHashExpr = new TTHashExpr();
		pTTHashExpr->m_pFirstToken = pTTHashToken;
		pTTHashExpr->m_pStringExpr = pStringExpr;
		NumbatLogic::StringExpr* __1742876149 = pStringExpr;
#line 54 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
		pStringExpr = 0;
#line 54 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
		pTTHashExpr->AddChild(__1742876149);
#line 56 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::TTHashExpr* __4133333365 = pTTHashExpr;
#line 57 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
		pTTHashExpr = 0;
		if (pTempOffset) delete pTempOffset;
		if (pStringExpr) delete pStringExpr;
#line 57 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
		return __4133333365;
	}

	void TTHashExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		m_pValueType = new ValueType(ValueType::Type::INT);
	}

	void TTHashExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		if (eLanguage == AST::Language::NLL || eLanguage == AST::Language::NLL_DEF)
		{
			pOutputBuilder->m_sOut->Append("tthash(");
			m_pStringExpr->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			pOutputBuilder->m_sOut->AppendChar(')');
		}
		else
		{
			InternalString* sTemp = new InternalString(m_pStringExpr->m_pFirstToken->m_sValue->GetExternalString());
			sTemp->Crop(1, sTemp->GetLength() - 2);
			pOutputBuilder->m_sOut->AppendUint32(ExternalString::GetChecksum(sTemp->GetExternalString()));
			if (sTemp) delete sTemp;
		}
	}

}

