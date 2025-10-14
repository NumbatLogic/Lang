#include "ClassDecl.hpp"
#include "AST.hpp"
#include "GenericTypeDecl.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "TypeRef.hpp"
#include "MemberVarDecl.hpp"
#include "MemberFunctionDecl.hpp"
#include "MemberClassDecl.hpp"
#include "MemberEnumDecl.hpp"
#include "TorDecl.hpp"
#include "DelegateDecl.hpp"
#include "../Validator.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../ValueType.hpp"
#include "VarDecl.hpp"
#include "Scope.hpp"
#include "MemberVarsSetDefaultStmt.hpp"
#include "AccessLevel.hpp"
#include "ParamDecl.hpp"
#include "../../../../LangShared/ExternalString/CPP/ExternalString.hpp"
#include "../Util.hpp"
#include "../NamespaceNode.hpp"

namespace NumbatLogic
{
	class AST;
	class GenericTypeDecl;
	template <class T>
	class OwnedVector;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class ClassDecl;
	class Console;
	class Assert;
	class TypeRef;
	class MemberFunctionDecl;
	class MemberClassDecl;
	class MemberEnumDecl;
	class DelegateDecl;
	class Validator;
	class ValueType;
	class InternalString;
	class MemberVarDecl;
	class VarDecl;
	class TorDecl;
	class MemberVarsSetDefaultStmt;
	class AccessLevel;
	class ParamDecl;
	class Scope;
	class ExternalString;
	class Util;
	class NamespaceNode;
}
namespace NumbatLogic
{
	ClassDecl::ClassDecl()
	{
		m_pNameToken = 0;
		m_pBaseTypeRef = 0;
		m_pGenericTypeDeclVector = 0;
		m_pNamespaceNode = 0;
		m_pBaseClassDecl = 0;
		m_pAccessLevelToken = 0;
		m_pTypeToken = 0;
		m_pConstructorAccessLevelToken = 0;
		m_pConstructorTypeToken = 0;
		m_eType = AST::Type::AST_CLASS_DECL;
		m_bCanDescend = true;
		m_pGenericTypeDeclVector = new OwnedVector<GenericTypeDecl*>();
		m_pNamespaceNode = 0;
		m_pBaseClassDecl = 0;
	}

