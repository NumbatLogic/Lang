#include "ClassDecl.hpp"
#include "AST.hpp"
#include "GenericTypeDecl.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "DecoratorCall.hpp"
#include "../../../../LangShared/Source/Vector/CPP/Vector.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Source/Console/CPP/Console.hpp"
#include "../../../../LangShared/Source/Assert/CPP/Assert.hpp"
#include "TypeRef.hpp"
#include "MemberVarDecl.hpp"
#include "MemberFunctionDecl.hpp"
#include "MemberClassDecl.hpp"
#include "MemberEnumDecl.hpp"
#include "TorDecl.hpp"
#include "DelegateDecl.hpp"
#include "../Validator.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"
#include "../ValueType.hpp"
#include "VarDecl.hpp"
#include "Scope.hpp"
#include "MemberVarsSetDefaultStmt.hpp"
#include "AccessLevel.hpp"
#include "ParamDecl.hpp"
#include "../Semantic/SymbolScope.hpp"
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
	class DecoratorCall;
	template <class T>
	class Vector;
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
	class Symbol;
	class Resolver;
	class Validator;
	class Project;
	class MemberClassDecl;
	class NamespaceNode;
	class OutputBuilder;
	class Util;
}
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
	ClassDecl::ClassDecl()
	{
		m_pNameToken = 0;
		m_bDisposable = false;
		m_pBaseTypeRef = 0;
		m_pGenericTypeDeclVector = 0;
		m_pDecoratorCallVector = 0;
		m_pNamespaceNode = 0;
		m_pBaseClassDecl = 0;
		m_pAccessLevelToken = 0;
		m_pTypeToken = 0;
		m_pConstructorAccessLevelToken = 0;
		m_pConstructorTypeToken = 0;
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		m_eType = AST::Type::AST_CLASS_DECL;
		m_bCanDescend = true;
		m_pGenericTypeDeclVector = new OwnedVector<GenericTypeDecl*>();
		m_pDecoratorCallVector = new Vector<DecoratorCall*>();
		m_pNamespaceNode = 0;
		m_pBaseClassDecl = 0;
	}

	ClassDecl* ClassDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, AST* pParent)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 34 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		Token* pClassToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_CLASS);
		if (pClassToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 36 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			return 0;
		}
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 39 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		Token* pDisposableToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_DISPOSABLE);
		if (pDisposableToken != 0)
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 43 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		ClassDecl* pClassDecl = new ClassDecl();
		pClassDecl->m_bDisposable = pDisposableToken != 0;
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		OwnedVector<DecoratorCall*>* pOwnedDecoratorCallVector = new OwnedVector<DecoratorCall*>();
		while (true)
		{
			DecoratorCall* pDecoratorCall = DecoratorCall::TryCreate(pTokenContainer, pTempOffset);
			if (pDecoratorCall == 0)
			{
				if (pDecoratorCall) delete pDecoratorCall;
#line 51 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				break;
			}
			NumbatLogic::DecoratorCall* __1592970759 = pDecoratorCall;
#line 53 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			pDecoratorCall = 0;
#line 53 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			pOwnedDecoratorCallVector->PushBack(__1592970759);
			if (pDecoratorCall) delete pDecoratorCall;
		}
		while (pOwnedDecoratorCallVector->GetSize() > 0)
		{
			DecoratorCall* pDecoratorCall = pOwnedDecoratorCallVector->PopFront();
			pDecoratorCall->m_pParent = pClassDecl;
			DecoratorCall* pTemp = pDecoratorCall;
			pClassDecl->m_pDecoratorCallVector->PushBack(pTemp);
			NumbatLogic::DecoratorCall* __1593036357 = pDecoratorCall;
#line 62 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			pDecoratorCall = 0;
#line 62 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			pClassDecl->AddChild(__1593036357);
			if (pDecoratorCall) delete pDecoratorCall;
		}
		Token* pNameToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
		if (pNameToken == 0)
		{
			Console::Log("expected class name");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pClassDecl) delete pClassDecl;
			if (pOwnedDecoratorCallVector) delete pOwnedDecoratorCallVector;
