#include "CastExpr.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "TypeRef.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "ParamCall.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class CastExpr;
	class AST;
	class OffsetDatum;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class Token;
	class TypeRef;
	class TypeRef;
	class Console;
	class Assert;
	class ParamCall;
	class ParamCall;
	class CastExpr;
	class Validator;
	class AST;
	class ValueType;
	class InternalString;
}
namespace NumbatLogic
{
	CastExpr::CastExpr()
	{
		m_pTypeRef = 0;
		m_pParamCall = 0;
		m_eType = AST::Type::AST_CAST_EXP;
	}

	CastExpr* CastExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pCastToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_CAST);
		if (pCastToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		TypeRef* pTypeRef = TypeRef::TryCreate(pTokenContainer, pTempOffset);
		if (pTypeRef == 0)
		{
			Console::Log("expected TypeRef...");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
			return 0;
		}
		ParamCall* pParamCall = ParamCall::TryCreate(pTokenContainer, pTempOffset);
		if (pParamCall == 0)
		{
			Console::Log("expected ParamCall");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
			if (pParamCall) delete pParamCall;
			return 0;
		}
		CastExpr* pCastExpr = new CastExpr();
		pCastExpr->m_pFirstToken = pCastToken;
		pCastExpr->m_pTypeRef = pTypeRef;
		pCastExpr->m_pParamCall = pParamCall;
		NumbatLogic::TypeRef* __2831758689 = pTypeRef;
		pTypeRef = 0;
		pCastExpr->AddChild(__2831758689);
		NumbatLogic::ParamCall* __1229252168 = pParamCall;
		pParamCall = 0;
		pCastExpr->AddChild(__1229252168);
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::CastExpr* __2271758890 = pCastExpr;
		pCastExpr = 0;
		if (pTempOffset) delete pTempOffset;
		if (pTypeRef) delete pTypeRef;
		if (pParamCall) delete pParamCall;
		return __2271758890;
	}

	void CastExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		m_pValueType = m_pTypeRef->CreateValueType();
		if (m_pValueType == 0)
		{
			pValidator->AddError("unable to determine what to cast TO", m_pTypeRef->m_pFirstToken->m_sFileName, m_pTypeRef->m_pFirstToken->m_nLine, m_pTypeRef->m_pFirstToken->m_nColumn);
			return;
		}
		AST* pFirstChild = m_pParamCall->m_pFirstChild;
		if (pFirstChild == 0)
		{
			pValidator->AddError("no FROM param?", m_pParamCall->m_pFirstToken->m_sFileName, m_pParamCall->m_pFirstToken->m_nLine, m_pParamCall->m_pFirstToken->m_nColumn);
			return;
		}
		if (pFirstChild->m_pNextSibling != 0)
		{
			pValidator->AddError("too many no FROM params?", pFirstChild->m_pFirstToken->m_sFileName, pFirstChild->m_pFirstToken->m_nLine, pFirstChild->m_pFirstToken->m_nColumn);
			return;
		}
		if (pFirstChild->m_pValueType == 0)
		{
			pValidator->AddError("unable to determine what to cast FROM", m_pParamCall->m_pFirstToken->m_sFileName, m_pParamCall->m_pFirstToken->m_nLine, m_pParamCall->m_pFirstToken->m_nColumn);
			return;
		}
		if (m_pValueType->m_ePointerType == TypeRef::PointerType::OWNED)
		{
			pValidator->AddError("cannot cast to an owned pointer", m_pTypeRef->m_pFirstToken->m_sFileName, m_pTypeRef->m_pFirstToken->m_nLine, m_pTypeRef->m_pFirstToken->m_nColumn);
			return;
		}
		if (pFirstChild->m_pValueType->m_ePointerType != m_pValueType->m_ePointerType && m_pValueType->m_ePointerType != TypeRef::PointerType::SHARED)
		{
			pValidator->AddError("must cast to/from the same pointer type (or to shared)", m_pTypeRef->m_pFirstToken->m_sFileName, m_pTypeRef->m_pFirstToken->m_nLine, m_pTypeRef->m_pFirstToken->m_nColumn);
			return;
		}
	}

	void CastExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		if (eLanguage == AST::Language::NLL_DEF)
		{
			sOut->Append("cast ");
			m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, sOut);
			m_pParamCall->Stringify(eLanguage, eOutputFile, 0, sOut);
		}
		else
		{
			sOut->AppendChar('(');
			m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut->AppendChar(')');
			m_pParamCall->Stringify(eLanguage, eOutputFile, 0, sOut);
		}
	}

}

