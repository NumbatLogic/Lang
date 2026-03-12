#include "VarDecl.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "TypeRef.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "../OutputBuilder.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "ClassDecl.hpp"
#include "MemberVarDecl.hpp"
#include "../Project.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class TypeRef;
	class Token;
	class TokenContainer;
	class VarDecl;
	template <class T>
	class Vector;
	class Console;
	class Assert;
	class Validator;
	class ValueType;
	class OutputBuilder;
	class Util;
	class InternalString;
	class ClassDecl;
	class MemberVarDecl;
	class Project;
}
#line 0 "../../../Source/Core/AST/VarDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/VarDecl.nll"
#line 14 "../../../Source/Core/AST/VarDecl.nll"
	VarDecl::VarDecl()
	{
		m_pTypeRef = 0;
		m_pNameToken = 0;
		m_pAssignment = 0;
		m_bInline = false;
		m_pArraySizeVector = 0;
		m_pOwnedNameToken = 0;
#line 16 "../../../Source/Core/AST/VarDecl.nll"
		m_bInline = false;
		m_eType = AST::Type::AST_VAR_DECL;
	}

	VarDecl* VarDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, bool bInline)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 24 "../../../Source/Core/AST/VarDecl.nll"
		TypeRef* pTypeRef = TypeRef::TryCreate(pTokenContainer, pTempOffset);
		if (pTypeRef == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
#line 26 "../../../Source/Core/AST/VarDecl.nll"
			return 0;
		}
		Token* pNameToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
		if (pNameToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
#line 30 "../../../Source/Core/AST/VarDecl.nll"
			return 0;
		}
#line 31 "../../../Source/Core/AST/VarDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 33 "../../../Source/Core/AST/VarDecl.nll"
		VarDecl* pVarDecl = new VarDecl();
#line 35 "../../../Source/Core/AST/VarDecl.nll"
		Token* pSquareBracketLeftToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_LEFT);
		while (pSquareBracketLeftToken != 0)
		{
			if (pVarDecl->m_pArraySizeVector == 0)
				pVarDecl->m_pArraySizeVector = new Vector<AST*>();
#line 41 "../../../Source/Core/AST/VarDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 43 "../../../Source/Core/AST/VarDecl.nll"
			AST* pArraySize = AST::TryCreateExpression(pTokenContainer, pTempOffset);
			if (pArraySize == 0)
			{
				Console::Log("unable to parse array size...");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				Assert::Plz(false);
				if (pArraySize) delete pArraySize;
				if (pTempOffset) delete pTempOffset;
				if (pTypeRef) delete pTypeRef;
				if (pVarDecl) delete pVarDecl;
#line 49 "../../../Source/Core/AST/VarDecl.nll"
				return 0;
			}
#line 52 "../../../Source/Core/AST/VarDecl.nll"
			Token* pSquareBracketRightToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_RIGHT);
			if (pSquareBracketRightToken == 0)
			{
				Console::Log("unable to parse closing square bracket");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				Assert::Plz(false);
				if (pArraySize) delete pArraySize;
				if (pTempOffset) delete pTempOffset;
				if (pTypeRef) delete pTypeRef;
				if (pVarDecl) delete pVarDecl;
#line 58 "../../../Source/Core/AST/VarDecl.nll"
				return 0;
			}
#line 61 "../../../Source/Core/AST/VarDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 63 "../../../Source/Core/AST/VarDecl.nll"
			pVarDecl->m_pArraySizeVector->PushBack(pArraySize);
			NumbatLogic::AST* __830257000 = pArraySize;
#line 64 "../../../Source/Core/AST/VarDecl.nll"
			pArraySize = 0;
#line 64 "../../../Source/Core/AST/VarDecl.nll"
			pVarDecl->AddChild(__830257000);
#line 66 "../../../Source/Core/AST/VarDecl.nll"
			pSquareBracketLeftToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_LEFT);
			if (pArraySize) delete pArraySize;
		}
		AST* pAssignment = 0;
		Token* pEqualsToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_EQUALS);
		if (pEqualsToken != 0)
		{
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 75 "../../../Source/Core/AST/VarDecl.nll"
			pAssignment = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 77 "../../../Source/Core/AST/VarDecl.nll"
			if (pAssignment == 0)
			{
				Console::Log("expected to parse assignment...");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				Assert::Plz(false);
				if (pTempOffset) delete pTempOffset;
				if (pTypeRef) delete pTypeRef;
				if (pVarDecl) delete pVarDecl;
				if (pAssignment) delete pAssignment;
#line 82 "../../../Source/Core/AST/VarDecl.nll"
				return 0;
			}
		}
