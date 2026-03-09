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
#line 4 "../../../Source/Core/AST/ClassDecl.nll"
#line 20 "../../../Source/Core/AST/ClassDecl.nll"
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
#line 22 "../../../Source/Core/AST/ClassDecl.nll"
		m_eType = AST::Type::AST_CLASS_DECL;
#line 23 "../../../Source/Core/AST/ClassDecl.nll"
		m_bCanDescend = true;
#line 24 "../../../Source/Core/AST/ClassDecl.nll"
		m_pGenericTypeDeclVector = new OwnedVector<GenericTypeDecl*>();
#line 25 "../../../Source/Core/AST/ClassDecl.nll"
		m_pNamespaceNode = 0;
#line 26 "../../../Source/Core/AST/ClassDecl.nll"
		m_pBaseClassDecl = 0;
	}

#line 29 "../../../Source/Core/AST/ClassDecl.nll"
	ClassDecl* ClassDecl::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum, AST* pParent)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pClassToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_CLASS);
#line 34 "../../../Source/Core/AST/ClassDecl.nll"
		if (pClassToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 35 "../../../Source/Core/AST/ClassDecl.nll"
			return 0;
		}
#line 36 "../../../Source/Core/AST/ClassDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		Token* pDisposableToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_DISPOSABLE);
#line 39 "../../../Source/Core/AST/ClassDecl.nll"
		if (pDisposableToken != 0)
#line 40 "../../../Source/Core/AST/ClassDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		ClassDecl* pClassDecl = new ClassDecl();
#line 43 "../../../Source/Core/AST/ClassDecl.nll"
		pClassDecl->m_bDisposable = pDisposableToken != 0;
		Token* pNameToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
#line 46 "../../../Source/Core/AST/ClassDecl.nll"
		if (pNameToken == 0)
		{
#line 48 "../../../Source/Core/AST/ClassDecl.nll"
			Console::Log("expected class name");
#line 49 "../../../Source/Core/AST/ClassDecl.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 50 "../../../Source/Core/AST/ClassDecl.nll"
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pClassDecl) delete pClassDecl;
#line 51 "../../../Source/Core/AST/ClassDecl.nll"
			return 0;
		}
#line 53 "../../../Source/Core/AST/ClassDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		Token* pAngleBracketLeft = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_ANGLE_BRACKET_LEFT);
#line 57 "../../../Source/Core/AST/ClassDecl.nll"
		if (pAngleBracketLeft != 0)
		{
#line 59 "../../../Source/Core/AST/ClassDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 61 "../../../Source/Core/AST/ClassDecl.nll"
			while (true)
			{
#line 63 "../../../Source/Core/AST/ClassDecl.nll"
				if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_ANGLE_BRACKET_RIGHT) != 0)
				{
#line 65 "../../../Source/Core/AST/ClassDecl.nll"
					pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 66 "../../../Source/Core/AST/ClassDecl.nll"
					break;
				}
				GenericTypeDecl* pGenericTypeDecl = GenericTypeDecl::TryCreate(pTokenContainer, pTempOffset);
#line 70 "../../../Source/Core/AST/ClassDecl.nll"
				if (pGenericTypeDecl == 0)
				{
#line 72 "../../../Source/Core/AST/ClassDecl.nll"
					Console::Log("expected inner GenericTypeDecl");
#line 73 "../../../Source/Core/AST/ClassDecl.nll"
					Assert::Plz(false);
				}
				NumbatLogic::GenericTypeDecl* __977309417 = pGenericTypeDecl;
#line 76 "../../../Source/Core/AST/ClassDecl.nll"
				pGenericTypeDecl = 0;
#line 76 "../../../Source/Core/AST/ClassDecl.nll"
				pClassDecl->m_pGenericTypeDeclVector->PushBack(__977309417);
#line 79 "../../../Source/Core/AST/ClassDecl.nll"
				if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_ANGLE_BRACKET_RIGHT) != 0)
				{
					if (pGenericTypeDecl) delete pGenericTypeDecl;
#line 80 "../../../Source/Core/AST/ClassDecl.nll"
					continue;
				}
#line 82 "../../../Source/Core/AST/ClassDecl.nll"
				if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COMMA) == 0)
				{
#line 84 "../../../Source/Core/AST/ClassDecl.nll"
					Console::Log("expected comma");
#line 85 "../../../Source/Core/AST/ClassDecl.nll"
					Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 86 "../../../Source/Core/AST/ClassDecl.nll"
					Assert::Plz(false);
				}
#line 88 "../../../Source/Core/AST/ClassDecl.nll"
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				if (pGenericTypeDecl) delete pGenericTypeDecl;
			}
		}
		TypeRef* pBaseTypeRef = 0;
