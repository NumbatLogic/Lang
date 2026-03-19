#include "FunctionDecl.hpp"
#include "DecoratorCall.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../OffsetDatum.hpp"
#include "TypeRef.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "ParamDecl.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "Scope.hpp"
#include "AST.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "ClassDecl.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "MemberFunctionDecl.hpp"
#include "../../../../LangShared/ExternalString/CPP/ExternalString.hpp"
#include "../OutputBuilder.hpp"

namespace NumbatLogic
{
	class AST;
	class DecoratorCall;
	template <class T>
	class Vector;
	class OffsetDatum;
	class TypeRef;
	template <class T>
	class OwnedVector;
	class Token;
	class TokenContainer;
	class ParamDecl;
	class Console;
	class Assert;
	class Scope;
	class FunctionDecl;
	class Validator;
	class ValueType;
	class ClassDecl;
	class MemberFunctionDecl;
	class ExternalString;
	class OutputBuilder;
	class InternalString;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
#line 13 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
	FunctionDecl::FunctionDecl()
	{
		m_pTypeRef = 0;
		m_pNameToken = 0;
		m_sMangledName = 0;
		m_pParamDecl = 0;
		m_bConst = false;
		m_pScope = 0;
		m_pDecoratorCallVector = 0;
#line 15 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		m_pDecoratorCallVector = new Vector<DecoratorCall*>();
	}

	FunctionDecl* FunctionDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, AST* pParent)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		TypeRef* pTypeRef = TypeRef::TryCreate(pTokenContainer, pTempOffset);
		if (pTypeRef == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
#line 24 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			return 0;
		}
		OwnedVector<DecoratorCall*>* pOwnedDecoratorCallVector = new OwnedVector<DecoratorCall*>();
		while (true)
		{
			DecoratorCall* pDecoratorCall = DecoratorCall::TryCreate(pTokenContainer, pTempOffset);
			if (pDecoratorCall == 0)
			{
				if (pDecoratorCall) delete pDecoratorCall;
#line 31 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
				break;
			}
			NumbatLogic::DecoratorCall* __1592839561 = pDecoratorCall;
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			pDecoratorCall = 0;
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			pOwnedDecoratorCallVector->PushBack(__1592839561);
			if (pDecoratorCall) delete pDecoratorCall;
		}
		Token* pNameToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
		if (pNameToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
			if (pOwnedDecoratorCallVector) delete pOwnedDecoratorCallVector;
#line 38 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			return 0;
		}
#line 39 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 41 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT) == 0)
		{
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
			if (pOwnedDecoratorCallVector) delete pOwnedDecoratorCallVector;
#line 42 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			return 0;
		}
		ParamDecl* pParamDecl = ParamDecl::TryCreate(pTokenContainer, pTempOffset);
		if (pParamDecl == 0)
		{
			Console::Log("expected ParamDecl");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pTypeRef) delete pTypeRef;
			if (pOwnedDecoratorCallVector) delete pOwnedDecoratorCallVector;
			if (pParamDecl) delete pParamDecl;
#line 50 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			return 0;
		}
#line 53 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		bool bConst = false;
		Token* pConst = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_CONST);
		if (pConst != 0)
		{
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			bConst = true;
		}
#line 61 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
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
				Assert::Plz(false);
			}
		}
#line 76 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
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
		NumbatLogic::TypeRef* __2942833288 = pTypeRef;
		pTypeRef = 0;
#line 87 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->AddChild(__2942833288);
		NumbatLogic::ParamDecl* __3702991591 = pParamDecl;
#line 88 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		pParamDecl = 0;
#line 88 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl->AddChild(__3702991591);
#line 90 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		while (pOwnedDecoratorCallVector->GetSize() > 0)
		{
			DecoratorCall* pDecoratorCall = pOwnedDecoratorCallVector->PopFront();
			pDecoratorCall->m_pParent = pFunctionDecl;
			DecoratorCall* pTemp = pDecoratorCall;
			pFunctionDecl->m_pDecoratorCallVector->PushBack(pTemp);
			NumbatLogic::DecoratorCall* __1593233158 = pDecoratorCall;
#line 96 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			pDecoratorCall = 0;
#line 96 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			pFunctionDecl->AddChild(__1593233158);
			if (pDecoratorCall) delete pDecoratorCall;
		}
		if (pScope != 0)
		{
			NumbatLogic::Scope* __3569555213 = pScope;
#line 100 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			pScope = 0;
#line 100 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			pFunctionDecl->AddChild(__3569555213);
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::FunctionDecl* __3411818370 = pFunctionDecl;
#line 103 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		pFunctionDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pTypeRef) delete pTypeRef;
		if (pOwnedDecoratorCallVector) delete pOwnedDecoratorCallVector;
		if (pParamDecl) delete pParamDecl;
		if (pScope) delete pScope;
#line 103 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		return __3411818370;
	}

	void FunctionDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AST::Validate(pValidator, pParent);