#line 86 "../../../Source/Core/AST/VarDecl.nll"
		if (!bInline)
		{
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
			{
				if (pTempOffset) delete pTempOffset;
				if (pTypeRef) delete pTypeRef;
				if (pVarDecl) delete pVarDecl;
				if (pAssignment) delete pAssignment;
#line 89 "../../../Source/Core/AST/VarDecl.nll"
				return 0;
			}
#line 90 "../../../Source/Core/AST/VarDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		}
#line 94 "../../../Source/Core/AST/VarDecl.nll"
		pVarDecl->m_bStatement = bInline == false;
		pVarDecl->m_pFirstToken = pTypeRef->m_pFirstToken;
		pVarDecl->m_pTypeRef = pTypeRef;
		pVarDecl->m_pNameToken = pNameToken;
		pVarDecl->m_pAssignment = pAssignment;
		pVarDecl->m_bInline = bInline;
		NumbatLogic::TypeRef* __967516521 = pTypeRef;
		pTypeRef = 0;
#line 101 "../../../Source/Core/AST/VarDecl.nll"
		pVarDecl->AddChild(__967516521);
		if (pAssignment != 0)
		{
			NumbatLogic::AST* __183753559 = pAssignment;
#line 103 "../../../Source/Core/AST/VarDecl.nll"
			pAssignment = 0;
#line 103 "../../../Source/Core/AST/VarDecl.nll"
			pVarDecl->AddChild(__183753559);
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::VarDecl* __2971982038 = pVarDecl;
#line 106 "../../../Source/Core/AST/VarDecl.nll"
		pVarDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pTypeRef) delete pTypeRef;
		if (pAssignment) delete pAssignment;
#line 106 "../../../Source/Core/AST/VarDecl.nll"
		return __2971982038;
	}

	void VarDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
#line 113 "../../../Source/Core/AST/VarDecl.nll"
		if (m_pParent->m_eType != AST::Type::AST_MEMBER_VAR_DECL && m_pParent->m_eType != AST::Type::AST_PARAM_DECL)
			pValidator->AddVarDecl(this);
#line 116 "../../../Source/Core/AST/VarDecl.nll"
		ValueType* pValueType = m_pTypeRef->CreateValueType(pValidator->m_pResolver);
		if (pValueType == 0)
		{
			pValidator->AddError("Unknown ValueType for TypeRef", m_pTypeRef->m_pFirstToken->m_sFileName, m_pTypeRef->m_pFirstToken->m_nLine, m_pTypeRef->m_pFirstToken->m_nColumn);
			if (pValueType) delete pValueType;
#line 120 "../../../Source/Core/AST/VarDecl.nll"
			return;
		}
