#include "ParamDecl.hpp"
#include "AST.hpp"
#include "VarDecl.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
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
#include "../OutputBuilder.hpp"

namespace NumbatLogic
{
	class AST;
	class VarDecl;
	template <class T>
	class Vector;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class ParamDecl;
	class Console;
	class Assert;
	class Validator;
	class TypeRef;
	class ParamCall;
	class InternalString;
	class ValueType;
	class OutputBuilder;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
#line 7 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
	ParamDecl::ParamDecl()
	{
		m_pParamVector = 0;
#line 9 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
		m_eType = AST::Type::AST_PARAM_DECL;
		m_bCanDescend = true;
		m_pParamVector = new Vector<VarDecl*>();
	}

	ParamDecl* ParamDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 18 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
		Token* m_pFirstToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT);
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
		if (m_pFirstToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 21 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
			return 0;
		}
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 25 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
		ParamDecl* pParamDecl = new ParamDecl();
		pParamDecl->m_pFirstToken = m_pFirstToken;
		while (true)
		{
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) != 0)
			{
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				break;
			}
#line 35 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
			VarDecl* pParam = VarDecl::TryCreate(pTokenContainer, pTempOffset, true);
			if (pParam == 0)
			{
				Console::Log("expected param");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				Assert::Plz(false);
			}
#line 43 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
			pParamDecl->m_pParamVector->PushBack(pParam);
			NumbatLogic::VarDecl* __3258004093 = pParam;
#line 44 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
			pParam = 0;
#line 44 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
			pParamDecl->AddChild(__3258004093);
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) != 0)
			{
				if (pParam) delete pParam;
#line 47 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
				continue;
			}
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COMMA) == 0)
			{
				Console::Log("expected comma");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				Assert::Plz(false);
			}
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			if (pParam) delete pParam;
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ParamDecl* __3702794795 = pParamDecl;
#line 59 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
		pParamDecl = 0;
		if (pTempOffset) delete pTempOffset;
#line 59 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
		return __3702794795;
	}

	void ParamDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
