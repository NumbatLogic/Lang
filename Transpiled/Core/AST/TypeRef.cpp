#include "TypeRef.hpp"
#include "AST.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../Semantic/Symbol.hpp"
#include "../Validator.hpp"
#include "../Semantic/Resolver.hpp"
#include "../Project.hpp"
#include "../ValueType.hpp"
#include "../OutputBuilder.hpp"
#include "ClassDecl.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "MemberClassDecl.hpp"
#include "MemberEnumDecl.hpp"

namespace NumbatLogic
{
	class AST;
	class TypeRef;
	template <class T>
	class Vector;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class Console;
	class Assert;
	class InternalString;
	class ClassDecl;
	class Symbol;
	class Validator;
	class Resolver;
	class Project;
	class ValueType;
	class OutputBuilder;
	template <class T>
	class OwnedVector;
	class MemberClassDecl;
	class GenericTypeDecl;
	class EnumDecl;
	class MemberEnumDecl;
	class EnumDeclValue;
	class DelegateDecl;
}
#line 0 "../../../Source/Core/AST/TypeRef.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/TypeRef.nll"
#line 24 "../../../Source/Core/AST/TypeRef.nll"
	TypeRef::TypeRef()
	{
		m_bConst = false;
		m_bRef = false;
		m_pTypeToken = 0;
		m_pGenericTypeRefVector = 0;
		m_pChildTypeRef = 0;
		m_ePointerType = PointerType::SHARED;
		m_pCloneToken = 0;
		m_pFoundType = 0;
#line 26 "../../../Source/Core/AST/TypeRef.nll"
		m_eType = AST::Type::AST_TYPE_REF;
#line 27 "../../../Source/Core/AST/TypeRef.nll"
		m_pGenericTypeRefVector = new Vector<TypeRef*>();
#line 28 "../../../Source/Core/AST/TypeRef.nll"
		m_bConst = false;
#line 29 "../../../Source/Core/AST/TypeRef.nll"
		m_bRef = false;
	}

#line 32 "../../../Source/Core/AST/TypeRef.nll"
	TypeRef* TypeRef::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		bool bConst = false;
		Token* pConstToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_CONST);
#line 38 "../../../Source/Core/AST/TypeRef.nll"
		if (pConstToken != 0)
		{
#line 40 "../../../Source/Core/AST/TypeRef.nll"
			bConst = true;
#line 41 "../../../Source/Core/AST/TypeRef.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		}
		bool bRef = false;
		Token* pRefToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_REF);
#line 46 "../../../Source/Core/AST/TypeRef.nll"
		if (pRefToken != 0)
		{
#line 48 "../../../Source/Core/AST/TypeRef.nll"
			bRef = true;
#line 49 "../../../Source/Core/AST/TypeRef.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		}
		Token* pTypeToken = pTokenContainer->Peek(pTempOffset);
#line 53 "../../../Source/Core/AST/TypeRef.nll"
		if (pTypeToken == 0 || pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_VOID && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_INT && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_BOOL && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_UNICHAR && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_STRING && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_UINT && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_UINT8 && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_UINT16 && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_UINT32 && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_UINT64 && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_INT8 && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_INT16 && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_INT32 && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_DOUBLE && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_FLOAT && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_VOIDPTR && pTypeToken->m_eType != Token::Type::TOKEN_IDENTIFIER)
		{
			if (pTempOffset) delete pTempOffset;
#line 71 "../../../Source/Core/AST/TypeRef.nll"
			return 0;
		}
#line 72 "../../../Source/Core/AST/TypeRef.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		TypeRef* pTypeRef = new TypeRef();
#line 77 "../../../Source/Core/AST/TypeRef.nll"
		pTypeRef->m_pFirstToken = pTypeToken;
#line 78 "../../../Source/Core/AST/TypeRef.nll"
		if (pConstToken != 0)
#line 79 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef->m_pFirstToken = pConstToken;
#line 80 "../../../Source/Core/AST/TypeRef.nll"
		pTypeRef->m_bConst = bConst;
#line 81 "../../../Source/Core/AST/TypeRef.nll"
		pTypeRef->m_pTypeToken = pTypeToken;
#line 82 "../../../Source/Core/AST/TypeRef.nll"
		pTypeRef->m_pChildTypeRef = 0;
#line 83 "../../../Source/Core/AST/TypeRef.nll"
		pTypeRef->m_ePointerType = PointerType::SHARED;
#line 85 "../../../Source/Core/AST/TypeRef.nll"
		pTypeRef->m_bRef = bRef;
#line 87 "../../../Source/Core/AST/TypeRef.nll"
		if (pTypeToken->m_eType == Token::Type::TOKEN_IDENTIFIER)
		{
			Token* pAngleBracketLeft = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_ANGLE_BRACKET_LEFT);
#line 90 "../../../Source/Core/AST/TypeRef.nll"
			if (pAngleBracketLeft != 0)
			{
#line 92 "../../../Source/Core/AST/TypeRef.nll"
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 94 "../../../Source/Core/AST/TypeRef.nll"
				while (true)
				{
#line 96 "../../../Source/Core/AST/TypeRef.nll"
					if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_ANGLE_BRACKET_RIGHT) != 0)
					{
#line 98 "../../../Source/Core/AST/TypeRef.nll"
						pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 99 "../../../Source/Core/AST/TypeRef.nll"
						break;
					}
					TypeRef* pGenericTypeRef = TypeRef::TryCreate(pTokenContainer, pTempOffset);
#line 103 "../../../Source/Core/AST/TypeRef.nll"
					if (pGenericTypeRef == 0)
					{
#line 105 "../../../Source/Core/AST/TypeRef.nll"
						Console::Log("expected inner TypeRef");
#line 106 "../../../Source/Core/AST/TypeRef.nll"
						Assert::Plz(false);
					}
#line 109 "../../../Source/Core/AST/TypeRef.nll"
					pTypeRef->m_pGenericTypeRefVector->PushBack(pGenericTypeRef);
					NumbatLogic::TypeRef* __3744382558 = pGenericTypeRef;
#line 110 "../../../Source/Core/AST/TypeRef.nll"
					pGenericTypeRef = 0;
#line 110 "../../../Source/Core/AST/TypeRef.nll"
					pTypeRef->AddChild(__3744382558);
#line 112 "../../../Source/Core/AST/TypeRef.nll"
					if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_ANGLE_BRACKET_RIGHT) != 0)
					{
						if (pGenericTypeRef) delete pGenericTypeRef;
#line 113 "../../../Source/Core/AST/TypeRef.nll"
						continue;
					}
#line 115 "../../../Source/Core/AST/TypeRef.nll"
					if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COMMA) == 0)
					{
						InternalString* sTemp = new InternalString("expected comma ");
#line 118 "../../../Source/Core/AST/TypeRef.nll"
						sTemp->Append(pTokenContainer->StringifyOffset(pTempOffset));
#line 119 "../../../Source/Core/AST/TypeRef.nll"
						Console::Log(sTemp->GetExternalString());
#line 120 "../../../Source/Core/AST/TypeRef.nll"
						Assert::Plz(false);
						if (sTemp) delete sTemp;
					}