#line 94 "../../../Source/Core/AST/ClassDecl.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COLON) != 0)
		{
#line 96 "../../../Source/Core/AST/ClassDecl.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 97 "../../../Source/Core/AST/ClassDecl.nll"
			pBaseTypeRef = TypeRef::TryCreate(pTokenContainer, pTempOffset);
#line 98 "../../../Source/Core/AST/ClassDecl.nll"
			if (pBaseTypeRef == 0)
			{
#line 100 "../../../Source/Core/AST/ClassDecl.nll"
				Console::Log("expected base class");
#line 101 "../../../Source/Core/AST/ClassDecl.nll"
				Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 102 "../../../Source/Core/AST/ClassDecl.nll"
				Assert::Plz(false);
				if (pTempOffset) delete pTempOffset;
				if (pClassDecl) delete pClassDecl;
				if (pBaseTypeRef) delete pBaseTypeRef;
#line 103 "../../../Source/Core/AST/ClassDecl.nll"
				return 0;
			}
		}
#line 107 "../../../Source/Core/AST/ClassDecl.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_LEFT) == 0)
		{
#line 109 "../../../Source/Core/AST/ClassDecl.nll"
			Console::Log("expected opening curly brace");
#line 110 "../../../Source/Core/AST/ClassDecl.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 111 "../../../Source/Core/AST/ClassDecl.nll"
			Assert::Plz(false);
			if (pTempOffset) delete pTempOffset;
			if (pClassDecl) delete pClassDecl;
			if (pBaseTypeRef) delete pBaseTypeRef;
#line 112 "../../../Source/Core/AST/ClassDecl.nll"
			return 0;
		}
#line 114 "../../../Source/Core/AST/ClassDecl.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 118 "../../../Source/Core/AST/ClassDecl.nll"
		pClassDecl->m_pFirstToken = pClassToken;
#line 119 "../../../Source/Core/AST/ClassDecl.nll"
		pClassDecl->m_pNameToken = pNameToken;
#line 120 "../../../Source/Core/AST/ClassDecl.nll"
		pClassDecl->m_pBaseTypeRef = pBaseTypeRef;
#line 121 "../../../Source/Core/AST/ClassDecl.nll"
		if (pBaseTypeRef != 0)
		{
			NumbatLogic::TypeRef* __276219192 = pBaseTypeRef;
#line 122 "../../../Source/Core/AST/ClassDecl.nll"
			pBaseTypeRef = 0;
#line 122 "../../../Source/Core/AST/ClassDecl.nll"
			pClassDecl->AddChild(__276219192);
		}
#line 125 "../../../Source/Core/AST/ClassDecl.nll"
		while (true)
		{
#line 127 "../../../Source/Core/AST/ClassDecl.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_CURLY_BRACE_RIGHT) != 0)
			{
#line 129 "../../../Source/Core/AST/ClassDecl.nll"
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 130 "../../../Source/Core/AST/ClassDecl.nll"
				break;
			}
			AST* pAST = 0;
#line 135 "../../../Source/Core/AST/ClassDecl.nll"
			pAST = MemberVarDecl::TryCreate(pTokenContainer, pTempOffset);
#line 136 "../../../Source/Core/AST/ClassDecl.nll"
			if (pAST != 0)
			{
				NumbatLogic::AST* __3057670627 = pAST;
#line 138 "../../../Source/Core/AST/ClassDecl.nll"
				pAST = 0;
#line 138 "../../../Source/Core/AST/ClassDecl.nll"
				pClassDecl->AddChild(__3057670627);
				if (pAST) delete pAST;
#line 139 "../../../Source/Core/AST/ClassDecl.nll"
				continue;
			}
#line 142 "../../../Source/Core/AST/ClassDecl.nll"
			pAST = MemberFunctionDecl::TryCreate(pTokenContainer, pTempOffset, pClassDecl);
#line 143 "../../../Source/Core/AST/ClassDecl.nll"
			if (pAST != 0)
			{
				NumbatLogic::AST* __3057736223 = pAST;
#line 145 "../../../Source/Core/AST/ClassDecl.nll"
				pAST = 0;
#line 145 "../../../Source/Core/AST/ClassDecl.nll"
				pClassDecl->AddChild(__3057736223);
				if (pAST) delete pAST;
#line 146 "../../../Source/Core/AST/ClassDecl.nll"
				continue;
			}
#line 149 "../../../Source/Core/AST/ClassDecl.nll"
			pAST = MemberClassDecl::TryCreate(pTokenContainer, pTempOffset, pClassDecl);
#line 150 "../../../Source/Core/AST/ClassDecl.nll"
			if (pAST != 0)
			{
				NumbatLogic::AST* __3057801819 = pAST;
#line 152 "../../../Source/Core/AST/ClassDecl.nll"
				pAST = 0;
#line 152 "../../../Source/Core/AST/ClassDecl.nll"
				pClassDecl->AddChild(__3057801819);
				if (pAST) delete pAST;
#line 153 "../../../Source/Core/AST/ClassDecl.nll"
				continue;
			}
#line 156 "../../../Source/Core/AST/ClassDecl.nll"
			pAST = MemberEnumDecl::TryCreate(pTokenContainer, pTempOffset);
#line 157 "../../../Source/Core/AST/ClassDecl.nll"
			if (pAST != 0)
			{
				NumbatLogic::AST* __3057801826 = pAST;
#line 159 "../../../Source/Core/AST/ClassDecl.nll"
				pAST = 0;
#line 159 "../../../Source/Core/AST/ClassDecl.nll"
				pClassDecl->AddChild(__3057801826);
				if (pAST) delete pAST;
#line 160 "../../../Source/Core/AST/ClassDecl.nll"
				continue;
			}
#line 163 "../../../Source/Core/AST/ClassDecl.nll"
			pAST = TorDecl::TryCreate(pTokenContainer, pTempOffset, pClassDecl);
#line 164 "../../../Source/Core/AST/ClassDecl.nll"
			if (pAST != 0)
			{
				NumbatLogic::AST* __3057867422 = pAST;
#line 166 "../../../Source/Core/AST/ClassDecl.nll"
				pAST = 0;
#line 166 "../../../Source/Core/AST/ClassDecl.nll"
				pClassDecl->AddChild(__3057867422);
				if (pAST) delete pAST;
#line 167 "../../../Source/Core/AST/ClassDecl.nll"
				continue;
			}
#line 170 "../../../Source/Core/AST/ClassDecl.nll"
			pAST = DelegateDecl::TryCreate(pTokenContainer, pTempOffset, pClassDecl);
#line 171 "../../../Source/Core/AST/ClassDecl.nll"
			if (pAST != 0)
			{
				NumbatLogic::AST* __3057933018 = pAST;
#line 173 "../../../Source/Core/AST/ClassDecl.nll"
				pAST = 0;
#line 173 "../../../Source/Core/AST/ClassDecl.nll"
				pClassDecl->AddChild(__3057933018);
				if (pAST) delete pAST;
#line 174 "../../../Source/Core/AST/ClassDecl.nll"
				continue;
			}
#line 177 "../../../Source/Core/AST/ClassDecl.nll"
			Console::Log("expected to parse somethting within class...");
#line 178 "../../../Source/Core/AST/ClassDecl.nll"
			Console::Log(pTokenContainer->StringifyOffset(pTempOffset));
#line 179 "../../../Source/Core/AST/ClassDecl.nll"
			Assert::Plz(false);
			if (pAST) delete pAST;
		}