#line 71 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 76 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		Token* pAngleBracketLeft = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_ANGLE_BRACKET_LEFT);
		if (pAngleBracketLeft != 0)
		{
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 81 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			while (true)
			{
				if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_ANGLE_BRACKET_RIGHT) != 0)
				{
					pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
					break;
				}
#line 89 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				GenericTypeDecl* pGenericTypeDecl = GenericTypeDecl::TryCreate(pTokenContainer, pTempOffset);
				if (pGenericTypeDecl == 0)
				{
					Console::Log("expected inner GenericTypeDecl");
					Assert::Plz(false);
				}
				NumbatLogic::GenericTypeDecl* __977440616 = pGenericTypeDecl;
				pGenericTypeDecl = 0;
#line 96 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pClassDecl->m_pGenericTypeDeclVector->PushBack(__977440616);
#line 99 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_ANGLE_BRACKET_RIGHT) != 0)
				{
					if (pGenericTypeDecl) delete pGenericTypeDecl;
#line 100 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
#line 113 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
				if (pOwnedDecoratorCallVector) delete pOwnedDecoratorCallVector;
				if (pBaseTypeRef) delete pBaseTypeRef;
#line 123 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				return 0;
			}
		}
#line 127 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_LEFT) == 0)
		{
			Console::Log("expected opening curly brace");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pClassDecl) delete pClassDecl;
			if (pOwnedDecoratorCallVector) delete pOwnedDecoratorCallVector;
			if (pBaseTypeRef) delete pBaseTypeRef;
#line 132 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 138 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		pClassDecl->m_pFirstToken = pClassToken;
		pClassDecl->m_pNameToken = pNameToken;
		pClassDecl->m_pBaseTypeRef = pBaseTypeRef;
		if (pBaseTypeRef != 0)
		{
			NumbatLogic::TypeRef* __276350391 = pBaseTypeRef;
#line 142 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			pBaseTypeRef = 0;
#line 142 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			pClassDecl->AddChild(__276350391);
		}
#line 145 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		while (true)
		{
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_RIGHT) != 0)
			{
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				break;
			}
#line 153 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			AST* pAST = 0;
#line 155 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			pAST = MemberVarDecl::TryCreate(pTokenContainer, pTempOffset);
			if (pAST != 0)
			{
				NumbatLogic::AST* __3057801826 = pAST;
#line 158 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pAST = 0;
#line 158 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pClassDecl->AddChild(__3057801826);
				if (pAST) delete pAST;
#line 159 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				continue;
			}
#line 162 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			pAST = MemberFunctionDecl::TryCreate(pTokenContainer, pTempOffset, pClassDecl);
			if (pAST != 0)
			{
				NumbatLogic::AST* __3057867422 = pAST;
#line 165 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pAST = 0;
#line 165 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pClassDecl->AddChild(__3057867422);
				if (pAST) delete pAST;
#line 166 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				continue;
			}
#line 169 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			pAST = MemberClassDecl::TryCreate(pTokenContainer, pTempOffset, pClassDecl);
			if (pAST != 0)
			{
				NumbatLogic::AST* __3057933018 = pAST;
#line 172 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pAST = 0;
#line 172 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pClassDecl->AddChild(__3057933018);
				if (pAST) delete pAST;
#line 173 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				continue;
			}
#line 176 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			pAST = MemberEnumDecl::TryCreate(pTokenContainer, pTempOffset);
			if (pAST != 0)
			{
				NumbatLogic::AST* __3057933025 = pAST;
#line 179 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pAST = 0;
#line 179 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pClassDecl->AddChild(__3057933025);
				if (pAST) delete pAST;
#line 180 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				continue;
			}
