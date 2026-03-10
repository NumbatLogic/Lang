#include "EnumDeclValue.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class EnumDeclValue;
	class Console;
	class Assert;
	class OutputBuilder;
	class InternalString;
}
#line 0 "../../../Source/Core/AST/EnumDeclValue.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/EnumDeclValue.nll"
#line 7 "../../../Source/Core/AST/EnumDeclValue.nll"
	EnumDeclValue::EnumDeclValue(Token* pFirstToken)
	{
		m_pForceValue = 0;
#line 9 "../../../Source/Core/AST/EnumDeclValue.nll"
		m_eType = AST::Type::ENUM_DECL_VALUE;
#line 10 "../../../Source/Core/AST/EnumDeclValue.nll"
		m_pFirstToken = pFirstToken;
	}

#line 13 "../../../Source/Core/AST/EnumDeclValue.nll"
	EnumDeclValue* EnumDeclValue::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
#line 18 "../../../Source/Core/AST/EnumDeclValue.nll"
		if (pToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 19 "../../../Source/Core/AST/EnumDeclValue.nll"
			return 0;
		}
#line 20 "../../../Source/Core/AST/EnumDeclValue.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		EnumDeclValue* pEnumDeclValue = new EnumDeclValue(pToken);
		Token* pEqualsToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_EQUALS);
#line 26 "../../../Source/Core/AST/EnumDeclValue.nll"
		if (pEqualsToken != 0)
		{
#line 28 "../../../Source/Core/AST/EnumDeclValue.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 30 "../../../Source/Core/AST/EnumDeclValue.nll"
			pEnumDeclValue->m_pForceValue = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 31 "../../../Source/Core/AST/EnumDeclValue.nll"
			if (pEnumDeclValue->m_pForceValue == 0)
			{
#line 33 "../../../Source/Core/AST/EnumDeclValue.nll"
				Console::Log("expected to parse something...");
#line 34 "../../../Source/Core/AST/EnumDeclValue.nll"
				Assert::Plz(false);
				if (pTempOffset) delete pTempOffset;
				if (pEnumDeclValue) delete pEnumDeclValue;
#line 35 "../../../Source/Core/AST/EnumDeclValue.nll"
				return 0;
			}
		}
#line 39 "../../../Source/Core/AST/EnumDeclValue.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::EnumDeclValue* __478499602 = pEnumDeclValue;
#line 40 "../../../Source/Core/AST/EnumDeclValue.nll"
		pEnumDeclValue = 0;
		if (pTempOffset) delete pTempOffset;
#line 40 "../../../Source/Core/AST/EnumDeclValue.nll"
		return __478499602;
	}

#line 43 "../../../Source/Core/AST/EnumDeclValue.nll"
	void EnumDeclValue::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 45 "../../../Source/Core/AST/EnumDeclValue.nll"
		m_pFirstToken->Stringify(pOutputBuilder->m_sOut);
#line 46 "../../../Source/Core/AST/EnumDeclValue.nll"
		if (m_pForceValue != 0)
		{
#line 48 "../../../Source/Core/AST/EnumDeclValue.nll"
			pOutputBuilder->m_sOut->AppendString(" = ");
#line 49 "../../../Source/Core/AST/EnumDeclValue.nll"
			m_pForceValue->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}
	}

#line 3 "../../../Source/Core/AST/EnumDeclValue.nll"
	EnumDeclValue::~EnumDeclValue()
	{
		if (m_pForceValue) delete m_pForceValue;
	}

}