#line 122 "../../../Source/Core/AST/TypeRef.nll"
					pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
					if (pGenericTypeRef) delete pGenericTypeRef;
				}
			}
		}
#line 127 "../../../Source/Core/AST/TypeRef.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_DOUBLE_COLON) != 0)
		{
#line 129 "../../../Source/Core/AST/TypeRef.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
			TypeRef* pChildTypeRef = TypeRef::TryCreate(pTokenContainer, pTempOffset);
#line 132 "../../../Source/Core/AST/TypeRef.nll"
			if (pChildTypeRef == 0)
			{
				InternalString* sTemp = new InternalString("expected child TypeRef... ");
#line 135 "../../../Source/Core/AST/TypeRef.nll"
				sTemp->Append(pTokenContainer->StringifyOffset(pTempOffset));
#line 136 "../../../Source/Core/AST/TypeRef.nll"
				Console::Log(sTemp->GetExternalString());
#line 137 "../../../Source/Core/AST/TypeRef.nll"
				Assert::Plz(false);
				if (sTemp) delete sTemp;
				if (pChildTypeRef) delete pChildTypeRef;
				if (pTempOffset) delete pTempOffset;
				if (pTypeRef) delete pTypeRef;
#line 138 "../../../Source/Core/AST/TypeRef.nll"
				return 0;
			}
#line 141 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef->m_pChildTypeRef = pChildTypeRef;
			NumbatLogic::TypeRef* __1983801666 = pChildTypeRef;
#line 142 "../../../Source/Core/AST/TypeRef.nll"
			pChildTypeRef = 0;
#line 142 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef->AddChild(__1983801666);
			if (pChildTypeRef) delete pChildTypeRef;
		}
		else
#line 149 "../../../Source/Core/AST/TypeRef.nll"
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_STAR) != 0)
			{
#line 151 "../../../Source/Core/AST/TypeRef.nll"
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 152 "../../../Source/Core/AST/TypeRef.nll"
				pTypeRef->m_ePointerType = PointerType::OWNED;
			}
			else
#line 154 "../../../Source/Core/AST/TypeRef.nll"
				if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_STAR_DOUBLE) != 0)
				{
#line 156 "../../../Source/Core/AST/TypeRef.nll"
					pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 157 "../../../Source/Core/AST/TypeRef.nll"
					pTypeRef->m_ePointerType = PointerType::TRANSITON;
				}
#line 163 "../../../Source/Core/AST/TypeRef.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::TypeRef* __967910118 = pTypeRef;
#line 164 "../../../Source/Core/AST/TypeRef.nll"
		pTypeRef = 0;
		if (pTempOffset) delete pTempOffset;
#line 164 "../../../Source/Core/AST/TypeRef.nll"
		return __967910118;
	}

#line 168 "../../../Source/Core/AST/TypeRef.nll"
	ClassDecl* TypeRef::GetFoundClassDecl()
	{
#line 170 "../../../Source/Core/AST/TypeRef.nll"
		if (m_pFoundType != 0 && m_pFoundType->m_eType == AST::Type::AST_CLASS_DECL)
#line 171 "../../../Source/Core/AST/TypeRef.nll"
			return (ClassDecl*)(m_pFoundType);
#line 172 "../../../Source/Core/AST/TypeRef.nll"
		return 0;
	}

