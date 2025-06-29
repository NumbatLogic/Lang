#include "EnumDeclValue.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../../../../LangShared/ExternalString/CPP/ExternalString.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
	class Token;
	class EnumDeclValue;
}
namespace NumbatLogic
{
	EnumDeclValue::EnumDeclValue(Token* pFirstToken)
	{
		m_pForceValue = 0;
		m_eType = AST::Type::ENUM_DECL_VALUE;
		m_pFirstToken = pFirstToken;
	}

	EnumDeclValue* EnumDeclValue::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
		if (pToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		EnumDeclValue* pEnumDeclValue = new EnumDeclValue(pToken);
		Token* pEqualsToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_EQUALS);
		if (pEqualsToken != 0)
		{
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			pEnumDeclValue->m_pForceValue = AST::TryCreateExpression(pTokenContainer, pTempOffset);
			if (pEnumDeclValue->m_pForceValue == 0)
			{
				Console::Log("expected to parse something...");
				NumbatLogic::Assert::Plz(false);
				if (pTempOffset) delete pTempOffset;
				if (pEnumDeclValue) delete pEnumDeclValue;
				return 0;
			}
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::EnumDeclValue* __3778153840 = pEnumDeclValue;
		pEnumDeclValue = 0;
		if (pTempOffset) delete pTempOffset;
		return __3778153840;
	}

	AST* EnumDeclValue::FindByName(const char* sxName, AST* pCallingChild)
	{
		if (ExternalString::Equal(sxName, m_pFirstToken->GetString()))
			return this;
		return AST::FindByName(sxName, pCallingChild);
	}

	void EnumDeclValue::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		m_pFirstToken->Stringify(sOut);
		if (m_pForceValue != 0)
		{
			sOut->AppendString(" = ");
			m_pForceValue->Stringify(eLanguage, eOutputFile, 0, sOut);
		}
	}

	EnumDeclValue::~EnumDeclValue()
	{
		if (m_pForceValue) delete m_pForceValue;
	}

}

