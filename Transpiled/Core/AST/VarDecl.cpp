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
#include "../Util.hpp"
#include "../OutputBuilder.hpp"
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
	class Util;
	class OutputBuilder;
	class InternalString;
	class ClassDecl;
	class MemberVarDecl;
	class Project;
}
#line 1 "../../../Source/Core/AST/VarDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/VarDecl.nll"
#line 15 "../../../Source/Core/AST/VarDecl.nll"
	VarDecl::VarDecl()
	{
		m_pTypeRef = 0;
		m_pNameToken = 0;
		m_pAssignment = 0;
		m_bInline = false;
		m_pArraySizeVector = 0;
		m_pOwnedNameToken = 0;
#line 17 "../../../Source/Core/AST/VarDecl.nll"
		m_bInline = false;
#line 18 "../../../Source/Core/AST/VarDecl.nll"
		m_eType = AST::Type::AST_VAR_DECL;
	}

#line 21 "../../../Source/Core/AST/VarDecl.nll"
	VarDecl* VarDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, bool bInline)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		TypeRef* pTypeRef = TypeRef::TryCreate(pTokenContainer, pTempOffset);
#line 26 "../../../Source/Core/AST/VarDecl.nll"
		if (pTypeRef == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
#line 27 "../../../Source/Core/AST/VarDecl.nll"
			return 0;
		}
		Token* pNameToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
#line 30 "../../../Source/Core/AST/VarDecl.nll"
		if (pNameToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
#line 31 "../../../Source/Core/AST/VarDecl.nll"
			return 0;
		}
#line 32 "../../../Source/Core/AST/VarDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		VarDecl* pVarDecl = new VarDecl();
		Token* pSquareBracketLeftToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_LEFT);
#line 37 "../../../Source/Core/AST/VarDecl.nll"
		while (pSquareBracketLeftToken != 0)
		{
#line 39 "../../../Source/Core/AST/VarDecl.nll"
			if (pVarDecl->m_pArraySizeVector == 0)
#line 40 "../../../Source/Core/AST/VarDecl.nll"
				pVarDecl->m_pArraySizeVector = new Vector<AST*>();
#line 42 "../../../Source/Core/AST/VarDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			AST* pArraySize = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 45 "../../../Source/Core/AST/VarDecl.nll"
			if (pArraySize == 0)
			{
#line 47 "../../../Source/Core/AST/VarDecl.nll"
				Console::Log("unable to parse array size...");
#line 48 "../../../Source/Core/AST/VarDecl.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 49 "../../../Source/Core/AST/VarDecl.nll"
				Assert::Plz(false);
				if (pArraySize) delete pArraySize;
				if (pTempOffset) delete pTempOffset;
				if (pTypeRef) delete pTypeRef;
				if (pVarDecl) delete pVarDecl;
#line 50 "../../../Source/Core/AST/VarDecl.nll"
				return 0;
			}
			Token* pSquareBracketRightToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_RIGHT);
#line 54 "../../../Source/Core/AST/VarDecl.nll"
			if (pSquareBracketRightToken == 0)
			{
#line 56 "../../../Source/Core/AST/VarDecl.nll"
				Console::Log("unable to parse closing square bracket");
#line 57 "../../../Source/Core/AST/VarDecl.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 58 "../../../Source/Core/AST/VarDecl.nll"
				Assert::Plz(false);
				if (pArraySize) delete pArraySize;
				if (pTempOffset) delete pTempOffset;
				if (pTypeRef) delete pTypeRef;
				if (pVarDecl) delete pVarDecl;
#line 59 "../../../Source/Core/AST/VarDecl.nll"
				return 0;
			}
#line 62 "../../../Source/Core/AST/VarDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 64 "../../../Source/Core/AST/VarDecl.nll"
			pVarDecl->m_pArraySizeVector->PushBack(pArraySize);
			NumbatLogic::AST* __830257000 = pArraySize;
#line 65 "../../../Source/Core/AST/VarDecl.nll"
			pArraySize = 0;
#line 65 "../../../Source/Core/AST/VarDecl.nll"
			pVarDecl->AddChild(__830257000);
#line 67 "../../../Source/Core/AST/VarDecl.nll"
			pSquareBracketLeftToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_LEFT);
			if (pArraySize) delete pArraySize;
		}
		AST* pAssignment = 0;
		Token* pEqualsToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_EQUALS);
