#include "New.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "TypeRef.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "ParamCall.hpp"
#include "AST.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "ClassDecl.hpp"
#include "TorDecl.hpp"
#include "ParamDecl.hpp"
#include "../OutputBuilder.hpp"

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
	class New;
	class Validator;
	class ValueType;
	class InternalString;
	class ClassDecl;
	class TorDecl;
	class ParamDecl;
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/New.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/New.nll"
#line 8 "../../../Source/Core/AST/New.nll"
	New* New::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
#line 10 "../../../Source/Core/AST/New.nll"
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 12 "../../../Source/Core/AST/New.nll"
		Token* pNewToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_NEW);
#line 13 "../../../Source/Core/AST/New.nll"
		if (pNewToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 14 "../../../Source/Core/AST/New.nll"
			return 0;
		}
#line 15 "../../../Source/Core/AST/New.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 17 "../../../Source/Core/AST/New.nll"
		TypeRef* pTypeRef = TypeRef::TryCreate(pTokenContainer, pTempOffset);
#line 18 "../../../Source/Core/AST/New.nll"
		if (pTypeRef == 0)
		{
#line 20 "../../../Source/Core/AST/New.nll"
			Console::Log("expected TypeRef...");
#line 21 "../../../Source/Core/AST/New.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 22 "../../../Source/Core/AST/New.nll"
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
#line 23 "../../../Source/Core/AST/New.nll"
			return 0;
		}
#line 26 "../../../Source/Core/AST/New.nll"
		ParamCall* pParamCall = ParamCall::TryCreate(pTokenContainer, pTempOffset);
#line 27 "../../../Source/Core/AST/New.nll"
		if (pParamCall == 0)
		{
#line 29 "../../../Source/Core/AST/New.nll"
			Console::Log("expected ParamCall ");
#line 30 "../../../Source/Core/AST/New.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 31 "../../../Source/Core/AST/New.nll"
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
			if (pParamCall) delete pParamCall;
#line 32 "../../../Source/Core/AST/New.nll"
			return 0;
		}
#line 35 "../../../Source/Core/AST/New.nll"
		New* pNew = new New();
#line 37 "../../../Source/Core/AST/New.nll"
		pNew->m_eType = AST::Type::AST_NEW_EXP;
#line 38 "../../../Source/Core/AST/New.nll"
		pNew->m_pFirstToken = pNewToken;
#line 39 "../../../Source/Core/AST/New.nll"
		pNew->m_pTypeRef = pTypeRef;
#line 40 "../../../Source/Core/AST/New.nll"
		pNew->m_pParamCall = pParamCall;
		NumbatLogic::TypeRef* __2942570887 = pTypeRef;
#line 42 "../../../Source/Core/AST/New.nll"
		pTypeRef = 0;
#line 42 "../../../Source/Core/AST/New.nll"
		pNew->AddChild(__2942570887);
		NumbatLogic::ParamCall* __1502782298 = pParamCall;
#line 43 "../../../Source/Core/AST/New.nll"
		pParamCall = 0;
#line 43 "../../../Source/Core/AST/New.nll"
		pNew->AddChild(__1502782298);
#line 45 "../../../Source/Core/AST/New.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::New* __4218231602 = pNew;
#line 46 "../../../Source/Core/AST/New.nll"
		pNew = 0;
		if (pTempOffset) delete pTempOffset;
		if (pTypeRef) delete pTypeRef;
		if (pParamCall) delete pParamCall;
#line 46 "../../../Source/Core/AST/New.nll"
		return __4218231602;
	}

#line 49 "../../../Source/Core/AST/New.nll"
	void New::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 51 "../../../Source/Core/AST/New.nll"
		AST::Validate(pValidator, pParent);
#line 52 "../../../Source/Core/AST/New.nll"
		m_pValueType = m_pTypeRef->CreateValueType(pValidator->m_pResolver);