#line 183 "../../../Source/Core/AST/ClassDecl.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::ClassDecl* __438903738 = pClassDecl;
#line 184 "../../../Source/Core/AST/ClassDecl.nll"
		pClassDecl = 0;
		if (pTempOffset) delete pTempOffset;
		if (pBaseTypeRef) delete pBaseTypeRef;
#line 184 "../../../Source/Core/AST/ClassDecl.nll"
		return __438903738;
	}

#line 187 "../../../Source/Core/AST/ClassDecl.nll"
	void ClassDecl::PreValidate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 189 "../../../Source/Core/AST/ClassDecl.nll"
		m_pNamespaceNode = pValidator->m_pCurrentNamespaceNode;
	}

#line 192 "../../../Source/Core/AST/ClassDecl.nll"
	void ClassDecl::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 194 "../../../Source/Core/AST/ClassDecl.nll"
		AddClassDeclReference(this, AST::OutputFile::SOURCE, false);
#line 196 "../../../Source/Core/AST/ClassDecl.nll"
		if (m_pBaseTypeRef != 0)
		{
			ValueType* pBaseValueType = m_pBaseTypeRef->CreateValueType(pValidator->m_pResolver);
#line 199 "../../../Source/Core/AST/ClassDecl.nll"
			if (pBaseValueType == 0)
			{
				InternalString* sTemp = new InternalString("Unknown base class: ");
#line 202 "../../../Source/Core/AST/ClassDecl.nll"
				sTemp->Append(m_pBaseTypeRef->m_pTypeToken->GetString());
#line 203 "../../../Source/Core/AST/ClassDecl.nll"
				pValidator->AddError(sTemp->GetExternalString(), m_pBaseTypeRef->m_pFirstToken->m_sFileName, m_pBaseTypeRef->m_pFirstToken->m_nLine, m_pBaseTypeRef->m_pFirstToken->m_nColumn);
				if (sTemp) delete sTemp;
				if (pBaseValueType) delete pBaseValueType;
#line 204 "../../../Source/Core/AST/ClassDecl.nll"
				return;
			}
#line 207 "../../../Source/Core/AST/ClassDecl.nll"
			if (pBaseValueType->m_eType != ValueType::Type::CLASS_DECL_VALUE)
			{
				InternalString* sTemp = new InternalString("Unknown base class is not a class: ");
#line 210 "../../../Source/Core/AST/ClassDecl.nll"
				sTemp->Append(m_pBaseTypeRef->m_pTypeToken->GetString());
#line 211 "../../../Source/Core/AST/ClassDecl.nll"
				pValidator->AddError(sTemp->GetExternalString(), m_pBaseTypeRef->m_pFirstToken->m_sFileName, m_pBaseTypeRef->m_pFirstToken->m_nLine, m_pBaseTypeRef->m_pFirstToken->m_nColumn);
				if (sTemp) delete sTemp;
			}
#line 214 "../../../Source/Core/AST/ClassDecl.nll"
			Assert::Plz(pBaseValueType->m_pClassDecl != 0);
#line 215 "../../../Source/Core/AST/ClassDecl.nll"
			AddClassDeclReference(pBaseValueType->m_pClassDecl, AST::OutputFile::HEADER, false);
			if (pBaseValueType) delete pBaseValueType;
		}
		{
			bool bHasOwnedPointer = false;
			bool bHasDefaultableVariable = false;
			bool bHasConstructor = false;
			bool bHasDestructor = false;
			AST* pChild = m_pFirstChild;
#line 226 "../../../Source/Core/AST/ClassDecl.nll"
			while (pChild != 0)
			{
#line 228 "../../../Source/Core/AST/ClassDecl.nll"
				if (pChild->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
				{
					MemberVarDecl* pMemberVarDecl = (MemberVarDecl*)(pChild);
					TypeRef* pTypeRef = pMemberVarDecl->m_pVarDecl->m_pTypeRef;
#line 232 "../../../Source/Core/AST/ClassDecl.nll"
					while (pTypeRef->m_pChildTypeRef != 0)
					{
#line 234 "../../../Source/Core/AST/ClassDecl.nll"
						pTypeRef = pTypeRef->m_pChildTypeRef;
					}
#line 236 "../../../Source/Core/AST/ClassDecl.nll"
					if (pTypeRef->m_ePointerType == TypeRef::PointerType::OWNED && !pMemberVarDecl->m_bStatic)
#line 237 "../../../Source/Core/AST/ClassDecl.nll"
						bHasOwnedPointer = true;
#line 240 "../../../Source/Core/AST/ClassDecl.nll"
					bHasDefaultableVariable = true;
				}
#line 243 "../../../Source/Core/AST/ClassDecl.nll"
				if (pChild->m_eType == AST::Type::AST_TOR_DECL)
				{
					TorDecl* pTorDecl = (TorDecl*)(pChild);
#line 246 "../../../Source/Core/AST/ClassDecl.nll"
					if (pTorDecl->m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DESTRUCT)
#line 247 "../../../Source/Core/AST/ClassDecl.nll"
						bHasDestructor = true;
#line 248 "../../../Source/Core/AST/ClassDecl.nll"
					if (pTorDecl->m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_CONSTRUCT)
					{
#line 250 "../../../Source/Core/AST/ClassDecl.nll"
						bHasConstructor = true;
#line 251 "../../../Source/Core/AST/ClassDecl.nll"
						if (pTorDecl->m_pScope != 0)
#line 252 "../../../Source/Core/AST/ClassDecl.nll"
							pTorDecl->m_pScope->AddChildFront(new MemberVarsSetDefaultStmt());
					}
				}
#line 256 "../../../Source/Core/AST/ClassDecl.nll"
				pChild = pChild->m_pNextSibling;
			}
#line 259 "../../../Source/Core/AST/ClassDecl.nll"
			if (bHasDefaultableVariable && !bHasConstructor)
			{
#line 261 "../../../Source/Core/AST/ClassDecl.nll"
				m_pConstructorAccessLevelToken = new Token();
#line 262 "../../../Source/Core/AST/ClassDecl.nll"
				m_pConstructorAccessLevelToken->m_eType = Token::Type::TOKEN_KEYWORD_PUBLIC;
				AccessLevel* pAccessLevel = new AccessLevel();
#line 265 "../../../Source/Core/AST/ClassDecl.nll"
				pAccessLevel->m_eType = AST::Type::AST_ACCESS_LEVEL;
#line 266 "../../../Source/Core/AST/ClassDecl.nll"
				pAccessLevel->m_pFirstToken = m_pConstructorAccessLevelToken;
#line 268 "../../../Source/Core/AST/ClassDecl.nll"
				m_pConstructorTypeToken = new Token();
#line 269 "../../../Source/Core/AST/ClassDecl.nll"
				m_pConstructorTypeToken->m_eType = Token::Type::TOKEN_KEYWORD_CONSTRUCT;
				ParamDecl* pParamDecl = new ParamDecl();
#line 272 "../../../Source/Core/AST/ClassDecl.nll"
				pParamDecl->m_pFirstToken = m_pFirstToken;
				Scope* pScope = new Scope();
#line 275 "../../../Source/Core/AST/ClassDecl.nll"
				pScope->AddChild(new MemberVarsSetDefaultStmt());
				TorDecl* pTorDecl = new TorDecl();
#line 278 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->m_eType = AST::Type::AST_TOR_DECL;
#line 279 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->m_pParent = this;
#line 280 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->m_pParentClassDecl = this;
#line 281 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->m_pFirstToken = m_pFirstToken;
#line 282 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->m_pAccessLevel = pAccessLevel;
#line 283 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->m_pTypeToken = m_pConstructorTypeToken;
#line 284 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->m_pParamDecl = pParamDecl;
#line 285 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->m_pScope = pScope;
#line 286 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->m_sDisambiguate = "";
				NumbatLogic::AccessLevel* __866280737 = pAccessLevel;
#line 288 "../../../Source/Core/AST/ClassDecl.nll"
				pAccessLevel = 0;
#line 288 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->AddChild(__866280737);
				NumbatLogic::ParamDecl* __2030449163 = pParamDecl;
#line 289 "../../../Source/Core/AST/ClassDecl.nll"
				pParamDecl = 0;
#line 289 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->AddChild(__2030449163);
				NumbatLogic::Scope* __3578341519 = pScope;
#line 290 "../../../Source/Core/AST/ClassDecl.nll"
				pScope = 0;
#line 290 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->AddChild(__3578341519);
				NumbatLogic::TorDecl* __3664169497 = pTorDecl;
#line 292 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl = 0;
#line 292 "../../../Source/Core/AST/ClassDecl.nll"
				AddChild(__3664169497);
				if (pAccessLevel) delete pAccessLevel;
				if (pParamDecl) delete pParamDecl;
				if (pScope) delete pScope;
				if (pTorDecl) delete pTorDecl;
			}
#line 295 "../../../Source/Core/AST/ClassDecl.nll"
			if (bHasOwnedPointer && !bHasDestructor)
			{
#line 297 "../../../Source/Core/AST/ClassDecl.nll"
				m_pAccessLevelToken = new Token();
#line 298 "../../../Source/Core/AST/ClassDecl.nll"
				m_pAccessLevelToken->m_eType = Token::Type::TOKEN_KEYWORD_PUBLIC;
				AccessLevel* pAccessLevel = new AccessLevel();
#line 301 "../../../Source/Core/AST/ClassDecl.nll"
				pAccessLevel->m_eType = AST::Type::AST_ACCESS_LEVEL;
#line 302 "../../../Source/Core/AST/ClassDecl.nll"
				pAccessLevel->m_pFirstToken = m_pAccessLevelToken;
#line 304 "../../../Source/Core/AST/ClassDecl.nll"
				m_pTypeToken = new Token();
#line 305 "../../../Source/Core/AST/ClassDecl.nll"
				m_pTypeToken->m_eType = Token::Type::TOKEN_KEYWORD_DESTRUCT;
				ParamDecl* pParamDecl = new ParamDecl();
#line 308 "../../../Source/Core/AST/ClassDecl.nll"
				pParamDecl->m_pFirstToken = m_pFirstToken;
				Scope* pScope = new Scope();
				TorDecl* pTorDecl = new TorDecl();
#line 313 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->m_eType = AST::Type::AST_TOR_DECL;
#line 314 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->m_pParent = this;
#line 315 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->m_pParentClassDecl = this;
#line 316 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->m_pFirstToken = m_pFirstToken;
#line 317 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->m_pAccessLevel = pAccessLevel;
#line 318 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->m_pTypeToken = m_pTypeToken;
#line 319 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->m_pParamDecl = pParamDecl;
#line 320 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->m_pScope = pScope;
#line 321 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->m_sDisambiguate = "";
				NumbatLogic::AccessLevel* __874148643 = pAccessLevel;
#line 323 "../../../Source/Core/AST/ClassDecl.nll"
				pAccessLevel = 0;
#line 323 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->AddChild(__874148643);
				NumbatLogic::ParamDecl* __2038317069 = pParamDecl;
#line 324 "../../../Source/Core/AST/ClassDecl.nll"
				pParamDecl = 0;
#line 324 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->AddChild(__2038317069);
				NumbatLogic::Scope* __3586209425 = pScope;
#line 325 "../../../Source/Core/AST/ClassDecl.nll"
				pScope = 0;
#line 325 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl->AddChild(__3586209425);
				NumbatLogic::TorDecl* __3671971814 = pTorDecl;
#line 327 "../../../Source/Core/AST/ClassDecl.nll"
				pTorDecl = 0;
#line 327 "../../../Source/Core/AST/ClassDecl.nll"
				AddChild(__3671971814);
				if (pAccessLevel) delete pAccessLevel;
				if (pParamDecl) delete pParamDecl;
				if (pScope) delete pScope;
				if (pTorDecl) delete pTorDecl;
			}
		}
#line 331 "../../../Source/Core/AST/ClassDecl.nll"
		AST::Validate(pValidator, pParent);
	}

