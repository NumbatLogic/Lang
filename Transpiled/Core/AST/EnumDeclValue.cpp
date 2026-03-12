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
		m_pFirstToken = pFirstToken;
	}

	EnumDeclValue* EnumDeclValue::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 17 "../../../Source/Core/AST/EnumDeclValue.nll"
		Token* pToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
		if (pToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 19 "../../../Source/Core/AST/EnumDeclValue.nll"
			return 0;
		}
#line 20 "../../../Source/Core/AST/EnumDeclValue.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 22 "../../../Source/Core/AST/EnumDeclValue.nll"
		EnumDeclValue* pEnumDeclValue = new EnumDeclValue(pToken);
#line 25 "../../../Source/Core/AST/EnumDeclValue.nll"
		Token* pEqualsToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_EQUALS);
		if (pEqualsToken != 0)
		{
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 30 "../../../Source/Core/AST/EnumDeclValue.nll"
			pEnumDeclValue->m_pForceValue = AST::TryCreateExpression(pTokenContainer, pTempOffset);
			if (pEnumDeclValue->m_pForceValue == 0)
			{
				Console::Log("expected to parse something...");
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

	void EnumDeclValue::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		m_pFirstToken->Stringify(pOutputBuilder->m_sOut);
		if (m_pForceValue != 0)
		{
			pOutputBuilder->m_sOut->AppendString(" = ");
			m_pForceValue->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}
	}

#line 3 "../../../Source/Core/AST/EnumDeclValue.nll"
	EnumDeclValue::~EnumDeclValue()
	{
		if (m_pForceValue) delete m_pForceValue;
	}

}