#line 183 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			pAST = TorDecl::TryCreate(pTokenContainer, pTempOffset, pClassDecl);
			if (pAST != 0)
			{
				NumbatLogic::AST* __3057998621 = pAST;
#line 186 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pAST = 0;
#line 186 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pClassDecl->AddChild(__3057998621);
				if (pAST) delete pAST;
#line 187 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				continue;
			}
#line 190 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			pAST = DelegateDecl::TryCreate(pTokenContainer, pTempOffset, pClassDecl);
			if (pAST != 0)
			{
				NumbatLogic::AST* __3058064217 = pAST;
#line 193 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pAST = 0;
#line 193 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pClassDecl->AddChild(__3058064217);
				if (pAST) delete pAST;
#line 194 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				continue;
			}
#line 197 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			Console::Log("expected to parse somethting within class...");
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
			Assert::Plz(false);
			if (pAST) delete pAST;
		}
#line 203 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ClassDecl* __446640452 = pClassDecl;
#line 204 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		pClassDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pOwnedDecoratorCallVector) delete pOwnedDecoratorCallVector;
		if (pBaseTypeRef) delete pBaseTypeRef;
#line 204 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		return __446640452;
	}

	void ClassDecl::PreValidate(Validator* pValidator, OperatorExpr* pParent)
	{
		m_pNamespaceNode = pValidator->m_pCurrentNamespaceNode;
	}

	void ClassDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		AddClassDeclReference(this, AST::OutputFile::SOURCE, false);
#line 216 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
#line 224 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				return;
			}
#line 227 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
#line 241 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
#line 260 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					bHasDefaultableVariable = true;
				}
#line 263 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
#line 276 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pChild = pChild->m_pNextSibling;
			}
#line 279 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			if (bHasDefaultableVariable && !bHasConstructor)
			{
				m_pConstructorAccessLevelToken = new Token();
				m_pConstructorAccessLevelToken->m_eType = Token::Type::TOKEN_KEYWORD_PUBLIC;
#line 284 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				AccessLevel* pAccessLevel = new AccessLevel();
				pAccessLevel->m_eType = AST::Type::AST_ACCESS_LEVEL;
				pAccessLevel->m_pFirstToken = m_pConstructorAccessLevelToken;
#line 288 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				m_pConstructorTypeToken = new Token();
				m_pConstructorTypeToken->m_eType = Token::Type::TOKEN_KEYWORD_CONSTRUCT;
#line 291 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				ParamDecl* pParamDecl = new ParamDecl();
				pParamDecl->m_pFirstToken = m_pFirstToken;
#line 294 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				Scope* pScope = new Scope();
				pScope->AddChild(new MemberVarsSetDefaultStmt());
#line 297 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
				NumbatLogic::AccessLevel* __874017451 = pAccessLevel;
				pAccessLevel = 0;
#line 308 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pTorDecl->AddChild(__874017451);
				NumbatLogic::ParamDecl* __2038185877 = pParamDecl;
#line 309 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pParamDecl = 0;
#line 309 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pTorDecl->AddChild(__2038185877);
				NumbatLogic::Scope* __3586143822 = pScope;
#line 310 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pScope = 0;
#line 310 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pTorDecl->AddChild(__3586143822);
				NumbatLogic::TorDecl* __3671906211 = pTorDecl;
				pTorDecl = 0;
#line 312 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				AddChild(__3671906211);
				if (pAccessLevel) delete pAccessLevel;
				if (pParamDecl) delete pParamDecl;
				if (pScope) delete pScope;
				if (pTorDecl) delete pTorDecl;
			}
