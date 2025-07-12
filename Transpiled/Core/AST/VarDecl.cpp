#include "VarDecl.hpp"
#include "AST.hpp"
#include "../OffsetDatum.hpp"
#include "TypeRef.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../../../../LangShared/ExternalString/CPP/ExternalString.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "../Util.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "ClassDecl.hpp"
#include "MemberVarDecl.hpp"

namespace NumbatLogic
{
	class OffsetDatum;
	class TypeRef;
	class Token;
	class VarDecl;
	class AST;
	class ValueType;
	class ClassDecl;
	class MemberVarDecl;
}
namespace NumbatLogic
{
	VarDecl::VarDecl()
	{
		m_pTypeRef = 0;
		m_pNameToken = 0;
		m_pAssignment = 0;
		m_bInline = false;
		m_pArraySize = 0;
		m_pOwnedNameToken = 0;
		m_bInline = false;
		m_eType = AST::Type::AST_VAR_DECL;
	}

	VarDecl* VarDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, bool bInline)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		TypeRef* pTypeRef = TypeRef::TryCreate(pTokenContainer, pTempOffset);
		if (pTypeRef == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
			return 0;
		}
		Token* pNameToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
		if (pNameToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		VarDecl* pVarDecl = new VarDecl();
		Token* pSquareBracketLeftToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_LEFT);
		if (pSquareBracketLeftToken != 0)
		{
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			AST* pArraySize = AST::TryCreateExpression(pTokenContainer, pTempOffset);
			if (pArraySize == 0)
			{
				Console::Log("unable to parse array size...");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				if (pArraySize) delete pArraySize;
				if (pTempOffset) delete pTempOffset;
				if (pTypeRef) delete pTypeRef;
				if (pVarDecl) delete pVarDecl;
				return 0;
			}
			Token* pSquareBracketRightToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SQUARE_BRACKET_RIGHT);
			if (pSquareBracketRightToken == 0)
			{
				Console::Log("unable to parse closing square bracket");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				if (pArraySize) delete pArraySize;
				if (pTempOffset) delete pTempOffset;
				if (pTypeRef) delete pTypeRef;
				if (pVarDecl) delete pVarDecl;
				return 0;
			}
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			pVarDecl->m_pArraySize = pArraySize;
			NumbatLogic::AST* __3043530774 = pArraySize;
			pArraySize = 0;
			pVarDecl->AddChild(__3043530774);
			if (pArraySize) delete pArraySize;
		}
		AST* pAssignment = 0;
		Token* pEqualsToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_EQUALS);
		if (pEqualsToken != 0)
		{
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			pAssignment = AST::TryCreateExpression(pTokenContainer, pTempOffset);
			if (pAssignment == 0)
			{
				Console::Log("expected to parse assignment...");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				if (pTempOffset) delete pTempOffset;
				if (pTypeRef) delete pTypeRef;
				if (pVarDecl) delete pVarDecl;
				if (pAssignment) delete pAssignment;
				return 0;
			}
		}
		if (!bInline)
		{
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON) == 0)
			{
				if (pTempOffset) delete pTempOffset;
				if (pTypeRef) delete pTypeRef;
				if (pVarDecl) delete pVarDecl;
				if (pAssignment) delete pAssignment;
				return 0;
			}
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		}
		pVarDecl->m_bStatement = bInline == false;
		pVarDecl->m_pFirstToken = pTypeRef->m_pFirstToken;
		pVarDecl->m_pTypeRef = pTypeRef;
		pVarDecl->m_pNameToken = pNameToken;
		pVarDecl->m_pAssignment = pAssignment;
		pVarDecl->m_bInline = bInline;
		NumbatLogic::TypeRef* __4039701331 = pTypeRef;
		pTypeRef = 0;
		pVarDecl->AddChild(__4039701331);
		if (pAssignment != 0)
		{
			NumbatLogic::AST* __3148560342 = pAssignment;
			pAssignment = 0;
			pVarDecl->AddChild(__3148560342);
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::VarDecl* __3184751856 = pVarDecl;
		pVarDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pTypeRef) delete pTypeRef;
		if (pAssignment) delete pAssignment;
		return __3184751856;
	}

	AST* VarDecl::FindByName(const char* sxName, AST* pCallingChild)
	{
		if (ExternalString::Equal(sxName, m_pNameToken->GetString()))
			return this;
		return AST::FindByName(sxName, pCallingChild);
	}

	void VarDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		if (m_pParent->m_eType != AST::Type::AST_MEMBER_VAR_DECL && m_pParent->m_eType != AST::Type::AST_PARAM_DECL)
			pValidator->AddVarDecl(this);
		ValueType* pValueType = m_pTypeRef->CreateValueType();
		if (pValueType == 0)
		{
			pValidator->AddError("Unknown ValueType for TypeRef", m_pTypeRef->m_pFirstToken->m_sFileName, m_pTypeRef->m_pFirstToken->m_nLine, m_pTypeRef->m_pFirstToken->m_nColumn);
			if (pValueType) delete pValueType;
			return;
		}
		if (m_pAssignment != 0)
		{
			if (m_pAssignment->m_pValueType == 0)
			{
				pValidator->AddError("Unknown assignment?", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
				return;
			}
			if (m_pArraySize != 0 && m_pAssignment->m_pValueType->m_eType != ValueType::Type::STATIC_ARRAY || m_pArraySize == 0 && m_pAssignment->m_pValueType->m_eType == ValueType::Type::STATIC_ARRAY)
			{
				pValidator->AddError("Can only assign a static array to a vardecl with array size", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
				return;
			}
			if (!m_pAssignment->m_pValueType->ValidateAssignable(pValueType, pValidator, m_pAssignment->m_pFirstToken))
			{
				if (pValueType) delete pValueType;
				return;
			}
			if (pValueType->m_ePointerType != TypeRef::PointerType::OWNED && m_pAssignment->m_pValueType->m_ePointerType == TypeRef::PointerType::OWNED_PREASSSIGN)
			{
				pValidator->AddError("Can't assign an owned pointer to a non-owned variable", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
				return;
			}
			if (pValueType->m_ePointerType == TypeRef::PointerType::OWNED && (m_pAssignment->m_pValueType->m_ePointerType != TypeRef::PointerType::OWNED_PREASSSIGN && m_pAssignment->m_pValueType->m_eType != ValueType::Type::NULL_VALUE))
			{
				pValidator->AddError("Expected right side of = to be OWNED_PREASSSIGN (result of own)", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
				if (pValueType) delete pValueType;
				return;
			}
			else
				if (m_pAssignment->m_pValueType->m_ePointerType == TypeRef::PointerType::TRANSITON)
				{
					pValidator->AddError("Cannot store a TRANSITION pointer (need to `own` it)", m_pAssignment->m_pFirstToken->m_sFileName, m_pAssignment->m_pFirstToken->m_nLine, m_pAssignment->m_pFirstToken->m_nColumn);
					if (pValueType) delete pValueType;
					return;
				}
		}
		if (pValueType) delete pValueType;
	}

	void VarDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		Util::Pad(nDepth, sOut);
		if (eLanguage == AST::Language::CS)
		{
			if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_PARAM_DECL)
			{
				bool bBefore = m_pTypeRef->m_bConst;
				m_pTypeRef->m_bConst = false;
				m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, sOut);
				m_pTypeRef->m_bConst = bBefore;
			}
			else
			{
				bool bBefore = m_pTypeRef->m_bConst;
				if (m_pArraySize != 0 && bBefore)
				{
					m_pTypeRef->m_bConst = false;
					sOut->Append("readonly ");
				}
				m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, sOut);
				m_pTypeRef->m_bConst = bBefore;
			}
			if (m_pArraySize != 0)
			{
				sOut->AppendChar('[');
				sOut->AppendChar(']');
			}
		}
		else
		{
			m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, sOut);
		}
		sOut->AppendChar(' ');
		if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL && eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
		{
			AST* pParentParent = m_pParent->m_pParent;
			if (pParentParent == 0 || pParentParent->m_eType != AST::Type::AST_CLASS_DECL)
			{
				NumbatLogic::Assert::Plz(false);
			}
			ClassDecl* pClassDecl = (ClassDecl*)(pParentParent);
			sOut->AppendString(pClassDecl->m_pNameToken->GetString());
			sOut->AppendString("::");
		}
		sOut->AppendString(m_pNameToken->GetString());
		if (m_pArraySize != 0 && eLanguage != AST::Language::CS)
		{
			sOut->AppendChar('[');
			m_pArraySize->Stringify(eLanguage, eOutputFile, 0, sOut);
			sOut->AppendChar(']');
		}
		if (m_pAssignment != 0)
		{
			bool bArrayAssignment = m_pArraySize != 0;
			bool bStatic = m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL && ((MemberVarDecl*)(m_pParent))->m_bStatic;
			bool bDoIt = true;
			if (eLanguage == AST::Language::CPP)
			{
				if (bArrayAssignment && eOutputFile == AST::OutputFile::HEADER)
					bDoIt = false;
				if (bStatic && !m_pTypeRef->IsIntegral() && eOutputFile == AST::OutputFile::HEADER)
					bDoIt = false;
				if (bStatic && m_pTypeRef->IsIntegral() && eOutputFile == AST::OutputFile::SOURCE)
					bDoIt = false;
				if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_PARAM_DECL && eOutputFile == AST::OutputFile::SOURCE)
					bDoIt = false;
			}
			if (bDoIt)
			{
				sOut->AppendString(" = ");
				m_pAssignment->Stringify(eLanguage, eOutputFile, 0, sOut);
			}
		}
		else
		{
			if (!m_bInline && eLanguage == AST::Language::CPP)
			{
				ValueType* pValueType = m_pTypeRef->CreateValueType();
				if (pValueType != 0 && pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE && m_pArraySize == 0 && eOutputFile == AST::OutputFile::SOURCE)
					sOut->AppendString(" = 0");
				if (pValueType) delete pValueType;
			}
			if (!m_bInline && eLanguage == AST::Language::CS && m_pArraySize != 0)
			{
				sOut->AppendString(" = new ");
				m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, sOut);
				sOut->AppendChar('[');
				m_pArraySize->Stringify(eLanguage, eOutputFile, 0, sOut);
				sOut->AppendChar(']');
			}
		}
		if (!m_bInline)
			sOut->AppendString(";\n");
	}

	VarDecl::~VarDecl()
	{
		if (m_pOwnedNameToken) delete m_pOwnedNameToken;
	}

}

