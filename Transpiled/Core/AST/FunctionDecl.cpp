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
#line 0 "../../../Source/Core/AST/FunctionDecl.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/FunctionDecl.nll"
#line 12 "../../../Source/Core/AST/FunctionDecl.nll"
	FunctionDecl* FunctionDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, AST* pParent)
	{
#line 14 "../../../Source/Core/AST/FunctionDecl.nll"
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 16 "../../../Source/Core/AST/FunctionDecl.nll"
		TypeRef* pTypeRef = TypeRef::TryCreate(pTokenContainer, pTempOffset);
#line 17 "../../../Source/Core/AST/FunctionDecl.nll"
		if (pTypeRef == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
#line 18 "../../../Source/Core/AST/FunctionDecl.nll"
			return 0;
		}
#line 20 "../../../Source/Core/AST/FunctionDecl.nll"
		Token* pNameToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
#line 21 "../../../Source/Core/AST/FunctionDecl.nll"
		if (pNameToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
#line 22 "../../../Source/Core/AST/FunctionDecl.nll"
			return 0;
		}
#line 23 "../../../Source/Core/AST/FunctionDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 25 "../../../Source/Core/AST/FunctionDecl.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT) == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
#line 26 "../../../Source/Core/AST/FunctionDecl.nll"
			return 0;
		}
#line 28 "../../../Source/Core/AST/FunctionDecl.nll"
		ParamDecl* pParamDecl = ParamDecl::TryCreate(pTokenContainer, pTempOffset);
#line 29 "../../../Source/Core/AST/FunctionDecl.nll"
		if (pParamDecl == 0)
		{
#line 31 "../../../Source/Core/AST/FunctionDecl.nll"
			Console::Log("expected ParamDecl");
#line 32 "../../../Source/Core/AST/FunctionDecl.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 33 "../../../Source/Core/AST/FunctionDecl.nll"
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
			if (pParamDecl) delete pParamDecl;
#line 34 "../../../Source/Core/AST/FunctionDecl.nll"
			return 0;
		}
#line 37 "../../../Source/Core/AST/FunctionDecl.nll"
		bool bConst = false;
#line 38 "../../../Source/Core/AST/FunctionDecl.nll"
		Token* pConst = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_CONST);
#line 39 "../../../Source/Core/AST/FunctionDecl.nll"
		if (pConst != 0)
		{
#line 41 "../../../Source/Core/AST/FunctionDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 42 "../../../Source/Core/AST/FunctionDecl.nll"
			bConst = true;
		}
#line 45 "../../../Source/Core/AST/FunctionDecl.nll"
		Scope* pScope = 0;
#line 46 "../../../Source/Core/AST/FunctionDecl.nll"
		Token* pSemicolon = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_SEMICOLON);
#line 47 "../../../Source/Core/AST/FunctionDecl.nll"
		if (pSemicolon != 0)
#line 48 "../../../Source/Core/AST/FunctionDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		else
		{
#line 51 "../../../Source/Core/AST/FunctionDecl.nll"
			pScope = Scope::TryCreate(pTokenContainer, pTempOffset, false);
#line 52 "../../../Source/Core/AST/FunctionDecl.nll"
			if (pScope == 0)
			{
#line 54 "../../../Source/Core/AST/FunctionDecl.nll"
				Console::Log("expected scope");
#line 55 "../../../Source/Core/AST/FunctionDecl.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 56 "../../../Source/Core/AST/FunctionDecl.nll"
				Assert::Plz(false);
			}
		}
#line 61 "../../../Source/Core/AST/FunctionDecl.nll"
		FunctionDecl* pFunctionDecl = new FunctionDecl();
#line 63 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->m_eType = AST::Type::AST_FUNCTION_DECL;
#line 64 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->m_pParent = pParent;
#line 65 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->m_pFirstToken = pTypeRef->m_pFirstToken;
#line 66 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->m_pTypeRef = pTypeRef;
#line 67 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->m_pNameToken = pNameToken;
#line 68 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->m_sMangledName = pNameToken->GetString();
#line 69 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->m_pParamDecl = pParamDecl;
#line 70 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->m_bConst = bConst;
#line 71 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->m_pScope = pScope;
		NumbatLogic::TypeRef* __2942767685 = pTypeRef;