#line 315 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			if (bHasOwnedPointer && !bHasDestructor)
			{
				m_pAccessLevelToken = new Token();
				m_pAccessLevelToken->m_eType = Token::Type::TOKEN_KEYWORD_PUBLIC;
#line 320 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				AccessLevel* pAccessLevel = new AccessLevel();
				pAccessLevel->m_eType = AST::Type::AST_ACCESS_LEVEL;
				pAccessLevel->m_pFirstToken = m_pAccessLevelToken;
#line 324 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				m_pTypeToken = new Token();
				m_pTypeToken->m_eType = Token::Type::TOKEN_KEYWORD_DESTRUCT;
#line 327 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				ParamDecl* pParamDecl = new ParamDecl();
				pParamDecl->m_pFirstToken = m_pFirstToken;
#line 330 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				Scope* pScope = new Scope();
#line 332 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
				NumbatLogic::AccessLevel* __874279842 = pAccessLevel;
				pAccessLevel = 0;
#line 343 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pTorDecl->AddChild(__874279842);
				NumbatLogic::ParamDecl* __2038448268 = pParamDecl;
#line 344 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pParamDecl = 0;
#line 344 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pTorDecl->AddChild(__2038448268);
				NumbatLogic::Scope* __3586340624 = pScope;
#line 345 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pScope = 0;
#line 345 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				pTorDecl->AddChild(__3586340624);
				NumbatLogic::TorDecl* __3672103013 = pTorDecl;
				pTorDecl = 0;
#line 347 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				AddChild(__3672103013);
				if (pAccessLevel) delete pAccessLevel;
				if (pParamDecl) delete pParamDecl;
				if (pScope) delete pScope;
				if (pTorDecl) delete pTorDecl;
			}
		}
#line 351 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		AST::Validate(pValidator, pParent);
	}

#line 357 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
#line 372 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
#line 386 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				return m_pBaseClassDecl;
			}
#line 389 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
#line 400 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
						return m_pBaseClassDecl;
					}
				}
				if (pChildCandidates) delete pChildCandidates;
			}
		}
		if (pCandidates) delete pCandidates;
#line 405 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		return 0;
	}

	ClassDecl* ClassDecl::GetBaseClassDecl(Validator* pValidator)
	{
		if (m_pBaseClassDecl != 0)
			return m_pBaseClassDecl;
#line 413 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
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
#line 426 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
				return m_pBaseClassDecl;
			}
			if (pBaseValueType) delete pBaseValueType;
		}