#line 175 "../../../Source/Core/AST/TypeRef.nll"
	void TypeRef::ValidateClassDecl(Validator* pValidator, ClassDecl* pClassDecl, TypeRef* pThisOrChild)
	{
#line 177 "../../../Source/Core/AST/TypeRef.nll"
		if (m_pParent != 0)
		{
#line 181 "../../../Source/Core/AST/TypeRef.nll"
			if (m_pParent->m_eType == AST::Type::AST_NEW_EXP)
			{
			}
			else
#line 186 "../../../Source/Core/AST/TypeRef.nll"
				if (m_pParent->m_eType == AST::Type::AST_TYPE_REF)
				{
					TypeRef* pSubParentTypeRef = (TypeRef*)(m_pParent);
#line 191 "../../../Source/Core/AST/TypeRef.nll"
					AddClassDeclReference(pClassDecl, AST::OutputFile::HEADER, true);
#line 194 "../../../Source/Core/AST/TypeRef.nll"
					if (pSubParentTypeRef->m_pChildTypeRef != this)
					{
						AST* pParentParent = m_pParent->m_pParent;
#line 197 "../../../Source/Core/AST/TypeRef.nll"
						if (pParentParent != 0)
						{
#line 199 "../../../Source/Core/AST/TypeRef.nll"
							if (pParentParent->m_eType == AST::Type::AST_NEW_EXP)
#line 200 "../../../Source/Core/AST/TypeRef.nll"
								AddClassDeclReference(pClassDecl, AST::OutputFile::SOURCE, false);
							AST* pParentParentParent = pParentParent->m_pParent;
#line 203 "../../../Source/Core/AST/TypeRef.nll"
							if (pParentParentParent != 0)
							{
#line 207 "../../../Source/Core/AST/TypeRef.nll"
								if (pParentParentParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
#line 208 "../../../Source/Core/AST/TypeRef.nll"
									AddClassDeclReference(pClassDecl, AST::OutputFile::HEADER, false);
								else
#line 209 "../../../Source/Core/AST/TypeRef.nll"
									if (pParentParentParent->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
#line 210 "../../../Source/Core/AST/TypeRef.nll"
										AddClassDeclReference(pClassDecl, AST::OutputFile::HEADER, true);
									else
#line 212 "../../../Source/Core/AST/TypeRef.nll"
										AddClassDeclReference(pClassDecl, AST::OutputFile::SOURCE, true);
							}
						}
					}
				}
				else
				{
					AST::OutputFile eOutputFile = AST::OutputFile::SOURCE;
					bool bForwardReference = pThisOrChild->m_pChildTypeRef == 0 && m_pGenericTypeRefVector->GetSize() == 0;
					AST* pParentParent = m_pParent->m_pParent;
#line 223 "../../../Source/Core/AST/TypeRef.nll"
					if (pParentParent != 0)
					{
#line 225 "../../../Source/Core/AST/TypeRef.nll"
						if (pParentParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL || pParentParent->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
						{
#line 227 "../../../Source/Core/AST/TypeRef.nll"
							eOutputFile = AST::OutputFile::HEADER;
						}
						else
						{
							AST* pParentParentParent = pParentParent->m_pParent;
#line 232 "../../../Source/Core/AST/TypeRef.nll"
							if (pParentParentParent != 0)
							{
								AST* pParentParentParentParent = pParentParentParent->m_pParent;
#line 235 "../../../Source/Core/AST/TypeRef.nll"
								if (pParentParentParentParent != 0)
								{
#line 237 "../../../Source/Core/AST/TypeRef.nll"
									if (m_pParent->m_eType == AST::Type::AST_VAR_DECL && pParentParent->m_eType == AST::Type::AST_PARAM_DECL && (pParentParentParent->m_eType == AST::Type::AST_FUNCTION_DECL && pParentParentParentParent->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL || pParentParentParent->m_eType == AST::Type::AST_TOR_DECL || (pParentParentParent->m_eType == AST::Type::AST_FUNCTION_DECL && pParentParentParentParent->m_eType == AST::Type::DELEGATE_DECL)))
#line 238 "../../../Source/Core/AST/TypeRef.nll"
										eOutputFile = AST::OutputFile::HEADER;
								}
							}
						}
					}
#line 244 "../../../Source/Core/AST/TypeRef.nll"
					AddClassDeclReference(pClassDecl, eOutputFile, bForwardReference);
				}
		}
	}

#line 249 "../../../Source/Core/AST/TypeRef.nll"
	void TypeRef::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
#line 251 "../../../Source/Core/AST/TypeRef.nll"
		if (m_pTypeToken->m_eType == Token::Type::TOKEN_IDENTIFIER)
		{
			AST* pType = 0;
			bool bResolverTypeAmbiguous = false;
			const char* sTypeName = m_pTypeToken->GetString();
			TypeRef* pParentTypeRef = 0;
#line 263 "../../../Source/Core/AST/TypeRef.nll"
			if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_TYPE_REF)
			{
#line 265 "../../../Source/Core/AST/TypeRef.nll"
				pParentTypeRef = (TypeRef*)(m_pParent);
#line 266 "../../../Source/Core/AST/TypeRef.nll"
				if (pParentTypeRef->m_pChildTypeRef != this)
#line 267 "../../../Source/Core/AST/TypeRef.nll"
					pParentTypeRef = 0;
			}
			Vector<Symbol*>* pCandidates = new Vector<Symbol*>();
			AST* pResolverBase = this;
#line 272 "../../../Source/Core/AST/TypeRef.nll"
			if (pParentTypeRef != 0 && pParentTypeRef->m_pFoundType != 0)
#line 273 "../../../Source/Core/AST/TypeRef.nll"
				pResolverBase = pParentTypeRef->m_pFoundType;
#line 274 "../../../Source/Core/AST/TypeRef.nll"
			pValidator->m_pResolver->ResolveFromNode(pResolverBase, sTypeName, pCandidates);
			Vector<Symbol*>* pTypeLike = new Vector<Symbol*>();
#line 277 "../../../Source/Core/AST/TypeRef.nll"
			for (int i = 0; i < pCandidates->GetSize(); i++)
			{
				Symbol* pSym = pCandidates->Get(i);
#line 280 "../../../Source/Core/AST/TypeRef.nll"
				if (pSym->m_eKind == Symbol::Kind::CLASS || pSym->m_eKind == Symbol::Kind::ENUM || pSym->m_eKind == Symbol::Kind::GENERIC_PARAM || pSym->m_eKind == Symbol::Kind::DELEGATE || pSym->m_eKind == Symbol::Kind::NAMESPACE)
				{
#line 286 "../../../Source/Core/AST/TypeRef.nll"
					pTypeLike->PushBack(pSym);
				}
			}
#line 290 "../../../Source/Core/AST/TypeRef.nll"
			if (pTypeLike->GetSize() == 1)
			{
				Symbol* pSymbol = pTypeLike->Get(0);
#line 293 "../../../Source/Core/AST/TypeRef.nll"
				if (pSymbol->m_pDeclAST != 0)
				{
#line 295 "../../../Source/Core/AST/TypeRef.nll"
					pType = pSymbol->m_pDeclAST;
#line 296 "../../../Source/Core/AST/TypeRef.nll"
					m_pFoundType = pType;
				}
			}
			else
#line 299 "../../../Source/Core/AST/TypeRef.nll"
				if (pTypeLike->GetSize() > 1)
#line 300 "../../../Source/Core/AST/TypeRef.nll"
					bResolverTypeAmbiguous = true;
#line 302 "../../../Source/Core/AST/TypeRef.nll"
			if (pType == 0)
			{
#line 304 "../../../Source/Core/AST/TypeRef.nll"
				if (bResolverTypeAmbiguous)
				{
					InternalString* sAmbiguous = new InternalString("Ambiguous type (multiple declarations in scope): ");
#line 307 "../../../Source/Core/AST/TypeRef.nll"
					sAmbiguous->Append(sTypeName);
#line 308 "../../../Source/Core/AST/TypeRef.nll"
					pValidator->AddError(sAmbiguous->GetExternalString(), m_pTypeToken->m_sFileName, m_pTypeToken->m_nLine, m_pTypeToken->m_nColumn);
					if (sAmbiguous) delete sAmbiguous;
				}
				else
				{
					InternalString* sTemp = new InternalString("Unknown type: ");
#line 313 "../../../Source/Core/AST/TypeRef.nll"
					sTemp->Append(sTypeName);
					TypeRef* pSubParentTypeRef = 0;
#line 316 "../../../Source/Core/AST/TypeRef.nll"
					if (m_pParent->m_eType == AST::Type::AST_TYPE_REF)
					{
#line 318 "../../../Source/Core/AST/TypeRef.nll"
						pSubParentTypeRef = (TypeRef*)(m_pParent);
#line 319 "../../../Source/Core/AST/TypeRef.nll"
						if (pSubParentTypeRef->m_pChildTypeRef != this)
#line 320 "../../../Source/Core/AST/TypeRef.nll"
							pSubParentTypeRef = 0;
					}
#line 322 "../../../Source/Core/AST/TypeRef.nll"
					if (pSubParentTypeRef != 0 && pSubParentTypeRef->m_pFoundType != 0)
#line 323 "../../../Source/Core/AST/TypeRef.nll"
						sTemp->Append(" -- had parent");
#line 325 "../../../Source/Core/AST/TypeRef.nll"
					pValidator->AddError(sTemp->GetExternalString(), m_pTypeToken->m_sFileName, m_pTypeToken->m_nLine, m_pTypeToken->m_nColumn);
					if (sTemp) delete sTemp;
				}
				if (pCandidates) delete pCandidates;
				if (pTypeLike) delete pTypeLike;
#line 327 "../../../Source/Core/AST/TypeRef.nll"
				return;
			}
#line 329 "../../../Source/Core/AST/TypeRef.nll"
			if (pType->m_eType == AST::Type::AST_CLASS_DECL)
			{
				ClassDecl* pClassDecl = (ClassDecl*)(pType);
#line 332 "../../../Source/Core/AST/TypeRef.nll"
				ValidateClassDecl(pValidator, pClassDecl, this);
#line 334 "../../../Source/Core/AST/TypeRef.nll"
				if (m_pChildTypeRef != 0)
				{
#line 336 "../../../Source/Core/AST/TypeRef.nll"
					m_pChildTypeRef->Validate(pValidator, 0);
				}
			}
			else
#line 339 "../../../Source/Core/AST/TypeRef.nll"
				if (pType->m_eType == AST::Type::NAMESPACE_DECL)
				{
#line 345 "../../../Source/Core/AST/TypeRef.nll"
					if (m_pChildTypeRef == 0)
					{
#line 347 "../../../Source/Core/AST/TypeRef.nll"
						pValidator->AddError("Namespace typeref musttt have a child???", m_pTypeToken->m_sFileName, m_pTypeToken->m_nLine, m_pTypeToken->m_nColumn);
						if (pCandidates) delete pCandidates;
						if (pTypeLike) delete pTypeLike;
#line 348 "../../../Source/Core/AST/TypeRef.nll"
						return;
					}
#line 351 "../../../Source/Core/AST/TypeRef.nll"
					if (m_pChildTypeRef->m_pTypeToken->m_eType != Token::Type::TOKEN_IDENTIFIER)
					{
#line 353 "../../../Source/Core/AST/TypeRef.nll"
						pValidator->AddError("child must be IDENTIFIER", m_pChildTypeRef->m_pTypeToken->m_sFileName, m_pChildTypeRef->m_pTypeToken->m_nLine, m_pChildTypeRef->m_pTypeToken->m_nColumn);
						if (pCandidates) delete pCandidates;
						if (pTypeLike) delete pTypeLike;
#line 354 "../../../Source/Core/AST/TypeRef.nll"
						return;
					}
#line 357 "../../../Source/Core/AST/TypeRef.nll"
					m_pChildTypeRef->Validate(pValidator, 0);
				}
				else
#line 360 "../../../Source/Core/AST/TypeRef.nll"
					if (pType->m_eType == AST::Type::AST_ENUM_DECL)
					{
					}
					else
#line 364 "../../../Source/Core/AST/TypeRef.nll"
						if (pType->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
						{
						}
						else
#line 369 "../../../Source/Core/AST/TypeRef.nll"
							if (pType->m_eType == AST::Type::AST_MEMBER_ENUM_DECL)
							{
							}
							else
#line 373 "../../../Source/Core/AST/TypeRef.nll"
								if (pType->m_eType == AST::Type::AST_GENERIC_TYPE_DECL)
								{
								}
								else
#line 377 "../../../Source/Core/AST/TypeRef.nll"
									if (pType->m_eType == AST::Type::DELEGATE_DECL)
									{
									}
									else
									{
										InternalString* sTemp = new InternalString("Found type, but it's not a AST_CLASS_DECL, AST_MEMBER_CLASS_DECL, NAMESPACE_DECL, AST_ENUM_DECL, AST_MEMBER_ENUM_DECL, AST_GENERIC_TYPE_DECL or DELEGATE_DECL! Got: ");
#line 384 "../../../Source/Core/AST/TypeRef.nll"
										pType->StringifyType(sTemp);
#line 386 "../../../Source/Core/AST/TypeRef.nll"
										pValidator->AddError(sTemp->GetExternalString(), m_pTypeToken->m_sFileName, m_pTypeToken->m_nLine, m_pTypeToken->m_nColumn);
										if (sTemp) delete sTemp;
									}
			if (pCandidates) delete pCandidates;
			if (pTypeLike) delete pTypeLike;
		}
		else
		{
#line 392 "../../../Source/Core/AST/TypeRef.nll"
			if (m_pChildTypeRef != 0)
			{
#line 394 "../../../Source/Core/AST/TypeRef.nll"
				pValidator->AddError("Not identifier but has child type ref???", m_pTypeToken->m_sFileName, m_pTypeToken->m_nLine, m_pTypeToken->m_nColumn);
#line 395 "../../../Source/Core/AST/TypeRef.nll"
				return;
			}
		}
#line 402 "../../../Source/Core/AST/TypeRef.nll"
		for (int i = 0; i < m_pGenericTypeRefVector->GetSize(); i++)
		{
			TypeRef* pGenericTypeRef = m_pGenericTypeRefVector->Get(i);
#line 405 "../../../Source/Core/AST/TypeRef.nll"
			pGenericTypeRef->Validate(pValidator, 0);
		}
#line 410 "../../../Source/Core/AST/TypeRef.nll"
		AST::Validate(pValidator, pParent);
	}

#line 413 "../../../Source/Core/AST/TypeRef.nll"
	TypeRef* TypeRef::Clone()
	{
		TypeRef* pTypeRef = new TypeRef();
#line 416 "../../../Source/Core/AST/TypeRef.nll"
		pTypeRef->m_pCloneToken = m_pTypeToken->Clone();
#line 417 "../../../Source/Core/AST/TypeRef.nll"
		pTypeRef->m_bConst = m_bConst;
#line 418 "../../../Source/Core/AST/TypeRef.nll"
		pTypeRef->m_pFirstToken = pTypeRef->m_pCloneToken;
#line 419 "../../../Source/Core/AST/TypeRef.nll"
		pTypeRef->m_pTypeToken = pTypeRef->m_pCloneToken;
#line 420 "../../../Source/Core/AST/TypeRef.nll"
		pTypeRef->m_pFoundType = m_pFoundType;
#line 422 "../../../Source/Core/AST/TypeRef.nll"
		for (int i = 0; i < m_pGenericTypeRefVector->GetSize(); i++)
		{
			TypeRef* pGenericTypeRef = m_pGenericTypeRefVector->Get(i)->Clone();
#line 425 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef->m_pGenericTypeRefVector->PushBack(pGenericTypeRef);
			NumbatLogic::TypeRef* __3769232678 = pGenericTypeRef;
#line 426 "../../../Source/Core/AST/TypeRef.nll"
			pGenericTypeRef = 0;
#line 426 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef->AddChild(__3769232678);
			if (pGenericTypeRef) delete pGenericTypeRef;
		}
#line 429 "../../../Source/Core/AST/TypeRef.nll"
		pTypeRef->m_pChildTypeRef = 0;
#line 430 "../../../Source/Core/AST/TypeRef.nll"
		if (m_pChildTypeRef != 0)
		{
			TypeRef* pChildTypeRef = m_pChildTypeRef->Clone();
#line 433 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef->m_pChildTypeRef = pChildTypeRef;
			NumbatLogic::TypeRef* __2008520584 = pChildTypeRef;
#line 434 "../../../Source/Core/AST/TypeRef.nll"
			pChildTypeRef = 0;
#line 434 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef->AddChild(__2008520584);
			if (pChildTypeRef) delete pChildTypeRef;
		}
#line 437 "../../../Source/Core/AST/TypeRef.nll"
		pTypeRef->m_ePointerType = m_ePointerType;
		NumbatLogic::TypeRef* __992497841 = pTypeRef;
#line 439 "../../../Source/Core/AST/TypeRef.nll"
		pTypeRef = 0;
#line 439 "../../../Source/Core/AST/TypeRef.nll"
		return __992497841;
	}

#line 442 "../../../Source/Core/AST/TypeRef.nll"
	AST* TypeRef::BaseClone()
	{
#line 444 "../../../Source/Core/AST/TypeRef.nll"
		return Clone();
	}

#line 447 "../../../Source/Core/AST/TypeRef.nll"
	void TypeRef::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 449 "../../../Source/Core/AST/TypeRef.nll"
		if (m_bConst)
		{
			bool bOutput = true;
#line 454 "../../../Source/Core/AST/TypeRef.nll"
			if (eLanguage == AST::Language::CS)
			{
#line 456 "../../../Source/Core/AST/TypeRef.nll"
				bOutput = false;
				Project* pProject = GetProject();
#line 458 "../../../Source/Core/AST/TypeRef.nll"
				if (pProject != 0 && pProject->m_pValidator != 0)
				{
					ValueType* pValueType = GetRecursiveValueType(pProject->m_pValidator->m_pResolver);
#line 462 "../../../Source/Core/AST/TypeRef.nll"
					switch (pValueType->m_eType)
					{
						case ValueType::Type::INT:
						case ValueType::Type::BOOL:
						case ValueType::Type::CHAR:
						case ValueType::Type::UNICHAR:
						case ValueType::Type::ENUM_DECL_VALUE:
						{
#line 471 "../../../Source/Core/AST/TypeRef.nll"
							bOutput = true;
#line 472 "../../../Source/Core/AST/TypeRef.nll"
							break;
						}

					}
				}
			}
#line 478 "../../../Source/Core/AST/TypeRef.nll"
			if (bOutput)
#line 479 "../../../Source/Core/AST/TypeRef.nll"
				pOutputBuilder->m_sOut->AppendString("const ");
		}
#line 484 "../../../Source/Core/AST/TypeRef.nll"
		if (eLanguage == AST::Language::CPP)
		{
#line 486 "../../../Source/Core/AST/TypeRef.nll"
			if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UNICHAR)
#line 487 "../../../Source/Core/AST/TypeRef.nll"
				pOutputBuilder->m_sOut->Append("unsigned short");
			else
#line 488 "../../../Source/Core/AST/TypeRef.nll"
				if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_STRING)
				{
#line 490 "../../../Source/Core/AST/TypeRef.nll"
					if (m_bConst)
#line 491 "../../../Source/Core/AST/TypeRef.nll"
						pOutputBuilder->m_sOut->Append("char*");
					else
#line 493 "../../../Source/Core/AST/TypeRef.nll"
						pOutputBuilder->m_sOut->Append("const char*");
				}
				else
#line 495 "../../../Source/Core/AST/TypeRef.nll"
					if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT)