#line 66 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
		AST* pParam = m_pFirstChild;
		while (pParam != 0)
		{
#line 70 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
			if (pParam->m_eType != AST::Type::AST_VAR_DECL)
			{
				pValidator->AddError("Param not var decl?", pParam->m_pFirstToken->m_sFileName, pParam->m_pFirstToken->m_nLine, pParam->m_pFirstToken->m_nColumn);
				return;
			}
#line 76 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
			VarDecl* pVarDecl = (VarDecl*)(pParam);
#line 78 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
			if (pVarDecl->m_pTypeRef->m_pTypeToken->m_eType == Token::Type::TOKEN_IDENTIFIER)
			{
				if (pVarDecl->m_pTypeRef->m_ePointerType == TypeRef::PointerType::OWNED)
				{
					pValidator->AddError("Param cannot be a owned pointer!", pParam->m_pFirstToken->m_sFileName, pParam->m_pFirstToken->m_nLine, pParam->m_pFirstToken->m_nColumn);
					return;
				}
			}
#line 87 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
			pParam = pParam->m_pNextSibling;
		}
	}

	bool ParamDecl::ValidateParamCall(ParamCall* pParamCall, Validator* pValidator, bool bReportErrors)
	{
		int nIndex = 0;
		AST* pCallChild = pParamCall->m_pFirstChild;
		AST* pDeclChild = m_pFirstChild;
#line 97 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
		while (true)
		{
			if (pCallChild == 0)
			{
				if (pDeclChild == 0)
					break;
#line 104 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
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
#line 115 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
				if (bReportErrors && pValidator != 0)
					pValidator->AddError("Param count mismatch (pCallChild == null)", pParamCall->m_pFirstToken->m_sFileName, pParamCall->m_pFirstToken->m_nLine, pParamCall->m_pFirstToken->m_nColumn);
				return false;
			}
			else
#line 119 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
				if (pDeclChild == 0)
				{
					if (bReportErrors && pValidator != 0)
						pValidator->AddError("Param count mismatch (pDeclChild == null)", pParamCall->m_pFirstToken->m_sFileName, pParamCall->m_pFirstToken->m_nLine, pParamCall->m_pFirstToken->m_nColumn);
					return false;
				}
#line 126 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
			if (pCallChild->m_pValueType == 0)
			{
				if (bReportErrors && pValidator != 0)
				{
					InternalString* sTemp = new InternalString("no value type for param at index: ");
					sTemp->AppendInt(nIndex);
					pValidator->AddError(sTemp->GetExternalString(), pCallChild->m_pFirstToken->m_sFileName, pCallChild->m_pFirstToken->m_nLine, pCallChild->m_pFirstToken->m_nColumn);
					if (sTemp) delete sTemp;
				}
#line 134 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
				return false;
			}
#line 138 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
			if (pDeclChild->m_eType != AST::Type::AST_VAR_DECL)
			{
				if (bReportErrors && pValidator != 0)
				{
					InternalString* sTemp = new InternalString("param expected to be var decl at index: ");
					sTemp->AppendInt(nIndex);
					pValidator->AddError(sTemp->GetExternalString(), pCallChild->m_pFirstToken->m_sFileName, pCallChild->m_pFirstToken->m_nLine, pCallChild->m_pFirstToken->m_nColumn);
					if (sTemp) delete sTemp;
				}
#line 146 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
				return false;
			}
#line 149 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
			VarDecl* pVarDecl = (VarDecl*)(pDeclChild);
			ValueType* pValueType = pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
#line 152 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
			if (pValueType == 0)
			{
				if (bReportErrors && pValidator != 0)
					pValidator->AddError("Unknown decl valuetype???", pCallChild->m_pFirstToken->m_sFileName, pCallChild->m_pFirstToken->m_nLine, pCallChild->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
#line 156 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
				return false;
			}
#line 159 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
			if (pValueType->m_ePointerType == TypeRef::PointerType::TRANSITON && pCallChild->m_pValueType->m_ePointerType != TypeRef::PointerType::TRANSITON && pCallChild->m_pValueType->m_eType != ValueType::Type::NULL_VALUE)
			{
				if (bReportErrors && pValidator != 0)
					pValidator->AddError("Must pass a transition pointer!", pCallChild->m_pFirstToken->m_sFileName, pCallChild->m_pFirstToken->m_nLine, pCallChild->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
#line 163 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
				return false;
			}
#line 166 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
			if (pCallChild->m_pValueType->m_ePointerType == TypeRef::PointerType::TRANSITON && pValueType->m_ePointerType != TypeRef::PointerType::TRANSITON)
			{
				if (bReportErrors && pValidator != 0)
					pValidator->AddError("Was not expecting a transition pointer??", pCallChild->m_pFirstToken->m_sFileName, pCallChild->m_pFirstToken->m_nLine, pCallChild->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
#line 170 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
				return false;
			}
#line 175 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
			if (pCallChild->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE || pCallChild->m_pValueType->m_eType == ValueType::Type::GENERIC_TYPE_DECL_VALUE || pCallChild->m_pValueType->m_eType == ValueType::Type::VOIDPTR)
			{
				if (pValueType->m_eType != ValueType::Type::CLASS_DECL_VALUE && pValueType->m_eType != ValueType::Type::GENERIC_TYPE_DECL_VALUE && pValueType->m_eType != ValueType::Type::VOIDPTR)
				{
					if (bReportErrors && pValidator != 0)
					{
						InternalString* sTemp = new InternalString("type mismatch ");
						pCallChild->m_pValueType->StringifyType(sTemp);
						sTemp->Append(" != ");
						pValueType->StringifyType(sTemp);
						pValidator->AddError(sTemp->GetExternalString(), pCallChild->m_pFirstToken->m_sFileName, pCallChild->m_pFirstToken->m_nLine, pCallChild->m_pFirstToken->m_nColumn);
						if (sTemp) delete sTemp;
					}
					if (pValueType) delete pValueType;
#line 187 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
					return false;
				}
			}
#line 192 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
			if (pVarDecl->m_pTypeRef->m_bRef)
			{
				if (pCallChild->m_eType != AST::Type::AST_REF_EXPR)
				{
					if (bReportErrors && pValidator != 0)
						pValidator->AddError("Must prefix ref parameter with ref!", pCallChild->m_pFirstToken->m_sFileName, pCallChild->m_pFirstToken->m_nLine, pCallChild->m_pFirstToken->m_nColumn);
					if (pValueType) delete pValueType;
#line 198 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
					return false;
				}
			}
#line 204 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
			nIndex++;
			pCallChild = pCallChild->m_pNextSibling;
			pDeclChild = pDeclChild->m_pNextSibling;
			if (pValueType) delete pValueType;
		}
		return true;
	}

	void ParamDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		pOutputBuilder->m_sOut->AppendChar('(');
		AST* pParam = m_pFirstChild;
		while (pParam != 0)
		{
			if (pParam != m_pFirstChild)
				pOutputBuilder->m_sOut->Append(", ");
			pParam->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			pParam = pParam->m_pNextSibling;
		}
		pOutputBuilder->m_sOut->AppendChar(')');
	}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/ParamDecl.nll"
	ParamDecl::~ParamDecl()
	{
		if (m_pParamVector) delete m_pParamVector;
	}

}