#line 123 "../../../Source/Core/AST/VarDecl.nll"
		if (m_pAssignment != 0)
		{
			if (m_pAssignment->m_pValueType == 0)
			{
				pValidator->AddError("Unknown assignment?", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
#line 128 "../../../Source/Core/AST/VarDecl.nll"
				return;
			}
#line 131 "../../../Source/Core/AST/VarDecl.nll"
			if (m_pArraySizeVector != 0 && m_pAssignment->m_pValueType->m_eType != ValueType::Type::STATIC_ARRAY || m_pArraySizeVector == 0 && m_pAssignment->m_pValueType->m_eType == ValueType::Type::STATIC_ARRAY)
			{
#line 134 "../../../Source/Core/AST/VarDecl.nll"
				pValidator->AddError("Can only assign a static array to a vardecl with array size", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
#line 135 "../../../Source/Core/AST/VarDecl.nll"
				return;
			}
#line 138 "../../../Source/Core/AST/VarDecl.nll"
			if (!m_pAssignment->m_pValueType->ValidateAssignable(pValueType, pValidator, m_pAssignment->m_pFirstToken))
			{
				if (pValueType) delete pValueType;
#line 139 "../../../Source/Core/AST/VarDecl.nll"
				return;
			}
			if (pValueType->m_ePointerType != TypeRef::PointerType::OWNED && m_pAssignment->m_pValueType->m_ePointerType == TypeRef::PointerType::OWNED_PREASSSIGN)
			{
				pValidator->AddError("Can't assign an owned pointer to a non-owned variable", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
#line 144 "../../../Source/Core/AST/VarDecl.nll"
				return;
			}
#line 147 "../../../Source/Core/AST/VarDecl.nll"
			if (pValueType->m_ePointerType == TypeRef::PointerType::OWNED && (m_pAssignment->m_pValueType->m_ePointerType != TypeRef::PointerType::OWNED_PREASSSIGN && m_pAssignment->m_pValueType->m_eType != ValueType::Type::NULL_VALUE))
			{
				pValidator->AddError("Expected right side of = to be OWNED_PREASSSIGN (result of own)", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
#line 150 "../../../Source/Core/AST/VarDecl.nll"
				return;
			}
			else
#line 152 "../../../Source/Core/AST/VarDecl.nll"
				if (m_pAssignment->m_pValueType->m_ePointerType == TypeRef::PointerType::TRANSITON)
				{
					pValidator->AddError("Cannot store a TRANSITION pointer (need to `own` it)", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
					if (pValueType) delete pValueType;
#line 155 "../../../Source/Core/AST/VarDecl.nll"
					return;
				}
		}
		if (pValueType) delete pValueType;
	}

#line 162 "../../../Source/Core/AST/VarDecl.nll"
	void VarDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		if (nDepth > 0 && m_pFirstToken != 0)
			pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 169 "../../../Source/Core/AST/VarDecl.nll"
		if (eLanguage == AST::Language::CS)
		{
			if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_PARAM_DECL)
			{
				bool bBefore = m_pTypeRef->m_bConst;
				m_pTypeRef->m_bConst = false;
				m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				m_pTypeRef->m_bConst = bBefore;
			}
			else
			{
				bool bBefore = m_pTypeRef->m_bConst;
				if (m_pArraySizeVector != 0 && bBefore)
				{
					m_pTypeRef->m_bConst = false;
					pOutputBuilder->m_sOut->Append("readonly ");
				}
				m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				m_pTypeRef->m_bConst = bBefore;
			}
#line 190 "../../../Source/Core/AST/VarDecl.nll"
			if (m_pArraySizeVector != 0)
			{
				pOutputBuilder->m_sOut->AppendChar('[');
#line 195 "../../../Source/Core/AST/VarDecl.nll"
				pOutputBuilder->m_sOut->AppendChar(']');
			}
		}
		else
		{
			m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}
		pOutputBuilder->m_sOut->AppendChar(' ');
#line 205 "../../../Source/Core/AST/VarDecl.nll"
		if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL && eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
		{
			AST* pParentParent = m_pParent->m_pParent;
			if (pParentParent == 0 || pParentParent->m_eType != AST::Type::AST_CLASS_DECL)
			{
				Assert::Plz(false);
			}
#line 213 "../../../Source/Core/AST/VarDecl.nll"
			ClassDecl* pClassDecl = (ClassDecl*)(pParentParent);
			pOutputBuilder->m_sOut->AppendString(pClassDecl->m_pNameToken->GetString());
			pOutputBuilder->m_sOut->AppendString("::");
		}
#line 218 "../../../Source/Core/AST/VarDecl.nll"
		pOutputBuilder->m_sOut->AppendString(m_pNameToken->GetString());
#line 220 "../../../Source/Core/AST/VarDecl.nll"
		if (m_pArraySizeVector != 0 && eLanguage != AST::Language::CS)
		{
			for (int i = 0; i < m_pArraySizeVector->GetSize(); i++)
			{
				AST* pArraySize = m_pArraySizeVector->Get(i);
				pOutputBuilder->m_sOut->AppendChar('[');
				pArraySize->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				pOutputBuilder->m_sOut->AppendChar(']');
			}
		}
#line 231 "../../../Source/Core/AST/VarDecl.nll"
		MemberVarDecl* pMemberVarDecl = (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL) ? (MemberVarDecl*)(m_pParent) : 0;
		bool bStatic = pMemberVarDecl != 0 && pMemberVarDecl->m_bStatic;
#line 234 "../../../Source/Core/AST/VarDecl.nll"
		if (m_pAssignment != 0)
		{
			bool bArrayAssignment = m_pArraySizeVector != 0;
#line 238 "../../../Source/Core/AST/VarDecl.nll"
			bool bDoIt = true;
#line 240 "../../../Source/Core/AST/VarDecl.nll"
			if (eLanguage == AST::Language::CPP)
			{
				if (pMemberVarDecl != 0)
				{
					if (eOutputFile == AST::OutputFile::HEADER)
					{
#line 247 "../../../Source/Core/AST/VarDecl.nll"
						if (!(bStatic && m_pTypeRef->m_bConst && m_pTypeRef->IsIntegral() && !bArrayAssignment))
							bDoIt = false;
					}
					else
					{
						if (bStatic && m_pTypeRef->m_bConst && m_pTypeRef->IsIntegral() && !bArrayAssignment)
							bDoIt = false;
					}
				}
				else
				{
#line 259 "../../../Source/Core/AST/VarDecl.nll"
					if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_PARAM_DECL && eOutputFile == AST::OutputFile::SOURCE)
						bDoIt = false;
				}
			}
#line 264 "../../../Source/Core/AST/VarDecl.nll"
			if (bDoIt)
			{
				pOutputBuilder->m_sOut->AppendString(" = ");
				m_pAssignment->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
		}
		else
		{
			if (!m_bInline)
			{
				const char* sxToAppend = 0;
				if (eOutputFile == AST::OutputFile::SOURCE && eLanguage != AST::Language::NLL && eLanguage != AST::Language::NLL_DEF)
				{
					if (m_pParent->m_eType != AST::Type::AST_MEMBER_VAR_DECL)
					{
						if (m_pArraySizeVector == 0)
						{
							if (m_pTypeRef->IsInt())
								sxToAppend = " = 0";
							else
#line 283 "../../../Source/Core/AST/VarDecl.nll"
								if (m_pTypeRef->IsBool())
									sxToAppend = " = false";
								else
#line 285 "../../../Source/Core/AST/VarDecl.nll"
									if (m_pTypeRef->IsFloat())
										sxToAppend = " = 0.0f";
									else
#line 287 "../../../Source/Core/AST/VarDecl.nll"
										if (m_pTypeRef->IsDouble())
											sxToAppend = " = 0.0";
						}
					}
				}
#line 293 "../../../Source/Core/AST/VarDecl.nll"
				if (sxToAppend != 0)
				{
					pOutputBuilder->m_sOut->AppendString(sxToAppend);
				}
				else
				{
					if (eLanguage == AST::Language::CPP)
					{
						if (eOutputFile == AST::OutputFile::SOURCE)
						{
							Project* pProject = GetProject();
							ValueType* pValueType = m_pTypeRef->CreateValueType(pProject->m_pValidator->m_pResolver);
#line 306 "../../../Source/Core/AST/VarDecl.nll"
							if (pValueType != 0 && pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE && m_pArraySizeVector == 0)
								pOutputBuilder->m_sOut->AppendString(" = 0");
#line 309 "../../../Source/Core/AST/VarDecl.nll"
							if (bStatic && m_pTypeRef->IsIntegral())
								pOutputBuilder->m_sOut->AppendString(" = 0");
							if (pValueType) delete pValueType;
						}
					}
					if (eLanguage == AST::Language::CS && m_pArraySizeVector != 0)
					{
						pOutputBuilder->m_sOut->AppendString(" = new ");
						m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 319 "../../../Source/Core/AST/VarDecl.nll"
						for (int i = 0; i < m_pArraySizeVector->GetSize(); i++)
						{
							AST* pArraySize = m_pArraySizeVector->Get(i);
							pOutputBuilder->m_sOut->AppendChar('[');
							pArraySize->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
							pOutputBuilder->m_sOut->AppendChar(']');
						}
					}
				}
			}
		}
#line 331 "../../../Source/Core/AST/VarDecl.nll"
		if (!m_bInline)
			pOutputBuilder->m_sOut->AppendString(";\n");
	}

#line 3 "../../../Source/Core/AST/VarDecl.nll"
	VarDecl::~VarDecl()
	{
		if (m_pArraySizeVector) delete m_pArraySizeVector;
		if (m_pOwnedNameToken) delete m_pOwnedNameToken;
	}

}