#line 496 "../../../Source/Core/AST/TypeRef.nll"
						pOutputBuilder->m_sOut->Append("unsigned int");
					else
#line 497 "../../../Source/Core/AST/TypeRef.nll"
						if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT8)
#line 498 "../../../Source/Core/AST/TypeRef.nll"
							pOutputBuilder->m_sOut->Append("unsigned char");
						else
#line 499 "../../../Source/Core/AST/TypeRef.nll"
							if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT16)
#line 500 "../../../Source/Core/AST/TypeRef.nll"
								pOutputBuilder->m_sOut->Append("unsigned short");
							else
#line 501 "../../../Source/Core/AST/TypeRef.nll"
								if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT32)
#line 502 "../../../Source/Core/AST/TypeRef.nll"
									pOutputBuilder->m_sOut->Append("unsigned int");
								else
#line 503 "../../../Source/Core/AST/TypeRef.nll"
									if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT64)
#line 504 "../../../Source/Core/AST/TypeRef.nll"
										pOutputBuilder->m_sOut->Append("unsigned long long");
									else
#line 505 "../../../Source/Core/AST/TypeRef.nll"
										if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT32)
#line 506 "../../../Source/Core/AST/TypeRef.nll"
											pOutputBuilder->m_sOut->Append("int");
										else
