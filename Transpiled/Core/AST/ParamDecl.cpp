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
#line 0 "../../../Source/Core/AST/ParamDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/ParamDecl.nll"
#line 7 "../../../Source/Core/AST/ParamDecl.nll"
	ParamDecl::ParamDecl()
	{
		m_pParamVector = 0;
#line 9 "../../../Source/Core/AST/ParamDecl.nll"
		m_eType = AST::Type::AST_PARAM_DECL;
#line 10 "../../../Source/Core/AST/ParamDecl.nll"
		m_bCanDescend = true;
#line 11 "../../../Source/Core/AST/ParamDecl.nll"
		m_pParamVector = new Vector<VarDecl*>();
	}

#line 14 "../../../Source/Core/AST/ParamDecl.nll"
	ParamDecl* ParamDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
#line 16 "../../../Source/Core/AST/ParamDecl.nll"
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 18 "../../../Source/Core/AST/ParamDecl.nll"
		Token* m_pFirstToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT);
#line 20 "../../../Source/Core/AST/ParamDecl.nll"
		if (m_pFirstToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 21 "../../../Source/Core/AST/ParamDecl.nll"
			return 0;
		}
#line 22 "../../../Source/Core/AST/ParamDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 25 "../../../Source/Core/AST/ParamDecl.nll"
		ParamDecl* pParamDecl = new ParamDecl();
#line 26 "../../../Source/Core/AST/ParamDecl.nll"
		pParamDecl->m_pFirstToken = m_pFirstToken;
#line 27 "../../../Source/Core/AST/ParamDecl.nll"
		while (true)
		{
#line 29 "../../../Source/Core/AST/ParamDecl.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) != 0)
			{
#line 31 "../../../Source/Core/AST/ParamDecl.nll"
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 32 "../../../Source/Core/AST/ParamDecl.nll"
				break;
			}
#line 35 "../../../Source/Core/AST/ParamDecl.nll"
			VarDecl* pParam = VarDecl::TryCreate(pTokenContainer, pTempOffset, true);
#line 36 "../../../Source/Core/AST/ParamDecl.nll"
			if (pParam == 0)
			{
#line 38 "../../../Source/Core/AST/ParamDecl.nll"
				Console::Log("expected param");
#line 39 "../../../Source/Core/AST/ParamDecl.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 40 "../../../Source/Core/AST/ParamDecl.nll"
				Assert::Plz(false);
			}
#line 43 "../../../Source/Core/AST/ParamDecl.nll"
			pParamDecl->m_pParamVector->PushBack(pParam);
			NumbatLogic::VarDecl* __3258004093 = pParam;
#line 44 "../../../Source/Core/AST/ParamDecl.nll"
			pParam = 0;
#line 44 "../../../Source/Core/AST/ParamDecl.nll"
			pParamDecl->AddChild(__3258004093);
#line 46 "../../../Source/Core/AST/ParamDecl.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_RIGHT) != 0)
			{
				if (pParam) delete pParam;
#line 47 "../../../Source/Core/AST/ParamDecl.nll"
				continue;
			}
#line 49 "../../../Source/Core/AST/ParamDecl.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COMMA) == 0)
			{
#line 51 "../../../Source/Core/AST/ParamDecl.nll"
				Console::Log("expected comma");
#line 52 "../../../Source/Core/AST/ParamDecl.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 53 "../../../Source/Core/AST/ParamDecl.nll"
				Assert::Plz(false);
			}
#line 55 "../../../Source/Core/AST/ParamDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			if (pParam) delete pParam;
		}
#line 58 "../../../Source/Core/AST/ParamDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ParamDecl* __3702794795 = pParamDecl;
#line 59 "../../../Source/Core/AST/ParamDecl.nll"
		pParamDecl = 0;
		if (pTempOffset) delete pTempOffset;
#line 59 "../../../Source/Core/AST/ParamDecl.nll"
		return __3702794795;
	}

#line 62 "../../../Source/Core/AST/ParamDecl.nll"
	void ParamDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 64 "../../../Source/Core/AST/ParamDecl.nll"
		AST::Validate(pValidator, pParent);
#line 66 "../../../Source/Core/AST/ParamDecl.nll"
		AST* pParam = m_pFirstChild;
