#include "CastExpr.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "TypeRef.hpp"
#include "../../../../LangShared/Source/Console/CPP/Console.hpp"
#include "../../../../LangShared/Source/Assert/CPP/Assert.hpp"
#include "ParamCall.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"

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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
#line 8 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
	CastExpr::CastExpr()
	{
		m_pTypeRef = 0;
		m_pParamCall = 0;
#line 10 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		m_eType = AST::Type::AST_CAST_EXP;
	}

	CastExpr* CastExpr::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		Token* pCastToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_CAST);
		if (pCastToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
			return 0;
		}
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		TypeRef* pTypeRef = TypeRef::TryCreate(pTokenContainer, pTempOffset);
		if (pTypeRef == 0)
		{
			Console::Log("expected TypeRef...");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
#line 28 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
			return 0;
		}
#line 31 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		ParamCall* pParamCall = ParamCall::TryCreate(pTokenContainer, pTempOffset);
		if (pParamCall == 0)
		{
			Console::Log("expected ParamCall");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
			if (pParamCall) delete pParamCall;
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
			return 0;
		}
#line 40 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		CastExpr* pCastExpr = new CastExpr();
		pCastExpr->m_pFirstToken = pCastToken;
		pCastExpr->m_pTypeRef = pTypeRef;
		pCastExpr->m_pParamCall = pParamCall;
		NumbatLogic::TypeRef* __2942570890 = pTypeRef;
		pTypeRef = 0;
#line 45 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		pCastExpr->AddChild(__2942570890);
		NumbatLogic::ParamCall* __1502782301 = pParamCall;
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		pParamCall = 0;
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		pCastExpr->AddChild(__1502782301);
#line 48 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::CastExpr* __4190875401 = pCastExpr;
#line 49 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		pCastExpr = 0;
		if (pTempOffset) delete pTempOffset;
		if (pTypeRef) delete pTypeRef;
		if (pParamCall) delete pParamCall;
#line 49 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		return __4190875401;
	}

	void CastExpr::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		m_pValueType = m_pTypeRef->CreateValueType(pValidator->m_pResolver);
#line 57 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		if (m_pValueType == 0)
		{
			pValidator->AddError("unable to determine what to cast TO", m_pTypeRef->m_pFirstToken->m_sFileName, m_pTypeRef->m_pFirstToken->m_nLine, m_pTypeRef->m_pFirstToken->m_nColumn);
			return;
		}
#line 63 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		AST* pFirstChild = m_pParamCall->m_pFirstChild;
		if (pFirstChild == 0)
		{
			pValidator->AddError("no FROM param?", m_pParamCall->m_pFirstToken->m_sFileName, m_pParamCall->m_pFirstToken->m_nLine, m_pParamCall->m_pFirstToken->m_nColumn);
			return;
		}
#line 70 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		if (pFirstChild->m_pNextSibling != 0)
		{
			pValidator->AddError("too many no FROM params?", pFirstChild->m_pFirstToken->m_sFileName, pFirstChild->m_pFirstToken->m_nLine, pFirstChild->m_pFirstToken->m_nColumn);
			return;
		}
#line 76 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		if (pFirstChild->m_pValueType == 0)
		{
			pValidator->AddError("unable to determine what to cast FROM", m_pParamCall->m_pFirstToken->m_sFileName, m_pParamCall->m_pFirstToken->m_nLine, m_pParamCall->m_pFirstToken->m_nColumn);
			return;
		}
#line 82 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		if (m_pValueType->m_ePointerType == TypeRef::PointerType::OWNED)
		{
			pValidator->AddError("cannot cast to an owned pointer", m_pTypeRef->m_pFirstToken->m_sFileName, m_pTypeRef->m_pFirstToken->m_nLine, m_pTypeRef->m_pFirstToken->m_nColumn);
			return;
		}
#line 88 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
		if (pFirstChild->m_pValueType->m_ePointerType != m_pValueType->m_ePointerType && m_pValueType->m_ePointerType != TypeRef::PointerType::SHARED)
		{
			pValidator->AddError("must cast to/from the same pointer type (or to shared)", m_pTypeRef->m_pFirstToken->m_sFileName, m_pTypeRef->m_pFirstToken->m_nLine, m_pTypeRef->m_pFirstToken->m_nColumn);
			return;
		}
	}

#line 97 "/home/cliffya/git/Lang/Source/Core/AST/CastExpr.nll"
	void CastExpr::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		if (eLanguage == AST::Language::NLL_DEF)
		{
			pOutputBuilder->m_sOut->Append("cast ");
			m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			m_pParamCall->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}
		else
		{
			pOutputBuilder->m_sOut->AppendChar('(');
			m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			pOutputBuilder->m_sOut->AppendChar(')');
			m_pParamCall->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}
	}

}

