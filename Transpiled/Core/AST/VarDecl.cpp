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
#line 17 "../../../Source/Core/AST/VarDecl.nll"
		m_eType = AST::Type::AST_VAR_DECL;
	}

#line 20 "../../../Source/Core/AST/VarDecl.nll"
	VarDecl* VarDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, bool bInline)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		TypeRef* pTypeRef = TypeRef::TryCreate(pTokenContainer, pTempOffset);
#line 25 "../../../Source/Core/AST/VarDecl.nll"
		if (pTypeRef == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
#line 26 "../../../Source/Core/AST/VarDecl.nll"
			return 0;
		}
		Token* pNameToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
#line 29 "../../../Source/Core/AST/VarDecl.nll"
		if (pNameToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
#line 30 "../../../Source/Core/AST/VarDecl.nll"
			return 0;
		}
#line 31 "../../../Source/Core/AST/VarDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		VarDecl* pVarDecl = new VarDecl();
		Token* pSquareBracketLeftToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_LEFT);
#line 36 "../../../Source/Core/AST/VarDecl.nll"
		while (pSquareBracketLeftToken != 0)
		{
#line 38 "../../../Source/Core/AST/VarDecl.nll"
			if (pVarDecl->m_pArraySizeVector == 0)
#line 39 "../../../Source/Core/AST/VarDecl.nll"
				pVarDecl->m_pArraySizeVector = new Vector<AST*>();
#line 41 "../../../Source/Core/AST/VarDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			AST* pArraySize = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 44 "../../../Source/Core/AST/VarDecl.nll"
			if (pArraySize == 0)
			{
#line 46 "../../../Source/Core/AST/VarDecl.nll"
				Console::Log("unable to parse array size...");
#line 47 "../../../Source/Core/AST/VarDecl.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 48 "../../../Source/Core/AST/VarDecl.nll"
				Assert::Plz(false);
				if (pArraySize) delete pArraySize;
				if (pTempOffset) delete pTempOffset;
				if (pTypeRef) delete pTypeRef;
				if (pVarDecl) delete pVarDecl;
#line 49 "../../../Source/Core/AST/VarDecl.nll"
				return 0;
			}
			Token* pSquareBracketRightToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_RIGHT);
