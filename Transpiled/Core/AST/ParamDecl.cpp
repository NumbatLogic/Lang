#include "ParamDecl.hpp"
#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "VarDecl.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../Validator.hpp"
#include "TypeRef.hpp"
#include "ParamCall.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../ValueType.hpp"

namespace NumbatLogic
{
	class VarDecl;
	class OffsetDatum;
	class Token;
	class ParamDecl;
	class AST;
	class InternalString;
	class ValueType;
}
namespace NumbatLogic
{
	ParamDecl::ParamDecl()
	{
		m_pParamVector = 0;
		m_eType = AST::Type::AST_PARAM_DECL;
		m_bCanDescend = true;
		m_pParamVector = new Vector<VarDecl*>();
	}

	ParamDecl* ParamDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* m_pFirstToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT);
		if (m_pFirstToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		ParamDecl* pParamDecl = new ParamDecl();
		pParamDecl->m_pFirstToken = m_pFirstToken;
		while (true)
		{
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) != 0)
			{
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				break;
			}
			VarDecl* pParam = VarDecl::TryCreate(pTokenContainer, pTempOffset, true);
			if (pParam == 0)
			{
				Console::Log("expected param");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
			}
			pParamDecl->m_pParamVector->PushBack(pParam);
			NumbatLogic::VarDecl* __2381799284 = pParam;
			pParam = 0;
			pParamDecl->AddChild(__2381799284);
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
		NumbatLogic::ParamDecl* __108452057 = pParamDecl;
		pParamDecl = 0;
		if (pTempOffset) delete pTempOffset;
		return __108452057;
	}

	void ParamDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		AST* pParam = m_pFirstChild;
		while (pParam != 0)
		{
			if (pParam->m_eType != AST::Type::AST_VAR_DECL)
			{
				pValidator->AddError("Param not var decl?", pParam->m_pFirstToken->m_sFileName, pParam->m_pFirstToken->m_nLine, pParam->m_pFirstToken->m_nColumn);
				return;
			}
			VarDecl* pVarDecl = (VarDecl*)(pParam);
			if (pVarDecl->m_pTypeRef->m_pTypeToken->m_eType == Token::Type::TOKEN_IDENTIFIER)
			{
				if (pVarDecl->m_pTypeRef->m_ePointerType == TypeRef::PointerType::OWNED)
				{
					pValidator->AddError("Param cannot be a owned pointer!", pParam->m_pFirstToken->m_sFileName, pParam->m_pFirstToken->m_nLine, pParam->m_pFirstToken->m_nColumn);
					return;
				}
			}
			pParam = pParam->m_pNextSibling;
		}
	}

	bool ParamDecl::ValidateParamCall(ParamCall* pParamCall, Validator* pValidator)
	{
		int nIndex = 0;
		AST* pCallChild = pParamCall->m_pFirstChild;
		AST* pDeclChild = m_pFirstChild;
		while (true)
		{
			if (pCallChild == 0)
			{
				if (pDeclChild == 0)
					break;
				if (pDeclChild->m_eType == AST::Type::AST_VAR_DECL)
				{
					VarDecl* pVarDecl2 = (VarDecl*)(pDeclChild);
					if (pVarDecl2->m_pAssignment != 0)
					{
						nIndex++;
						pDeclChild = pDeclChild->m_pNextSibling;
						continue;
					}
				}
				if (pValidator != 0)
					pValidator->AddError("Param count mismatch (pCallChild == null)", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				return false;
			}
			else
				if (pDeclChild == 0)
				{
					if (pValidator != 0)
						pValidator->AddError("Param count mismatch (pDeclChild == null)", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
					return false;
				}
			if (pCallChild->m_pValueType == 0)
			{
				if (pValidator != 0)
				{
					InternalString* sTemp = new InternalString("no value type for param at index: ");
					sTemp->AppendInt(nIndex);
					pValidator->AddError(sTemp->GetExternalString(), pCallChild->m_pFirstToken->m_sFileName, pCallChild->m_pFirstToken->m_nLine, pCallChild->m_pFirstToken->m_nColumn);
					if (sTemp) delete sTemp;
				}
				return false;
			}
			if (pDeclChild->m_eType != AST::Type::AST_VAR_DECL)
			{
				if (pValidator != 0)
				{
					InternalString* sTemp = new InternalString("param expected to be var decl at index: ");
					sTemp->AppendInt(nIndex);
					pValidator->AddError(sTemp->GetExternalString(), pCallChild->m_pFirstToken->m_sFileName, pCallChild->m_pFirstToken->m_nLine, pCallChild->m_pFirstToken->m_nColumn);
					if (sTemp) delete sTemp;
				}
				return false;
			}
			VarDecl* pVarDecl = (VarDecl*)(pDeclChild);
			ValueType* pValueType = pVarDecl->m_pTypeRef->CreateValueType();
			if (pValueType == 0)
			{
				if (pValidator != 0)
					pValidator->AddError("Unknown decl valuetype???", pCallChild->m_pFirstToken->m_sFileName, pCallChild->m_pFirstToken->m_nLine, pCallChild->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
				return false;
			}
			if (pValueType->m_ePointerType == TypeRef::PointerType::TRANSITON && pCallChild->m_pValueType->m_ePointerType != TypeRef::PointerType::TRANSITON && pCallChild->m_pValueType->m_eType != ValueType::Type::NULL_VALUE)
			{
				if (pValidator != 0)
					pValidator->AddError("Must pass a transition pointer!", pCallChild->m_pFirstToken->m_sFileName, pCallChild->m_pFirstToken->m_nLine, pCallChild->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
				return false;
			}
			if (pCallChild->m_pValueType->m_ePointerType == TypeRef::PointerType::TRANSITON && pValueType->m_ePointerType != TypeRef::PointerType::TRANSITON)
			{
				if (pValidator != 0)
					pValidator->AddError("Was not expecting a transition pointer??", pCallChild->m_pFirstToken->m_sFileName, pCallChild->m_pFirstToken->m_nLine, pCallChild->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
				return false;
			}
			if (pCallChild->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE || pCallChild->m_pValueType->m_eType == ValueType::Type::GENERIC_TYPE_DECL_VALUE || pCallChild->m_pValueType->m_eType == ValueType::Type::VOIDPTR)
			{
				if (pValueType->m_eType != ValueType::Type::CLASS_DECL_VALUE && pValueType->m_eType != ValueType::Type::GENERIC_TYPE_DECL_VALUE && pValueType->m_eType != ValueType::Type::VOIDPTR)
				{
					if (pValidator != 0)
					{
						InternalString* sTemp = new InternalString("type mismatch ");
						pCallChild->m_pValueType->StringifyType(sTemp);
						sTemp->Append(" != ");
						pValueType->StringifyType(sTemp);
						pValidator->AddError(sTemp->GetExternalString(), pCallChild->m_pFirstToken->m_sFileName, pCallChild->m_pFirstToken->m_nLine, pCallChild->m_pFirstToken->m_nColumn);
						if (sTemp) delete sTemp;
					}
					if (pValueType) delete pValueType;
					return false;
				}
			}
			nIndex++;
			pCallChild = pCallChild->m_pNextSibling;
			pDeclChild = pDeclChild->m_pNextSibling;
			if (pValueType) delete pValueType;
		}
		return true;
	}

	void ParamDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		sOut->AppendChar('(');
		AST* pParam = m_pFirstChild;
		while (pParam != 0)
		{
			if (pParam != m_pFirstChild)
				sOut->Append(", ");
			pParam->Stringify(eLanguage, eOutputFile, 0, sOut);
			pParam = pParam->m_pNextSibling;
		}
		sOut->AppendChar(')');
	}

	ParamDecl::~ParamDecl()
	{
		if (m_pParamVector) delete m_pParamVector;
	}

}

