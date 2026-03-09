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
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "MemberFunctionDecl.hpp"
#include "ClassDecl.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "../../../../LangShared/ExternalString/CPP/ExternalString.hpp"
#include "../OutputBuilder.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class TypeRef;
	class Token;
	class TokenContainer;
	class ParamDecl;
	class Console;
	class Assert;
	class Scope;
	class FunctionDecl;
	class Validator;
	class ValueType;
	class MemberFunctionDecl;
	template <class T>
	class OwnedVector;
	class ExternalString;
	class OutputBuilder;
	class InternalString;
	class ClassDecl;
}
#line 1 "../../../Source/Core/AST/FunctionDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/FunctionDecl.nll"
#line 13 "../../../Source/Core/AST/FunctionDecl.nll"
	FunctionDecl* FunctionDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, AST* pParent)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		TypeRef* pTypeRef = TypeRef::TryCreate(pTokenContainer, pTempOffset);
#line 18 "../../../Source/Core/AST/FunctionDecl.nll"
		if (pTypeRef == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
#line 19 "../../../Source/Core/AST/FunctionDecl.nll"
			return 0;
		}
		Token* pNameToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
#line 22 "../../../Source/Core/AST/FunctionDecl.nll"
		if (pNameToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
#line 23 "../../../Source/Core/AST/FunctionDecl.nll"
			return 0;
		}
#line 24 "../../../Source/Core/AST/FunctionDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 26 "../../../Source/Core/AST/FunctionDecl.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT) == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
#line 27 "../../../Source/Core/AST/FunctionDecl.nll"
			return 0;
		}
		ParamDecl* pParamDecl = ParamDecl::TryCreate(pTokenContainer, pTempOffset);
#line 30 "../../../Source/Core/AST/FunctionDecl.nll"
		if (pParamDecl == 0)
		{
#line 32 "../../../Source/Core/AST/FunctionDecl.nll"
			Console::Log("expected ParamDecl");
#line 33 "../../../Source/Core/AST/FunctionDecl.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 34 "../../../Source/Core/AST/FunctionDecl.nll"
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
			if (pParamDecl) delete pParamDecl;
#line 35 "../../../Source/Core/AST/FunctionDecl.nll"
			return 0;
		}
		bool bConst = false;
		Token* pConst = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_CONST);
#line 40 "../../../Source/Core/AST/FunctionDecl.nll"
		if (pConst != 0)
		{
#line 42 "../../../Source/Core/AST/FunctionDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 43 "../../../Source/Core/AST/FunctionDecl.nll"
			bConst = true;
		}
		Scope* pScope = 0;
		Token* pSemicolon = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON);
#line 48 "../../../Source/Core/AST/FunctionDecl.nll"
		if (pSemicolon != 0)
#line 49 "../../../Source/Core/AST/FunctionDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		else
		{
#line 52 "../../../Source/Core/AST/FunctionDecl.nll"
			pScope = Scope::TryCreate(pTokenContainer, pTempOffset, false);
#line 53 "../../../Source/Core/AST/FunctionDecl.nll"
			if (pScope == 0)
			{
#line 55 "../../../Source/Core/AST/FunctionDecl.nll"
				Console::Log("expected scope");
#line 56 "../../../Source/Core/AST/FunctionDecl.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 57 "../../../Source/Core/AST/FunctionDecl.nll"
				Assert::Plz(false);
			}
		}
		FunctionDecl* pFunctionDecl = new FunctionDecl();
#line 64 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->m_eType = AST::Type::AST_FUNCTION_DECL;
#line 65 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->m_pParent = pParent;
#line 66 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->m_pFirstToken = pTypeRef->m_pFirstToken;
#line 67 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->m_pTypeRef = pTypeRef;
#line 68 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->m_pNameToken = pNameToken;
#line 69 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->m_sMangledName = pNameToken->GetString();
#line 70 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->m_pParamDecl = pParamDecl;
#line 71 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->m_bConst = bConst;
#line 72 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->m_pScope = pScope;
		NumbatLogic::TypeRef* __2942767685 = pTypeRef;
#line 74 "../../../Source/Core/AST/FunctionDecl.nll"
		pTypeRef = 0;
#line 74 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->AddChild(__2942767685);
		NumbatLogic::ParamDecl* __3702925988 = pParamDecl;
#line 75 "../../../Source/Core/AST/FunctionDecl.nll"
		pParamDecl = 0;
#line 75 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->AddChild(__3702925988);
#line 77 "../../../Source/Core/AST/FunctionDecl.nll"
		if (pScope != 0)
		{
			NumbatLogic::Scope* __1530815332 = pScope;
#line 78 "../../../Source/Core/AST/FunctionDecl.nll"
			pScope = 0;
#line 78 "../../../Source/Core/AST/FunctionDecl.nll"
			pFunctionDecl->AddChild(__1530815332);
		}
#line 80 "../../../Source/Core/AST/FunctionDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::FunctionDecl* __4280092330 = pFunctionDecl;
#line 81 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pTypeRef) delete pTypeRef;
		if (pParamDecl) delete pParamDecl;
		if (pScope) delete pScope;
#line 81 "../../../Source/Core/AST/FunctionDecl.nll"
		return __4280092330;
	}

#line 84 "../../../Source/Core/AST/FunctionDecl.nll"
	void FunctionDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 86 "../../../Source/Core/AST/FunctionDecl.nll"
		AST::Validate(pValidator, pParent);
