#include "VarDecl.hpp"
#include "AST.hpp"
#include "DecoratorCall.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../OffsetDatum.hpp"
#include "TypeRef.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
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
	class DecoratorCall;
	template <class T>
	class Vector;
	class OffsetDatum;
	class TypeRef;
	class VarDecl;
	template <class T>
	class OwnedVector;
	class Token;
	class TokenContainer;
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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
#line 15 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
	VarDecl::VarDecl()
	{
		m_pTypeRef = 0;
		m_pNameToken = 0;
		m_pAssignment = 0;
		m_bInline = false;
		m_pArraySizeVector = 0;
		m_pOwnedNameToken = 0;
		m_pDecoratorCallVector = 0;
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		m_bInline = false;
		m_eType = AST::Type::AST_VAR_DECL;
		m_pDecoratorCallVector = new Vector<DecoratorCall*>();
	}

	VarDecl* VarDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, bool bInline)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 26 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		TypeRef* pTypeRef = TypeRef::TryCreate(pTokenContainer, pTempOffset);
		if (pTypeRef == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
#line 28 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			return 0;
		}
		VarDecl* pVarDecl = new VarDecl();
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		OwnedVector<DecoratorCall*>* pOwnedDecoratorCallVector = new OwnedVector<DecoratorCall*>();
		while (true)
		{
			DecoratorCall* pDecoratorCall = DecoratorCall::TryCreate(pTokenContainer, pTempOffset);
			if (pDecoratorCall == 0)
			{
				if (pDecoratorCall) delete pDecoratorCall;
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				break;
			}
			NumbatLogic::DecoratorCall* __1592839567 = pDecoratorCall;
#line 39 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pDecoratorCall = 0;
#line 39 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pOwnedDecoratorCallVector->PushBack(__1592839567);
			if (pDecoratorCall) delete pDecoratorCall;
		}
		while (pOwnedDecoratorCallVector->GetSize() > 0)
		{
			DecoratorCall* pDecoratorCall = pOwnedDecoratorCallVector->PopFront();
			pDecoratorCall->m_pParent = pVarDecl;
			DecoratorCall* pTemp = pDecoratorCall;
			pVarDecl->m_pDecoratorCallVector->PushBack(pTemp);
			NumbatLogic::DecoratorCall* __1592905165 = pDecoratorCall;
#line 48 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pDecoratorCall = 0;
#line 48 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pVarDecl->AddChild(__1592905165);
			if (pDecoratorCall) delete pDecoratorCall;
		}
		Token* pNameToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
		if (pNameToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
			if (pVarDecl) delete pVarDecl;
			if (pOwnedDecoratorCallVector) delete pOwnedDecoratorCallVector;
#line 53 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			return 0;
		}
#line 54 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 56 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		Token* pSquareBracketLeftToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_LEFT);
		while (pSquareBracketLeftToken != 0)
		{
			if (pVarDecl->m_pArraySizeVector == 0)
				pVarDecl->m_pArraySizeVector = new Vector<AST*>();
#line 62 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 64 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
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
				if (pOwnedDecoratorCallVector) delete pOwnedDecoratorCallVector;
#line 70 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				return 0;
			}
#line 73 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
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
				if (pOwnedDecoratorCallVector) delete pOwnedDecoratorCallVector;
#line 79 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				return 0;
			}
#line 82 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 84 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pVarDecl->m_pArraySizeVector->PushBack(pArraySize);
			NumbatLogic::AST* __830388199 = pArraySize;
#line 85 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pArraySize = 0;
#line 85 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pVarDecl->AddChild(__830388199);
#line 87 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pSquareBracketLeftToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_LEFT);
			if (pArraySize) delete pArraySize;
		}
		AST* pAssignment = 0;
		Token* pEqualsToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_EQUALS);
		if (pEqualsToken != 0)
		{
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 96 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pAssignment = AST::TryCreateExpression(pTokenContainer, pTempOffset);
#line 98 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			if (pAssignment == 0)
			{
				Console::Log("expected to parse assignment...");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				Assert::Plz(false);
				if (pTempOffset) delete pTempOffset;
				if (pTypeRef) delete pTypeRef;
				if (pVarDecl) delete pVarDecl;
				if (pOwnedDecoratorCallVector) delete pOwnedDecoratorCallVector;
				if (pAssignment) delete pAssignment;
#line 103 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				return 0;
			}
		}