#line 507 "../../../Source/Core/AST/TypeRef.nll"
											if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT16)
#line 508 "../../../Source/Core/AST/TypeRef.nll"
												pOutputBuilder->m_sOut->Append("short");
											else
#line 509 "../../../Source/Core/AST/TypeRef.nll"
												if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT8)
#line 510 "../../../Source/Core/AST/TypeRef.nll"
													pOutputBuilder->m_sOut->Append("signed char");
												else
#line 511 "../../../Source/Core/AST/TypeRef.nll"
													if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_VOIDPTR)
#line 512 "../../../Source/Core/AST/TypeRef.nll"
														pOutputBuilder->m_sOut->Append("void*");
													else
#line 514 "../../../Source/Core/AST/TypeRef.nll"
														m_pTypeToken->Stringify(pOutputBuilder->m_sOut);
#line 516 "../../../Source/Core/AST/TypeRef.nll"
			if (m_bRef)
#line 517 "../../../Source/Core/AST/TypeRef.nll"
				pOutputBuilder->m_sOut->AppendString("&");
		}
		else
#line 519 "../../../Source/Core/AST/TypeRef.nll"
			if (eLanguage == AST::Language::CS)
			{
#line 521 "../../../Source/Core/AST/TypeRef.nll"
				if (m_bRef && eLanguage == AST::Language::CS)
#line 522 "../../../Source/Core/AST/TypeRef.nll"
					pOutputBuilder->m_sOut->AppendString("ref ");
#line 524 "../../../Source/Core/AST/TypeRef.nll"
				switch (m_pTypeToken->m_eType)
				{
					case Token::Type::TOKEN_KEYWORD_UNICHAR:
					{
#line 526 "../../../Source/Core/AST/TypeRef.nll"
						pOutputBuilder->m_sOut->Append("char");
#line 526 "../../../Source/Core/AST/TypeRef.nll"
						break;
					}

					case Token::Type::TOKEN_KEYWORD_STRING:
					{
#line 527 "../../../Source/Core/AST/TypeRef.nll"
						pOutputBuilder->m_sOut->Append("string");
#line 527 "../../../Source/Core/AST/TypeRef.nll"
						break;
					}

					case Token::Type::TOKEN_KEYWORD_VOIDPTR:
					{
#line 528 "../../../Source/Core/AST/TypeRef.nll"
						pOutputBuilder->m_sOut->Append("object");
#line 528 "../../../Source/Core/AST/TypeRef.nll"
						break;
					}

					case Token::Type::TOKEN_KEYWORD_UINT8:
					{
#line 529 "../../../Source/Core/AST/TypeRef.nll"
						pOutputBuilder->m_sOut->Append("byte");
#line 529 "../../../Source/Core/AST/TypeRef.nll"
						break;
					}

					case Token::Type::TOKEN_KEYWORD_UINT16:
					{
#line 530 "../../../Source/Core/AST/TypeRef.nll"
						pOutputBuilder->m_sOut->Append("ushort");
#line 530 "../../../Source/Core/AST/TypeRef.nll"
						break;
					}

					case Token::Type::TOKEN_KEYWORD_UINT32:
					{
#line 531 "../../../Source/Core/AST/TypeRef.nll"
						pOutputBuilder->m_sOut->Append("uint");
#line 531 "../../../Source/Core/AST/TypeRef.nll"
						break;
					}

					case Token::Type::TOKEN_KEYWORD_UINT64:
					{
#line 532 "../../../Source/Core/AST/TypeRef.nll"
						pOutputBuilder->m_sOut->Append("ulong");
#line 532 "../../../Source/Core/AST/TypeRef.nll"
						break;
					}

					case Token::Type::TOKEN_KEYWORD_INT8:
					{
#line 533 "../../../Source/Core/AST/TypeRef.nll"
						pOutputBuilder->m_sOut->Append("sbyte");
#line 533 "../../../Source/Core/AST/TypeRef.nll"
						break;
					}

					case Token::Type::TOKEN_KEYWORD_INT16:
					{
#line 534 "../../../Source/Core/AST/TypeRef.nll"
						pOutputBuilder->m_sOut->Append("short");
#line 534 "../../../Source/Core/AST/TypeRef.nll"
						break;
					}

					case Token::Type::TOKEN_KEYWORD_INT32:
					{
#line 535 "../../../Source/Core/AST/TypeRef.nll"
						pOutputBuilder->m_sOut->Append("int");
#line 535 "../../../Source/Core/AST/TypeRef.nll"
						break;
					}

					default:
					{
#line 539 "../../../Source/Core/AST/TypeRef.nll"
						m_pTypeToken->Stringify(pOutputBuilder->m_sOut);
#line 540 "../../../Source/Core/AST/TypeRef.nll"
						break;
					}

				}
			}
			else
			{
#line 548 "../../../Source/Core/AST/TypeRef.nll"
				m_pTypeToken->Stringify(pOutputBuilder->m_sOut);
			}