#line 337 "../../../Source/Core/AST/ClassDecl.nll"
	ClassDecl* ClassDecl::GetBaseClassDeclForScopeLookup(Resolver* pResolver)
	{
#line 339 "../../../Source/Core/AST/ClassDecl.nll"
		if (m_pBaseClassDecl != 0)
#line 340 "../../../Source/Core/AST/ClassDecl.nll"
			return m_pBaseClassDecl;
#line 341 "../../../Source/Core/AST/ClassDecl.nll"
		if (m_pBaseTypeRef == 0)
#line 342 "../../../Source/Core/AST/ClassDecl.nll"
			return 0;
		ClassDecl* pBase = m_pBaseTypeRef->GetFoundClassDecl();
#line 344 "../../../Source/Core/AST/ClassDecl.nll"
		if (pBase == 0 && m_pBaseTypeRef->m_pChildTypeRef != 0)
#line 345 "../../../Source/Core/AST/ClassDecl.nll"
			pBase = m_pBaseTypeRef->m_pChildTypeRef->GetFoundClassDecl();
#line 346 "../../../Source/Core/AST/ClassDecl.nll"
		if (pBase != 0)
		{
#line 348 "../../../Source/Core/AST/ClassDecl.nll"
			m_pBaseClassDecl = pBase;
#line 349 "../../../Source/Core/AST/ClassDecl.nll"
			return m_pBaseClassDecl;
		}
#line 352 "../../../Source/Core/AST/ClassDecl.nll"
		if (pResolver == 0 || m_pSymbolScope == 0)
#line 353 "../../../Source/Core/AST/ClassDecl.nll"
			return 0;
		SymbolScope* pParentScope = m_pSymbolScope->m_pParent;
#line 355 "../../../Source/Core/AST/ClassDecl.nll"
		if (pParentScope == 0)
#line 356 "../../../Source/Core/AST/ClassDecl.nll"
			return 0;
		const char* sBaseName = m_pBaseTypeRef->m_pTypeToken->GetString();
		Vector<Symbol*>* pCandidates = new Vector<Symbol*>();
#line 359 "../../../Source/Core/AST/ClassDecl.nll"
		pResolver->ResolveInScopeChainNoBaseClasses(sBaseName, pParentScope, pCandidates);
#line 360 "../../../Source/Core/AST/ClassDecl.nll"
		if (pCandidates->GetSize() == 1)
		{
			Symbol* pSym = pCandidates->Get(0);
#line 363 "../../../Source/Core/AST/ClassDecl.nll"
			if (pSym->m_eKind == Symbol::Kind::CLASS && pSym->m_pDeclAST != 0 && pSym->m_pDeclAST->m_eType == AST::Type::AST_CLASS_DECL)
			{
#line 365 "../../../Source/Core/AST/ClassDecl.nll"
				m_pBaseClassDecl = (ClassDecl*)(pSym->m_pDeclAST);
				if (pCandidates) delete pCandidates;
#line 366 "../../../Source/Core/AST/ClassDecl.nll"
				return m_pBaseClassDecl;
			}
#line 369 "../../../Source/Core/AST/ClassDecl.nll"
			if (pSym->m_eKind == Symbol::Kind::NAMESPACE && pSym->m_pScope != 0 && m_pBaseTypeRef->m_pChildTypeRef != 0)
			{
				const char* sChildName = m_pBaseTypeRef->m_pChildTypeRef->m_pTypeToken->GetString();
				Vector<Symbol*>* pChildCandidates = new Vector<Symbol*>();
#line 373 "../../../Source/Core/AST/ClassDecl.nll"
				pResolver->ResolveInScopeChainNoBaseClasses(sChildName, pSym->m_pScope, pChildCandidates);
#line 374 "../../../Source/Core/AST/ClassDecl.nll"
				if (pChildCandidates->GetSize() == 1)
				{
					Symbol* pChildSym = pChildCandidates->Get(0);
#line 377 "../../../Source/Core/AST/ClassDecl.nll"
					if (pChildSym->m_eKind == Symbol::Kind::CLASS && pChildSym->m_pDeclAST != 0 && pChildSym->m_pDeclAST->m_eType == AST::Type::AST_CLASS_DECL)
					{
#line 379 "../../../Source/Core/AST/ClassDecl.nll"
						m_pBaseClassDecl = (ClassDecl*)(pChildSym->m_pDeclAST);
						if (pChildCandidates) delete pChildCandidates;
						if (pCandidates) delete pCandidates;
#line 380 "../../../Source/Core/AST/ClassDecl.nll"
						return m_pBaseClassDecl;
					}
				}
				if (pChildCandidates) delete pChildCandidates;
			}
		}
		if (pCandidates) delete pCandidates;
#line 385 "../../../Source/Core/AST/ClassDecl.nll"
		return 0;
	}