#line 107 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		if (!bInline)
		{
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
			{
				if (pTempOffset) delete pTempOffset;
				if (pTypeRef) delete pTypeRef;
				if (pVarDecl) delete pVarDecl;
				if (pOwnedDecoratorCallVector) delete pOwnedDecoratorCallVector;
				if (pAssignment) delete pAssignment;
#line 110 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				return 0;
			}
#line 111 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		}
#line 115 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		pVarDecl->m_bStatement = bInline == false;
		pVarDecl->m_pFirstToken = pTypeRef->m_pFirstToken;
		pVarDecl->m_pTypeRef = pTypeRef;
		pVarDecl->m_pNameToken = pNameToken;
		pVarDecl->m_pAssignment = pAssignment;
		pVarDecl->m_bInline = bInline;
		NumbatLogic::TypeRef* __967647720 = pTypeRef;
		pTypeRef = 0;
#line 122 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		pVarDecl->AddChild(__967647720);
		if (pAssignment != 0)
		{
			NumbatLogic::AST* __183884758 = pAssignment;
#line 124 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pAssignment = 0;
#line 124 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pVarDecl->AddChild(__183884758);
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::VarDecl* __2972113237 = pVarDecl;
#line 127 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		pVarDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pTypeRef) delete pTypeRef;
		if (pOwnedDecoratorCallVector) delete pOwnedDecoratorCallVector;
		if (pAssignment) delete pAssignment;
#line 127 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		return __2972113237;
	}

	void VarDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
#line 134 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		if (m_pParent->m_eType != AST::Type::AST_MEMBER_VAR_DECL && m_pParent->m_eType != AST::Type::AST_PARAM_DECL)
			pValidator->AddVarDecl(this);
#line 137 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		ValueType* pValueType = m_pTypeRef->CreateValueType(pValidator->m_pResolver);
		if (pValueType == 0)
		{
			pValidator->AddError("Unknown ValueType for TypeRef", m_pTypeRef->m_pFirstToken->m_sFileName, m_pTypeRef->m_pFirstToken->m_nLine, m_pTypeRef->m_pFirstToken->m_nColumn);
			if (pValueType) delete pValueType;
#line 141 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			return;
		}
#line 144 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		if (m_pAssignment != 0)
		{
			if (m_pAssignment->m_pValueType == 0)
			{
				pValidator->AddError("Unknown assignment?", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
#line 149 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				return;
			}
#line 152 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			if (m_pArraySizeVector != 0 && m_pAssignment->m_pValueType->m_eType != ValueType::Type::STATIC_ARRAY || m_pArraySizeVector == 0 && m_pAssignment->m_pValueType->m_eType == ValueType::Type::STATIC_ARRAY)
			{
#line 155 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pValidator->AddError("Can only assign a static array to a vardecl with array size", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
#line 156 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				return;
			}
#line 159 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			if (!m_pAssignment->m_pValueType->ValidateAssignable(pValueType, pValidator, m_pAssignment->m_pFirstToken))
			{
				if (pValueType) delete pValueType;
#line 160 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				return;
			}
			if (pValueType->m_ePointerType != TypeRef::PointerType::OWNED && m_pAssignment->m_pValueType->m_ePointerType == TypeRef::PointerType::OWNED_PREASSSIGN)
			{
				pValidator->AddError("Can't assign an owned pointer to a non-owned variable", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
#line 165 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				return;
			}
#line 168 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			if (pValueType->m_ePointerType == TypeRef::PointerType::OWNED && (m_pAssignment->m_pValueType->m_ePointerType != TypeRef::PointerType::OWNED_PREASSSIGN && m_pAssignment->m_pValueType->m_eType != ValueType::Type::NULL_VALUE))
			{
				pValidator->AddError("Expected right side of = to be OWNED_PREASSSIGN (result of own)", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
#line 171 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				return;
			}
			else
#line 173 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				if (m_pAssignment->m_pValueType->m_ePointerType == TypeRef::PointerType::TRANSITON)
				{
					pValidator->AddError("Cannot store a TRANSITION pointer (need to `own` it)", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
					if (pValueType) delete pValueType;
#line 176 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
					return;
				}
		}
		if (pValueType) delete pValueType;
	}

#line 183 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
	void VarDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		if (nDepth > 0 && m_pFirstToken != 0)
			pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
		Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 190 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
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
#line 211 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			if (m_pArraySizeVector != 0)
			{
				pOutputBuilder->m_sOut->AppendChar('[');
#line 216 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pOutputBuilder->m_sOut->AppendChar(']');
			}
		}
		else
		{
			m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}
#line 224 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		pOutputBuilder->m_sOut->AppendChar(' ');
#line 226 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		if (eLanguage == AST::Language::NLL && m_pDecoratorCallVector != 0 && m_pDecoratorCallVector->GetSize() > 0)
		{
			for (int i = 0; i < m_pDecoratorCallVector->GetSize(); i++)
			{
				DecoratorCall* pDecoratorCall = m_pDecoratorCallVector->Get(i);
				pDecoratorCall->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
			pOutputBuilder->m_sOut->AppendChar(' ');
		}
#line 237 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL && eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
		{
			AST* pParentParent = m_pParent->m_pParent;
			if (pParentParent == 0 || pParentParent->m_eType != AST::Type::AST_CLASS_DECL)
			{
				Assert::Plz(false);
			}
#line 245 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			ClassDecl* pClassDecl = (ClassDecl*)(pParentParent);
			pOutputBuilder->m_sOut->AppendString(pClassDecl->m_pNameToken->GetString());
			pOutputBuilder->m_sOut->AppendString("::");
		}
#line 250 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		pOutputBuilder->m_sOut->AppendString(m_pNameToken->GetString());
#line 252 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
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
#line 263 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		MemberVarDecl* pMemberVarDecl = (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL) ? (MemberVarDecl*)(m_pParent) : 0;
		bool bStatic = pMemberVarDecl != 0 && pMemberVarDecl->m_bStatic;
#line 266 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		if (m_pAssignment != 0)
		{
			bool bArrayAssignment = m_pArraySizeVector != 0;
#line 270 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			bool bDoIt = true;
#line 272 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			if (eLanguage == AST::Language::CPP)
			{
				if (pMemberVarDecl != 0)
				{
					if (eOutputFile == AST::OutputFile::HEADER)
					{
#line 279 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
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
#line 291 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
					if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_PARAM_DECL && eOutputFile == AST::OutputFile::SOURCE)
						bDoIt = false;
				}
			}
#line 296 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
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
#line 315 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
								if (m_pTypeRef->IsBool())
									sxToAppend = " = false";
								else
#line 317 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
									if (m_pTypeRef->IsFloat())
										sxToAppend = " = 0.0f";
									else
#line 319 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
										if (m_pTypeRef->IsDouble())
											sxToAppend = " = 0.0";
						}
					}
				}
#line 325 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
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
#line 338 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
							if (pValueType != 0 && pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE && m_pArraySizeVector == 0)
								pOutputBuilder->m_sOut->AppendString(" = 0");
#line 341 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
							if (bStatic && m_pTypeRef->IsIntegral())
								pOutputBuilder->m_sOut->AppendString(" = 0");
							if (pValueType) delete pValueType;
						}
					}
					if (eLanguage == AST::Language::CS && m_pArraySizeVector != 0)
					{
						pOutputBuilder->m_sOut->AppendString(" = new ");
						m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 351 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
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
#line 363 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		if (!m_bInline)
			pOutputBuilder->m_sOut->AppendString(";\n");
	}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
	VarDecl::~VarDecl()
	{
		if (m_pArraySizeVector) delete m_pArraySizeVector;
		if (m_pOwnedNameToken) delete m_pOwnedNameToken;
		if (m_pDecoratorCallVector) delete m_pDecoratorCallVector;
	}

}

