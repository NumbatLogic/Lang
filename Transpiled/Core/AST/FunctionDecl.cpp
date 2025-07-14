#include "FunctionDecl.hpp"
#include "../OffsetDatum.hpp"
#include "TypeRef.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "ParamDecl.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "Scope.hpp"
#include "AST.hpp"
#include "../../../../LangShared/ExternalString/CPP/ExternalString.hpp"
#include "../Validator.hpp"
#include "MemberFunctionDecl.hpp"
#include "ClassDecl.hpp"
#include "../../LangShared/Vector/OwnedVector.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class FunctionDecl;
	class OffsetDatum;
	class OffsetDatum;
	class TypeRef;
	class TypeRef;
	class Token;
	class TokenContainer;
	class Token;
	class ParamDecl;
	class ParamDecl;
	class Console;
	class Assert;
	class Scope;
	class Scope;
	class FunctionDecl;
	class AST;
	class ExternalString;
	class Validator;
	class MemberFunctionDecl;
	class MemberFunctionDecl;
	class ClassDecl;
	template <class T>
	class OwnedVector;
	class InternalString;
}
namespace NumbatLogic
{
	FunctionDecl* FunctionDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, AST* pParent)
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
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT) == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
			return 0;
		}
		ParamDecl* pParamDecl = ParamDecl::TryCreate(pTokenContainer, pTempOffset);
		if (pParamDecl == 0)
		{
			Console::Log("expected ParamDecl");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
			if (pParamDecl) delete pParamDecl;
			return 0;
		}
		bool bConst = false;
		Token* pConst = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_CONST);
		if (pConst != 0)
		{
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			bConst = true;
		}
		Scope* pScope = 0;
		Token* pSemicolon = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON);
		if (pSemicolon != 0)
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		else
		{
			pScope = Scope::TryCreate(pTokenContainer, pTempOffset, false);
			if (pScope == 0)
			{
				Console::Log("expected scope");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
			}
		}
		FunctionDecl* pFunctionDecl = new FunctionDecl();
		pFunctionDecl->m_eType = AST::Type::AST_FUNCTION_DECL;
		pFunctionDecl->m_pParent = pParent;
		pFunctionDecl->m_pFirstToken = pTypeRef->m_pFirstToken;
		pFunctionDecl->m_pTypeRef = pTypeRef;
		pFunctionDecl->m_pNameToken = pNameToken;
		pFunctionDecl->m_sMangledName = pNameToken->GetString();
		pFunctionDecl->m_pParamDecl = pParamDecl;
		pFunctionDecl->m_bConst = bConst;
		pFunctionDecl->m_pScope = pScope;
		NumbatLogic::TypeRef* __3049869076 = pTypeRef;
		pTypeRef = 0;
		pFunctionDecl->AddChild(__3049869076);
		NumbatLogic::ParamDecl* __759239250 = pParamDecl;
		pParamDecl = 0;
		pFunctionDecl->AddChild(__759239250);
		if (pScope != 0)
		{
			NumbatLogic::Scope* __371996354 = pScope;
			pScope = 0;
			pFunctionDecl->AddChild(__371996354);
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::FunctionDecl* __3436580640 = pFunctionDecl;
		pFunctionDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pTypeRef) delete pTypeRef;
		if (pParamDecl) delete pParamDecl;
		if (pScope) delete pScope;
		return __3436580640;
	}

	AST* FunctionDecl::FindByName(const char* sxName, AST* pCallingChild)
	{
		if (ExternalString::Equal(sxName, m_pNameToken->GetString()))
			return this;
		return AST::FindByName(sxName, pCallingChild);
	}

	void FunctionDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
		if (m_pTypeRef->m_pTypeToken->m_eType == Token::Type::TOKEN_IDENTIFIER)
		{
			if (m_pTypeRef->m_ePointerType == TypeRef::PointerType::OWNED)
			{
				pValidator->AddError("Return value cannot be a owned pointer!", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				return;
			}
		}
	}

	void FunctionDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		MemberFunctionDecl* pMemberFunctionDecl = 0;
		if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
			pMemberFunctionDecl = (MemberFunctionDecl*)(m_pParent);
		bool bGeneric = pMemberFunctionDecl != 0 && pMemberFunctionDecl->m_pParentClassDecl->m_pGenericTypeDeclVector->GetSize() > 0;
		if (bGeneric && eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
			return;
		if (pMemberFunctionDecl != 0 && eLanguage == AST::Language::CS && ExternalString::Equal("GetType", m_pNameToken->GetString()))
		{
			sOut->Append("new ");
		}
		m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, sOut);
		sOut->AppendChar(' ');
		if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
		{
			if (pMemberFunctionDecl != 0)
			{
				pMemberFunctionDecl->m_pParentClassDecl->m_pNameToken->Stringify(sOut);
				sOut->Append("::");
			}
		}
		sOut->Append(m_sMangledName);
		m_pParamDecl->Stringify(eLanguage, eOutputFile, 0, sOut);
		if (m_bConst && eLanguage == AST::Language::CPP)
			sOut->Append(" const");
		if ((eOutputFile == AST::OutputFile::HEADER && !bGeneric) || eLanguage == AST::Language::NLL_DEF)
		{
			sOut->Append(";\n");
			return;
		}
		if (m_pScope == 0)
		{
			sOut->Append(";\n");
		}
		else
		{
			sOut->AppendChar('\n');
			m_pScope->Stringify(eLanguage, eOutputFile, nDepth, sOut);
			sOut->AppendChar('\n');
		}
	}

	FunctionDecl::FunctionDecl()
	{
		m_pTypeRef = 0;
		m_pNameToken = 0;
		m_sMangledName = 0;
		m_pParamDecl = 0;
		m_bConst = false;
		m_pScope = 0;
	}

}