#line 388 "../../../Source/Core/AST/ClassDecl.nll"
	ClassDecl* ClassDecl::GetBaseClassDecl(Validator* pValidator)
	{
#line 390 "../../../Source/Core/AST/ClassDecl.nll"
		if (m_pBaseClassDecl != 0)
#line 391 "../../../Source/Core/AST/ClassDecl.nll"
			return m_pBaseClassDecl;
		Validator* pV = pValidator;
#line 394 "../../../Source/Core/AST/ClassDecl.nll"
		if (pV == 0)
		{
			Project* pProject = GetProject();
#line 397 "../../../Source/Core/AST/ClassDecl.nll"
			if (pProject != 0)
#line 398 "../../../Source/Core/AST/ClassDecl.nll"
				pV = pProject->m_pValidator;
		}
#line 400 "../../../Source/Core/AST/ClassDecl.nll"
		if (m_pBaseTypeRef != 0 && m_pParent != 0 && pV != 0)
		{
			ValueType* pBaseValueType = m_pBaseTypeRef->CreateValueType(pV->m_pResolver);
#line 403 "../../../Source/Core/AST/ClassDecl.nll"
			if (pBaseValueType != 0)
			{
#line 405 "../../../Source/Core/AST/ClassDecl.nll"
				m_pBaseClassDecl = pBaseValueType->m_pClassDecl;
				if (pBaseValueType) delete pBaseValueType;
#line 406 "../../../Source/Core/AST/ClassDecl.nll"
				return m_pBaseClassDecl;
			}
			if (pBaseValueType) delete pBaseValueType;
		}
#line 409 "../../../Source/Core/AST/ClassDecl.nll"
		return 0;
	}

