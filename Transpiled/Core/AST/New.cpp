#include "New.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "TypeRef.hpp"
#include "../../../../LangShared/Source/Console/CPP/Console.hpp"
#include "../../../../LangShared/Source/Assert/CPP/Assert.hpp"
#include "ParamCall.hpp"
#include "AST.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"
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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
#line 8 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
	New* New::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 12 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
		Token* pNewToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_NEW);
		if (pNewToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
			return 0;
		}
#line 15 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
		TypeRef* pTypeRef = TypeRef::TryCreate(pTokenContainer, pTempOffset);
		if (pTypeRef == 0)
		{
			Console::Log("expected TypeRef...");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
#line 23 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
			return 0;
		}
#line 26 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
		ParamCall* pParamCall = ParamCall::TryCreate(pTokenContainer, pTempOffset);
		if (pParamCall == 0)
		{
			Console::Log("expected ParamCall ");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
			if (pParamCall) delete pParamCall;
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
			return 0;
		}
#line 35 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
		New* pNew = new New();
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
		pNew->m_eType = AST::Type::AST_NEW_EXP;
		pNew->m_pFirstToken = pNewToken;
		pNew->m_pTypeRef = pTypeRef;
		pNew->m_pParamCall = pParamCall;
		NumbatLogic::TypeRef* __2942570887 = pTypeRef;
		pTypeRef = 0;
#line 42 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
		pNew->AddChild(__2942570887);
		NumbatLogic::ParamCall* __1502782298 = pParamCall;
#line 43 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
		pParamCall = 0;
#line 43 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
		pNew->AddChild(__1502782298);
#line 45 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::New* __4218231602 = pNew;
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
		pNew = 0;
		if (pTempOffset) delete pTempOffset;
		if (pTypeRef) delete pTypeRef;
		if (pParamCall) delete pParamCall;
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
		return __4218231602;
	}

	void New::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		m_pValueType = m_pTypeRef->CreateValueType(pValidator->m_pResolver);
		if (m_pValueType == 0)
		{
			pValidator->AddError("Unable to compute value type from new", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			return;
		}
#line 60 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
		if (m_pParamCall->m_pFirstChild != 0)
		{
#line 64 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
			if (m_pValueType->m_eType != ValueType::Type::CLASS_DECL_VALUE)
			{
				InternalString* sTemp = new InternalString("expected to be newing a CLASS_DECL_VALUE, got ");
				m_pValueType->StringifyType(sTemp);
				sTemp->AppendString(" \"");
				sTemp->AppendString(m_pTypeRef->m_pFirstToken->m_sValue->GetExternalString());
				sTemp->AppendString("\"");
#line 72 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
				pValidator->AddError(sTemp->GetExternalString(), m_pParamCall->m_pFirstToken->m_sFileName, m_pParamCall->m_pFirstToken->m_nLine, m_pParamCall->m_pFirstToken->m_nColumn);
				if (sTemp) delete sTemp;
#line 73 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
				return;
			}
#line 76 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
			ClassDecl* pClassDecl = m_pValueType->m_pClassDecl;
			AST* pMember = pClassDecl->m_pFirstChild;
			while (pMember != 0)
			{
				if (pMember->m_eType == AST::Type::AST_TOR_DECL)
				{
					TorDecl* pTorDecl = (TorDecl*)(pMember);
					if (pTorDecl->m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_CONSTRUCT)
					{
						if (pTorDecl->m_pParamDecl->ValidateParamCall(m_pParamCall, pValidator, false))
						{
							break;
						}
					}
				}
				pMember = pMember->m_pNextSibling;
			}
#line 94 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
			if (pMember == 0)
			{
				pValidator->AddError("could not find a matching constructor", m_pParamCall->m_pFirstToken->m_sFileName, m_pParamCall->m_pFirstToken->m_nLine, m_pParamCall->m_pFirstToken->m_nColumn);
				return;
			}
		}
#line 102 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
		m_pValueType->m_ePointerType = TypeRef::PointerType::TRANSITON;
#line 104 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
		AddClassDeclReference(m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
	}

	void New::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		pOutputBuilder->m_sOut->Append("new ");
		m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		m_pParamCall->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
	}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/New.nll"
	New::New()
	{
		m_pTypeRef = 0;
		m_pParamCall = 0;
	}

}

