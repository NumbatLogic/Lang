#include "FunctionCall.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "ParamCall.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "AST.hpp"
#include "OperatorExpr.hpp"
#include "../ValueType.hpp"
#include "ClassDecl.hpp"
#include "EnumDecl.hpp"
#include "../Validator.hpp"
#include "VarDecl.hpp"
#include "TypeRef.hpp"
#include "DelegateDecl.hpp"
#include "../../LangShared/Vector/OwnedVector.hpp"
#include "../../../../LangShared/ExternalString/CPP/ExternalString.hpp"
#include "GenericTypeDecl.hpp"
#include "FunctionDecl.hpp"
#include "ParamDecl.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
	class Token;
	class ParamCall;
	class InternalString;
	class FunctionCall;
	class AST;
	class FunctionDecl;
	class VarDecl;
	class ValueType;
	class GenericTypeDecl;
}
namespace NumbatLogic
{
	FunctionCall* FunctionCall::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pNameToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
		if (pNameToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT) == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		ParamCall* pParamCall = ParamCall::TryCreate(pTokenContainer, pTempOffset);
		if (pParamCall == 0)
		{
			InternalString* sTemp = new InternalString("expected ParamCall ");
			sTemp->Append(pTokenContainer->StringifyOffset(pTempOffset));
			Console::Log(sTemp->GetExternalString());
			NumbatLogic::Assert::Plz(false);
			if (sTemp) delete sTemp;
			if (pTempOffset) delete pTempOffset;
			if (pParamCall) delete pParamCall;
			return 0;
		}
		FunctionCall* pFunctionCall = new FunctionCall();
		pFunctionCall->m_eType = AST::Type::AST_FUNCTION_CALL;
		pFunctionCall->m_pFirstToken = pNameToken;
		pFunctionCall->m_sMangledName = pNameToken->GetString();
		pFunctionCall->m_pParamCall = pParamCall;
		NumbatLogic::ParamCall* __1296316563 = pParamCall;
		pParamCall = 0;
		pFunctionCall->AddChild(__1296316563);
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::FunctionCall* __1523740656 = pFunctionCall;
		pFunctionCall = 0;
		if (pTempOffset) delete pTempOffset;
		if (pParamCall) delete pParamCall;
		return __1523740656;
	}

	void FunctionCall::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		const char* sName = m_pFirstToken->GetString();
		AST* pBase = this;
		AST* pChild = this;
		if (pParent != 0)
		{
			if (pParent->m_pOperatorToken->m_eType == Token::Type::TOKEN_DOT && pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
			{
				AddClassDeclReference(pParent->m_pLeft->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
				pBase = pParent->m_pLeft->m_pValueType->m_pClassDecl;
				pChild = 0;
			}
			else
				if (pParent->m_pOperatorToken->m_eType == Token::Type::TOKEN_DOUBLE_COLON)
				{
					if (pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL)
					{
						AddClassDeclReference(pParent->m_pLeft->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
						pBase = pParent->m_pLeft->m_pValueType->m_pClassDecl;
						pChild = 0;
					}
					else
						if (pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::ENUM_DECL)
						{
							pBase = pParent->m_pLeft->m_pValueType->m_pEnumDecl;
							pChild = 0;
						}
						else
						{
							pValidator->AddError("Unexpected left of ::", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
							return;
						}
				}
		}
		AST* pAST = pBase->FindByName(sName, pChild);
		if (pAST == 0)
		{
			InternalString* sTemp = new InternalString("Func Unbeknownst! ");
			sTemp->Append(sName);
			pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			if (sTemp) delete sTemp;
			return;
		}
		FunctionDecl* pFunctionDecl = 0;
		if (pAST->m_eType == AST::Type::AST_VAR_DECL)
		{
			VarDecl* pVarDecl = (VarDecl*)(pAST);
			ValueType* pValueType = pVarDecl->m_pTypeRef->CreateValueType();
			if (pValueType != 0)
			{
				if (pValueType->m_eType == ValueType::Type::DELEGATE_DECL_VALUE)
				{
					if (pValueType->m_pDelegateDecl == 0)
					{
						InternalString* sTemp = new InternalString("DELEGATE_DECL_VALUE does not have m_pDelegateDecl set???");
						pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
						if (sTemp) delete sTemp;
						if (pValueType) delete pValueType;
						return;
					}
					pFunctionDecl = pValueType->m_pDelegateDecl->m_pFunctionDecl;
				}
			}
			if (pValueType) delete pValueType;
		}
		if (pAST->m_eType == AST::Type::AST_FUNCTION_DECL)
		{
			pFunctionDecl = (FunctionDecl*)(pAST);
		}
		if (pFunctionDecl == 0)
		{
			InternalString* sTemp = new InternalString("Is not a function? ");
			sTemp->Append(sName);
			sTemp->Append(" ");
			pAST->StringifyType(sTemp);
			pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			if (sTemp) delete sTemp;
			return;
		}
		if (pParent != 0 && pParent->m_pLeft != 0)
		{
			ValueType* pLeftValueType = pParent->m_pLeft->m_pValueType;
			if (pLeftValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE && pLeftValueType->m_pGenericValueTypeVector != 0 && pLeftValueType->m_pGenericValueTypeVector->GetSize() > 0)
			{
				if (pLeftValueType->m_pGenericValueTypeVector->GetSize() != pLeftValueType->m_pClassDecl->m_pGenericTypeDeclVector->GetSize())
				{
					InternalString* sTemp2 = new InternalString("Mismatched generics? ");
					pLeftValueType->StringifyType(sTemp2);
					sTemp2->Append(" ");
					sTemp2->AppendInt(pLeftValueType->m_pGenericValueTypeVector->GetSize());
					sTemp2->Append(" != ");
					sTemp2->Append(pLeftValueType->m_pClassDecl->m_pNameToken->GetString());
					sTemp2->Append(" ");
					sTemp2->AppendInt(pLeftValueType->m_pClassDecl->m_pGenericTypeDeclVector->GetSize());
					pValidator->AddError(sTemp2->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
					if (sTemp2) delete sTemp2;
					return;
				}
				for (int i = 0; i < pLeftValueType->m_pGenericValueTypeVector->GetSize(); i++)
				{
					ValueType* pGenericValueType = pLeftValueType->m_pGenericValueTypeVector->Get(i)->Clone();
					GenericTypeDecl* pGenericTypeDecl = pLeftValueType->m_pClassDecl->m_pGenericTypeDeclVector->Get(i);
					if (ExternalString::Equal(pGenericTypeDecl->m_pFirstToken->GetString(), pFunctionDecl->m_pTypeRef->m_pTypeToken->GetString()))
					{
						NumbatLogic::ValueType* __3843479488 = pGenericValueType;
						pGenericValueType = 0;
						m_pValueType = __3843479488;
						m_pValueType->m_ePointerType = pFunctionDecl->m_pTypeRef->m_ePointerType;
					}
					if (pGenericValueType) delete pGenericValueType;
				}
			}
		}
		if (m_pValueType == 0)
		{
			m_pValueType = pFunctionDecl->m_pTypeRef->CreateValueType();
		}
		if (m_pValueType == 0)
		{
			InternalString* sTemp = new InternalString("could not get valuetype for some reason ");
			sTemp->Append(pFunctionDecl->m_pTypeRef->m_pTypeToken->GetString());
			pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			if (sTemp) delete sTemp;
		}
		AST::Validate(pValidator, pParent);
		if (m_pParamCall->m_pFirstChild == 0)
		{
			if (pFunctionDecl->m_pParamDecl->m_pFirstChild != 0)
			{
				pValidator->AddError("Params needed for function call?", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				return;
			}
		}
		else
		{
			if (!pFunctionDecl->m_pParamDecl->ValidateParamCall(m_pParamCall, pValidator))
				return;
		}
	}

	void FunctionCall::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		sOut->Append(m_sMangledName);
		m_pParamCall->Stringify(eLanguage, eOutputFile, 0, sOut);
	}

	FunctionCall::FunctionCall()
	{
		m_sMangledName = 0;
		m_pParamCall = 0;
	}

}