#line 88 "../../../Source/Core/AST/FunctionDecl.nll"
		if (m_pTypeRef->m_pTypeToken->m_eType == Token::Type::TOKEN_IDENTIFIER)
		{
#line 90 "../../../Source/Core/AST/FunctionDecl.nll"
			if (m_pTypeRef->m_ePointerType == TypeRef::PointerType::OWNED)
			{
#line 92 "../../../Source/Core/AST/FunctionDecl.nll"
				pValidator->AddError("Return value cannot be a owned pointer!", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
#line 93 "../../../Source/Core/AST/FunctionDecl.nll"
				return;
			}
		}
		ValueType* pValueType = m_pTypeRef->CreateValueType(pValidator->m_pResolver);
#line 99 "../../../Source/Core/AST/FunctionDecl.nll"
		if (pValueType == 0)
		{
#line 101 "../../../Source/Core/AST/FunctionDecl.nll"
			pValidator->AddError("Unable to compute value type of function result", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			if (pValueType) delete pValueType;
#line 102 "../../../Source/Core/AST/FunctionDecl.nll"
			return;
		}
#line 105 "../../../Source/Core/AST/FunctionDecl.nll"
		if (pValueType->m_pClassDecl != 0)
#line 106 "../../../Source/Core/AST/FunctionDecl.nll"
			AddClassDeclReference(pValueType->m_pClassDecl, AST::OutputFile::HEADER, true);
		if (pValueType) delete pValueType;
	}

#line 109 "../../../Source/Core/AST/FunctionDecl.nll"
	void FunctionDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		MemberFunctionDecl* pMemberFunctionDecl = 0;
#line 112 "../../../Source/Core/AST/FunctionDecl.nll"
		if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
#line 113 "../../../Source/Core/AST/FunctionDecl.nll"
			pMemberFunctionDecl = (MemberFunctionDecl*)(m_pParent);
		bool bGeneric = pMemberFunctionDecl != 0 && pMemberFunctionDecl->m_pParentClassDecl->m_pGenericTypeDeclVector->GetSize() > 0;
#line 117 "../../../Source/Core/AST/FunctionDecl.nll"
		if (pMemberFunctionDecl != 0 && eLanguage == AST::Language::CS && ExternalString::Equal("GetType", m_pNameToken->GetString()))
		{
#line 120 "../../../Source/Core/AST/FunctionDecl.nll"
			pOutputBuilder->m_sOut->Append("new ");
		}
#line 123 "../../../Source/Core/AST/FunctionDecl.nll"
		m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 125 "../../../Source/Core/AST/FunctionDecl.nll"
		pOutputBuilder->m_sOut->AppendChar(' ');
#line 127 "../../../Source/Core/AST/FunctionDecl.nll"
		if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
		{
#line 129 "../../../Source/Core/AST/FunctionDecl.nll"
			if (pMemberFunctionDecl != 0)
			{
				AST* pPrefixParent = pMemberFunctionDecl;
				InternalString* sPrefix = new InternalString("");
				InternalString* sTemp = new InternalString("");
#line 135 "../../../Source/Core/AST/FunctionDecl.nll"
				while (pPrefixParent->m_pParent != 0)
				{
#line 137 "../../../Source/Core/AST/FunctionDecl.nll"
					if (pPrefixParent->m_eType == AST::Type::AST_CLASS_DECL)
					{
#line 139 "../../../Source/Core/AST/FunctionDecl.nll"
						sTemp->Set(sPrefix->GetExternalString());
#line 140 "../../../Source/Core/AST/FunctionDecl.nll"
						sPrefix->Set("");
#line 141 "../../../Source/Core/AST/FunctionDecl.nll"
						((ClassDecl*)(pPrefixParent))->m_pNameToken->Stringify(sPrefix);
#line 142 "../../../Source/Core/AST/FunctionDecl.nll"
						sPrefix->Append("::");
#line 143 "../../../Source/Core/AST/FunctionDecl.nll"
						sPrefix->Append(sTemp->GetExternalString());
					}
#line 146 "../../../Source/Core/AST/FunctionDecl.nll"
					pPrefixParent = pPrefixParent->m_pParent;
				}
#line 150 "../../../Source/Core/AST/FunctionDecl.nll"
				pOutputBuilder->m_sOut->Append(sPrefix->GetExternalString());
				if (sPrefix) delete sPrefix;
				if (sTemp) delete sTemp;
			}
		}
#line 154 "../../../Source/Core/AST/FunctionDecl.nll"
		pOutputBuilder->m_sOut->Append(m_sMangledName);
#line 155 "../../../Source/Core/AST/FunctionDecl.nll"
		m_pParamDecl->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 157 "../../../Source/Core/AST/FunctionDecl.nll"
		if (m_bConst && eLanguage == AST::Language::CPP)
#line 158 "../../../Source/Core/AST/FunctionDecl.nll"
			pOutputBuilder->m_sOut->Append(" const");
#line 161 "../../../Source/Core/AST/FunctionDecl.nll"
		if ((eOutputFile == AST::OutputFile::HEADER && !bGeneric) || eLanguage == AST::Language::NLL_DEF)
		{
#line 163 "../../../Source/Core/AST/FunctionDecl.nll"
			pOutputBuilder->m_sOut->Append(";\n");
#line 164 "../../../Source/Core/AST/FunctionDecl.nll"
			return;
		}
#line 167 "../../../Source/Core/AST/FunctionDecl.nll"
		if (m_pScope == 0)
		{
#line 169 "../../../Source/Core/AST/FunctionDecl.nll"
			pOutputBuilder->m_sOut->Append(";\n");
		}
		else
		{
#line 173 "../../../Source/Core/AST/FunctionDecl.nll"
			pOutputBuilder->m_sOut->AppendChar('\n');
#line 174 "../../../Source/Core/AST/FunctionDecl.nll"
			m_pScope->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 175 "../../../Source/Core/AST/FunctionDecl.nll"
			pOutputBuilder->m_sOut->AppendChar('\n');
		}
	}

#line 4 "../../../Source/Core/AST/FunctionDecl.nll"
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

