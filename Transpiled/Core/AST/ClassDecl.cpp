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
#include "../Semantic/SymbolScope.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../Semantic/Symbol.hpp"
#include "../Semantic/Resolver.hpp"
#include "../Project.hpp"
#include "../NamespaceNode.hpp"
#include "../OutputBuilder.hpp"
#include "../Util.hpp"

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
	class MemberEnumDecl;
	class DelegateDecl;
	class ValueType;
	class InternalString;
	class MemberVarDecl;
	class VarDecl;
	class TorDecl;
	class MemberVarsSetDefaultStmt;
	class AccessLevel;
	class ParamDecl;
	class Scope;
	class SymbolScope;
	template <class T>
	class Vector;
	class Symbol;
	class Resolver;
	class Validator;
	class Project;
	class MemberClassDecl;
	class NamespaceNode;
	class OutputBuilder;
	class Util;
}
#line 1 "../../../Source/Core/AST/ClassDecl.nll"
namespace NumbatLogic
{
	ClassDecl::ClassDecl()
	{
		m_pNameToken = 0;
		m_bDisposable = false;
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
		Token* pDisposableToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_DISPOSABLE);
		if (pDisposableToken != 0)
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		ClassDecl* pClassDecl = new ClassDecl();
		pClassDecl->m_bDisposable = pDisposableToken != 0;
		Token* pNameToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
		if (pNameToken == 0)
		{
			Console::Log("expected class name");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			Assert::Plz(false);
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
					Assert::Plz(false);
				}
				NumbatLogic::GenericTypeDecl* __977309417 = pGenericTypeDecl;
				pGenericTypeDecl = 0;
				pClassDecl->m_pGenericTypeDeclVector->PushBack(__977309417);
				if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_ANGLE_BRACKET_RIGHT) != 0)
				{
					if (pGenericTypeDecl) delete pGenericTypeDecl;
					continue;
				}
				if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COMMA) == 0)
				{
					Console::Log("expected comma");
					Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
					Assert::Plz(false);
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
				Assert::Plz(false);
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
			Assert::Plz(false);
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
			NumbatLogic::TypeRef* __276219192 = pBaseTypeRef;
			pBaseTypeRef = 0;
			pClassDecl->AddChild(__276219192);
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
				NumbatLogic::AST* __3057670627 = pAST;
				pAST = 0;
				pClassDecl->AddChild(__3057670627);
				if (pAST) delete pAST;
				continue;
			}
			pAST = MemberFunctionDecl::TryCreate(pTokenContainer, pTempOffset, pClassDecl);
			if (pAST != 0)
			{
				NumbatLogic::AST* __3057736223 = pAST;
				pAST = 0;
				pClassDecl->AddChild(__3057736223);
				if (pAST) delete pAST;
				continue;
			}
			pAST = MemberClassDecl::TryCreate(pTokenContainer, pTempOffset, pClassDecl);
			if (pAST != 0)
			{
				NumbatLogic::AST* __3057801819 = pAST;
				pAST = 0;
				pClassDecl->AddChild(__3057801819);
				if (pAST) delete pAST;
				continue;
			}
			pAST = MemberEnumDecl::TryCreate(pTokenContainer, pTempOffset);
			if (pAST != 0)
			{
				NumbatLogic::AST* __3057801826 = pAST;
				pAST = 0;
				pClassDecl->AddChild(__3057801826);
				if (pAST) delete pAST;
				continue;
			}
			pAST = TorDecl::TryCreate(pTokenContainer, pTempOffset, pClassDecl);
			if (pAST != 0)
			{
				NumbatLogic::AST* __3057867422 = pAST;
				pAST = 0;
				pClassDecl->AddChild(__3057867422);
				if (pAST) delete pAST;
				continue;
			}
			pAST = DelegateDecl::TryCreate(pTokenContainer, pTempOffset, pClassDecl);
			if (pAST != 0)
			{
				NumbatLogic::AST* __3057933018 = pAST;
				pAST = 0;
				pClassDecl->AddChild(__3057933018);
				if (pAST) delete pAST;
				continue;
			}
			Console::Log("expected to parse somethting within class...");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			Assert::Plz(false);
			if (pAST) delete pAST;
		}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ClassDecl* __438903738 = pClassDecl;
		pClassDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pBaseTypeRef) delete pBaseTypeRef;
		return __438903738;
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
			ValueType* pBaseValueType = m_pBaseTypeRef->CreateValueType(pValidator->m_pResolver);
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
				NumbatLogic::AccessLevel* __866280737 = pAccessLevel;
				pAccessLevel = 0;
				pTorDecl->AddChild(__866280737);
				NumbatLogic::ParamDecl* __2030449163 = pParamDecl;
				pParamDecl = 0;
				pTorDecl->AddChild(__2030449163);
				NumbatLogic::Scope* __3578341519 = pScope;
				pScope = 0;
				pTorDecl->AddChild(__3578341519);
				NumbatLogic::TorDecl* __3664169497 = pTorDecl;
				pTorDecl = 0;
				AddChild(__3664169497);
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
				NumbatLogic::AccessLevel* __874148643 = pAccessLevel;
				pAccessLevel = 0;
				pTorDecl->AddChild(__874148643);
				NumbatLogic::ParamDecl* __2038317069 = pParamDecl;
				pParamDecl = 0;
				pTorDecl->AddChild(__2038317069);
				NumbatLogic::Scope* __3586209425 = pScope;
				pScope = 0;
				pTorDecl->AddChild(__3586209425);
				NumbatLogic::TorDecl* __3671971814 = pTorDecl;
				pTorDecl = 0;
				AddChild(__3671971814);
				if (pAccessLevel) delete pAccessLevel;
				if (pParamDecl) delete pParamDecl;
				if (pScope) delete pScope;
				if (pTorDecl) delete pTorDecl;
			}
		}
		AST::Validate(pValidator, pParent);
	}

	ClassDecl* ClassDecl::GetBaseClassDeclForScopeLookup(Resolver* pResolver)
	{
		if (m_pBaseClassDecl != 0)
			return m_pBaseClassDecl;
		if (m_pBaseTypeRef == 0)
			return 0;
		ClassDecl* pBase = m_pBaseTypeRef->GetFoundClassDecl();
		if (pBase == 0 && m_pBaseTypeRef->m_pChildTypeRef != 0)
			pBase = m_pBaseTypeRef->m_pChildTypeRef->GetFoundClassDecl();
		if (pBase != 0)
		{
			m_pBaseClassDecl = pBase;
			return m_pBaseClassDecl;
		}
		if (pResolver == 0 || m_pSymbolScope == 0)
			return 0;
		SymbolScope* pParentScope = m_pSymbolScope->m_pParent;
		if (pParentScope == 0)
			return 0;
		const char* sBaseName = m_pBaseTypeRef->m_pTypeToken->GetString();
		Vector<Symbol*>* pCandidates = new Vector<Symbol*>();
		pResolver->ResolveInScopeChainNoBaseClasses(sBaseName, pParentScope, pCandidates);
		if (pCandidates->GetSize() == 1)
		{
			Symbol* pSym = pCandidates->Get(0);
			if (pSym->m_eKind == Symbol::Kind::CLASS && pSym->m_pDeclAST != 0 && pSym->m_pDeclAST->m_eType == AST::Type::AST_CLASS_DECL)
			{
				m_pBaseClassDecl = (ClassDecl*)(pSym->m_pDeclAST);
				if (pCandidates) delete pCandidates;
				return m_pBaseClassDecl;
			}
			if (pSym->m_eKind == Symbol::Kind::NAMESPACE && pSym->m_pScope != 0 && m_pBaseTypeRef->m_pChildTypeRef != 0)
			{
				const char* sChildName = m_pBaseTypeRef->m_pChildTypeRef->m_pTypeToken->GetString();
				Vector<Symbol*>* pChildCandidates = new Vector<Symbol*>();
				pResolver->ResolveInScopeChainNoBaseClasses(sChildName, pSym->m_pScope, pChildCandidates);
				if (pChildCandidates->GetSize() == 1)
				{
					Symbol* pChildSym = pChildCandidates->Get(0);
					if (pChildSym->m_eKind == Symbol::Kind::CLASS && pChildSym->m_pDeclAST != 0 && pChildSym->m_pDeclAST->m_eType == AST::Type::AST_CLASS_DECL)
					{
						m_pBaseClassDecl = (ClassDecl*)(pChildSym->m_pDeclAST);
						if (pChildCandidates) delete pChildCandidates;
						if (pCandidates) delete pCandidates;
						return m_pBaseClassDecl;
					}
				}
				if (pChildCandidates) delete pChildCandidates;
			}
		}
		if (pCandidates) delete pCandidates;
		return 0;
	}

	ClassDecl* ClassDecl::GetBaseClassDecl(Validator* pValidator)
	{
		if (m_pBaseClassDecl != 0)
			return m_pBaseClassDecl;
		Validator* pV = pValidator;
		if (pV == 0)
		{
			Project* pProject = GetProject();
			if (pProject != 0)
				pV = pProject->m_pValidator;
		}
		if (m_pBaseTypeRef != 0 && m_pParent != 0 && pV != 0)
		{
			ValueType* pBaseValueType = m_pBaseTypeRef->CreateValueType(pV->m_pResolver);
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

	void ClassDecl::AppendFullyQualifiedName(InternalString* sOut)
	{
		if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
		{
			MemberClassDecl* pMember = (MemberClassDecl*)(m_pParent);
			pMember->m_pParentClassDecl->AppendFullyQualifiedName(sOut);
			sOut->Append("::");
		}
		else
			if (m_pNamespaceNode != 0 && m_pNamespaceNode->m_sName != 0)
			{
				m_pNamespaceNode->AppendFullyQualifiedName(sOut);
				sOut->Append("::");
			}
		sOut->Append(m_pNameToken->GetString());
	}

	void ClassDecl::StringifyTemplateThing(Language eLanguage, OutputFile eOutputFile, OutputBuilder* out)
	{
		out->m_sOut->AppendString("template <class ");
		for (int i = 0; i < m_pGenericTypeDeclVector->GetSize(); i++)
		{
			if (i > 0)
				out->m_sOut->Append(", ");
			GenericTypeDecl* pGenericTypeDecl = m_pGenericTypeDeclVector->Get(i);
			pGenericTypeDecl->Stringify(eLanguage, eOutputFile, 0, out);
		}
		out->m_sOut->AppendString(">");
	}

	void ClassDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out)
	{
		if (!(eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE))
		{
			if (eLanguage == AST::Language::CPP)
			{
				if (m_pGenericTypeDeclVector->GetSize() > 0)
				{
					Util::Pad(nDepth, out->m_sOut);
					StringifyTemplateThing(eLanguage, eOutputFile, out);
					out->m_sOut->AppendString("\n");
				}
			}
			Util::Pad(nDepth, out->m_sOut);
			out->m_sOut->Append("class ");
			m_pNameToken->Stringify(out->m_sOut);
			if (eLanguage == AST::Language::CS || eLanguage == AST::Language::NLL_DEF)
			{
				if (m_pGenericTypeDeclVector->GetSize() > 0)
				{
					out->m_sOut->AppendChar('<');
					for (int i = 0; i < m_pGenericTypeDeclVector->GetSize(); i++)
					{
						if (i > 0)
							out->m_sOut->Append(", ");
						GenericTypeDecl* pGenericTypeDecl = m_pGenericTypeDeclVector->Get(i);
						pGenericTypeDecl->Stringify(eLanguage, eOutputFile, 0, out);
					}
					out->m_sOut->AppendChar('>');
				}
			}
			if (m_pBaseTypeRef != 0)
			{
				out->m_sOut->Append(" : ");
				if (eLanguage == AST::Language::CPP)
					out->m_sOut->Append("public ");
				m_pBaseTypeRef->Stringify(eLanguage, eOutputFile, 0, out);
			}
			if (eLanguage == AST::Language::CS && m_bDisposable)
			{
				if (m_pBaseTypeRef == 0)
					out->m_sOut->Append(" : ");
				else
					out->m_sOut->Append(", ");
				out->m_sOut->Append("System.IDisposable");
			}
			if (eLanguage == AST::Language::CS && m_pGenericTypeDeclVector->GetSize() > 0)
			{
				for (int i = 0; i < m_pGenericTypeDeclVector->GetSize(); i++)
				{
					if (m_pGenericTypeDeclVector->GetSize() == 1)
					{
						out->m_sOut->AppendChar(' ');
					}
					else
					{
						out->m_sOut->Append("\n");
						Util::Pad(nDepth + 1, out->m_sOut);
					}
					out->m_sOut->Append("where ");
					GenericTypeDecl* pGenericTypeDecl = m_pGenericTypeDeclVector->Get(i);
					pGenericTypeDecl->Stringify(eLanguage, eOutputFile, 0, out);
					out->m_sOut->Append(" : class");
				}
			}
			out->m_sOut->Append("\n");
			Util::Pad(nDepth, out->m_sOut);
			out->m_sOut->Append("{\n");
			nDepth++;
		}
		AST* pMember = m_pFirstChild;
		while (pMember != 0)
		{
			if (pMember != m_pBaseTypeRef)
				pMember->Stringify(eLanguage, eOutputFile, nDepth, out);
			pMember = pMember->m_pNextSibling;
		}
		if (!(eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE))
		{
			nDepth--;
			Util::Pad(nDepth, out->m_sOut);
			if (eLanguage == AST::Language::CPP)
				out->m_sOut->Append("};\n");
			else
				out->m_sOut->Append("}\n");
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

