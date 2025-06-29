#include "EnumDecl.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "EnumDeclValue.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../../../../LangShared/ExternalString/CPP/ExternalString.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../Util.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
	class Token;
	class EnumDecl;
	class EnumDeclValue;
}
namespace NumbatLogic
{
	EnumDecl::EnumDecl()
	{
		m_pNameToken = 0;
		m_pEnumDeclValueVector = 0;
		m_bCanDescend = true;
	}

	EnumDecl* EnumDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pEnumToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_ENUM);
		if (pEnumToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		EnumDecl* pEnumDecl = new EnumDecl();
		pEnumDecl->m_eType = AST::Type::AST_ENUM_DECL;
		pEnumDecl->m_pFirstToken = pEnumToken;
		pEnumDecl->m_pEnumDeclValueVector = new Vector<EnumDeclValue*>();
		pEnumDecl->m_pNameToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
		if (pEnumDecl->m_pNameToken == 0)
		{
			Console::Log("expected enum name");
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pEnumDecl) delete pEnumDecl;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_LEFT) == 0)
		{
			Console::Log("expected opening curly brace");
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pEnumDecl) delete pEnumDecl;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		while (true)
		{
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_RIGHT) != 0)
			{
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				break;
			}
			EnumDeclValue* pEnumDeclValue = EnumDeclValue::TryCreate(pTokenContainer, pTempOffset);
			if (pEnumDeclValue == 0)
			{
				Console::Log("expected EnumDeclValue");
				NumbatLogic::Assert::Plz(false);
			}
			pEnumDecl->m_pEnumDeclValueVector->PushBack(pEnumDeclValue);
			NumbatLogic::EnumDeclValue* __954462356 = pEnumDeclValue;
			pEnumDeclValue = 0;
			pEnumDecl->AddChild(__954462356);
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_RIGHT) != 0)
			{
				if (pEnumDeclValue) delete pEnumDeclValue;
				continue;
			}
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COMMA) == 0)
			{
				Console::Log("expected comma");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
			}
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			if (pEnumDeclValue) delete pEnumDeclValue;
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::EnumDecl* __3345757416 = pEnumDecl;
		pEnumDecl = 0;
		if (pTempOffset) delete pTempOffset;
		return __3345757416;
	}

	AST* EnumDecl::FindByName(const char* sxName, AST* pCallingChild)
	{
		if (ExternalString::Equal(sxName, m_pNameToken->GetString()))
			return this;
		return AST::FindByName(sxName, pCallingChild);
	}

	void EnumDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		sOut->Append("enum ");
		m_pNameToken->Stringify(sOut);
		sOut->AppendChar('\n');
		Util::Pad(nDepth, sOut);
		sOut->Append("{\n");
		for (int i = 0; i < m_pEnumDeclValueVector->GetSize(); i++)
		{
			Util::Pad(nDepth + 1, sOut);
			EnumDeclValue* pEnumDeclValue = m_pEnumDeclValueVector->Get(i);
			pEnumDeclValue->Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut->Append(",\n");
		}
		Util::Pad(nDepth, sOut);
		if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::HEADER)
			sOut->Append("};\n");
		else
			sOut->Append("}\n");
	}

	EnumDecl::~EnumDecl()
	{
		if (m_pEnumDeclValueVector) delete m_pEnumDeclValueVector;
	}

}