#line 429 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		return 0;
	}

	void ClassDecl::AppendFullyQualifiedName(AST::Language eLanguage, InternalString* sOut)
	{
		const char* sxSeparator = "::";
		if (eLanguage == AST::Language::CS)
			sxSeparator = ".";
#line 438 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
		{
			MemberClassDecl* pMember = (MemberClassDecl*)(m_pParent);
			pMember->m_pParentClassDecl->AppendFullyQualifiedName(eLanguage, sOut);
			sOut->Append(sxSeparator);
		}
		else
#line 444 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			if (m_pNamespaceNode != 0 && m_pNamespaceNode->m_sName != 0)
			{
				m_pNamespaceNode->AppendFullyQualifiedName(eLanguage, sOut);
				sOut->Append(sxSeparator);
			}
		sOut->Append(m_pNameToken->GetString());
	}

	void ClassDecl::StringifyTemplateThing(Language eLanguage, OutputFile eOutputFile, OutputBuilder* pOutputBuilder)
	{
		pOutputBuilder->m_sOut->AppendString("template <class ");
		for (int i = 0; i < m_pGenericTypeDeclVector->GetSize(); i++)
		{
			if (i > 0)
				pOutputBuilder->m_sOut->Append(", ");
			GenericTypeDecl* pGenericTypeDecl = m_pGenericTypeDeclVector->Get(i);
			pGenericTypeDecl->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}
		pOutputBuilder->m_sOut->AppendString(">");
	}

	void ClassDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 469 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		if (!(eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE))
		{
			if (eLanguage == AST::Language::CPP)
			{
				if (m_pGenericTypeDeclVector->GetSize() > 0)
				{
					Util::Pad(nDepth, pOutputBuilder->m_sOut);
					StringifyTemplateThing(eLanguage, eOutputFile, pOutputBuilder);
					pOutputBuilder->m_sOut->AppendString("\n");
				}
			}
#line 481 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
			pOutputBuilder->m_sOut->Append("class ");
#line 484 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			if (eLanguage == AST::Language::NLL && m_pDecoratorCallVector != 0 && m_pDecoratorCallVector->GetSize() > 0)
			{
				for (int i = 0; i < m_pDecoratorCallVector->GetSize(); i++)
				{
					DecoratorCall* pDecoratorCall = m_pDecoratorCallVector->Get(i);
					pDecoratorCall->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				}
				pOutputBuilder->m_sOut->AppendChar(' ');
			}
#line 494 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			m_pNameToken->Stringify(pOutputBuilder->m_sOut);
#line 496 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			if (eLanguage == AST::Language::CS || eLanguage == AST::Language::NLL_DEF)
			{
				if (m_pGenericTypeDeclVector->GetSize() > 0)
				{
					pOutputBuilder->m_sOut->AppendChar('<');
					for (int i = 0; i < m_pGenericTypeDeclVector->GetSize(); i++)
					{
						if (i > 0)
							pOutputBuilder->m_sOut->Append(", ");
						GenericTypeDecl* pGenericTypeDecl = m_pGenericTypeDeclVector->Get(i);
						pGenericTypeDecl->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
					}
					pOutputBuilder->m_sOut->AppendChar('>');
				}
			}
#line 512 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			if (m_pBaseTypeRef != 0)
			{
				pOutputBuilder->m_sOut->Append(" : ");
				if (eLanguage == AST::Language::CPP)
					pOutputBuilder->m_sOut->Append("public ");
				m_pBaseTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
#line 520 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			if (eLanguage == AST::Language::CS && m_bDisposable)
			{
				if (m_pBaseTypeRef == 0)
					pOutputBuilder->m_sOut->Append(" : ");
				else
					pOutputBuilder->m_sOut->Append(", ");
				pOutputBuilder->m_sOut->Append("System.IDisposable");
			}
#line 529 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			if (eLanguage == AST::Language::CS && m_pGenericTypeDeclVector->GetSize() > 0)
			{
				for (int i = 0; i < m_pGenericTypeDeclVector->GetSize(); i++)
				{
					if (m_pGenericTypeDeclVector->GetSize() == 1)
					{
						pOutputBuilder->m_sOut->AppendChar(' ');
					}
					else
					{
						pOutputBuilder->m_sOut->Append("\n");
						Util::Pad(nDepth + 1, pOutputBuilder->m_sOut);
					}
#line 543 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
					pOutputBuilder->m_sOut->Append("where ");
					GenericTypeDecl* pGenericTypeDecl = m_pGenericTypeDeclVector->Get(i);
					pGenericTypeDecl->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
					pOutputBuilder->m_sOut->Append(" : class");
				}
			}
#line 550 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			pOutputBuilder->m_sOut->Append("\n");
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
			pOutputBuilder->m_sOut->Append("{\n");
#line 554 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			nDepth++;
		}
#line 557 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		AST* pMember = m_pFirstChild;
		while (pMember != 0)
		{
			if (pMember != m_pBaseTypeRef && pMember->m_eType != AST::Type::AST_DECORATOR_CALL)
				pMember->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
			pMember = pMember->m_pNextSibling;
		}
#line 565 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
		if (!(eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE))
		{
			nDepth--;
#line 569 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
			if (eLanguage == AST::Language::CPP)
				pOutputBuilder->m_sOut->Append("};\n");
			else
				pOutputBuilder->m_sOut->Append("}\n");
		}
	}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/ClassDecl.nll"
	ClassDecl::~ClassDecl()
	{
		if (m_pGenericTypeDeclVector) delete m_pGenericTypeDeclVector;
		if (m_pDecoratorCallVector) delete m_pDecoratorCallVector;
		if (m_pAccessLevelToken) delete m_pAccessLevelToken;
		if (m_pTypeToken) delete m_pTypeToken;
		if (m_pConstructorAccessLevelToken) delete m_pConstructorAccessLevelToken;
		if (m_pConstructorTypeToken) delete m_pConstructorTypeToken;
	}

}

