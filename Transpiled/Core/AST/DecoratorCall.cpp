#include "DecoratorCall.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"
#include "ParamCall.hpp"
#include "AST.hpp"
#include "../Validator.hpp"
#include "FunctionDecl.hpp"
#include "MemberFunctionDecl.hpp"
#include "ParamDecl.hpp"
#include "../../../../LangShared/Source/Vector/CPP/Vector.hpp"
#include "VarDecl.hpp"
#include "TypeRef.hpp"
#include "../../../../LangShared/Source/ExternalString/CPP/ExternalString.hpp"
#include "../OutputBuilder.hpp"
#include "../Util.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class InternalString;
	class ParamCall;
	class DecoratorCall;
	class Validator;
	class FunctionDecl;
	class MemberFunctionDecl;
	class ParamDecl;
	template <class T>
	class Vector;
	class VarDecl;
	class TypeRef;
	class ExternalString;
	class OutputBuilder;
	class Util;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
	DecoratorCall* DecoratorCall::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
		Token* pDecoratorToken = pTokenContainer->Peek(pTempOffset);
		if (pDecoratorToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
			return 0;
		}
		if (pDecoratorToken->m_eType != Token::Type::TOKEN_IDENTIFIER)
		{
			if (pTempOffset) delete pTempOffset;
#line 25 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
			return 0;
		}
		InternalString* sDecoratorName = new InternalString(pDecoratorToken->GetString());
		if (!sDecoratorName->StartsWith("@"))
		{
			if (pTempOffset) delete pTempOffset;
			if (sDecoratorName) delete sDecoratorName;
#line 29 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
			return 0;
		}
#line 30 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
		ParamCall* pParamCall = ParamCall::TryCreate(pTokenContainer, pTempOffset);
		if (pParamCall == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (sDecoratorName) delete sDecoratorName;
			if (pParamCall) delete pParamCall;
#line 35 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
			return 0;
		}
		DecoratorCall* pDecoratorCall = new DecoratorCall();
		pDecoratorCall->m_eType = AST::Type::AST_DECORATOR_CALL;
		pDecoratorCall->m_pFirstToken = pDecoratorToken;
		pDecoratorCall->m_pDecoratorNameToken = pDecoratorToken;
		pDecoratorCall->m_pParamCall = pParamCall;
#line 43 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
		pDecoratorCall->m_eDecoratorType = DecoratorType::UNKNOWN;
		if (sDecoratorName->IsEqual("@Dummy"))
			pDecoratorCall->m_eDecoratorType = DecoratorType::DUMMY;
		else
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
			if (sDecoratorName->IsEqual("@EntryPoint"))
				pDecoratorCall->m_eDecoratorType = DecoratorType::ENTRY_POINT;
		NumbatLogic::ParamCall* __1502782304 = pParamCall;
		pParamCall = 0;
#line 49 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
		pDecoratorCall->AddChild(__1502782304);
#line 51 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::DecoratorCall* __1592970758 = pDecoratorCall;
#line 52 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
		pDecoratorCall = 0;
		if (pTempOffset) delete pTempOffset;
		if (sDecoratorName) delete sDecoratorName;
		if (pParamCall) delete pParamCall;
#line 52 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
		return __1592970758;
	}

	void DecoratorCall::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		if (m_eDecoratorType == DecoratorType::UNKNOWN)
		{
			InternalString* sError = new InternalString("Unknown decorator: ");
			sError->Append(m_pDecoratorNameToken->GetString());
			pValidator->AddError(sError->GetExternalString(), m_pDecoratorNameToken->m_sFileName, m_pDecoratorNameToken->m_nLine, m_pDecoratorNameToken->m_nColumn);
			if (sError) delete sError;
		}
		if (m_eDecoratorType == DecoratorType::ENTRY_POINT)
		{
			if (m_pParent == 0 || m_pParent->m_eType != AST::Type::AST_FUNCTION_DECL)
			{
				InternalString* sError = new InternalString("Decorator ");
				sError->Append(m_pDecoratorNameToken->GetString());
				sError->Append(" must be attached to a function");
				pValidator->AddError(sError->GetExternalString(), m_pDecoratorNameToken->m_sFileName, m_pDecoratorNameToken->m_nLine, m_pDecoratorNameToken->m_nColumn);
				if (sError) delete sError;
			}
			else
			{
#line 75 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
				FunctionDecl* pFunctionDecl = (FunctionDecl*)(m_pParent);
				if (pFunctionDecl->m_pParent == 0 || pFunctionDecl->m_pParent->m_eType != AST::Type::AST_MEMBER_FUNCTION_DECL || !((MemberFunctionDecl*)(pFunctionDecl->m_pParent))->m_bStatic)
					pValidator->AddError("@EntryPoint must be on a static member function", m_pDecoratorNameToken->m_sFileName, m_pDecoratorNameToken->m_nLine, m_pDecoratorNameToken->m_nColumn);
#line 79 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
				if (pFunctionDecl->m_pParamDecl == 0 || pFunctionDecl->m_pParamDecl->m_pParamVector->GetSize() != 1)
				{
					pValidator->AddError("@EntryPoint function must have exactly 1 parameter: Vector<string>", m_pDecoratorNameToken->m_sFileName, m_pDecoratorNameToken->m_nLine, m_pDecoratorNameToken->m_nColumn);
				}
				else
				{
					VarDecl* pParam = pFunctionDecl->m_pParamDecl->m_pParamVector->Get(0);
					TypeRef* pTypeRef = pParam->m_pTypeRef;
					bool bValidType = pTypeRef != 0 && pTypeRef->m_pTypeToken != 0 && pTypeRef->m_pTypeToken->m_eType == Token::Type::TOKEN_IDENTIFIER && ExternalString::Equal("Vector", pTypeRef->m_pTypeToken->GetString()) && pTypeRef->m_pGenericTypeRefVector->GetSize() == 1;
#line 93 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
					if (bValidType)
					{
						TypeRef* pInnerTypeRef = pTypeRef->m_pGenericTypeRefVector->Get(0);
						bValidType = pInnerTypeRef != 0 && pInnerTypeRef->m_pTypeToken != 0 && pInnerTypeRef->m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_STRING;
					}
#line 101 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
					if (!bValidType)
						pValidator->AddError("@EntryPoint function parameter must be Vector<string>", pParam->m_pFirstToken->m_sFileName, pParam->m_pFirstToken->m_nLine, pParam->m_pFirstToken->m_nColumn);
				}
			}
		}
#line 107 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
		AST::Validate(pValidator, pParent);
	}

	void DecoratorCall::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		if (eLanguage != AST::Language::NLL)
			return;
#line 115 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
		if (nDepth > 0 && m_pFirstToken != 0)
			pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 118 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
		m_pDecoratorNameToken->Stringify(pOutputBuilder->m_sOut);
		m_pParamCall->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
	}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
	DecoratorCall::DecoratorCall()
	{
		m_eDecoratorType = DecoratorType::UNKNOWN;
		m_pDecoratorNameToken = 0;
		m_pParamCall = 0;
	}

}

