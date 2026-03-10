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
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class TypeRef;
	class Console;
	class Assert;
	class ParamCall;
	class CastExpr;
	class Validator;
	class ValueType;
	class OutputBuilder;
	class InternalString;
}
#line 0 "../../../Source/Core/AST/CastExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/CastExpr.nll"
#line 8 "../../../Source/Core/AST/CastExpr.nll"
	CastExpr::CastExpr()
	{
		m_pTypeRef = 0;
		m_pParamCall = 0;
#line 10 "../../../Source/Core/AST/CastExpr.nll"
		m_eType = AST::Type::AST_CAST_EXP;
	}

#line 13 "../../../Source/Core/AST/CastExpr.nll"
	CastExpr* CastExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pCastToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_CAST);
#line 18 "../../../Source/Core/AST/CastExpr.nll"
		if (pCastToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 19 "../../../Source/Core/AST/CastExpr.nll"
			return 0;
		}
#line 20 "../../../Source/Core/AST/CastExpr.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		TypeRef* pTypeRef = TypeRef::TryCreate(pTokenContainer, pTempOffset);
#line 23 "../../../Source/Core/AST/CastExpr.nll"
		if (pTypeRef == 0)
		{
#line 25 "../../../Source/Core/AST/CastExpr.nll"
			Console::Log("expected TypeRef...");
#line 26 "../../../Source/Core/AST/CastExpr.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 27 "../../../Source/Core/AST/CastExpr.nll"
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
#line 28 "../../../Source/Core/AST/CastExpr.nll"
			return 0;
		}
		ParamCall* pParamCall = ParamCall::TryCreate(pTokenContainer, pTempOffset);
#line 32 "../../../Source/Core/AST/CastExpr.nll"
		if (pParamCall == 0)
		{
#line 34 "../../../Source/Core/AST/CastExpr.nll"
			Console::Log("expected ParamCall");
#line 35 "../../../Source/Core/AST/CastExpr.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 36 "../../../Source/Core/AST/CastExpr.nll"
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
			if (pParamCall) delete pParamCall;
#line 37 "../../../Source/Core/AST/CastExpr.nll"
			return 0;
		}
		CastExpr* pCastExpr = new CastExpr();
#line 41 "../../../Source/Core/AST/CastExpr.nll"
		pCastExpr->m_pFirstToken = pCastToken;
#line 42 "../../../Source/Core/AST/CastExpr.nll"
		pCastExpr->m_pTypeRef = pTypeRef;
#line 43 "../../../Source/Core/AST/CastExpr.nll"
		pCastExpr->m_pParamCall = pParamCall;
		NumbatLogic::TypeRef* __2942570890 = pTypeRef;
#line 45 "../../../Source/Core/AST/CastExpr.nll"
		pTypeRef = 0;
#line 45 "../../../Source/Core/AST/CastExpr.nll"
		pCastExpr->AddChild(__2942570890);
		NumbatLogic::ParamCall* __1502782301 = pParamCall;
#line 46 "../../../Source/Core/AST/CastExpr.nll"
		pParamCall = 0;
#line 46 "../../../Source/Core/AST/CastExpr.nll"
		pCastExpr->AddChild(__1502782301);
#line 48 "../../../Source/Core/AST/CastExpr.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::CastExpr* __4190875401 = pCastExpr;
#line 49 "../../../Source/Core/AST/CastExpr.nll"
		pCastExpr = 0;
		if (pTempOffset) delete pTempOffset;
		if (pTypeRef) delete pTypeRef;
		if (pParamCall) delete pParamCall;
#line 49 "../../../Source/Core/AST/CastExpr.nll"
		return __4190875401;
	}

#line 52 "../../../Source/Core/AST/CastExpr.nll"
	void CastExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 54 "../../../Source/Core/AST/CastExpr.nll"
		AST::Validate(pValidator, pParent);
#line 55 "../../../Source/Core/AST/CastExpr.nll"
		m_pValueType = m_pTypeRef->CreateValueType(pValidator->m_pResolver);