#line 67 "../../../Source/Core/AST/ParamDecl.nll"
		while (pParam != 0)
		{
#line 70 "../../../Source/Core/AST/ParamDecl.nll"
			if (pParam->m_eType != AST::Type::AST_VAR_DECL)
			{
#line 72 "../../../Source/Core/AST/ParamDecl.nll"
				pValidator->AddError("Param not var decl?", pParam->m_pFirstToken->m_sFileName, pParam->m_pFirstToken->m_nLine, pParam->m_pFirstToken->m_nColumn);
#line 73 "../../../Source/Core/AST/ParamDecl.nll"
				return;
			}
#line 76 "../../../Source/Core/AST/ParamDecl.nll"
			VarDecl* pVarDecl = (VarDecl*)(pParam);
#line 78 "../../../Source/Core/AST/ParamDecl.nll"
			if (pVarDecl->m_pTypeRef->m_pTypeToken->m_eType == Token::Type::TOKEN_IDENTIFIER)
			{
#line 80 "../../../Source/Core/AST/ParamDecl.nll"
				if (pVarDecl->m_pTypeRef->m_ePointerType == TypeRef::PointerType::OWNED)
				{
#line 82 "../../../Source/Core/AST/ParamDecl.nll"
					pValidator->AddError("Param cannot be a owned pointer!", pParam->m_pFirstToken->m_sFileName, pParam->m_pFirstToken->m_nLine, pParam->m_pFirstToken->m_nColumn);
#line 83 "../../../Source/Core/AST/ParamDecl.nll"
					return;
				}
			}
#line 87 "../../../Source/Core/AST/ParamDecl.nll"
			pParam = pParam->m_pNextSibling;
		}
	}