#line 552 "../../../Source/Core/AST/TypeRef.nll"
		if (m_pGenericTypeRefVector->GetSize() > 0)
		{
#line 554 "../../../Source/Core/AST/TypeRef.nll"
			pOutputBuilder->m_sOut->AppendChar('<');
#line 555 "../../../Source/Core/AST/TypeRef.nll"
			for (int i = 0; i < m_pGenericTypeRefVector->GetSize(); i++)
			{
#line 557 "../../../Source/Core/AST/TypeRef.nll"
				if (i > 0)
#line 558 "../../../Source/Core/AST/TypeRef.nll"
					pOutputBuilder->m_sOut->Append(", ");
				TypeRef* pGenericTypeRef = m_pGenericTypeRefVector->Get(i);
#line 560 "../../../Source/Core/AST/TypeRef.nll"
				pGenericTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
#line 562 "../../../Source/Core/AST/TypeRef.nll"
			if (eLanguage == AST::Language::NLL_DEF)
#line 563 "../../../Source/Core/AST/TypeRef.nll"
				pOutputBuilder->m_sOut->AppendChar('!');
#line 564 "../../../Source/Core/AST/TypeRef.nll"
			pOutputBuilder->m_sOut->AppendChar('>');
		}
#line 567 "../../../Source/Core/AST/TypeRef.nll"
		if (m_pChildTypeRef != 0)
		{
#line 569 "../../../Source/Core/AST/TypeRef.nll"
			switch (eLanguage)
			{
				case AST::Language::NLL:
				case AST::Language::NLL_DEF:
				case AST::Language::CPP:
				{
#line 575 "../../../Source/Core/AST/TypeRef.nll"
					pOutputBuilder->m_sOut->Append("::");
#line 576 "../../../Source/Core/AST/TypeRef.nll"
					break;
				}

				case AST::Language::CS:
				{
#line 580 "../../../Source/Core/AST/TypeRef.nll"
					pOutputBuilder->m_sOut->AppendChar('.');
#line 581 "../../../Source/Core/AST/TypeRef.nll"
					break;
				}

			}
#line 584 "../../../Source/Core/AST/TypeRef.nll"
			m_pChildTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}
		TypeRef* pFinalChildTypeRef = this;
#line 588 "../../../Source/Core/AST/TypeRef.nll"
		while (pFinalChildTypeRef->m_pChildTypeRef != 0)
		{
#line 590 "../../../Source/Core/AST/TypeRef.nll"
			pFinalChildTypeRef = pFinalChildTypeRef->m_pChildTypeRef;
		}
#line 593 "../../../Source/Core/AST/TypeRef.nll"
		if (pFinalChildTypeRef->m_pTypeToken->m_eType == Token::Type::TOKEN_IDENTIFIER)
		{
			const char* sTypeName = pFinalChildTypeRef->m_pTypeToken->GetString();
			AST* pType = pFinalChildTypeRef->m_pFoundType;
			const char* sxAppendString = "";
#line 601 "../../../Source/Core/AST/TypeRef.nll"
			if (eLanguage == AST::Language::CPP && pType != 0 && pType->m_eType == AST::Type::AST_CLASS_DECL)
#line 602 "../../../Source/Core/AST/TypeRef.nll"
				sxAppendString = "*";
#line 604 "../../../Source/Core/AST/TypeRef.nll"
			if (eLanguage == AST::Language::CPP && pType != 0 && pType->m_eType == AST::Type::DELEGATE_DECL)
#line 605 "../../../Source/Core/AST/TypeRef.nll"
				sxAppendString = "*";
#line 612 "../../../Source/Core/AST/TypeRef.nll"
			if (m_pParent != 0)
			{
#line 614 "../../../Source/Core/AST/TypeRef.nll"
				if (m_pParent->m_eType == AST::Type::AST_NEW_EXP)
#line 615 "../../../Source/Core/AST/TypeRef.nll"
					sxAppendString = "";
#line 617 "../../../Source/Core/AST/TypeRef.nll"
				if (m_pParent->m_eType == AST::Type::AST_TYPE_REF)
				{
					TypeRef* pParentTypeRef = (TypeRef*)(m_pParent);
#line 620 "../../../Source/Core/AST/TypeRef.nll"
					if (pParentTypeRef->m_pChildTypeRef == this)
#line 621 "../../../Source/Core/AST/TypeRef.nll"
						sxAppendString = "";
				}
#line 624 "../../../Source/Core/AST/TypeRef.nll"
				if (m_pParent->m_eType == AST::Type::AST_CLASS_DECL)
				{
					ClassDecl* pParentClassDecl = (ClassDecl*)(m_pParent);
#line 627 "../../../Source/Core/AST/TypeRef.nll"
					if (pParentClassDecl->m_pBaseTypeRef == this)
#line 628 "../../../Source/Core/AST/TypeRef.nll"
						sxAppendString = "";
				}
#line 631 "../../../Source/Core/AST/TypeRef.nll"
				pOutputBuilder->m_sOut->AppendString(sxAppendString);
			}
		}
	}

#line 636 "../../../Source/Core/AST/TypeRef.nll"
	ValueType* TypeRef::GetRecursiveValueType(Resolver* pResolver)
	{
#line 638 "../../../Source/Core/AST/TypeRef.nll"
		if (m_pValueType == 0)
#line 639 "../../../Source/Core/AST/TypeRef.nll"
			SetValueType(pResolver);
#line 641 "../../../Source/Core/AST/TypeRef.nll"
		if (m_pChildTypeRef != 0)
#line 642 "../../../Source/Core/AST/TypeRef.nll"
			return m_pChildTypeRef->GetRecursiveValueType(pResolver);
#line 644 "../../../Source/Core/AST/TypeRef.nll"
		return m_pValueType;
	}

#line 648 "../../../Source/Core/AST/TypeRef.nll"
	ValueType* TypeRef::CreateValueType(Resolver* pResolver)
	{
#line 650 "../../../Source/Core/AST/TypeRef.nll"
		if (m_pValueType == 0)
#line 651 "../../../Source/Core/AST/TypeRef.nll"
			SetValueType(pResolver);
#line 653 "../../../Source/Core/AST/TypeRef.nll"
		if (m_pChildTypeRef != 0)
#line 654 "../../../Source/Core/AST/TypeRef.nll"
			return m_pChildTypeRef->CreateValueType(pResolver);
#line 656 "../../../Source/Core/AST/TypeRef.nll"
		if (m_pValueType != 0)
#line 657 "../../../Source/Core/AST/TypeRef.nll"
			return m_pValueType->Clone();
#line 659 "../../../Source/Core/AST/TypeRef.nll"
		return 0;
	}