#line 73 "../../../Source/Core/AST/FunctionDecl.nll"
		pTypeRef = 0;
#line 73 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->AddChild(__2942767685);
		NumbatLogic::ParamDecl* __3702925988 = pParamDecl;
#line 74 "../../../Source/Core/AST/FunctionDecl.nll"
		pParamDecl = 0;
#line 74 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->AddChild(__3702925988);
#line 76 "../../../Source/Core/AST/FunctionDecl.nll"
		if (pScope != 0)
		{
			NumbatLogic::Scope* __1530815332 = pScope;
#line 77 "../../../Source/Core/AST/FunctionDecl.nll"
			pScope = 0;
#line 77 "../../../Source/Core/AST/FunctionDecl.nll"
			pFunctionDecl->AddChild(__1530815332);
		}
#line 79 "../../../Source/Core/AST/FunctionDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::FunctionDecl* __4280092330 = pFunctionDecl;
#line 80 "../../../Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pTypeRef) delete pTypeRef;
		if (pParamDecl) delete pParamDecl;
		if (pScope) delete pScope;
#line 80 "../../../Source/Core/AST/FunctionDecl.nll"
		return __4280092330;
	}

#line 83 "../../../Source/Core/AST/FunctionDecl.nll"
	void FunctionDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 85 "../../../Source/Core/AST/FunctionDecl.nll"
		AST::Validate(pValidator, pParent);