	ClassDecl* ClassDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, AST* pParent)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pClassToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_CLASS);
		if (pClassToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		ClassDecl* pClassDecl = new ClassDecl();
		Token* pNameToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
		if (pNameToken == 0)
		{
			Console::Log("expected class name");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pClassDecl) delete pClassDecl;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		Token* pAngleBracketLeft = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_ANGLE_BRACKET_LEFT);
		if (pAngleBracketLeft != 0)
		{
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			while (true)
			{
				if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_ANGLE_BRACKET_RIGHT) != 0)
				{
					pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
					break;
				}
				GenericTypeDecl* pGenericTypeDecl = GenericTypeDecl::TryCreate(pTokenContainer, pTempOffset);
				if (pGenericTypeDecl == 0)
				{
					Console::Log("expected inner GenericTypeDecl");
					NumbatLogic::Assert::Plz(false);
				}
				NumbatLogic::GenericTypeDecl* __3472322917 = pGenericTypeDecl;
				pGenericTypeDecl = 0;
				pClassDecl->m_pGenericTypeDeclVector->PushBack(__3472322917);
				if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_ANGLE_BRACKET_RIGHT) != 0)
				{
					if (pGenericTypeDecl) delete pGenericTypeDecl;
					continue;
				}
				if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COMMA) == 0)
				{
					Console::Log("expected comma");
					Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
					NumbatLogic::Assert::Plz(false);
				}
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				if (pGenericTypeDecl) delete pGenericTypeDecl;
			}
		}
		TypeRef* pBaseTypeRef = 0;
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COLON) != 0)
		{
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			pBaseTypeRef = TypeRef::TryCreate(pTokenContainer, pTempOffset);
			if (pBaseTypeRef == 0)
			{
				Console::Log("expected base class");
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
				NumbatLogic::Assert::Plz(false);
				if (pTempOffset) delete pTempOffset;
				if (pClassDecl) delete pClassDecl;
				if (pBaseTypeRef) delete pBaseTypeRef;
				return 0;
			}
		}
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_LEFT) == 0)
		{
			Console::Log("expected opening curly brace");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pClassDecl) delete pClassDecl;
			if (pBaseTypeRef) delete pBaseTypeRef;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		pClassDecl->m_pFirstToken = pClassToken;
		pClassDecl->m_pNameToken = pNameToken;
		pClassDecl->m_pBaseTypeRef = pBaseTypeRef;
		if (pBaseTypeRef != 0)
		{
			NumbatLogic::TypeRef* __2444892862 = pBaseTypeRef;
			pBaseTypeRef = 0;
			pClassDecl->AddChild(__2444892862);
		}
		while (true)
		{
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_RIGHT) != 0)
			{
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				break;
			}
			AST* pAST = 0;
			pAST = MemberVarDecl::TryCreate(pTokenContainer, pTempOffset);
			if (pAST != 0)
			{
				NumbatLogic::AST* __1913155045 = pAST;
				pAST = 0;
				pClassDecl->AddChild(__1913155045);
				if (pAST) delete pAST;
				continue;
			}
			pAST = MemberFunctionDecl::TryCreate(pTokenContainer, pTempOffset, pClassDecl);
			if (pAST != 0)
			{
				NumbatLogic::AST* __2768793590 = pAST;
				pAST = 0;
				pClassDecl->AddChild(__2768793590);
				if (pAST) delete pAST;
				continue;
			}
			pAST = MemberClassDecl::TryCreate(pTokenContainer, pTempOffset, pClassDecl);
			if (pAST != 0)
			{
				NumbatLogic::AST* __1695068768 = pAST;
				pAST = 0;
				pClassDecl->AddChild(__1695068768);
				if (pAST) delete pAST;
				continue;
			}
			pAST = MemberEnumDecl::TryCreate(pTokenContainer, pTempOffset);
			if (pAST != 0)
			{
				NumbatLogic::AST* __2097715949 = pAST;
				pAST = 0;
				pClassDecl->AddChild(__2097715949);
				if (pAST) delete pAST;
				continue;
			}
			pAST = TorDecl::TryCreate(pTokenContainer, pTempOffset, pClassDecl);
			if (pAST != 0)
			{
				NumbatLogic::AST* __4094203985 = pAST;
				pAST = 0;
				pClassDecl->AddChild(__4094203985);
				if (pAST) delete pAST;
				continue;
			}
			pAST = DelegateDecl::TryCreate(pTokenContainer, pTempOffset, pClassDecl);
			if (pAST != 0)
			{
				NumbatLogic::AST* __1040769079 = pAST;
				pAST = 0;
				pClassDecl->AddChild(__1040769079);
				if (pAST) delete pAST;
				continue;
			}
			Console::Log("expected to parse somethting within class...");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			NumbatLogic::Assert::Plz(false);
			if (pAST) delete pAST;
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ClassDecl* __2697205707 = pClassDecl;
		pClassDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pBaseTypeRef) delete pBaseTypeRef;
		return __2697205707;
	}

	void ClassDecl::PreValidate(Validator* pValidator, OperatorExpr* pParent)
	{
		m_pNamespaceNode = pValidator->m_pCurrentNamespaceNode;
	}

	void ClassDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AddClassDeclReference(this, AST::OutputFile::SOURCE, false);
		if (m_pBaseTypeRef != 0)
		{
			ValueType* pBaseValueType = m_pBaseTypeRef->CreateValueType();
			if (pBaseValueType == 0)
			{
				InternalString* sTemp = new InternalString("Unknown base class: ");
				sTemp->Append(m_pBaseTypeRef->m_pTypeToken->GetString());
				pValidator->AddError(sTemp->GetExternalString(), m_pBaseTypeRef->m_pFirstToken->m_sFileName, m_pBaseTypeRef->m_pFirstToken->m_nLine, m_pBaseTypeRef->m_pFirstToken->m_nColumn);
				if (sTemp) delete sTemp;
				if (pBaseValueType) delete pBaseValueType;
				return;
			}
			if (pBaseValueType->m_eType != ValueType::Type::CLASS_DECL_VALUE)
			{
				InternalString* sTemp = new InternalString("Unknown base class is not a class: ");
				sTemp->Append(m_pBaseTypeRef->m_pTypeToken->GetString());
				pValidator->AddError(sTemp->GetExternalString(), m_pBaseTypeRef->m_pFirstToken->m_sFileName, m_pBaseTypeRef->m_pFirstToken->m_nLine, m_pBaseTypeRef->m_pFirstToken->m_nColumn);
				if (sTemp) delete sTemp;
			}
			Assert::Plz(pBaseValueType->m_pClassDecl != 0);
			AddClassDeclReference(pBaseValueType->m_pClassDecl, AST::OutputFile::HEADER, false);
			if (pBaseValueType) delete pBaseValueType;
		}
		{
			bool bHasOwnedPointer = false;
			bool bHasDefaultableVariable = false;
			bool bHasConstructor = false;
			bool bHasDestructor = false;
			AST* pChild = m_pFirstChild;
			while (pChild != 0)
			{
				if (pChild->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
				{
					MemberVarDecl* pMemberVarDecl = (MemberVarDecl*)(pChild);
					TypeRef* pTypeRef = pMemberVarDecl->m_pVarDecl->m_pTypeRef;
					while (pTypeRef->m_pChildTypeRef != 0)
					{
						pTypeRef = pTypeRef->m_pChildTypeRef;
					}
					if (pTypeRef->m_ePointerType == TypeRef::PointerType::OWNED && !pMemberVarDecl->m_bStatic)
						bHasOwnedPointer = true;
					bHasDefaultableVariable = true;
				}
				if (pChild->m_eType == AST::Type::AST_TOR_DECL)
				{
					TorDecl* pTorDecl = (TorDecl*)(pChild);
					if (pTorDecl->m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DESTRUCT)
						bHasDestructor = true;
					if (pTorDecl->m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_CONSTRUCT)
					{
						bHasConstructor = true;
						if (pTorDecl->m_pScope != 0)
							pTorDecl->m_pScope->AddChildFront(new MemberVarsSetDefaultStmt());
					}
				}
				pChild = pChild->m_pNextSibling;
			}
			if (bHasDefaultableVariable && !bHasConstructor)
			{
				m_pConstructorAccessLevelToken = new Token();
				m_pConstructorAccessLevelToken->m_eType = Token::Type::TOKEN_KEYWORD_PUBLIC;
				AccessLevel* pAccessLevel = new AccessLevel();
				pAccessLevel->m_eType = AST::Type::AST_ACCESS_LEVEL;
				pAccessLevel->m_pFirstToken = m_pConstructorAccessLevelToken;
				m_pConstructorTypeToken = new Token();
				m_pConstructorTypeToken->m_eType = Token::Type::TOKEN_KEYWORD_CONSTRUCT;
				ParamDecl* pParamDecl = new ParamDecl();
				pParamDecl->m_pFirstToken = m_pFirstToken;
				Scope* pScope = new Scope();
				pScope->AddChild(new MemberVarsSetDefaultStmt());
				TorDecl* pTorDecl = new TorDecl();
				pTorDecl->m_eType = AST::Type::AST_TOR_DECL;
				pTorDecl->m_pParent = this;
				pTorDecl->m_pParentClassDecl = this;
				pTorDecl->m_pFirstToken = m_pFirstToken;
				pTorDecl->m_pAccessLevel = pAccessLevel;
				pTorDecl->m_pTypeToken = m_pConstructorTypeToken;
				pTorDecl->m_pParamDecl = pParamDecl;
				pTorDecl->m_pScope = pScope;
				pTorDecl->m_sDisambiguate = "";
				NumbatLogic::AccessLevel* __2009174746 = pAccessLevel;
				pAccessLevel = 0;
				pTorDecl->AddChild(__2009174746);
				NumbatLogic::ParamDecl* __3174381146 = pParamDecl;
				pParamDecl = 0;
				pTorDecl->AddChild(__3174381146);
				NumbatLogic::Scope* __1298744023 = pScope;
				pScope = 0;
				pTorDecl->AddChild(__1298744023);
				NumbatLogic::TorDecl* __2430494305 = pTorDecl;
				pTorDecl = 0;
				AddChild(__2430494305);
				if (pAccessLevel) delete pAccessLevel;
				if (pParamDecl) delete pParamDecl;
				if (pScope) delete pScope;
				if (pTorDecl) delete pTorDecl;
			}
			if (bHasOwnedPointer && !bHasDestructor)
			{
				m_pAccessLevelToken = new Token();
				m_pAccessLevelToken->m_eType = Token::Type::TOKEN_KEYWORD_PUBLIC;
				AccessLevel* pAccessLevel = new AccessLevel();
				pAccessLevel->m_eType = AST::Type::AST_ACCESS_LEVEL;
				pAccessLevel->m_pFirstToken = m_pAccessLevelToken;
				m_pTypeToken = new Token();
				m_pTypeToken->m_eType = Token::Type::TOKEN_KEYWORD_DESTRUCT;
				ParamDecl* pParamDecl = new ParamDecl();
				pParamDecl->m_pFirstToken = m_pFirstToken;
				Scope* pScope = new Scope();
				TorDecl* pTorDecl = new TorDecl();
				pTorDecl->m_eType = AST::Type::AST_TOR_DECL;
				pTorDecl->m_pParent = this;
				pTorDecl->m_pParentClassDecl = this;
				pTorDecl->m_pFirstToken = m_pFirstToken;
				pTorDecl->m_pAccessLevel = pAccessLevel;
				pTorDecl->m_pTypeToken = m_pTypeToken;
				pTorDecl->m_pParamDecl = pParamDecl;
				pTorDecl->m_pScope = pScope;
				pTorDecl->m_sDisambiguate = "";
				NumbatLogic::AccessLevel* __3838894316 = pAccessLevel;
				pAccessLevel = 0;
				pTorDecl->AddChild(__3838894316);
				NumbatLogic::ParamDecl* __1881425091 = pParamDecl;
				pParamDecl = 0;
				pTorDecl->AddChild(__1881425091);
				NumbatLogic::Scope* __444085164 = pScope;
				pScope = 0;
				pTorDecl->AddChild(__444085164);
				NumbatLogic::TorDecl* __2731503484 = pTorDecl;
				pTorDecl = 0;
				AddChild(__2731503484);
				if (pAccessLevel) delete pAccessLevel;
				if (pParamDecl) delete pParamDecl;
				if (pScope) delete pScope;
				if (pTorDecl) delete pTorDecl;
			}
		}
		AST::Validate(pValidator, pParent);
	}

	ClassDecl* ClassDecl::FindClassDecl(const char* sTypeName, AST* pCallingChild)
	{
		if (ExternalString::Equal(sTypeName, m_pNameToken->GetString()))
			return this;
		return 0;
	}

	AST* ClassDecl::FindByName(const char* sxName, AST* pCallingChild)
	{
		if (ExternalString::Equal(sxName, m_pNameToken->GetString()))
			return this;
		ClassDecl* pBaseClassDecl = GetBaseClassDecl();
		if (pBaseClassDecl != 0)
		{
			AST* pResult = pBaseClassDecl->FindByName(sxName, 0);
			if (pResult != 0)
				return pResult;
		}
		if (pCallingChild != 0)
		{
			for (int i = 0; i < m_pGenericTypeDeclVector->GetSize(); i++)
			{
				GenericTypeDecl* pGenericTypeDecl = m_pGenericTypeDeclVector->Get(i);
				if (ExternalString::Equal(pGenericTypeDecl->m_pFirstToken->GetString(), sxName))
				{
					return pGenericTypeDecl;
				}
			}
		}
		return AST::FindByName(sxName, pCallingChild);
	}

	ClassDecl* ClassDecl::GetBaseClassDecl()
	{
		if (m_pBaseClassDecl != 0)
			return m_pBaseClassDecl;
		if (m_pBaseTypeRef != 0 && m_pParent != 0)
		{
			ValueType* pBaseValueType = m_pBaseTypeRef->CreateValueType();
			if (pBaseValueType != 0)
			{
				m_pBaseClassDecl = pBaseValueType->m_pClassDecl;
				if (pBaseValueType) delete pBaseValueType;
				return m_pBaseClassDecl;
			}
			if (pBaseValueType) delete pBaseValueType;
		}
		return 0;
	}

	void ClassDecl::StringifyTemplateThing(Language eLanguage, OutputFile eOutputFile, InternalString* sOut)
	{
		sOut->AppendString("template <class ");
		for (int i = 0; i < m_pGenericTypeDeclVector->GetSize(); i++)
		{
			if (i > 0)
				sOut->Append(", ");
			GenericTypeDecl* pGenericTypeDecl = m_pGenericTypeDeclVector->Get(i);
			pGenericTypeDecl->Stringify(eLanguage, eOutputFile, 0, sOut);
		}
		sOut->AppendString(">");
	}

	void ClassDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		if (!(eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE))
		{
			if (eLanguage == AST::Language::CPP)
			{
				if (m_pGenericTypeDeclVector->GetSize() > 0)
				{
					Util::Pad(nDepth, sOut);
					StringifyTemplateThing(eLanguage, eOutputFile, sOut);
					sOut->AppendString("\n");
				}
			}
			Util::Pad(nDepth, sOut);
			sOut->Append("class ");
			m_pNameToken->Stringify(sOut);
			if (eLanguage == AST::Language::CS || eLanguage == AST::Language::NLL_DEF)
			{
				if (m_pGenericTypeDeclVector->GetSize() > 0)
				{
					sOut->AppendChar('<');
					for (int i = 0; i < m_pGenericTypeDeclVector->GetSize(); i++)
					{
						if (i > 0)
							sOut->Append(", ");
						GenericTypeDecl* pGenericTypeDecl = m_pGenericTypeDeclVector->Get(i);
						pGenericTypeDecl->Stringify(eLanguage, eOutputFile, 0, sOut);
					}
					sOut->AppendChar('>');
				}
			}
			if (m_pBaseTypeRef != 0)
			{
				sOut->Append(" : ");
				if (eLanguage == AST::Language::CPP)
					sOut->Append("public ");
				m_pBaseTypeRef->Stringify(eLanguage, eOutputFile, 0, sOut);
			}
			if (eLanguage == AST::Language::CS && m_pGenericTypeDeclVector->GetSize() > 0)
			{
				for (int i = 0; i < m_pGenericTypeDeclVector->GetSize(); i++)
				{
					if (m_pGenericTypeDeclVector->GetSize() == 1)
					{
						sOut->AppendChar(' ');
					}
					else
					{
						sOut->Append("\n");
						Util::Pad(nDepth + 1, sOut);
					}
					sOut->Append("where ");
					GenericTypeDecl* pGenericTypeDecl = m_pGenericTypeDeclVector->Get(i);
					pGenericTypeDecl->Stringify(eLanguage, eOutputFile, 0, sOut);
					sOut->Append(" : class");
				}
			}
			sOut->Append("\n");
			Util::Pad(nDepth, sOut);
			sOut->Append("{\n");
			nDepth++;
		}
		AST* pMember = m_pFirstChild;
		while (pMember != 0)
		{
			if (pMember != m_pBaseTypeRef)
				pMember->Stringify(eLanguage, eOutputFile, nDepth, sOut);
			pMember = pMember->m_pNextSibling;
		}
		if (!(eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE))
		{
			nDepth--;
			Util::Pad(nDepth, sOut);
			if (eLanguage == AST::Language::CPP)
				sOut->Append("};\n");
			else
				sOut->Append("}\n");
		}
	}

	ClassDecl::~ClassDecl()
	{
		if (m_pGenericTypeDeclVector) delete m_pGenericTypeDeclVector;
		if (m_pAccessLevelToken) delete m_pAccessLevelToken;
		if (m_pTypeToken) delete m_pTypeToken;
		if (m_pConstructorAccessLevelToken) delete m_pConstructorAccessLevelToken;
		if (m_pConstructorTypeToken) delete m_pConstructorTypeToken;
	}

}