#line 662 "../../../Source/Core/AST/TypeRef.nll"
	ValueType* TypeRef::SetValueType(Resolver* pResolver)
	{
#line 666 "../../../Source/Core/AST/TypeRef.nll"
		switch (m_pTypeToken->m_eType)
		{
			case Token::Type::TOKEN_IDENTIFIER:
			{
				AST* pType = m_pFoundType;
#line 672 "../../../Source/Core/AST/TypeRef.nll"
				if (pType == 0 && pResolver != 0)
				{
					const char* sTypeName = m_pTypeToken->GetString();
					TypeRef* pParentTypeRef = 0;
#line 677 "../../../Source/Core/AST/TypeRef.nll"
					if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_TYPE_REF)
					{
#line 679 "../../../Source/Core/AST/TypeRef.nll"
						pParentTypeRef = (TypeRef*)(m_pParent);
#line 680 "../../../Source/Core/AST/TypeRef.nll"
						if (pParentTypeRef->m_pChildTypeRef != this)
#line 681 "../../../Source/Core/AST/TypeRef.nll"
							pParentTypeRef = 0;
					}
					Vector<Symbol*>* pCandidates = new Vector<Symbol*>();
					AST* pResolverBase = this;
#line 685 "../../../Source/Core/AST/TypeRef.nll"
					if (pParentTypeRef != 0 && pParentTypeRef->m_pFoundType != 0)
#line 686 "../../../Source/Core/AST/TypeRef.nll"
						pResolverBase = pParentTypeRef->m_pFoundType;
#line 687 "../../../Source/Core/AST/TypeRef.nll"
					pResolver->ResolveFromNode(pResolverBase, sTypeName, pCandidates);
					Vector<Symbol*>* pTypeLike = new Vector<Symbol*>();
#line 689 "../../../Source/Core/AST/TypeRef.nll"
					for (int i = 0; i < pCandidates->GetSize(); i++)
					{
						Symbol* pSym = pCandidates->Get(i);
#line 692 "../../../Source/Core/AST/TypeRef.nll"
						if (pSym->m_eKind == Symbol::Kind::CLASS || pSym->m_eKind == Symbol::Kind::ENUM || pSym->m_eKind == Symbol::Kind::GENERIC_PARAM || pSym->m_eKind == Symbol::Kind::DELEGATE || pSym->m_eKind == Symbol::Kind::NAMESPACE)
						{
#line 698 "../../../Source/Core/AST/TypeRef.nll"
							pTypeLike->PushBack(pSym);
						}
					}
#line 701 "../../../Source/Core/AST/TypeRef.nll"
					if (pTypeLike->GetSize() == 1)
					{
						Symbol* pSymbol = pTypeLike->Get(0);
#line 704 "../../../Source/Core/AST/TypeRef.nll"
						if (pSymbol->m_pDeclAST != 0)
						{
#line 706 "../../../Source/Core/AST/TypeRef.nll"
							pType = pSymbol->m_pDeclAST;
#line 707 "../../../Source/Core/AST/TypeRef.nll"
							m_pFoundType = pType;
						}
					}
					if (pCandidates) delete pCandidates;
					if (pTypeLike) delete pTypeLike;
				}
#line 712 "../../../Source/Core/AST/TypeRef.nll"
				if (pType != 0)
				{
#line 714 "../../../Source/Core/AST/TypeRef.nll"
					if (pType->m_eType == AST::Type::AST_CLASS_DECL)
					{
#line 716 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType = new ValueType(ValueType::Type::CLASS_DECL_VALUE);
#line 717 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_bConst = m_bConst;
#line 718 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_pClassDecl = (ClassDecl*)(pType);
#line 719 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_ePointerType = m_ePointerType;
#line 723 "../../../Source/Core/AST/TypeRef.nll"
						for (int i = 0; i < m_pGenericTypeRefVector->GetSize(); i++)
						{
							TypeRef* pGenericTypeRef = m_pGenericTypeRefVector->Get(i);
							ValueType* pGenericValueType = pGenericTypeRef->CreateValueType(pResolver);
#line 728 "../../../Source/Core/AST/TypeRef.nll"
							if (pGenericValueType == 0)
							{
								if (pGenericValueType) delete pGenericValueType;
#line 729 "../../../Source/Core/AST/TypeRef.nll"
								return 0;
							}
							NumbatLogic::ValueType* __2199059312 = pGenericValueType;
#line 730 "../../../Source/Core/AST/TypeRef.nll"
							pGenericValueType = 0;
#line 730 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType->m_pGenericValueTypeVector->PushBack(__2199059312);
							if (pGenericValueType) delete pGenericValueType;
						}
#line 733 "../../../Source/Core/AST/TypeRef.nll"
						return m_pValueType;
					}
#line 736 "../../../Source/Core/AST/TypeRef.nll"
					if (pType->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
					{
						MemberClassDecl* pMemberClass = (MemberClassDecl*)(pType);
#line 739 "../../../Source/Core/AST/TypeRef.nll"
						if (pMemberClass->m_pClassDecl != 0)
						{
#line 741 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType = new ValueType(ValueType::Type::CLASS_DECL_VALUE);
#line 742 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType->m_bConst = m_bConst;
#line 743 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType->m_pClassDecl = pMemberClass->m_pClassDecl;
#line 744 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType->m_ePointerType = m_ePointerType;
#line 746 "../../../Source/Core/AST/TypeRef.nll"
							for (int i = 0; i < m_pGenericTypeRefVector->GetSize(); i++)
							{
								TypeRef* pGenericTypeRef = m_pGenericTypeRefVector->Get(i);
								ValueType* pGenericValueType = pGenericTypeRef->CreateValueType(pResolver);
#line 750 "../../../Source/Core/AST/TypeRef.nll"
								if (pGenericValueType == 0)
								{
									if (pGenericValueType) delete pGenericValueType;
#line 751 "../../../Source/Core/AST/TypeRef.nll"
									return 0;
								}
								NumbatLogic::ValueType* __2199190512 = pGenericValueType;
#line 752 "../../../Source/Core/AST/TypeRef.nll"
								pGenericValueType = 0;
#line 752 "../../../Source/Core/AST/TypeRef.nll"
								m_pValueType->m_pGenericValueTypeVector->PushBack(__2199190512);
								if (pGenericValueType) delete pGenericValueType;
							}
#line 755 "../../../Source/Core/AST/TypeRef.nll"
							return m_pValueType;
						}
					}
#line 759 "../../../Source/Core/AST/TypeRef.nll"
					if (pType->m_eType == AST::Type::AST_GENERIC_TYPE_DECL)
					{
#line 761 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType = new ValueType(ValueType::Type::GENERIC_TYPE_DECL_VALUE);
#line 762 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_bConst = m_bConst;
#line 763 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_pGenericTypeDecl = (GenericTypeDecl*)(pType);
#line 764 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_ePointerType = m_ePointerType;
#line 765 "../../../Source/Core/AST/TypeRef.nll"
						return m_pValueType;
					}
#line 768 "../../../Source/Core/AST/TypeRef.nll"
					if (pType->m_eType == AST::Type::AST_ENUM_DECL)
					{
#line 770 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType = new ValueType(ValueType::Type::ENUM_DECL_VALUE);
#line 771 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_bConst = m_bConst;
#line 772 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_pEnumDecl = (EnumDecl*)(pType);
#line 773 "../../../Source/Core/AST/TypeRef.nll"
						return m_pValueType;
					}
#line 776 "../../../Source/Core/AST/TypeRef.nll"
					if (pType->m_eType == AST::Type::AST_MEMBER_ENUM_DECL)
					{
						MemberEnumDecl* pMemberEnum = (MemberEnumDecl*)(pType);
#line 779 "../../../Source/Core/AST/TypeRef.nll"
						if (pMemberEnum->m_pEnumDecl != 0)
						{
#line 781 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType = new ValueType(ValueType::Type::ENUM_DECL_VALUE);
#line 782 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType->m_bConst = m_bConst;
#line 783 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType->m_pEnumDecl = pMemberEnum->m_pEnumDecl;
#line 784 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType->m_ePointerType = m_ePointerType;
#line 785 "../../../Source/Core/AST/TypeRef.nll"
							return m_pValueType;
						}
					}
#line 789 "../../../Source/Core/AST/TypeRef.nll"
					if (pType->m_eType == AST::Type::ENUM_DECL_VALUE)
					{
#line 791 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType = new ValueType(ValueType::Type::ENUM_DECL_VALUE);
#line 792 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_bConst = m_bConst;
#line 793 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_pEnumDeclValue = (EnumDeclValue*)(pType);
#line 794 "../../../Source/Core/AST/TypeRef.nll"
						return m_pValueType;
					}
#line 797 "../../../Source/Core/AST/TypeRef.nll"
					if (pType->m_eType == AST::Type::DELEGATE_DECL)
					{
#line 799 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType = new ValueType(ValueType::Type::DELEGATE_DECL_VALUE);
#line 800 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_bConst = m_bConst;
#line 801 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_pDelegateDecl = (DelegateDecl*)(pType);
#line 802 "../../../Source/Core/AST/TypeRef.nll"
						return m_pValueType;
					}
				}
#line 806 "../../../Source/Core/AST/TypeRef.nll"
				return 0;
			}

			case Token::Type::TOKEN_KEYWORD_INT:
			case Token::Type::TOKEN_KEYWORD_UINT:
			case Token::Type::TOKEN_KEYWORD_UINT8:
			case Token::Type::TOKEN_KEYWORD_UINT16:
			case Token::Type::TOKEN_KEYWORD_UINT32:
			case Token::Type::TOKEN_KEYWORD_UINT64:
			case Token::Type::TOKEN_KEYWORD_INT8:
			case Token::Type::TOKEN_KEYWORD_INT16:
			case Token::Type::TOKEN_KEYWORD_INT32:
			case Token::Type::TOKEN_KEYWORD_DOUBLE:
			case Token::Type::TOKEN_KEYWORD_FLOAT:
			{
#line 820 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType = new ValueType(ValueType::Type::INT);
#line 821 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType->m_bConst = m_bConst;
#line 822 "../../../Source/Core/AST/TypeRef.nll"
				return m_pValueType;
			}

			case Token::Type::TOKEN_KEYWORD_STRING:
			{
#line 826 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType = new ValueType(ValueType::Type::STRING);
#line 827 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType->m_bConst = m_bConst;
#line 828 "../../../Source/Core/AST/TypeRef.nll"
				return m_pValueType;
			}

			case Token::Type::TOKEN_KEYWORD_BOOL:
			{
#line 832 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType = new ValueType(ValueType::Type::BOOL);
#line 833 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType->m_bConst = m_bConst;
#line 834 "../../../Source/Core/AST/TypeRef.nll"
				return m_pValueType;
			}

			case Token::Type::TOKEN_KEYWORD_UNICHAR:
			{
#line 838 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType = new ValueType(ValueType::Type::UNICHAR);
#line 839 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType->m_bConst = m_bConst;
#line 840 "../../../Source/Core/AST/TypeRef.nll"
				return m_pValueType;
			}

			case Token::Type::TOKEN_KEYWORD_VOID:
			{
#line 844 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType = new ValueType(ValueType::Type::VOID);
#line 845 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType->m_bConst = m_bConst;
#line 846 "../../../Source/Core/AST/TypeRef.nll"
				return m_pValueType;
			}

			case Token::Type::TOKEN_KEYWORD_VOIDPTR:
			{
#line 850 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType = new ValueType(ValueType::Type::VOIDPTR);
#line 851 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType->m_bConst = m_bConst;
#line 852 "../../../Source/Core/AST/TypeRef.nll"
				return m_pValueType;
			}

		}
#line 855 "../../../Source/Core/AST/TypeRef.nll"
		return 0;
	}