#line 72 "../../../Source/Core/AST/VarDecl.nll"
		if (pEqualsToken != 0)
		{
#line 74 "../../../Source/Core/AST/VarDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 76 "../../../Source/Core/AST/VarDecl.nll"
			pAssignment = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 78 "../../../Source/Core/AST/VarDecl.nll"
			if (pAssignment == 0)
			{
#line 80 "../../../Source/Core/AST/VarDecl.nll"
				Console::Log("expected to parse assignment...");
#line 81 "../../../Source/Core/AST/VarDecl.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 82 "../../../Source/Core/AST/VarDecl.nll"
				Assert::Plz(false);
				if (pTempOffset) delete pTempOffset;
				if (pTypeRef) delete pTypeRef;
				if (pVarDecl) delete pVarDecl;
				if (pAssignment) delete pAssignment;
#line 83 "../../../Source/Core/AST/VarDecl.nll"
				return 0;
			}
		}
#line 87 "../../../Source/Core/AST/VarDecl.nll"
		if (!bInline)
		{
#line 89 "../../../Source/Core/AST/VarDecl.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
			{
				if (pTempOffset) delete pTempOffset;
				if (pTypeRef) delete pTypeRef;
				if (pVarDecl) delete pVarDecl;
				if (pAssignment) delete pAssignment;
#line 90 "../../../Source/Core/AST/VarDecl.nll"
				return 0;
			}
#line 91 "../../../Source/Core/AST/VarDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		}
#line 95 "../../../Source/Core/AST/VarDecl.nll"
		pVarDecl->m_bStatement = bInline == false;
#line 96 "../../../Source/Core/AST/VarDecl.nll"
		pVarDecl->m_pFirstToken = pTypeRef->m_pFirstToken;
#line 97 "../../../Source/Core/AST/VarDecl.nll"
		pVarDecl->m_pTypeRef = pTypeRef;
#line 98 "../../../Source/Core/AST/VarDecl.nll"
		pVarDecl->m_pNameToken = pNameToken;
#line 99 "../../../Source/Core/AST/VarDecl.nll"
		pVarDecl->m_pAssignment = pAssignment;
#line 100 "../../../Source/Core/AST/VarDecl.nll"
		pVarDecl->m_bInline = bInline;
		NumbatLogic::TypeRef* __967516521 = pTypeRef;
#line 102 "../../../Source/Core/AST/VarDecl.nll"
		pTypeRef = 0;
#line 102 "../../../Source/Core/AST/VarDecl.nll"
		pVarDecl->AddChild(__967516521);
#line 103 "../../../Source/Core/AST/VarDecl.nll"
		if (pAssignment != 0)
		{
			NumbatLogic::AST* __183753559 = pAssignment;
#line 104 "../../../Source/Core/AST/VarDecl.nll"
			pAssignment = 0;
#line 104 "../../../Source/Core/AST/VarDecl.nll"
			pVarDecl->AddChild(__183753559);
		}
#line 106 "../../../Source/Core/AST/VarDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::VarDecl* __2971982038 = pVarDecl;
#line 107 "../../../Source/Core/AST/VarDecl.nll"
		pVarDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pTypeRef) delete pTypeRef;
		if (pAssignment) delete pAssignment;
#line 107 "../../../Source/Core/AST/VarDecl.nll"
		return __2971982038;
	}

#line 110 "../../../Source/Core/AST/VarDecl.nll"
	void VarDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 112 "../../../Source/Core/AST/VarDecl.nll"
		AST::Validate(pValidator, pParent);
#line 114 "../../../Source/Core/AST/VarDecl.nll"
		if (m_pParent->m_eType != AST::Type::AST_MEMBER_VAR_DECL && m_pParent->m_eType != AST::Type::AST_PARAM_DECL)
#line 115 "../../../Source/Core/AST/VarDecl.nll"
			pValidator->AddVarDecl(this);
		ValueType* pValueType = m_pTypeRef->CreateValueType(pValidator->m_pResolver);
#line 118 "../../../Source/Core/AST/VarDecl.nll"
		if (pValueType == 0)
		{
#line 120 "../../../Source/Core/AST/VarDecl.nll"
			pValidator->AddError("Unknown ValueType for TypeRef", m_pTypeRef->m_pFirstToken->m_sFileName, m_pTypeRef->m_pFirstToken->m_nLine, m_pTypeRef->m_pFirstToken->m_nColumn);
			if (pValueType) delete pValueType;
#line 121 "../../../Source/Core/AST/VarDecl.nll"
			return;
		}
