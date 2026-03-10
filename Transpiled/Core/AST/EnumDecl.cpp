#include "EnumDecl.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "AST.hpp"
#include "EnumDeclValue.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../Util.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class EnumDecl;
	class EnumDeclValue;
	template <class T>
	class Vector;
	class Console;
	class Assert;
	class OutputBuilder;
	class InternalString;
	class Util;
}
#line 0 "../../../Source/Core/AST/EnumDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/EnumDecl.nll"
#line 8 "../../../Source/Core/AST/EnumDecl.nll"
	EnumDecl::EnumDecl()
	{
		m_pNameToken = 0;
		m_pEnumDeclValueVector = 0;
#line 10 "../../../Source/Core/AST/EnumDecl.nll"
		m_bCanDescend = true;
	}

#line 13 "../../../Source/Core/AST/EnumDecl.nll"
	EnumDecl* EnumDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pEnumToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_ENUM);
#line 18 "../../../Source/Core/AST/EnumDecl.nll"
		if (pEnumToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 19 "../../../Source/Core/AST/EnumDecl.nll"
			return 0;
		}
#line 20 "../../../Source/Core/AST/EnumDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		EnumDecl* pEnumDecl = new EnumDecl();
#line 24 "../../../Source/Core/AST/EnumDecl.nll"
		pEnumDecl->m_eType = AST::Type::AST_ENUM_DECL;
#line 25 "../../../Source/Core/AST/EnumDecl.nll"
		pEnumDecl->m_pFirstToken = pEnumToken;
#line 26 "../../../Source/Core/AST/EnumDecl.nll"
		pEnumDecl->m_pEnumDeclValueVector = new Vector<EnumDeclValue*>();
#line 28 "../../../Source/Core/AST/EnumDecl.nll"
		pEnumDecl->m_pNameToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
#line 29 "../../../Source/Core/AST/EnumDecl.nll"
		if (pEnumDecl->m_pNameToken == 0)
		{
#line 31 "../../../Source/Core/AST/EnumDecl.nll"
			Console::Log("expected enum name");
#line 32 "../../../Source/Core/AST/EnumDecl.nll"
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pEnumDecl) delete pEnumDecl;
#line 33 "../../../Source/Core/AST/EnumDecl.nll"
			return 0;
		}
#line 35 "../../../Source/Core/AST/EnumDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 37 "../../../Source/Core/AST/EnumDecl.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_LEFT) == 0)
		{
#line 39 "../../../Source/Core/AST/EnumDecl.nll"
			Console::Log("expected opening curly brace");
#line 40 "../../../Source/Core/AST/EnumDecl.nll"
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pEnumDecl) delete pEnumDecl;
#line 41 "../../../Source/Core/AST/EnumDecl.nll"
			return 0;
		}
#line 43 "../../../Source/Core/AST/EnumDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 46 "../../../Source/Core/AST/EnumDecl.nll"
		while (true)
		{
#line 48 "../../../Source/Core/AST/EnumDecl.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_RIGHT) != 0)
			{
#line 50 "../../../Source/Core/AST/EnumDecl.nll"
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 51 "../../../Source/Core/AST/EnumDecl.nll"
				break;
			}
			EnumDeclValue* pEnumDeclValue = EnumDeclValue::TryCreate(pTokenContainer, pTempOffset);
#line 55 "../../../Source/Core/AST/EnumDecl.nll"
			if (pEnumDeclValue == 0)
			{
#line 57 "../../../Source/Core/AST/EnumDecl.nll"
				Console::Log("expected EnumDeclValue");
#line 58 "../../../Source/Core/AST/EnumDecl.nll"
				Assert::Plz(false);
			}
#line 60 "../../../Source/Core/AST/EnumDecl.nll"
			pEnumDecl->m_pEnumDeclValueVector->PushBack(pEnumDeclValue);
			NumbatLogic::EnumDeclValue* __478630801 = pEnumDeclValue;
#line 61 "../../../Source/Core/AST/EnumDecl.nll"
			pEnumDeclValue = 0;
#line 61 "../../../Source/Core/AST/EnumDecl.nll"
			pEnumDecl->AddChild(__478630801);
#line 63 "../../../Source/Core/AST/EnumDecl.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_RIGHT) != 0)
			{
				if (pEnumDeclValue) delete pEnumDeclValue;
#line 64 "../../../Source/Core/AST/EnumDecl.nll"
				continue;
			}
#line 66 "../../../Source/Core/AST/EnumDecl.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COMMA) == 0)
			{
#line 68 "../../../Source/Core/AST/EnumDecl.nll"
				Console::Log("expected comma");
#line 69 "../../../Source/Core/AST/EnumDecl.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 70 "../../../Source/Core/AST/EnumDecl.nll"
				Assert::Plz(false);
			}
#line 72 "../../../Source/Core/AST/EnumDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			if (pEnumDeclValue) delete pEnumDeclValue;
		}
#line 75 "../../../Source/Core/AST/EnumDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::EnumDecl* __4282209082 = pEnumDecl;
#line 76 "../../../Source/Core/AST/EnumDecl.nll"
		pEnumDecl = 0;
		if (pTempOffset) delete pTempOffset;
#line 76 "../../../Source/Core/AST/EnumDecl.nll"
		return __4282209082;
	}

#line 79 "../../../Source/Core/AST/EnumDecl.nll"
	void EnumDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 81 "../../../Source/Core/AST/EnumDecl.nll"
		pOutputBuilder->m_sOut->Append("enum ");
#line 82 "../../../Source/Core/AST/EnumDecl.nll"
		m_pNameToken->Stringify(pOutputBuilder->m_sOut);
#line 83 "../../../Source/Core/AST/EnumDecl.nll"
		pOutputBuilder->m_sOut->AppendChar('\n');
#line 84 "../../../Source/Core/AST/EnumDecl.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 85 "../../../Source/Core/AST/EnumDecl.nll"
		pOutputBuilder->m_sOut->Append("{\n");
#line 86 "../../../Source/Core/AST/EnumDecl.nll"
		for (int i = 0; i < m_pEnumDeclValueVector->GetSize(); i++)
		{
#line 88 "../../../Source/Core/AST/EnumDecl.nll"
			Util::Pad(nDepth + 1, pOutputBuilder->m_sOut);
			EnumDeclValue* pEnumDeclValue = m_pEnumDeclValueVector->Get(i);
#line 90 "../../../Source/Core/AST/EnumDecl.nll"
			pEnumDeclValue->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 91 "../../../Source/Core/AST/EnumDecl.nll"
			pOutputBuilder->m_sOut->Append(",\n");
		}
#line 93 "../../../Source/Core/AST/EnumDecl.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 95 "../../../Source/Core/AST/EnumDecl.nll"
		if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::HEADER)
#line 96 "../../../Source/Core/AST/EnumDecl.nll"
			pOutputBuilder->m_sOut->Append("};\n");
		else
#line 98 "../../../Source/Core/AST/EnumDecl.nll"
			pOutputBuilder->m_sOut->Append("}\n");
	}

#line 3 "../../../Source/Core/AST/EnumDecl.nll"
	EnumDecl::~EnumDecl()
	{
		if (m_pEnumDeclValueVector) delete m_pEnumDeclValueVector;
	}

}

