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

namespace NumbatLogic
{
	class OffsetDatum;
	class Token;
	class TypeRef;
	class ParamCall;
	class New;
	class InternalString;
	class ClassDecl;
	class AST;
	class TorDecl;
}
namespace NumbatLogic
{
	New* New::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pNewToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_NEW);
		if (pNewToken == 0)
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
			Console::Log("expected ParamCall ");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
			if (pParamCall) delete pParamCall;
			return 0;
		}
		New* pNew = new New();
		pNew->m_eType = AST::Type::AST_NEW_EXP;
		pNew->m_pFirstToken = pNewToken;
		pNew->m_pTypeRef = pTypeRef;
		pNew->m_pParamCall = pParamCall;
		NumbatLogic::TypeRef* __3855168656 = pTypeRef;
		pTypeRef = 0;
		pNew->AddChild(__3855168656);
		NumbatLogic::ParamCall* __1514465046 = pParamCall;
		pParamCall = 0;
		pNew->AddChild(__1514465046);
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::New* __4194715350 = pNew;
		pNew = 0;
		if (pTempOffset) delete pTempOffset;
		if (pTypeRef) delete pTypeRef;
		if (pParamCall) delete pParamCall;
		return __4194715350;
	}

	void New::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		m_pValueType = m_pTypeRef->CreateValueType();
		if (m_pValueType == 0)
		{
			pValidator->AddError("Unable to compute value type from new", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			return;
		}
		if (m_pParamCall->m_pFirstChild != 0)
		{
			if (m_pValueType->m_eType != ValueType::Type::CLASS_DECL_VALUE)
			{
				InternalString* sTemp = new InternalString("expected to be newing a CLASS_DECL_VALUE, got ");
				m_pValueType->StringifyType(sTemp);
				sTemp->AppendString(" \"");
				sTemp->AppendString(m_pTypeRef->m_pFirstToken->m_sValue->GetExternalString());
				sTemp->AppendString("\"");
				pValidator->AddError(sTemp->GetExternalString(), m_pParamCall->m_pFirstToken->m_sFileName, m_pParamCall->m_pFirstToken->m_nLine, m_pParamCall->m_pFirstToken->m_nColumn);
				if (sTemp) delete sTemp;
				return;
			}
			ClassDecl* pClassDecl = m_pValueType->m_pClassDecl;
			AST* pMember = pClassDecl->m_pFirstChild;
			while (pMember != 0)
			{
				if (pMember->m_eType == AST::Type::AST_TOR_DECL)
				{
					TorDecl* pTorDecl = (TorDecl*)(pMember);
					if (pTorDecl->m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_CONSTRUCT)
					{
						if (pTorDecl->m_pParamDecl->ValidateParamCall(m_pParamCall, 0))
						{
							break;
						}
					}
				}
				pMember = pMember->m_pNextSibling;
			}
			if (pMember == 0)
			{
				pValidator->AddError("could not find a matching constructor", m_pParamCall->m_pFirstToken->m_sFileName, m_pParamCall->m_pFirstToken->m_nLine, m_pParamCall->m_pFirstToken->m_nColumn);
				return;
			}
		}
		m_pValueType->m_ePointerType = TypeRef::PointerType::TRANSITON;
	}

	void New::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		sOut->Append("new ");
		m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, sOut);
		m_pParamCall->Stringify(eLanguage, eOutputFile, 0, sOut);
	}

	New::New()
	{
		m_pTypeRef = 0;
		m_pParamCall = 0;
	}

}