#line 412 "../../../Source/Core/AST/ClassDecl.nll"
	void ClassDecl::AppendFullyQualifiedName(InternalString* sOut)
	{
#line 414 "../../../Source/Core/AST/ClassDecl.nll"
		if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
		{
			MemberClassDecl* pMember = (MemberClassDecl*)(m_pParent);
#line 417 "../../../Source/Core/AST/ClassDecl.nll"
			pMember->m_pParentClassDecl->AppendFullyQualifiedName(sOut);
#line 418 "../../../Source/Core/AST/ClassDecl.nll"
			sOut->Append("::");
		}
		else
#line 420 "../../../Source/Core/AST/ClassDecl.nll"
			if (m_pNamespaceNode != 0 && m_pNamespaceNode->m_sName != 0)
			{
#line 422 "../../../Source/Core/AST/ClassDecl.nll"
				m_pNamespaceNode->AppendFullyQualifiedName(sOut);
#line 423 "../../../Source/Core/AST/ClassDecl.nll"
				sOut->Append("::");
			}
#line 425 "../../../Source/Core/AST/ClassDecl.nll"
		sOut->Append(m_pNameToken->GetString());
	}

#line 428 "../../../Source/Core/AST/ClassDecl.nll"
	void ClassDecl::StringifyTemplateThing(Language eLanguage, OutputFile eOutputFile, OutputBuilder* pOutputBuilder)
	{
#line 430 "../../../Source/Core/AST/ClassDecl.nll"
		pOutputBuilder->m_sOut->AppendString("template <class ");
#line 431 "../../../Source/Core/AST/ClassDecl.nll"
		for (int i = 0; i < m_pGenericTypeDeclVector->GetSize(); i++)
		{
#line 433 "../../../Source/Core/AST/ClassDecl.nll"
			if (i > 0)
#line 434 "../../../Source/Core/AST/ClassDecl.nll"
				pOutputBuilder->m_sOut->Append(", ");
			GenericTypeDecl* pGenericTypeDecl = m_pGenericTypeDeclVector->Get(i);
#line 436 "../../../Source/Core/AST/ClassDecl.nll"
			pGenericTypeDecl->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}
#line 438 "../../../Source/Core/AST/ClassDecl.nll"
		pOutputBuilder->m_sOut->AppendString(">");
	}

