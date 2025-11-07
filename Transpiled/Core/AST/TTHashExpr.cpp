#include "TTHashExpr.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "StringExpr.hpp"
#include "../ValueType.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../../../../LangShared/ExternalString/CPP/ExternalString.hpp"

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
	class InternalString;
	class ExternalString;
}
namespace NumbatLogic
{
	TTHashExpr::TTHashExpr()
	{
		m_pStringExpr = 0;
		m_eType = AST::Type::AST_TTHASH_EXP;
	}

	TTHashExpr* TTHashExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pTTHashToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_TTHASH);
		if (pTTHashToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		Token* pOpenToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT);
		if (pOpenToken == 0)
		{
			Console::Log("expected '(' ");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		StringExpr* pStringExpr = StringExpr::TryCreate(pTokenContainer, pTempOffset);
		if (pStringExpr == 0)
		{
			Console::Log("expected a string to tthash");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pStringExpr) delete pStringExpr;
			return 0;
		}
		Token* pCloseToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT);
		if (pCloseToken == 0)
		{
			Console::Log("expected ')' ");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pStringExpr) delete pStringExpr;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		TTHashExpr* pTTHashExpr = new TTHashExpr();
		pTTHashExpr->m_pFirstToken = pTTHashToken;
		pTTHashExpr->m_pStringExpr = pStringExpr;
		NumbatLogic::StringExpr* __83238656 = pStringExpr;
		pStringExpr = 0;
		pTTHashExpr->AddChild(__83238656);
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::TTHashExpr* __141090572 = pTTHashExpr;
		pTTHashExpr = 0;
		if (pTempOffset) delete pTempOffset;
		if (pStringExpr) delete pStringExpr;
		return __141090572;
	}

	void TTHashExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		m_pValueType = new ValueType(ValueType::Type::INT);
	}

	void TTHashExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		if (eLanguage == AST::Language::NLL || eLanguage == AST::Language::NLL_DEF)
		{
			sOut->Append("tthash(");
			m_pStringExpr->Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut->AppendChar(')');
		}
		else
		{
			InternalString* sTemp = new InternalString(m_pStringExpr->m_pFirstToken->m_sValue->GetExternalString());
			sTemp->Crop(1, sTemp->GetLength() - 2);
			sOut->AppendUint32(ExternalString::GetChecksum(sTemp->GetExternalString()));
			if (sTemp) delete sTemp;
		}
	}

}

