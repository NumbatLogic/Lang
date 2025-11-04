#include "ParamCall.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "AST.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "ParamDecl.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "VarDecl.hpp"
#include "TypeRef.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class Console;
	class Assert;
	class ParamCall;
	class InternalString;
	class VarDecl;
	class ParamDecl;
	template <class T>
	class Vector;
	class TypeRef;
}
namespace NumbatLogic
{
	ParamCall* ParamCall::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* m_pFirstToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT);
		if (m_pFirstToken == 0)
		{
			Console::Log("expected '(' ");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		ParamCall* pParamCall = new ParamCall();
		pParamCall->m_eType = AST::Type::AST_PARAM_CALL;
		pParamCall->m_pFirstToken = m_pFirstToken;
		while (true)
		{
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) != 0)
			{
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				break;
			}
			AST* pParam = AST::TryCreateExpression(pTokenContainer, pTempOffset);
			if (pParam == 0)
			{
				Console::Log("expected param");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
			}
			NumbatLogic::AST* __1782193718 = pParam;
			pParam = 0;
			pParamCall->AddChild(__1782193718);
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) != 0)
			{
				if (pParam) delete pParam;
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
		NumbatLogic::ParamCall* __2252655830 = pParamCall;
		pParamCall = 0;
		if (pTempOffset) delete pTempOffset;
		return __2252655830;
	}

	void ParamCall::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		sOut->AppendChar('(');
		AST* pParam = m_pFirstChild;
		int index = 0;
		while (pParam != 0)
		{
			VarDecl* pDeclParam = m_pFoundParamDecl != 0 ? m_pFoundParamDecl->m_pParamVector->Get(index) : 0;
			if (pParam != m_pFirstChild)
				sOut->Append(", ");
			if (eLanguage == AST::Language::CS && pDeclParam != 0 && pDeclParam->m_pTypeRef->m_bRef)
			{
			}
			pParam->Stringify(eLanguage, eOutputFile, 0, sOut);
			pParam = pParam->m_pNextSibling;
			index++;
		}
		sOut->AppendChar(')');
	}

	ParamCall::ParamCall()
	{
		m_pFoundParamDecl = 0;
	}

}