#line 53 "../../../Source/Core/AST/New.nll"
		if (m_pValueType == 0)
		{
#line 55 "../../../Source/Core/AST/New.nll"
			pValidator->AddError("Unable to compute value type from new", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
#line 56 "../../../Source/Core/AST/New.nll"
			return;
		}
#line 60 "../../../Source/Core/AST/New.nll"
		if (m_pParamCall->m_pFirstChild != 0)
		{
#line 64 "../../../Source/Core/AST/New.nll"
			if (m_pValueType->m_eType != ValueType::Type::CLASS_DECL_VALUE)
			{
#line 66 "../../../Source/Core/AST/New.nll"
				InternalString* sTemp = new InternalString("expected to be newing a CLASS_DECL_VALUE, got ");
#line 67 "../../../Source/Core/AST/New.nll"
				m_pValueType->StringifyType(sTemp);
#line 68 "../../../Source/Core/AST/New.nll"
				sTemp->AppendString(" \"");
#line 69 "../../../Source/Core/AST/New.nll"
				sTemp->AppendString(m_pTypeRef->m_pFirstToken->m_sValue->GetExternalString());
#line 70 "../../../Source/Core/AST/New.nll"
				sTemp->AppendString("\"");
#line 72 "../../../Source/Core/AST/New.nll"
				pValidator->AddError(sTemp->GetExternalString(), m_pParamCall->m_pFirstToken->m_sFileName, m_pParamCall->m_pFirstToken->m_nLine, m_pParamCall->m_pFirstToken->m_nColumn);
				if (sTemp) delete sTemp;
#line 73 "../../../Source/Core/AST/New.nll"
				return;
			}
#line 76 "../../../Source/Core/AST/New.nll"
			ClassDecl* pClassDecl = m_pValueType->m_pClassDecl;
#line 77 "../../../Source/Core/AST/New.nll"
			AST* pMember = pClassDecl->m_pFirstChild;
#line 78 "../../../Source/Core/AST/New.nll"
			while (pMember != 0)
			{
#line 80 "../../../Source/Core/AST/New.nll"
				if (pMember->m_eType == AST::Type::AST_TOR_DECL)
				{
#line 82 "../../../Source/Core/AST/New.nll"
					TorDecl* pTorDecl = (TorDecl*)(pMember);
#line 83 "../../../Source/Core/AST/New.nll"
					if (pTorDecl->m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_CONSTRUCT)
					{
#line 85 "../../../Source/Core/AST/New.nll"
						if (pTorDecl->m_pParamDecl->ValidateParamCall(m_pParamCall, pValidator, false))
						{
#line 87 "../../../Source/Core/AST/New.nll"
							break;
						}
					}
				}
#line 91 "../../../Source/Core/AST/New.nll"
				pMember = pMember->m_pNextSibling;
			}
#line 94 "../../../Source/Core/AST/New.nll"
			if (pMember == 0)
			{
#line 96 "../../../Source/Core/AST/New.nll"
				pValidator->AddError("could not find a matching constructor", m_pParamCall->m_pFirstToken->m_sFileName, m_pParamCall->m_pFirstToken->m_nLine, m_pParamCall->m_pFirstToken->m_nColumn);
#line 97 "../../../Source/Core/AST/New.nll"
				return;
			}
		}
#line 102 "../../../Source/Core/AST/New.nll"
		m_pValueType->m_ePointerType = TypeRef::PointerType::TRANSITON;
#line 104 "../../../Source/Core/AST/New.nll"
		AddClassDeclReference(m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
	}

#line 107 "../../../Source/Core/AST/New.nll"
	void New::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 109 "../../../Source/Core/AST/New.nll"
		pOutputBuilder->m_sOut->Append("new ");
#line 110 "../../../Source/Core/AST/New.nll"
		m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 111 "../../../Source/Core/AST/New.nll"
		m_pParamCall->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
	}

#line 3 "../../../Source/Core/AST/New.nll"
	New::New()
	{
		m_pTypeRef = 0;
		m_pParamCall = 0;
	}

}