#line 858 "../../../Source/Core/AST/TypeRef.nll"
	bool TypeRef::IsIntegral()
	{
		Project* pProject = GetProject();
#line 861 "../../../Source/Core/AST/TypeRef.nll"
		if (pProject == 0 || pProject->m_pValidator == 0)
#line 862 "../../../Source/Core/AST/TypeRef.nll"
			return IsInt() || IsBool() || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UNICHAR;
		ValueType* pValueType = GetRecursiveValueType(pProject->m_pValidator->m_pResolver);
#line 864 "../../../Source/Core/AST/TypeRef.nll"
		if (pValueType->m_eType == ValueType::Type::ENUM_DECL_VALUE)
#line 865 "../../../Source/Core/AST/TypeRef.nll"
			return true;
#line 866 "../../../Source/Core/AST/TypeRef.nll"
		return IsInt() || IsBool() || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UNICHAR;
	}

#line 870 "../../../Source/Core/AST/TypeRef.nll"
	bool TypeRef::IsInt()
	{
#line 872 "../../../Source/Core/AST/TypeRef.nll"
		return m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT8 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT16 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT32 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT64 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT8 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT16 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT32;
	}

#line 883 "../../../Source/Core/AST/TypeRef.nll"
	bool TypeRef::IsBool()
	{
#line 885 "../../../Source/Core/AST/TypeRef.nll"
		return m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_BOOL;
	}

#line 888 "../../../Source/Core/AST/TypeRef.nll"
	bool TypeRef::IsFloat()
	{
#line 890 "../../../Source/Core/AST/TypeRef.nll"
		return m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_FLOAT;
	}

#line 893 "../../../Source/Core/AST/TypeRef.nll"
	bool TypeRef::IsDouble()
	{
#line 895 "../../../Source/Core/AST/TypeRef.nll"
		return m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DOUBLE;
	}

#line 3 "../../../Source/Core/AST/TypeRef.nll"
	TypeRef::~TypeRef()
	{
		if (m_pGenericTypeRefVector) delete m_pGenericTypeRefVector;
		if (m_pCloneToken) delete m_pCloneToken;
	}

}