#line 57 "../../../Source/Core/AST/CastExpr.nll"
		if (m_pValueType == 0)
		{
#line 59 "../../../Source/Core/AST/CastExpr.nll"
			pValidator->AddError("unable to determine what to cast TO", m_pTypeRef->m_pFirstToken->m_sFileName, m_pTypeRef->m_pFirstToken->m_nLine, m_pTypeRef->m_pFirstToken->m_nColumn);
#line 60 "../../../Source/Core/AST/CastExpr.nll"
			return;
		}
		AST* pFirstChild = m_pParamCall->m_pFirstChild;
#line 64 "../../../Source/Core/AST/CastExpr.nll"
		if (pFirstChild == 0)
		{
#line 66 "../../../Source/Core/AST/CastExpr.nll"
			pValidator->AddError("no FROM param?", m_pParamCall->m_pFirstToken->m_sFileName, m_pParamCall->m_pFirstToken->m_nLine, m_pParamCall->m_pFirstToken->m_nColumn);
#line 67 "../../../Source/Core/AST/CastExpr.nll"
			return;
		}
#line 70 "../../../Source/Core/AST/CastExpr.nll"
		if (pFirstChild->m_pNextSibling != 0)
		{
#line 72 "../../../Source/Core/AST/CastExpr.nll"
			pValidator->AddError("too many no FROM params?", pFirstChild->m_pFirstToken->m_sFileName, pFirstChild->m_pFirstToken->m_nLine, pFirstChild->m_pFirstToken->m_nColumn);
#line 73 "../../../Source/Core/AST/CastExpr.nll"
			return;
		}
#line 76 "../../../Source/Core/AST/CastExpr.nll"
		if (pFirstChild->m_pValueType == 0)
		{
#line 78 "../../../Source/Core/AST/CastExpr.nll"
			pValidator->AddError("unable to determine what to cast FROM", m_pParamCall->m_pFirstToken->m_sFileName, m_pParamCall->m_pFirstToken->m_nLine, m_pParamCall->m_pFirstToken->m_nColumn);
#line 79 "../../../Source/Core/AST/CastExpr.nll"
			return;
		}
#line 82 "../../../Source/Core/AST/CastExpr.nll"
		if (m_pValueType->m_ePointerType == TypeRef::PointerType::OWNED)
		{
#line 84 "../../../Source/Core/AST/CastExpr.nll"
			pValidator->AddError("cannot cast to an owned pointer", m_pTypeRef->m_pFirstToken->m_sFileName, m_pTypeRef->m_pFirstToken->m_nLine, m_pTypeRef->m_pFirstToken->m_nColumn);
#line 85 "../../../Source/Core/AST/CastExpr.nll"
			return;
		}
#line 88 "../../../Source/Core/AST/CastExpr.nll"
		if (pFirstChild->m_pValueType->m_ePointerType != m_pValueType->m_ePointerType && m_pValueType->m_ePointerType != TypeRef::PointerType::SHARED)
		{
#line 90 "../../../Source/Core/AST/CastExpr.nll"
			pValidator->AddError("must cast to/from the same pointer type (or to shared)", m_pTypeRef->m_pFirstToken->m_sFileName, m_pTypeRef->m_pFirstToken->m_nLine, m_pTypeRef->m_pFirstToken->m_nColumn);
#line 91 "../../../Source/Core/AST/CastExpr.nll"
			return;
		}
	}

#line 97 "../../../Source/Core/AST/CastExpr.nll"
	void CastExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 99 "../../../Source/Core/AST/CastExpr.nll"
		if (eLanguage == AST::Language::NLL_DEF)
		{
#line 101 "../../../Source/Core/AST/CastExpr.nll"
			pOutputBuilder->m_sOut->Append("cast ");
#line 102 "../../../Source/Core/AST/CastExpr.nll"
			m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 103 "../../../Source/Core/AST/CastExpr.nll"
			m_pParamCall->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}
		else
		{
#line 107 "../../../Source/Core/AST/CastExpr.nll"
			pOutputBuilder->m_sOut->AppendChar('(');
#line 108 "../../../Source/Core/AST/CastExpr.nll"
			m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 109 "../../../Source/Core/AST/CastExpr.nll"
			pOutputBuilder->m_sOut->AppendChar(')');
#line 110 "../../../Source/Core/AST/CastExpr.nll"
			m_pParamCall->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}
	}

}