#line 91 "../../../Source/Core/AST/ParamDecl.nll"
	bool ParamDecl::ValidateParamCall(ParamCall* pParamCall, Validator* pValidator, bool bReportErrors)
	{
#line 93 "../../../Source/Core/AST/ParamDecl.nll"
		int nIndex = 0;
#line 94 "../../../Source/Core/AST/ParamDecl.nll"
		AST* pCallChild = pParamCall->m_pFirstChild;
#line 95 "../../../Source/Core/AST/ParamDecl.nll"
		AST* pDeclChild = m_pFirstChild;
#line 97 "../../../Source/Core/AST/ParamDecl.nll"
		while (true)
		{
#line 99 "../../../Source/Core/AST/ParamDecl.nll"
			if (pCallChild == 0)
			{
#line 101 "../../../Source/Core/AST/ParamDecl.nll"
				if (pDeclChild == 0)
#line 102 "../../../Source/Core/AST/ParamDecl.nll"
					break;
#line 104 "../../../Source/Core/AST/ParamDecl.nll"
				if (pDeclChild->m_eType == AST::Type::AST_VAR_DECL)
				{
#line 106 "../../../Source/Core/AST/ParamDecl.nll"
					VarDecl* pVarDecl2 = (VarDecl*)(pDeclChild);
#line 107 "../../../Source/Core/AST/ParamDecl.nll"
					if (pVarDecl2->m_pAssignment != 0)
					{
#line 109 "../../../Source/Core/AST/ParamDecl.nll"
						nIndex++;
#line 110 "../../../Source/Core/AST/ParamDecl.nll"
						pDeclChild = pDeclChild->m_pNextSibling;
#line 111 "../../../Source/Core/AST/ParamDecl.nll"
						continue;
					}
				}
#line 115 "../../../Source/Core/AST/ParamDecl.nll"
				if (bReportErrors && pValidator != 0)
#line 116 "../../../Source/Core/AST/ParamDecl.nll"
					pValidator->AddError("Param count mismatch (pCallChild == null)", pParamCall->m_pFirstToken->m_sFileName, pParamCall->m_pFirstToken->m_nLine, pParamCall->m_pFirstToken->m_nColumn);
#line 117 "../../../Source/Core/AST/ParamDecl.nll"
				return false;
			}
			else
#line 119 "../../../Source/Core/AST/ParamDecl.nll"
				if (pDeclChild == 0)
				{
#line 121 "../../../Source/Core/AST/ParamDecl.nll"
					if (bReportErrors && pValidator != 0)
#line 122 "../../../Source/Core/AST/ParamDecl.nll"
						pValidator->AddError("Param count mismatch (pDeclChild == null)", pParamCall->m_pFirstToken->m_sFileName, pParamCall->m_pFirstToken->m_nLine, pParamCall->m_pFirstToken->m_nColumn);
#line 123 "../../../Source/Core/AST/ParamDecl.nll"
					return false;
				}
#line 126 "../../../Source/Core/AST/ParamDecl.nll"
			if (pCallChild->m_pValueType == 0)
			{
#line 128 "../../../Source/Core/AST/ParamDecl.nll"
				if (bReportErrors && pValidator != 0)
				{
#line 130 "../../../Source/Core/AST/ParamDecl.nll"
					InternalString* sTemp = new InternalString("no value type for param at index: ");
#line 131 "../../../Source/Core/AST/ParamDecl.nll"
					sTemp->AppendInt(nIndex);
#line 132 "../../../Source/Core/AST/ParamDecl.nll"
					pValidator->AddError(sTemp->GetExternalString(), pCallChild->m_pFirstToken->m_sFileName, pCallChild->m_pFirstToken->m_nLine, pCallChild->m_pFirstToken->m_nColumn);
					if (sTemp) delete sTemp;
				}
#line 134 "../../../Source/Core/AST/ParamDecl.nll"
				return false;
			}
#line 138 "../../../Source/Core/AST/ParamDecl.nll"
			if (pDeclChild->m_eType != AST::Type::AST_VAR_DECL)
			{
#line 140 "../../../Source/Core/AST/ParamDecl.nll"
				if (bReportErrors && pValidator != 0)
				{
#line 142 "../../../Source/Core/AST/ParamDecl.nll"
					InternalString* sTemp = new InternalString("param expected to be var decl at index: ");
#line 143 "../../../Source/Core/AST/ParamDecl.nll"
					sTemp->AppendInt(nIndex);
#line 144 "../../../Source/Core/AST/ParamDecl.nll"
					pValidator->AddError(sTemp->GetExternalString(), pCallChild->m_pFirstToken->m_sFileName, pCallChild->m_pFirstToken->m_nLine, pCallChild->m_pFirstToken->m_nColumn);
					if (sTemp) delete sTemp;
				}
#line 146 "../../../Source/Core/AST/ParamDecl.nll"
				return false;
			}
#line 149 "../../../Source/Core/AST/ParamDecl.nll"
			VarDecl* pVarDecl = (VarDecl*)(pDeclChild);
#line 150 "../../../Source/Core/AST/ParamDecl.nll"
			ValueType* pValueType = pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
#line 152 "../../../Source/Core/AST/ParamDecl.nll"
			if (pValueType == 0)
			{
#line 154 "../../../Source/Core/AST/ParamDecl.nll"
				if (bReportErrors && pValidator != 0)
#line 155 "../../../Source/Core/AST/ParamDecl.nll"
					pValidator->AddError("Unknown decl valuetype???", pCallChild->m_pFirstToken->m_sFileName, pCallChild->m_pFirstToken->m_nLine, pCallChild->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
#line 156 "../../../Source/Core/AST/ParamDecl.nll"
				return false;
			}
#line 159 "../../../Source/Core/AST/ParamDecl.nll"
			if (pValueType->m_ePointerType == TypeRef::PointerType::TRANSITON && pCallChild->m_pValueType->m_ePointerType != TypeRef::PointerType::TRANSITON && pCallChild->m_pValueType->m_eType != ValueType::Type::NULL_VALUE)
			{
#line 161 "../../../Source/Core/AST/ParamDecl.nll"
				if (bReportErrors && pValidator != 0)
#line 162 "../../../Source/Core/AST/ParamDecl.nll"
					pValidator->AddError("Must pass a transition pointer!", pCallChild->m_pFirstToken->m_sFileName, pCallChild->m_pFirstToken->m_nLine, pCallChild->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
#line 163 "../../../Source/Core/AST/ParamDecl.nll"
				return false;
			}
#line 166 "../../../Source/Core/AST/ParamDecl.nll"
			if (pCallChild->m_pValueType->m_ePointerType == TypeRef::PointerType::TRANSITON && pValueType->m_ePointerType != TypeRef::PointerType::TRANSITON)
			{
#line 168 "../../../Source/Core/AST/ParamDecl.nll"
				if (bReportErrors && pValidator != 0)
#line 169 "../../../Source/Core/AST/ParamDecl.nll"
					pValidator->AddError("Was not expecting a transition pointer??", pCallChild->m_pFirstToken->m_sFileName, pCallChild->m_pFirstToken->m_nLine, pCallChild->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
#line 170 "../../../Source/Core/AST/ParamDecl.nll"
				return false;
			}
#line 175 "../../../Source/Core/AST/ParamDecl.nll"
			if (pCallChild->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE || pCallChild->m_pValueType->m_eType == ValueType::Type::GENERIC_TYPE_DECL_VALUE || pCallChild->m_pValueType->m_eType == ValueType::Type::VOIDPTR)
			{
#line 177 "../../../Source/Core/AST/ParamDecl.nll"
				if (pValueType->m_eType != ValueType::Type::CLASS_DECL_VALUE && pValueType->m_eType != ValueType::Type::GENERIC_TYPE_DECL_VALUE && pValueType->m_eType != ValueType::Type::VOIDPTR)
				{
#line 179 "../../../Source/Core/AST/ParamDecl.nll"
					if (bReportErrors && pValidator != 0)
					{
#line 181 "../../../Source/Core/AST/ParamDecl.nll"
						InternalString* sTemp = new InternalString("type mismatch ");
#line 182 "../../../Source/Core/AST/ParamDecl.nll"
						pCallChild->m_pValueType->StringifyType(sTemp);
#line 183 "../../../Source/Core/AST/ParamDecl.nll"
						sTemp->Append(" != ");
#line 184 "../../../Source/Core/AST/ParamDecl.nll"
						pValueType->StringifyType(sTemp);
#line 185 "../../../Source/Core/AST/ParamDecl.nll"
						pValidator->AddError(sTemp->GetExternalString(), pCallChild->m_pFirstToken->m_sFileName, pCallChild->m_pFirstToken->m_nLine, pCallChild->m_pFirstToken->m_nColumn);
						if (sTemp) delete sTemp;
					}
					if (pValueType) delete pValueType;
#line 187 "../../../Source/Core/AST/ParamDecl.nll"
					return false;
				}
			}
#line 192 "../../../Source/Core/AST/ParamDecl.nll"
			if (pVarDecl->m_pTypeRef->m_bRef)
			{
#line 194 "../../../Source/Core/AST/ParamDecl.nll"
				if (pCallChild->m_eType != AST::Type::AST_REF_EXPR)
				{
#line 196 "../../../Source/Core/AST/ParamDecl.nll"
					if (bReportErrors && pValidator != 0)
#line 197 "../../../Source/Core/AST/ParamDecl.nll"
						pValidator->AddError("Must prefix ref parameter with ref!", pCallChild->m_pFirstToken->m_sFileName, pCallChild->m_pFirstToken->m_nLine, pCallChild->m_pFirstToken->m_nColumn);
					if (pValueType) delete pValueType;
#line 198 "../../../Source/Core/AST/ParamDecl.nll"
					return false;
				}
			}
#line 204 "../../../Source/Core/AST/ParamDecl.nll"
			nIndex++;
#line 205 "../../../Source/Core/AST/ParamDecl.nll"
			pCallChild = pCallChild->m_pNextSibling;
#line 206 "../../../Source/Core/AST/ParamDecl.nll"
			pDeclChild = pDeclChild->m_pNextSibling;
			if (pValueType) delete pValueType;
		}
#line 209 "../../../Source/Core/AST/ParamDecl.nll"
		return true;
	}

#line 212 "../../../Source/Core/AST/ParamDecl.nll"
	void ParamDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 214 "../../../Source/Core/AST/ParamDecl.nll"
		pOutputBuilder->m_sOut->AppendChar('(');
#line 215 "../../../Source/Core/AST/ParamDecl.nll"
		AST* pParam = m_pFirstChild;
#line 216 "../../../Source/Core/AST/ParamDecl.nll"
		while (pParam != 0)
		{
#line 218 "../../../Source/Core/AST/ParamDecl.nll"
			if (pParam != m_pFirstChild)
#line 219 "../../../Source/Core/AST/ParamDecl.nll"
				pOutputBuilder->m_sOut->Append(", ");
#line 220 "../../../Source/Core/AST/ParamDecl.nll"
			pParam->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 221 "../../../Source/Core/AST/ParamDecl.nll"
			pParam = pParam->m_pNextSibling;
		}
#line 223 "../../../Source/Core/AST/ParamDecl.nll"
		pOutputBuilder->m_sOut->AppendChar(')');
	}

#line 3 "../../../Source/Core/AST/ParamDecl.nll"
	ParamDecl::~ParamDecl()
	{
		if (m_pParamVector) delete m_pParamVector;
	}

}