#line 87 "../../../Source/Core/AST/FunctionDecl.nll"
		if (m_pTypeRef->m_pTypeToken->m_eType == Token::Type::TOKEN_IDENTIFIER)
		{
#line 89 "../../../Source/Core/AST/FunctionDecl.nll"
			if (m_pTypeRef->m_ePointerType == TypeRef::PointerType::OWNED)
			{
#line 91 "../../../Source/Core/AST/FunctionDecl.nll"
				pValidator->AddError("Return value cannot be a owned pointer!", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
#line 92 "../../../Source/Core/AST/FunctionDecl.nll"
				return;
			}
		}
#line 97 "../../../Source/Core/AST/FunctionDecl.nll"
		ValueType* pValueType = m_pTypeRef->CreateValueType(pValidator->m_pResolver);
#line 98 "../../../Source/Core/AST/FunctionDecl.nll"
		if (pValueType == 0)
		{
#line 100 "../../../Source/Core/AST/FunctionDecl.nll"
			pValidator->AddError("Unable to compute value type of function result", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			if (pValueType) delete pValueType;
#line 101 "../../../Source/Core/AST/FunctionDecl.nll"
			return;
		}
#line 104 "../../../Source/Core/AST/FunctionDecl.nll"
		if (pValueType->m_pClassDecl != 0)
#line 105 "../../../Source/Core/AST/FunctionDecl.nll"
			AddClassDeclReference(pValueType->m_pClassDecl, AST::OutputFile::HEADER, true);
		if (pValueType) delete pValueType;
	}

#line 108 "../../../Source/Core/AST/FunctionDecl.nll"
	void FunctionDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 110 "../../../Source/Core/AST/FunctionDecl.nll"
		MemberFunctionDecl* pMemberFunctionDecl = 0;
#line 111 "../../../Source/Core/AST/FunctionDecl.nll"
		if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
#line 112 "../../../Source/Core/AST/FunctionDecl.nll"
			pMemberFunctionDecl = (MemberFunctionDecl*)(m_pParent);
#line 114 "../../../Source/Core/AST/FunctionDecl.nll"
		bool bGeneric = pMemberFunctionDecl != 0 && pMemberFunctionDecl->m_pParentClassDecl->m_pGenericTypeDeclVector->GetSize() > 0;
#line 116 "../../../Source/Core/AST/FunctionDecl.nll"
		if (pMemberFunctionDecl != 0 && eLanguage == AST::Language::CS && ExternalString::Equal("GetType", m_pNameToken->GetString()))
		{
#line 119 "../../../Source/Core/AST/FunctionDecl.nll"
			pOutputBuilder->m_sOut->Append("new ");
		}
#line 122 "../../../Source/Core/AST/FunctionDecl.nll"
		m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 124 "../../../Source/Core/AST/FunctionDecl.nll"
		pOutputBuilder->m_sOut->AppendChar(' ');
#line 126 "../../../Source/Core/AST/FunctionDecl.nll"
		if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
		{
#line 128 "../../../Source/Core/AST/FunctionDecl.nll"
			if (pMemberFunctionDecl != 0)
			{
#line 130 "../../../Source/Core/AST/FunctionDecl.nll"
				AST* pPrefixParent = pMemberFunctionDecl;
#line 131 "../../../Source/Core/AST/FunctionDecl.nll"
				InternalString* sPrefix = new InternalString("");
#line 132 "../../../Source/Core/AST/FunctionDecl.nll"
				InternalString* sTemp = new InternalString("");
#line 134 "../../../Source/Core/AST/FunctionDecl.nll"
				while (pPrefixParent->m_pParent != 0)
				{
#line 136 "../../../Source/Core/AST/FunctionDecl.nll"
					if (pPrefixParent->m_eType == AST::Type::AST_CLASS_DECL)
					{
#line 138 "../../../Source/Core/AST/FunctionDecl.nll"
						sTemp->Set(sPrefix->GetExternalString());
#line 139 "../../../Source/Core/AST/FunctionDecl.nll"
						sPrefix->Set("");
#line 140 "../../../Source/Core/AST/FunctionDecl.nll"
						((ClassDecl*)(pPrefixParent))->m_pNameToken->Stringify(sPrefix);
#line 141 "../../../Source/Core/AST/FunctionDecl.nll"
						sPrefix->Append("::");
#line 142 "../../../Source/Core/AST/FunctionDecl.nll"
						sPrefix->Append(sTemp->GetExternalString());
					}
#line 145 "../../../Source/Core/AST/FunctionDecl.nll"
					pPrefixParent = pPrefixParent->m_pParent;
				}
#line 149 "../../../Source/Core/AST/FunctionDecl.nll"
				pOutputBuilder->m_sOut->Append(sPrefix->GetExternalString());
				if (sPrefix) delete sPrefix;
				if (sTemp) delete sTemp;
			}
		}
#line 153 "../../../Source/Core/AST/FunctionDecl.nll"
		pOutputBuilder->m_sOut->Append(m_sMangledName);
#line 154 "../../../Source/Core/AST/FunctionDecl.nll"
		m_pParamDecl->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 156 "../../../Source/Core/AST/FunctionDecl.nll"
		if (m_bConst && eLanguage == AST::Language::CPP)
#line 157 "../../../Source/Core/AST/FunctionDecl.nll"
			pOutputBuilder->m_sOut->Append(" const");
#line 160 "../../../Source/Core/AST/FunctionDecl.nll"
		if ((eOutputFile == AST::OutputFile::HEADER && !bGeneric) || eLanguage == AST::Language::NLL_DEF)
		{
#line 162 "../../../Source/Core/AST/FunctionDecl.nll"
			pOutputBuilder->m_sOut->Append(";\n");
#line 163 "../../../Source/Core/AST/FunctionDecl.nll"
			return;
		}
#line 166 "../../../Source/Core/AST/FunctionDecl.nll"
		if (m_pScope == 0)
		{
#line 168 "../../../Source/Core/AST/FunctionDecl.nll"
			pOutputBuilder->m_sOut->Append(";\n");
		}
		else
		{
#line 172 "../../../Source/Core/AST/FunctionDecl.nll"
			pOutputBuilder->m_sOut->AppendChar('\n');
#line 173 "../../../Source/Core/AST/FunctionDecl.nll"
			m_pScope->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 174 "../../../Source/Core/AST/FunctionDecl.nll"
			pOutputBuilder->m_sOut->AppendChar('\n');
		}
	}

#line 3 "../../../Source/Core/AST/FunctionDecl.nll"
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