#line 110 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		if (m_pTypeRef->m_pTypeToken->m_eType == Token::Type::TOKEN_IDENTIFIER)
		{
			if (m_pTypeRef->m_ePointerType == TypeRef::PointerType::OWNED)
			{
				pValidator->AddError("Return value cannot be a owned pointer!", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				return;
			}
		}
#line 120 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		ValueType* pValueType = m_pTypeRef->CreateValueType(pValidator->m_pResolver);
		if (pValueType == 0)
		{
			pValidator->AddError("Unable to compute value type of function result", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			if (pValueType) delete pValueType;
#line 124 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			return;
		}
#line 127 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		if (pValueType->m_pClassDecl != 0)
			AddClassDeclReference(pValueType->m_pClassDecl, AST::OutputFile::HEADER, true);
		if (pValueType) delete pValueType;
	}

#line 131 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
	void FunctionDecl::AppendFullyQualifiedName(Language eLanguage, InternalString* sOut)
	{
		const char* sxSeparator = "::";
		if (eLanguage == AST::Language::CS)
			sxSeparator = ".";
#line 137 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		AST* pParent = m_pParent;
		while (pParent != 0)
		{
			if (pParent->m_eType == AST::Type::AST_CLASS_DECL)
			{
				ClassDecl* pClassDecl = (ClassDecl*)(pParent);
				pClassDecl->AppendFullyQualifiedName(eLanguage, sOut);
				sOut->Append(sxSeparator);
				break;
			}
			pParent = pParent->m_pParent;
		}
#line 150 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		sOut->Append(m_sMangledName);
	}

	void FunctionDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		MemberFunctionDecl* pMemberFunctionDecl = 0;
		if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
			pMemberFunctionDecl = (MemberFunctionDecl*)(m_pParent);
#line 159 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		bool bGeneric = pMemberFunctionDecl != 0 && pMemberFunctionDecl->m_pParentClassDecl->m_pGenericTypeDeclVector->GetSize() > 0;
#line 161 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		if (pMemberFunctionDecl != 0 && eLanguage == AST::Language::CS && ExternalString::Equal("GetType", m_pNameToken->GetString()))
		{
#line 164 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
			pOutputBuilder->m_sOut->Append("new ");
		}
#line 167 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		m_pTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		pOutputBuilder->m_sOut->AppendChar(' ');
#line 170 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		if (eLanguage == AST::Language::NLL && m_pDecoratorCallVector != 0 && m_pDecoratorCallVector->GetSize() > 0)
		{
			for (int i = 0; i < m_pDecoratorCallVector->GetSize(); i++)
			{
				DecoratorCall* pDecoratorCall = m_pDecoratorCallVector->Get(i);
				pDecoratorCall->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
			pOutputBuilder->m_sOut->AppendChar(' ');
		}
#line 181 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		if (eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE)
		{
			if (pMemberFunctionDecl != 0)
			{
				AST* pPrefixParent = pMemberFunctionDecl;
				InternalString* sPrefix = new InternalString("");
				InternalString* sTemp = new InternalString("");
				while (pPrefixParent->m_pParent != 0)
				{
					if (pPrefixParent->m_eType == AST::Type::AST_CLASS_DECL)
					{
						sTemp->Set(sPrefix->GetExternalString());
						sPrefix->Set("");
						((ClassDecl*)(pPrefixParent))->m_pNameToken->Stringify(sPrefix);
						sPrefix->Append("::");
						sPrefix->Append(sTemp->GetExternalString());
					}
#line 199 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
					pPrefixParent = pPrefixParent->m_pParent;
				}
#line 202 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
				pOutputBuilder->m_sOut->Append(sPrefix->GetExternalString());
				if (sPrefix) delete sPrefix;
				if (sTemp) delete sTemp;
			}
		}
#line 206 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		pOutputBuilder->m_sOut->Append(m_sMangledName);
		m_pParamDecl->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 209 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		if (m_bConst && eLanguage == AST::Language::CPP)
			pOutputBuilder->m_sOut->Append(" const");
#line 213 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		if ((eOutputFile == AST::OutputFile::HEADER && !bGeneric) || eLanguage == AST::Language::NLL_DEF)
		{
			pOutputBuilder->m_sOut->Append(";\n");
			return;
		}
#line 219 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
		if (m_pScope == 0)
		{
			pOutputBuilder->m_sOut->Append(";\n");
		}
		else
		{
			pOutputBuilder->m_sOut->AppendChar('\n');
			m_pScope->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
			pOutputBuilder->m_sOut->AppendChar('\n');
		}
	}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/FunctionDecl.nll"
	FunctionDecl::~FunctionDecl()
	{
		if (m_pDecoratorCallVector) delete m_pDecoratorCallVector;
	}

}

