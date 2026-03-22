#include "EnumDecl.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "AST.hpp"
#include "EnumDeclValue.hpp"
#include "../../../../LangShared/Source/Vector/CPP/Vector.hpp"
#include "../../../../LangShared/Source/Console/CPP/Console.hpp"
#include "../../../../LangShared/Source/Assert/CPP/Assert.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"
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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
#line 8 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
	EnumDecl::EnumDecl()
	{
		m_pNameToken = 0;
		m_pEnumDeclValueVector = 0;
#line 10 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
		m_bCanDescend = true;
	}

	EnumDecl* EnumDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
		Token* pEnumToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_ENUM);
		if (pEnumToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
			return 0;
		}
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
		EnumDecl* pEnumDecl = new EnumDecl();
#line 24 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
		pEnumDecl->m_eType = AST::Type::AST_ENUM_DECL;
		pEnumDecl->m_pFirstToken = pEnumToken;
		pEnumDecl->m_pEnumDeclValueVector = new Vector<EnumDeclValue*>();
#line 28 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
		pEnumDecl->m_pNameToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
		if (pEnumDecl->m_pNameToken == 0)
		{
			Console::Log("expected enum name");
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pEnumDecl) delete pEnumDecl;
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_LEFT) == 0)
		{
			Console::Log("expected opening curly brace");
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pEnumDecl) delete pEnumDecl;
#line 41 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
		while (true)
		{
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_RIGHT) != 0)
			{
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				break;
			}
#line 54 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
			EnumDeclValue* pEnumDeclValue = EnumDeclValue::TryCreate(pTokenContainer, pTempOffset);
			if (pEnumDeclValue == 0)
			{
				Console::Log("expected EnumDeclValue");
				Assert::Plz(false);
			}
			pEnumDecl->m_pEnumDeclValueVector->PushBack(pEnumDeclValue);
			NumbatLogic::EnumDeclValue* __478630801 = pEnumDeclValue;
#line 61 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
			pEnumDeclValue = 0;
#line 61 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
			pEnumDecl->AddChild(__478630801);
#line 63 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_RIGHT) != 0)
			{
				if (pEnumDeclValue) delete pEnumDeclValue;
#line 64 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
				continue;
			}
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COMMA) == 0)
			{
				Console::Log("expected comma");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				Assert::Plz(false);
			}
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			if (pEnumDeclValue) delete pEnumDeclValue;
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::EnumDecl* __4282209082 = pEnumDecl;
#line 76 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
		pEnumDecl = 0;
		if (pTempOffset) delete pTempOffset;
#line 76 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
		return __4282209082;
	}

	void EnumDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		pOutputBuilder->m_sOut->Append("enum ");
		m_pNameToken->Stringify(pOutputBuilder->m_sOut);
		pOutputBuilder->m_sOut->AppendChar('\n');
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
		pOutputBuilder->m_sOut->Append("{\n");
		for (int i = 0; i < m_pEnumDeclValueVector->GetSize(); i++)
		{
			Util::Pad(nDepth + 1, pOutputBuilder->m_sOut);
			EnumDeclValue* pEnumDeclValue = m_pEnumDeclValueVector->Get(i);
			pEnumDeclValue->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			pOutputBuilder->m_sOut->Append(",\n");
		}
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 95 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
		if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::HEADER)
			pOutputBuilder->m_sOut->Append("};\n");
		else
			pOutputBuilder->m_sOut->Append("}\n");
	}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/EnumDecl.nll"
	EnumDecl::~EnumDecl()
	{
		if (m_pEnumDeclValueVector) delete m_pEnumDeclValueVector;
	}

}