#line 124 "../../../Source/Core/AST/VarDecl.nll"
		if (m_pAssignment != 0)
		{
#line 126 "../../../Source/Core/AST/VarDecl.nll"
			if (m_pAssignment->m_pValueType == 0)
			{
#line 128 "../../../Source/Core/AST/VarDecl.nll"
				pValidator->AddError("Unknown assignment?", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
#line 129 "../../../Source/Core/AST/VarDecl.nll"
				return;
			}
#line 132 "../../../Source/Core/AST/VarDecl.nll"
			if (m_pArraySizeVector != 0 && m_pAssignment->m_pValueType->m_eType != ValueType::Type::STATIC_ARRAY || m_pArraySizeVector == 0 && m_pAssignment->m_pValueType->m_eType == ValueType::Type::STATIC_ARRAY)
			{
#line 135 "../../../Source/Core/AST/VarDecl.nll"
				pValidator->AddError("Can only assign a static array to a vardecl with array size", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
#line 136 "../../../Source/Core/AST/VarDecl.nll"
				return;
			}
#line 139 "../../../Source/Core/AST/VarDecl.nll"
			if (!m_pAssignment->m_pValueType->ValidateAssignable(pValueType, pValidator, m_pAssignment->m_pFirstToken))
			{
				if (pValueType) delete pValueType;
#line 140 "../../../Source/Core/AST/VarDecl.nll"
				return;
			}
#line 142 "../../../Source/Core/AST/VarDecl.nll"
			if (pValueType->m_ePointerType != TypeRef::PointerType::OWNED && m_pAssignment->m_pValueType->m_ePointerType == TypeRef::PointerType::OWNED_PREASSSIGN)
			{
#line 144 "../../../Source/Core/AST/VarDecl.nll"
				pValidator->AddError("Can't assign an owned pointer to a non-owned variable", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
#line 145 "../../../Source/Core/AST/VarDecl.nll"
				return;
			}
#line 148 "../../../Source/Core/AST/VarDecl.nll"
			if (pValueType->m_ePointerType == TypeRef::PointerType::OWNED && (m_pAssignment->m_pValueType->m_ePointerType != TypeRef::PointerType::OWNED_PREASSSIGN && m_pAssignment->m_pValueType->m_eType != ValueType::Type::NULL_VALUE))
			{
#line 150 "../../../Source/Core/AST/VarDecl.nll"
				pValidator->AddError("Expected right side of = to be OWNED_PREASSSIGN (result of own)", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
#line 151 "../../../Source/Core/AST/VarDecl.nll"
				return;
			}
			else
#line 153 "../../../Source/Core/AST/VarDecl.nll"
				if (m_pAssignment->m_pValueType->m_ePointerType == TypeRef::PointerType::TRANSITON)
				{
#line 155 "../../../Source/Core/AST/VarDecl.nll"
					pValidator->AddError("Cannot store a TRANSITION pointer (need to `own` it)", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
					if (pValueType) delete pValueType;
#line 156 "../../../Source/Core/AST/VarDecl.nll"
					return;
				}
		}
		if (pValueType) delete pValueType;
	}

#line 163 "../../../Source/Core/AST/VarDecl.nll"
	void VarDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 165 "../../../Source/Core/AST/VarDecl.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 168 "../../../Source/Core/AST/VarDecl.nll"
		if (eLanguage == AST::Language::CS)
		{
#line 170 "../../../Source/Core/AST/VarDecl.nll"
			if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_PARAM_DECL)
			{
				bool bBefore = m_pTypeRef->m_bConst;
#line 173 "../../../Source/Core/AST/VarDecl.nll"
				m_pTypeRef->m_bConst = false;
#line 174 "../../../Source/Core/AST/VarDecl.nll"
				m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 175 "../../../Source/Core/AST/VarDecl.nll"
				m_pTypeRef->m_bConst = bBefore;
			}
			else
			{
				bool bBefore = m_pTypeRef->m_bConst;
#line 180 "../../../Source/Core/AST/VarDecl.nll"
				if (m_pArraySizeVector != 0 && bBefore)
				{
#line 182 "../../../Source/Core/AST/VarDecl.nll"
					m_pTypeRef->m_bConst = false;
#line 183 "../../../Source/Core/AST/VarDecl.nll"
					pOutputBuilder->m_sOut->Append("readonly ");
				}
#line 185 "../../../Source/Core/AST/VarDecl.nll"
				m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 186 "../../../Source/Core/AST/VarDecl.nll"
				m_pTypeRef->m_bConst = bBefore;
			}
#line 189 "../../../Source/Core/AST/VarDecl.nll"
			if (m_pArraySizeVector != 0)
			{
#line 191 "../../../Source/Core/AST/VarDecl.nll"
				pOutputBuilder->m_sOut->AppendChar('[');
#line 194 "../../../Source/Core/AST/VarDecl.nll"
				pOutputBuilder->m_sOut->AppendChar(']');
			}
		}
		else
		{
#line 199 "../../../Source/Core/AST/VarDecl.nll"
			m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}
#line 201 "../../../Source/Core/AST/VarDecl.nll"
		pOutputBuilder->m_sOut->AppendChar(' ');
#line 204 "../../../Source/Core/AST/VarDecl.nll"
		if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL && eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
		{
			AST* pParentParent = m_pParent->m_pParent;
#line 207 "../../../Source/Core/AST/VarDecl.nll"
			if (pParentParent == 0 || pParentParent->m_eType != AST::Type::AST_CLASS_DECL)
			{
#line 209 "../../../Source/Core/AST/VarDecl.nll"
				Assert::Plz(false);
			}
			ClassDecl* pClassDecl = (ClassDecl*)(pParentParent);
#line 213 "../../../Source/Core/AST/VarDecl.nll"
			pOutputBuilder->m_sOut->AppendString(pClassDecl->m_pNameToken->GetString());
#line 214 "../../../Source/Core/AST/VarDecl.nll"
			pOutputBuilder->m_sOut->AppendString("::");
		}
#line 217 "../../../Source/Core/AST/VarDecl.nll"
		pOutputBuilder->m_sOut->AppendString(m_pNameToken->GetString());
#line 219 "../../../Source/Core/AST/VarDecl.nll"
		if (m_pArraySizeVector != 0 && eLanguage != AST::Language::CS)
		{
#line 221 "../../../Source/Core/AST/VarDecl.nll"
			for (int i = 0; i < m_pArraySizeVector->GetSize(); i++)
			{
				AST* pArraySize = m_pArraySizeVector->Get(i);
#line 224 "../../../Source/Core/AST/VarDecl.nll"
				pOutputBuilder->m_sOut->AppendChar('[');
#line 225 "../../../Source/Core/AST/VarDecl.nll"
				pArraySize->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 226 "../../../Source/Core/AST/VarDecl.nll"
				pOutputBuilder->m_sOut->AppendChar(']');
			}
		}
		MemberVarDecl* pMemberVarDecl = (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL) ? (MemberVarDecl*)(m_pParent) : 0;
		bool bStatic = pMemberVarDecl != 0 && pMemberVarDecl->m_bStatic;
#line 233 "../../../Source/Core/AST/VarDecl.nll"
		if (m_pAssignment != 0)
		{
			bool bArrayAssignment = m_pArraySizeVector != 0;
			bool bDoIt = true;
#line 239 "../../../Source/Core/AST/VarDecl.nll"
			if (eLanguage == AST::Language::CPP)
			{
#line 241 "../../../Source/Core/AST/VarDecl.nll"
				if (pMemberVarDecl != 0)
				{
#line 243 "../../../Source/Core/AST/VarDecl.nll"
					if (eOutputFile == AST::OutputFile::HEADER)
					{
#line 246 "../../../Source/Core/AST/VarDecl.nll"
						if (!(bStatic && m_pTypeRef->m_bConst && m_pTypeRef->IsIntegral() && !bArrayAssignment))
#line 247 "../../../Source/Core/AST/VarDecl.nll"
							bDoIt = false;
					}
					else
					{
#line 251 "../../../Source/Core/AST/VarDecl.nll"
						if (bStatic && m_pTypeRef->m_bConst && m_pTypeRef->IsIntegral() && !bArrayAssignment)
#line 252 "../../../Source/Core/AST/VarDecl.nll"
							bDoIt = false;
					}
				}
				else
				{
#line 258 "../../../Source/Core/AST/VarDecl.nll"
					if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_PARAM_DECL && eOutputFile == AST::OutputFile::SOURCE)
#line 259 "../../../Source/Core/AST/VarDecl.nll"
						bDoIt = false;
				}
			}
#line 263 "../../../Source/Core/AST/VarDecl.nll"
			if (bDoIt)
			{
#line 265 "../../../Source/Core/AST/VarDecl.nll"
				pOutputBuilder->m_sOut->AppendString(" = ");
#line 266 "../../../Source/Core/AST/VarDecl.nll"
				m_pAssignment->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
		}
		else
		{
#line 271 "../../../Source/Core/AST/VarDecl.nll"
			if (!m_bInline)
			{
				const char* sxToAppend = 0;
#line 274 "../../../Source/Core/AST/VarDecl.nll"
				if (eOutputFile == AST::OutputFile::SOURCE && eLanguage != AST::Language::NLL && eLanguage != AST::Language::NLL_DEF)
				{
#line 276 "../../../Source/Core/AST/VarDecl.nll"
					if (m_pParent->m_eType != AST::Type::AST_MEMBER_VAR_DECL)
					{
#line 278 "../../../Source/Core/AST/VarDecl.nll"
						if (m_pArraySizeVector == 0)
						{
#line 280 "../../../Source/Core/AST/VarDecl.nll"
							if (m_pTypeRef->IsInt())
#line 281 "../../../Source/Core/AST/VarDecl.nll"
								sxToAppend = " = 0";
							else
#line 282 "../../../Source/Core/AST/VarDecl.nll"
								if (m_pTypeRef->IsBool())
#line 283 "../../../Source/Core/AST/VarDecl.nll"
									sxToAppend = " = false";
								else
#line 284 "../../../Source/Core/AST/VarDecl.nll"
									if (m_pTypeRef->IsFloat())
#line 285 "../../../Source/Core/AST/VarDecl.nll"
										sxToAppend = " = 0.0f";
									else
#line 286 "../../../Source/Core/AST/VarDecl.nll"
										if (m_pTypeRef->IsDouble())
#line 287 "../../../Source/Core/AST/VarDecl.nll"
											sxToAppend = " = 0.0";
						}
					}
				}
#line 292 "../../../Source/Core/AST/VarDecl.nll"
				if (sxToAppend != 0)
				{
#line 294 "../../../Source/Core/AST/VarDecl.nll"
					pOutputBuilder->m_sOut->AppendString(sxToAppend);
				}
				else
				{
#line 298 "../../../Source/Core/AST/VarDecl.nll"
					if (eLanguage == AST::Language::CPP)
					{
#line 300 "../../../Source/Core/AST/VarDecl.nll"
						if (eOutputFile == AST::OutputFile::SOURCE)
						{
							Project* pProject = GetProject();
							ValueType* pValueType = m_pTypeRef->CreateValueType(pProject->m_pValidator->m_pResolver);
#line 305 "../../../Source/Core/AST/VarDecl.nll"
							if (pValueType != 0 && pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE && m_pArraySizeVector == 0)
#line 306 "../../../Source/Core/AST/VarDecl.nll"
								pOutputBuilder->m_sOut->AppendString(" = 0");
#line 308 "../../../Source/Core/AST/VarDecl.nll"
							if (bStatic && m_pTypeRef->IsIntegral())
#line 309 "../../../Source/Core/AST/VarDecl.nll"
								pOutputBuilder->m_sOut->AppendString(" = 0");
							if (pValueType) delete pValueType;
						}
					}
#line 313 "../../../Source/Core/AST/VarDecl.nll"
					if (eLanguage == AST::Language::CS && m_pArraySizeVector != 0)
					{
#line 315 "../../../Source/Core/AST/VarDecl.nll"
						pOutputBuilder->m_sOut->AppendString(" = new ");
#line 316 "../../../Source/Core/AST/VarDecl.nll"
						m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 318 "../../../Source/Core/AST/VarDecl.nll"
						for (int i = 0; i < m_pArraySizeVector->GetSize(); i++)
						{
							AST* pArraySize = m_pArraySizeVector->Get(i);
#line 321 "../../../Source/Core/AST/VarDecl.nll"
							pOutputBuilder->m_sOut->AppendChar('[');
#line 322 "../../../Source/Core/AST/VarDecl.nll"
							pArraySize->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 323 "../../../Source/Core/AST/VarDecl.nll"
							pOutputBuilder->m_sOut->AppendChar(']');
						}
					}
				}
			}
		}
#line 330 "../../../Source/Core/AST/VarDecl.nll"
		if (!m_bInline)
#line 331 "../../../Source/Core/AST/VarDecl.nll"
			pOutputBuilder->m_sOut->AppendString(";\n");
	}

#line 4 "../../../Source/Core/AST/VarDecl.nll"
	VarDecl::~VarDecl()
	{
		if (m_pArraySizeVector) delete m_pArraySizeVector;
		if (m_pOwnedNameToken) delete m_pOwnedNameToken;
	}

}