#line 53 "../../../Source/Core/AST/VarDecl.nll"
			if (pSquareBracketRightToken == 0)
			{
#line 55 "../../../Source/Core/AST/VarDecl.nll"
				Console::Log("unable to parse closing square bracket");
#line 56 "../../../Source/Core/AST/VarDecl.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 57 "../../../Source/Core/AST/VarDecl.nll"
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
#line 71 "../../../Source/Core/AST/VarDecl.nll"
		if (pEqualsToken != 0)
		{
#line 73 "../../../Source/Core/AST/VarDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 75 "../../../Source/Core/AST/VarDecl.nll"
			pAssignment = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 77 "../../../Source/Core/AST/VarDecl.nll"
			if (pAssignment == 0)
			{
#line 79 "../../../Source/Core/AST/VarDecl.nll"
				Console::Log("expected to parse assignment...");
#line 80 "../../../Source/Core/AST/VarDecl.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 81 "../../../Source/Core/AST/VarDecl.nll"
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
#line 88 "../../../Source/Core/AST/VarDecl.nll"
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
#line 95 "../../../Source/Core/AST/VarDecl.nll"
		pVarDecl->m_pFirstToken = pTypeRef->m_pFirstToken;
#line 96 "../../../Source/Core/AST/VarDecl.nll"
		pVarDecl->m_pTypeRef = pTypeRef;
#line 97 "../../../Source/Core/AST/VarDecl.nll"
		pVarDecl->m_pNameToken = pNameToken;
#line 98 "../../../Source/Core/AST/VarDecl.nll"
		pVarDecl->m_pAssignment = pAssignment;
#line 99 "../../../Source/Core/AST/VarDecl.nll"
		pVarDecl->m_bInline = bInline;
		NumbatLogic::TypeRef* __967516521 = pTypeRef;
#line 101 "../../../Source/Core/AST/VarDecl.nll"
		pTypeRef = 0;
#line 101 "../../../Source/Core/AST/VarDecl.nll"
		pVarDecl->AddChild(__967516521);
#line 102 "../../../Source/Core/AST/VarDecl.nll"
		if (pAssignment != 0)
		{
			NumbatLogic::AST* __183753559 = pAssignment;
#line 103 "../../../Source/Core/AST/VarDecl.nll"
			pAssignment = 0;
#line 103 "../../../Source/Core/AST/VarDecl.nll"
			pVarDecl->AddChild(__183753559);
		}
#line 105 "../../../Source/Core/AST/VarDecl.nll"
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

#line 109 "../../../Source/Core/AST/VarDecl.nll"
	void VarDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 111 "../../../Source/Core/AST/VarDecl.nll"
		AST::Validate(pValidator, pParent);
#line 113 "../../../Source/Core/AST/VarDecl.nll"
		if (m_pParent->m_eType != AST::Type::AST_MEMBER_VAR_DECL && m_pParent->m_eType != AST::Type::AST_PARAM_DECL)
#line 114 "../../../Source/Core/AST/VarDecl.nll"
			pValidator->AddVarDecl(this);
		ValueType* pValueType = m_pTypeRef->CreateValueType(pValidator->m_pResolver);
#line 117 "../../../Source/Core/AST/VarDecl.nll"
		if (pValueType == 0)
		{
#line 119 "../../../Source/Core/AST/VarDecl.nll"
			pValidator->AddError("Unknown ValueType for TypeRef", m_pTypeRef->m_pFirstToken->m_sFileName, m_pTypeRef->m_pFirstToken->m_nLine, m_pTypeRef->m_pFirstToken->m_nColumn);
			if (pValueType) delete pValueType;
#line 120 "../../../Source/Core/AST/VarDecl.nll"
			return;
		}
#line 123 "../../../Source/Core/AST/VarDecl.nll"
		if (m_pAssignment != 0)
		{
#line 125 "../../../Source/Core/AST/VarDecl.nll"
			if (m_pAssignment->m_pValueType == 0)
			{
#line 127 "../../../Source/Core/AST/VarDecl.nll"
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
#line 141 "../../../Source/Core/AST/VarDecl.nll"
			if (pValueType->m_ePointerType != TypeRef::PointerType::OWNED && m_pAssignment->m_pValueType->m_ePointerType == TypeRef::PointerType::OWNED_PREASSSIGN)
			{
#line 143 "../../../Source/Core/AST/VarDecl.nll"
				pValidator->AddError("Can't assign an owned pointer to a non-owned variable", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
#line 144 "../../../Source/Core/AST/VarDecl.nll"
				return;
			}
#line 147 "../../../Source/Core/AST/VarDecl.nll"
			if (pValueType->m_ePointerType == TypeRef::PointerType::OWNED && (m_pAssignment->m_pValueType->m_ePointerType != TypeRef::PointerType::OWNED_PREASSSIGN && m_pAssignment->m_pValueType->m_eType != ValueType::Type::NULL_VALUE))
			{
#line 149 "../../../Source/Core/AST/VarDecl.nll"
				pValidator->AddError("Expected right side of = to be OWNED_PREASSSIGN (result of own)", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
#line 150 "../../../Source/Core/AST/VarDecl.nll"
				return;
			}
			else
#line 152 "../../../Source/Core/AST/VarDecl.nll"
				if (m_pAssignment->m_pValueType->m_ePointerType == TypeRef::PointerType::TRANSITON)
				{
#line 154 "../../../Source/Core/AST/VarDecl.nll"
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
#line 164 "../../../Source/Core/AST/VarDecl.nll"
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 167 "../../../Source/Core/AST/VarDecl.nll"
		if (eLanguage == AST::Language::CS)
		{
#line 169 "../../../Source/Core/AST/VarDecl.nll"
			if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_PARAM_DECL)
			{
				bool bBefore = m_pTypeRef->m_bConst;
#line 172 "../../../Source/Core/AST/VarDecl.nll"
				m_pTypeRef->m_bConst = false;
#line 173 "../../../Source/Core/AST/VarDecl.nll"
				m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 174 "../../../Source/Core/AST/VarDecl.nll"
				m_pTypeRef->m_bConst = bBefore;
			}
			else
			{
				bool bBefore = m_pTypeRef->m_bConst;
#line 179 "../../../Source/Core/AST/VarDecl.nll"
				if (m_pArraySizeVector != 0 && bBefore)
				{
#line 181 "../../../Source/Core/AST/VarDecl.nll"
					m_pTypeRef->m_bConst = false;
#line 182 "../../../Source/Core/AST/VarDecl.nll"
					pOutputBuilder->m_sOut->Append("readonly ");
				}
#line 184 "../../../Source/Core/AST/VarDecl.nll"
				m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 185 "../../../Source/Core/AST/VarDecl.nll"
				m_pTypeRef->m_bConst = bBefore;
			}
#line 188 "../../../Source/Core/AST/VarDecl.nll"
			if (m_pArraySizeVector != 0)
			{
#line 190 "../../../Source/Core/AST/VarDecl.nll"
				pOutputBuilder->m_sOut->AppendChar('[');
#line 193 "../../../Source/Core/AST/VarDecl.nll"
				pOutputBuilder->m_sOut->AppendChar(']');
			}
		}
		else
		{
#line 198 "../../../Source/Core/AST/VarDecl.nll"
			m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}
#line 200 "../../../Source/Core/AST/VarDecl.nll"
		pOutputBuilder->m_sOut->AppendChar(' ');
#line 203 "../../../Source/Core/AST/VarDecl.nll"
		if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL && eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
		{
			AST* pParentParent = m_pParent->m_pParent;
#line 206 "../../../Source/Core/AST/VarDecl.nll"
			if (pParentParent == 0 || pParentParent->m_eType != AST::Type::AST_CLASS_DECL)
			{
#line 208 "../../../Source/Core/AST/VarDecl.nll"
				Assert::Plz(false);
			}
			ClassDecl* pClassDecl = (ClassDecl*)(pParentParent);
#line 212 "../../../Source/Core/AST/VarDecl.nll"
			pOutputBuilder->m_sOut->AppendString(pClassDecl->m_pNameToken->GetString());
#line 213 "../../../Source/Core/AST/VarDecl.nll"
			pOutputBuilder->m_sOut->AppendString("::");
		}
#line 216 "../../../Source/Core/AST/VarDecl.nll"
		pOutputBuilder->m_sOut->AppendString(m_pNameToken->GetString());
#line 218 "../../../Source/Core/AST/VarDecl.nll"
		if (m_pArraySizeVector != 0 && eLanguage != AST::Language::CS)
		{
#line 220 "../../../Source/Core/AST/VarDecl.nll"
			for (int i = 0; i < m_pArraySizeVector->GetSize(); i++)
			{
				AST* pArraySize = m_pArraySizeVector->Get(i);
#line 223 "../../../Source/Core/AST/VarDecl.nll"
				pOutputBuilder->m_sOut->AppendChar('[');
#line 224 "../../../Source/Core/AST/VarDecl.nll"
				pArraySize->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 225 "../../../Source/Core/AST/VarDecl.nll"
				pOutputBuilder->m_sOut->AppendChar(']');
			}
		}
		MemberVarDecl* pMemberVarDecl = (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL) ? (MemberVarDecl*)(m_pParent) : 0;
		bool bStatic = pMemberVarDecl != 0 && pMemberVarDecl->m_bStatic;
#line 232 "../../../Source/Core/AST/VarDecl.nll"
		if (m_pAssignment != 0)
		{
			bool bArrayAssignment = m_pArraySizeVector != 0;
			bool bDoIt = true;
#line 238 "../../../Source/Core/AST/VarDecl.nll"
			if (eLanguage == AST::Language::CPP)
			{
#line 240 "../../../Source/Core/AST/VarDecl.nll"
				if (pMemberVarDecl != 0)
				{
#line 242 "../../../Source/Core/AST/VarDecl.nll"
					if (eOutputFile == AST::OutputFile::HEADER)
					{
#line 245 "../../../Source/Core/AST/VarDecl.nll"
						if (!(bStatic && m_pTypeRef->m_bConst && m_pTypeRef->IsIntegral() && !bArrayAssignment))
#line 246 "../../../Source/Core/AST/VarDecl.nll"
							bDoIt = false;
					}
					else
					{
#line 250 "../../../Source/Core/AST/VarDecl.nll"
						if (bStatic && m_pTypeRef->m_bConst && m_pTypeRef->IsIntegral() && !bArrayAssignment)
#line 251 "../../../Source/Core/AST/VarDecl.nll"
							bDoIt = false;
					}
				}
				else
				{
#line 257 "../../../Source/Core/AST/VarDecl.nll"
					if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_PARAM_DECL && eOutputFile == AST::OutputFile::SOURCE)
#line 258 "../../../Source/Core/AST/VarDecl.nll"
						bDoIt = false;
				}
			}
#line 262 "../../../Source/Core/AST/VarDecl.nll"
			if (bDoIt)
			{
#line 264 "../../../Source/Core/AST/VarDecl.nll"
				pOutputBuilder->m_sOut->AppendString(" = ");
#line 265 "../../../Source/Core/AST/VarDecl.nll"
				m_pAssignment->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
		}
		else
		{
#line 270 "../../../Source/Core/AST/VarDecl.nll"
			if (!m_bInline)
			{
				const char* sxToAppend = 0;
#line 273 "../../../Source/Core/AST/VarDecl.nll"
				if (eOutputFile == AST::OutputFile::SOURCE && eLanguage != AST::Language::NLL && eLanguage != AST::Language::NLL_DEF)
				{
#line 275 "../../../Source/Core/AST/VarDecl.nll"
					if (m_pParent->m_eType != AST::Type::AST_MEMBER_VAR_DECL)
					{
#line 277 "../../../Source/Core/AST/VarDecl.nll"
						if (m_pArraySizeVector == 0)
						{
#line 279 "../../../Source/Core/AST/VarDecl.nll"
							if (m_pTypeRef->IsInt())
#line 280 "../../../Source/Core/AST/VarDecl.nll"
								sxToAppend = " = 0";
							else
#line 281 "../../../Source/Core/AST/VarDecl.nll"
								if (m_pTypeRef->IsBool())
#line 282 "../../../Source/Core/AST/VarDecl.nll"
									sxToAppend = " = false";
								else
#line 283 "../../../Source/Core/AST/VarDecl.nll"
									if (m_pTypeRef->IsFloat())
#line 284 "../../../Source/Core/AST/VarDecl.nll"
										sxToAppend = " = 0.0f";
									else
#line 285 "../../../Source/Core/AST/VarDecl.nll"
										if (m_pTypeRef->IsDouble())
#line 286 "../../../Source/Core/AST/VarDecl.nll"
											sxToAppend = " = 0.0";
						}
					}
				}
#line 291 "../../../Source/Core/AST/VarDecl.nll"
				if (sxToAppend != 0)
				{
#line 293 "../../../Source/Core/AST/VarDecl.nll"
					pOutputBuilder->m_sOut->AppendString(sxToAppend);
				}
				else
				{
#line 297 "../../../Source/Core/AST/VarDecl.nll"
					if (eLanguage == AST::Language::CPP)
					{
#line 299 "../../../Source/Core/AST/VarDecl.nll"
						if (eOutputFile == AST::OutputFile::SOURCE)
						{
							Project* pProject = GetProject();
							ValueType* pValueType = m_pTypeRef->CreateValueType(pProject->m_pValidator->m_pResolver);
#line 304 "../../../Source/Core/AST/VarDecl.nll"
							if (pValueType != 0 && pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE && m_pArraySizeVector == 0)
#line 305 "../../../Source/Core/AST/VarDecl.nll"
								pOutputBuilder->m_sOut->AppendString(" = 0");
#line 307 "../../../Source/Core/AST/VarDecl.nll"
							if (bStatic && m_pTypeRef->IsIntegral())
#line 308 "../../../Source/Core/AST/VarDecl.nll"
								pOutputBuilder->m_sOut->AppendString(" = 0");
							if (pValueType) delete pValueType;
						}
					}
#line 312 "../../../Source/Core/AST/VarDecl.nll"
					if (eLanguage == AST::Language::CS && m_pArraySizeVector != 0)
					{
#line 314 "../../../Source/Core/AST/VarDecl.nll"
						pOutputBuilder->m_sOut->AppendString(" = new ");
#line 315 "../../../Source/Core/AST/VarDecl.nll"
						m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 317 "../../../Source/Core/AST/VarDecl.nll"
						for (int i = 0; i < m_pArraySizeVector->GetSize(); i++)
						{
							AST* pArraySize = m_pArraySizeVector->Get(i);
#line 320 "../../../Source/Core/AST/VarDecl.nll"
							pOutputBuilder->m_sOut->AppendChar('[');
#line 321 "../../../Source/Core/AST/VarDecl.nll"
							pArraySize->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 322 "../../../Source/Core/AST/VarDecl.nll"
							pOutputBuilder->m_sOut->AppendChar(']');
						}
					}
				}
			}
		}
#line 329 "../../../Source/Core/AST/VarDecl.nll"
		if (!m_bInline)
#line 330 "../../../Source/Core/AST/VarDecl.nll"
			pOutputBuilder->m_sOut->AppendString(";\n");
	}

#line 3 "../../../Source/Core/AST/VarDecl.nll"
	VarDecl::~VarDecl()
	{
		if (m_pArraySizeVector) delete m_pArraySizeVector;
		if (m_pOwnedNameToken) delete m_pOwnedNameToken;
	}

}