#line 441 "../../../Source/Core/AST/ClassDecl.nll"
	void ClassDecl::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 443 "../../../Source/Core/AST/ClassDecl.nll"
		pOutputBuilder->UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 445 "../../../Source/Core/AST/ClassDecl.nll"
		if (!(eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE))
		{
#line 447 "../../../Source/Core/AST/ClassDecl.nll"
			if (eLanguage == AST::Language::CPP)
			{
#line 449 "../../../Source/Core/AST/ClassDecl.nll"
				if (m_pGenericTypeDeclVector->GetSize() > 0)
				{
#line 451 "../../../Source/Core/AST/ClassDecl.nll"
					Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 452 "../../../Source/Core/AST/ClassDecl.nll"
					StringifyTemplateThing(eLanguage, eOutputFile, pOutputBuilder);
#line 453 "../../../Source/Core/AST/ClassDecl.nll"
					pOutputBuilder->m_sOut->AppendString("\n");
				}
			}
#line 457 "../../../Source/Core/AST/ClassDecl.nll"
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 458 "../../../Source/Core/AST/ClassDecl.nll"
			pOutputBuilder->m_sOut->Append("class ");
#line 459 "../../../Source/Core/AST/ClassDecl.nll"
			m_pNameToken->Stringify(pOutputBuilder->m_sOut);
#line 461 "../../../Source/Core/AST/ClassDecl.nll"
			if (eLanguage == AST::Language::CS || eLanguage == AST::Language::NLL_DEF)
			{
#line 463 "../../../Source/Core/AST/ClassDecl.nll"
				if (m_pGenericTypeDeclVector->GetSize() > 0)
				{
#line 465 "../../../Source/Core/AST/ClassDecl.nll"
					pOutputBuilder->m_sOut->AppendChar('<');
#line 466 "../../../Source/Core/AST/ClassDecl.nll"
					for (int i = 0; i < m_pGenericTypeDeclVector->GetSize(); i++)
					{
#line 468 "../../../Source/Core/AST/ClassDecl.nll"
						if (i > 0)
#line 469 "../../../Source/Core/AST/ClassDecl.nll"
							pOutputBuilder->m_sOut->Append(", ");
						GenericTypeDecl* pGenericTypeDecl = m_pGenericTypeDeclVector->Get(i);
#line 471 "../../../Source/Core/AST/ClassDecl.nll"
						pGenericTypeDecl->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
					}
#line 473 "../../../Source/Core/AST/ClassDecl.nll"
					pOutputBuilder->m_sOut->AppendChar('>');
				}
			}
#line 477 "../../../Source/Core/AST/ClassDecl.nll"
			if (m_pBaseTypeRef != 0)
			{
#line 479 "../../../Source/Core/AST/ClassDecl.nll"
				pOutputBuilder->m_sOut->Append(" : ");
#line 480 "../../../Source/Core/AST/ClassDecl.nll"
				if (eLanguage == AST::Language::CPP)
#line 481 "../../../Source/Core/AST/ClassDecl.nll"
					pOutputBuilder->m_sOut->Append("public ");
#line 482 "../../../Source/Core/AST/ClassDecl.nll"
				m_pBaseTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
#line 485 "../../../Source/Core/AST/ClassDecl.nll"
			if (eLanguage == AST::Language::CS && m_bDisposable)
			{
#line 487 "../../../Source/Core/AST/ClassDecl.nll"
				if (m_pBaseTypeRef == 0)
#line 488 "../../../Source/Core/AST/ClassDecl.nll"
					pOutputBuilder->m_sOut->Append(" : ");
				else
#line 490 "../../../Source/Core/AST/ClassDecl.nll"
					pOutputBuilder->m_sOut->Append(", ");
#line 491 "../../../Source/Core/AST/ClassDecl.nll"
				pOutputBuilder->m_sOut->Append("System.IDisposable");
			}
#line 494 "../../../Source/Core/AST/ClassDecl.nll"
			if (eLanguage == AST::Language::CS && m_pGenericTypeDeclVector->GetSize() > 0)
			{
#line 496 "../../../Source/Core/AST/ClassDecl.nll"
				for (int i = 0; i < m_pGenericTypeDeclVector->GetSize(); i++)
				{
#line 498 "../../../Source/Core/AST/ClassDecl.nll"
					if (m_pGenericTypeDeclVector->GetSize() == 1)
					{
#line 500 "../../../Source/Core/AST/ClassDecl.nll"
						pOutputBuilder->m_sOut->AppendChar(' ');
					}
					else
					{
#line 504 "../../../Source/Core/AST/ClassDecl.nll"
						pOutputBuilder->m_sOut->Append("\n");
#line 505 "../../../Source/Core/AST/ClassDecl.nll"
						Util::Pad(nDepth + 1, pOutputBuilder->m_sOut);
					}
#line 508 "../../../Source/Core/AST/ClassDecl.nll"
					pOutputBuilder->m_sOut->Append("where ");
					GenericTypeDecl* pGenericTypeDecl = m_pGenericTypeDeclVector->Get(i);
#line 510 "../../../Source/Core/AST/ClassDecl.nll"
					pGenericTypeDecl->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 511 "../../../Source/Core/AST/ClassDecl.nll"
					pOutputBuilder->m_sOut->Append(" : class");
				}
			}
#line 515 "../../../Source/Core/AST/ClassDecl.nll"
			pOutputBuilder->m_sOut->Append("\n");
#line 516 "../../../Source/Core/AST/ClassDecl.nll"
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 517 "../../../Source/Core/AST/ClassDecl.nll"
			pOutputBuilder->m_sOut->Append("{\n");
#line 519 "../../../Source/Core/AST/ClassDecl.nll"
			nDepth++;
		}
		AST* pMember = m_pFirstChild;
#line 523 "../../../Source/Core/AST/ClassDecl.nll"
		while (pMember != 0)
		{
#line 525 "../../../Source/Core/AST/ClassDecl.nll"
			if (pMember != m_pBaseTypeRef)
#line 526 "../../../Source/Core/AST/ClassDecl.nll"
				pMember->Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
#line 527 "../../../Source/Core/AST/ClassDecl.nll"
			pMember = pMember->m_pNextSibling;
		}
#line 530 "../../../Source/Core/AST/ClassDecl.nll"
		if (!(eLanguage == AST::Language::CPP && eOutputFile == AST::OutputFile::SOURCE))
		{
#line 532 "../../../Source/Core/AST/ClassDecl.nll"
			nDepth--;
#line 534 "../../../Source/Core/AST/ClassDecl.nll"
			Util::Pad(nDepth, pOutputBuilder->m_sOut);
#line 535 "../../../Source/Core/AST/ClassDecl.nll"
			if (eLanguage == AST::Language::CPP)
#line 536 "../../../Source/Core/AST/ClassDecl.nll"
				pOutputBuilder->m_sOut->Append("};\n");
			else
#line 538 "../../../Source/Core/AST/ClassDecl.nll"
				pOutputBuilder->m_sOut->Append("}\n");
		}
	}

#line 4 "../../../Source/Core/AST/ClassDecl.nll"
	ClassDecl::~ClassDecl()
	{
		if (m_pGenericTypeDeclVector) delete m_pGenericTypeDeclVector;
		if (m_pAccessLevelToken) delete m_pAccessLevelToken;
		if (m_pTypeToken) delete m_pTypeToken;
		if (m_pConstructorAccessLevelToken) delete m_pConstructorAccessLevelToken;
		if (m_pConstructorTypeToken) delete m_pConstructorTypeToken;
	}

}

