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
#line 34 "../../../Source/Core/AST/TypeRef.nll"
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 36 "../../../Source/Core/AST/TypeRef.nll"
		bool bConst = false;
#line 37 "../../../Source/Core/AST/TypeRef.nll"
		Token* pConstToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_CONST);
#line 38 "../../../Source/Core/AST/TypeRef.nll"
		if (pConstToken != 0)
		{
#line 40 "../../../Source/Core/AST/TypeRef.nll"
			bConst = true;
#line 41 "../../../Source/Core/AST/TypeRef.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		}
#line 44 "../../../Source/Core/AST/TypeRef.nll"
		bool bRef = false;
#line 45 "../../../Source/Core/AST/TypeRef.nll"
		Token* pRefToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_REF);
#line 46 "../../../Source/Core/AST/TypeRef.nll"
		if (pRefToken != 0)
		{
#line 48 "../../../Source/Core/AST/TypeRef.nll"
			bRef = true;
#line 49 "../../../Source/Core/AST/TypeRef.nll"
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		}
#line 52 "../../../Source/Core/AST/TypeRef.nll"
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
#line 75 "../../../Source/Core/AST/TypeRef.nll"
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
#line 89 "../../../Source/Core/AST/TypeRef.nll"
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
#line 102 "../../../Source/Core/AST/TypeRef.nll"
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
#line 117 "../../../Source/Core/AST/TypeRef.nll"
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
#line 131 "../../../Source/Core/AST/TypeRef.nll"
			TypeRef* pChildTypeRef = TypeRef::TryCreate(pTokenContainer, pTempOffset);
#line 132 "../../../Source/Core/AST/TypeRef.nll"
			if (pChildTypeRef == 0)
			{
#line 134 "../../../Source/Core/AST/TypeRef.nll"
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
#line 188 "../../../Source/Core/AST/TypeRef.nll"
					TypeRef* pSubParentTypeRef = (TypeRef*)(m_pParent);
#line 191 "../../../Source/Core/AST/TypeRef.nll"
					AddClassDeclReference(pClassDecl, AST::OutputFile::HEADER, true);
#line 194 "../../../Source/Core/AST/TypeRef.nll"
					if (pSubParentTypeRef->m_pChildTypeRef != this)
					{
#line 196 "../../../Source/Core/AST/TypeRef.nll"
						AST* pParentParent = m_pParent->m_pParent;
#line 197 "../../../Source/Core/AST/TypeRef.nll"
						if (pParentParent != 0)
						{
#line 199 "../../../Source/Core/AST/TypeRef.nll"
							if (pParentParent->m_eType == AST::Type::AST_NEW_EXP)
#line 200 "../../../Source/Core/AST/TypeRef.nll"
								AddClassDeclReference(pClassDecl, AST::OutputFile::SOURCE, false);
#line 202 "../../../Source/Core/AST/TypeRef.nll"
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
#line 219 "../../../Source/Core/AST/TypeRef.nll"
					AST::OutputFile eOutputFile = AST::OutputFile::SOURCE;
#line 220 "../../../Source/Core/AST/TypeRef.nll"
					bool bForwardReference = pThisOrChild->m_pChildTypeRef == 0 && m_pGenericTypeRefVector->GetSize() == 0;
#line 222 "../../../Source/Core/AST/TypeRef.nll"
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
#line 231 "../../../Source/Core/AST/TypeRef.nll"
							AST* pParentParentParent = pParentParent->m_pParent;
#line 232 "../../../Source/Core/AST/TypeRef.nll"
							if (pParentParentParent != 0)
							{
#line 234 "../../../Source/Core/AST/TypeRef.nll"
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
#line 253 "../../../Source/Core/AST/TypeRef.nll"
			AST* pType = 0;
#line 254 "../../../Source/Core/AST/TypeRef.nll"
			bool bResolverTypeAmbiguous = false;
#line 255 "../../../Source/Core/AST/TypeRef.nll"
			const char* sTypeName = m_pTypeToken->GetString();
#line 262 "../../../Source/Core/AST/TypeRef.nll"
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
#line 270 "../../../Source/Core/AST/TypeRef.nll"
			Vector<Symbol*>* pCandidates = new Vector<Symbol*>();
#line 271 "../../../Source/Core/AST/TypeRef.nll"
			AST* pResolverBase = this;
#line 272 "../../../Source/Core/AST/TypeRef.nll"
			if (pParentTypeRef != 0 && pParentTypeRef->m_pFoundType != 0)
#line 273 "../../../Source/Core/AST/TypeRef.nll"
				pResolverBase = pParentTypeRef->m_pFoundType;
#line 274 "../../../Source/Core/AST/TypeRef.nll"
			pValidator->m_pResolver->ResolveFromNode(pResolverBase, sTypeName, pCandidates);
#line 276 "../../../Source/Core/AST/TypeRef.nll"
			Vector<Symbol*>* pTypeLike = new Vector<Symbol*>();
#line 277 "../../../Source/Core/AST/TypeRef.nll"
			for (int i = 0; i < pCandidates->GetSize(); i++)
			{
#line 279 "../../../Source/Core/AST/TypeRef.nll"
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
#line 292 "../../../Source/Core/AST/TypeRef.nll"
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
#line 306 "../../../Source/Core/AST/TypeRef.nll"
					InternalString* sAmbiguous = new InternalString("Ambiguous type (multiple declarations in scope): ");
#line 307 "../../../Source/Core/AST/TypeRef.nll"
					sAmbiguous->Append(sTypeName);
#line 308 "../../../Source/Core/AST/TypeRef.nll"
					pValidator->AddError(sAmbiguous->GetExternalString(), m_pTypeToken->m_sFileName, m_pTypeToken->m_nLine, m_pTypeToken->m_nColumn);
					if (sAmbiguous) delete sAmbiguous;
				}
				else
				{
#line 312 "../../../Source/Core/AST/TypeRef.nll"
					InternalString* sTemp = new InternalString("Unknown type: ");
#line 313 "../../../Source/Core/AST/TypeRef.nll"
					sTemp->Append(sTypeName);
#line 315 "../../../Source/Core/AST/TypeRef.nll"
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
#line 331 "../../../Source/Core/AST/TypeRef.nll"
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
#line 383 "../../../Source/Core/AST/TypeRef.nll"
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
#line 404 "../../../Source/Core/AST/TypeRef.nll"
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
#line 415 "../../../Source/Core/AST/TypeRef.nll"
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
#line 424 "../../../Source/Core/AST/TypeRef.nll"
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
#line 432 "../../../Source/Core/AST/TypeRef.nll"
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
#line 451 "../../../Source/Core/AST/TypeRef.nll"
			bool bOutput = true;
#line 454 "../../../Source/Core/AST/TypeRef.nll"
			if (eLanguage == AST::Language::CS)
			{
#line 456 "../../../Source/Core/AST/TypeRef.nll"
				bOutput = false;
#line 457 "../../../Source/Core/AST/TypeRef.nll"
				Project* pProject = GetProject();
#line 458 "../../../Source/Core/AST/TypeRef.nll"
				if (pProject != 0 && pProject->m_pValidator != 0)
				{
#line 460 "../../../Source/Core/AST/TypeRef.nll"
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
#line 559 "../../../Source/Core/AST/TypeRef.nll"
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
#line 587 "../../../Source/Core/AST/TypeRef.nll"
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
#line 595 "../../../Source/Core/AST/TypeRef.nll"
			AST* pType = pFinalChildTypeRef->m_pFoundType;
#line 598 "../../../Source/Core/AST/TypeRef.nll"
			const char* sxAppendString = "";
#line 600 "../../../Source/Core/AST/TypeRef.nll"
			if (eLanguage == AST::Language::CPP && pType != 0 && pType->m_eType == AST::Type::AST_CLASS_DECL)
#line 601 "../../../Source/Core/AST/TypeRef.nll"
				sxAppendString = "*";
#line 603 "../../../Source/Core/AST/TypeRef.nll"
			if (eLanguage == AST::Language::CPP && pType != 0 && pType->m_eType == AST::Type::DELEGATE_DECL)
#line 604 "../../../Source/Core/AST/TypeRef.nll"
				sxAppendString = "*";
#line 611 "../../../Source/Core/AST/TypeRef.nll"
			if (m_pParent != 0)
			{
#line 613 "../../../Source/Core/AST/TypeRef.nll"
				if (m_pParent->m_eType == AST::Type::AST_NEW_EXP)
#line 614 "../../../Source/Core/AST/TypeRef.nll"
					sxAppendString = "";
#line 616 "../../../Source/Core/AST/TypeRef.nll"
				if (m_pParent->m_eType == AST::Type::AST_TYPE_REF)
				{
#line 618 "../../../Source/Core/AST/TypeRef.nll"
					TypeRef* pParentTypeRef = (TypeRef*)(m_pParent);
#line 619 "../../../Source/Core/AST/TypeRef.nll"
					if (pParentTypeRef->m_pChildTypeRef == this)
#line 620 "../../../Source/Core/AST/TypeRef.nll"
						sxAppendString = "";
				}
#line 623 "../../../Source/Core/AST/TypeRef.nll"
				if (m_pParent->m_eType == AST::Type::AST_CLASS_DECL)
				{
#line 625 "../../../Source/Core/AST/TypeRef.nll"
					ClassDecl* pParentClassDecl = (ClassDecl*)(m_pParent);
#line 626 "../../../Source/Core/AST/TypeRef.nll"
					if (pParentClassDecl->m_pBaseTypeRef == this)
#line 627 "../../../Source/Core/AST/TypeRef.nll"
						sxAppendString = "";
				}
#line 630 "../../../Source/Core/AST/TypeRef.nll"
				pOutputBuilder->m_sOut->AppendString(sxAppendString);
			}
		}
	}

#line 635 "../../../Source/Core/AST/TypeRef.nll"
	ValueType* TypeRef::GetRecursiveValueType(Resolver* pResolver)
	{
#line 637 "../../../Source/Core/AST/TypeRef.nll"
		if (m_pValueType == 0)
#line 638 "../../../Source/Core/AST/TypeRef.nll"
			SetValueType(pResolver);
#line 640 "../../../Source/Core/AST/TypeRef.nll"
		if (m_pChildTypeRef != 0)
#line 641 "../../../Source/Core/AST/TypeRef.nll"
			return m_pChildTypeRef->GetRecursiveValueType(pResolver);
#line 643 "../../../Source/Core/AST/TypeRef.nll"
		return m_pValueType;
	}

#line 647 "../../../Source/Core/AST/TypeRef.nll"
	ValueType* TypeRef::CreateValueType(Resolver* pResolver)
	{
#line 649 "../../../Source/Core/AST/TypeRef.nll"
		if (m_pValueType == 0)
#line 650 "../../../Source/Core/AST/TypeRef.nll"
			SetValueType(pResolver);
#line 652 "../../../Source/Core/AST/TypeRef.nll"
		if (m_pChildTypeRef != 0)
#line 653 "../../../Source/Core/AST/TypeRef.nll"
			return m_pChildTypeRef->CreateValueType(pResolver);
#line 655 "../../../Source/Core/AST/TypeRef.nll"
		if (m_pValueType != 0)
#line 656 "../../../Source/Core/AST/TypeRef.nll"
			return m_pValueType->Clone();
#line 658 "../../../Source/Core/AST/TypeRef.nll"
		return 0;
	}

#line 661 "../../../Source/Core/AST/TypeRef.nll"
	ValueType* TypeRef::SetValueType(Resolver* pResolver)
	{
#line 665 "../../../Source/Core/AST/TypeRef.nll"
		switch (m_pTypeToken->m_eType)
		{
			case Token::Type::TOKEN_IDENTIFIER:
			{
#line 670 "../../../Source/Core/AST/TypeRef.nll"
				AST* pType = m_pFoundType;
#line 671 "../../../Source/Core/AST/TypeRef.nll"
				if (pType == 0 && pResolver != 0)
				{
#line 674 "../../../Source/Core/AST/TypeRef.nll"
					const char* sTypeName = m_pTypeToken->GetString();
#line 675 "../../../Source/Core/AST/TypeRef.nll"
					TypeRef* pParentTypeRef = 0;
#line 676 "../../../Source/Core/AST/TypeRef.nll"
					if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_TYPE_REF)
					{
#line 678 "../../../Source/Core/AST/TypeRef.nll"
						pParentTypeRef = (TypeRef*)(m_pParent);
#line 679 "../../../Source/Core/AST/TypeRef.nll"
						if (pParentTypeRef->m_pChildTypeRef != this)
#line 680 "../../../Source/Core/AST/TypeRef.nll"
							pParentTypeRef = 0;
					}
#line 682 "../../../Source/Core/AST/TypeRef.nll"
					Vector<Symbol*>* pCandidates = new Vector<Symbol*>();
#line 683 "../../../Source/Core/AST/TypeRef.nll"
					AST* pResolverBase = this;
#line 684 "../../../Source/Core/AST/TypeRef.nll"
					if (pParentTypeRef != 0 && pParentTypeRef->m_pFoundType != 0)
#line 685 "../../../Source/Core/AST/TypeRef.nll"
						pResolverBase = pParentTypeRef->m_pFoundType;
#line 686 "../../../Source/Core/AST/TypeRef.nll"
					pResolver->ResolveFromNode(pResolverBase, sTypeName, pCandidates);
#line 687 "../../../Source/Core/AST/TypeRef.nll"
					Vector<Symbol*>* pTypeLike = new Vector<Symbol*>();
#line 688 "../../../Source/Core/AST/TypeRef.nll"
					for (int i = 0; i < pCandidates->GetSize(); i++)
					{
#line 690 "../../../Source/Core/AST/TypeRef.nll"
						Symbol* pSym = pCandidates->Get(i);
#line 691 "../../../Source/Core/AST/TypeRef.nll"
						if (pSym->m_eKind == Symbol::Kind::CLASS || pSym->m_eKind == Symbol::Kind::ENUM || pSym->m_eKind == Symbol::Kind::GENERIC_PARAM || pSym->m_eKind == Symbol::Kind::DELEGATE || pSym->m_eKind == Symbol::Kind::NAMESPACE)
						{
#line 697 "../../../Source/Core/AST/TypeRef.nll"
							pTypeLike->PushBack(pSym);
						}
					}
#line 700 "../../../Source/Core/AST/TypeRef.nll"
					if (pTypeLike->GetSize() == 1)
					{
#line 702 "../../../Source/Core/AST/TypeRef.nll"
						Symbol* pSymbol = pTypeLike->Get(0);
#line 703 "../../../Source/Core/AST/TypeRef.nll"
						if (pSymbol->m_pDeclAST != 0)
						{
#line 705 "../../../Source/Core/AST/TypeRef.nll"
							pType = pSymbol->m_pDeclAST;
#line 706 "../../../Source/Core/AST/TypeRef.nll"
							m_pFoundType = pType;
						}
					}
					if (pCandidates) delete pCandidates;
					if (pTypeLike) delete pTypeLike;
				}
#line 711 "../../../Source/Core/AST/TypeRef.nll"
				if (pType != 0)
				{
#line 713 "../../../Source/Core/AST/TypeRef.nll"
					if (pType->m_eType == AST::Type::AST_CLASS_DECL)
					{
#line 715 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType = new ValueType(ValueType::Type::CLASS_DECL_VALUE);
#line 716 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_bConst = m_bConst;
#line 717 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_pClassDecl = (ClassDecl*)(pType);
#line 718 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_ePointerType = m_ePointerType;
#line 722 "../../../Source/Core/AST/TypeRef.nll"
						for (int i = 0; i < m_pGenericTypeRefVector->GetSize(); i++)
						{
#line 724 "../../../Source/Core/AST/TypeRef.nll"
							TypeRef* pGenericTypeRef = m_pGenericTypeRefVector->Get(i);
#line 726 "../../../Source/Core/AST/TypeRef.nll"
							ValueType* pGenericValueType = pGenericTypeRef->CreateValueType(pResolver);
#line 727 "../../../Source/Core/AST/TypeRef.nll"
							if (pGenericValueType == 0)
							{
								if (pGenericValueType) delete pGenericValueType;
#line 728 "../../../Source/Core/AST/TypeRef.nll"
								return 0;
							}
							NumbatLogic::ValueType* __2198993722 = pGenericValueType;
#line 729 "../../../Source/Core/AST/TypeRef.nll"
							pGenericValueType = 0;
#line 729 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType->m_pGenericValueTypeVector->PushBack(__2198993722);
							if (pGenericValueType) delete pGenericValueType;
						}
#line 732 "../../../Source/Core/AST/TypeRef.nll"
						return m_pValueType;
					}
#line 735 "../../../Source/Core/AST/TypeRef.nll"
					if (pType->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
					{
#line 737 "../../../Source/Core/AST/TypeRef.nll"
						MemberClassDecl* pMemberClass = (MemberClassDecl*)(pType);
#line 738 "../../../Source/Core/AST/TypeRef.nll"
						if (pMemberClass->m_pClassDecl != 0)
						{
#line 740 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType = new ValueType(ValueType::Type::CLASS_DECL_VALUE);
#line 741 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType->m_bConst = m_bConst;
#line 742 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType->m_pClassDecl = pMemberClass->m_pClassDecl;
#line 743 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType->m_ePointerType = m_ePointerType;
#line 745 "../../../Source/Core/AST/TypeRef.nll"
							for (int i = 0; i < m_pGenericTypeRefVector->GetSize(); i++)
							{
#line 747 "../../../Source/Core/AST/TypeRef.nll"
								TypeRef* pGenericTypeRef = m_pGenericTypeRefVector->Get(i);
#line 748 "../../../Source/Core/AST/TypeRef.nll"
								ValueType* pGenericValueType = pGenericTypeRef->CreateValueType(pResolver);
#line 749 "../../../Source/Core/AST/TypeRef.nll"
								if (pGenericValueType == 0)
								{
									if (pGenericValueType) delete pGenericValueType;
#line 750 "../../../Source/Core/AST/TypeRef.nll"
									return 0;
								}
								NumbatLogic::ValueType* __2199190511 = pGenericValueType;
#line 751 "../../../Source/Core/AST/TypeRef.nll"
								pGenericValueType = 0;
#line 751 "../../../Source/Core/AST/TypeRef.nll"
								m_pValueType->m_pGenericValueTypeVector->PushBack(__2199190511);
								if (pGenericValueType) delete pGenericValueType;
							}
#line 754 "../../../Source/Core/AST/TypeRef.nll"
							return m_pValueType;
						}
					}
#line 758 "../../../Source/Core/AST/TypeRef.nll"
					if (pType->m_eType == AST::Type::AST_GENERIC_TYPE_DECL)
					{
#line 760 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType = new ValueType(ValueType::Type::GENERIC_TYPE_DECL_VALUE);
#line 761 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_bConst = m_bConst;
#line 762 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_pGenericTypeDecl = (GenericTypeDecl*)(pType);
#line 763 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_ePointerType = m_ePointerType;
#line 764 "../../../Source/Core/AST/TypeRef.nll"
						return m_pValueType;
					}
#line 767 "../../../Source/Core/AST/TypeRef.nll"
					if (pType->m_eType == AST::Type::AST_ENUM_DECL)
					{
#line 769 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType = new ValueType(ValueType::Type::ENUM_DECL_VALUE);
#line 770 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_bConst = m_bConst;
#line 771 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_pEnumDecl = (EnumDecl*)(pType);
#line 772 "../../../Source/Core/AST/TypeRef.nll"
						return m_pValueType;
					}
#line 775 "../../../Source/Core/AST/TypeRef.nll"
					if (pType->m_eType == AST::Type::AST_MEMBER_ENUM_DECL)
					{
#line 777 "../../../Source/Core/AST/TypeRef.nll"
						MemberEnumDecl* pMemberEnum = (MemberEnumDecl*)(pType);
#line 778 "../../../Source/Core/AST/TypeRef.nll"
						if (pMemberEnum->m_pEnumDecl != 0)
						{
#line 780 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType = new ValueType(ValueType::Type::ENUM_DECL_VALUE);
#line 781 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType->m_bConst = m_bConst;
#line 782 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType->m_pEnumDecl = pMemberEnum->m_pEnumDecl;
#line 783 "../../../Source/Core/AST/TypeRef.nll"
							m_pValueType->m_ePointerType = m_ePointerType;
#line 784 "../../../Source/Core/AST/TypeRef.nll"
							return m_pValueType;
						}
					}
#line 788 "../../../Source/Core/AST/TypeRef.nll"
					if (pType->m_eType == AST::Type::ENUM_DECL_VALUE)
					{
#line 790 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType = new ValueType(ValueType::Type::ENUM_DECL_VALUE);
#line 791 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_bConst = m_bConst;
#line 792 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_pEnumDeclValue = (EnumDeclValue*)(pType);
#line 793 "../../../Source/Core/AST/TypeRef.nll"
						return m_pValueType;
					}
#line 796 "../../../Source/Core/AST/TypeRef.nll"
					if (pType->m_eType == AST::Type::DELEGATE_DECL)
					{
#line 798 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType = new ValueType(ValueType::Type::DELEGATE_DECL_VALUE);
#line 799 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_bConst = m_bConst;
#line 800 "../../../Source/Core/AST/TypeRef.nll"
						m_pValueType->m_pDelegateDecl = (DelegateDecl*)(pType);
#line 801 "../../../Source/Core/AST/TypeRef.nll"
						return m_pValueType;
					}
				}
#line 805 "../../../Source/Core/AST/TypeRef.nll"
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
#line 819 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType = new ValueType(ValueType::Type::INT);
#line 820 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType->m_bConst = m_bConst;
#line 821 "../../../Source/Core/AST/TypeRef.nll"
				return m_pValueType;
			}

			case Token::Type::TOKEN_KEYWORD_STRING:
			{
#line 825 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType = new ValueType(ValueType::Type::STRING);
#line 826 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType->m_bConst = m_bConst;
#line 827 "../../../Source/Core/AST/TypeRef.nll"
				return m_pValueType;
			}

			case Token::Type::TOKEN_KEYWORD_BOOL:
			{
#line 831 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType = new ValueType(ValueType::Type::BOOL);
#line 832 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType->m_bConst = m_bConst;
#line 833 "../../../Source/Core/AST/TypeRef.nll"
				return m_pValueType;
			}

			case Token::Type::TOKEN_KEYWORD_UNICHAR:
			{
#line 837 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType = new ValueType(ValueType::Type::UNICHAR);
#line 838 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType->m_bConst = m_bConst;
#line 839 "../../../Source/Core/AST/TypeRef.nll"
				return m_pValueType;
			}

			case Token::Type::TOKEN_KEYWORD_VOID:
			{
#line 843 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType = new ValueType(ValueType::Type::VOID);
#line 844 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType->m_bConst = m_bConst;
#line 845 "../../../Source/Core/AST/TypeRef.nll"
				return m_pValueType;
			}

			case Token::Type::TOKEN_KEYWORD_VOIDPTR:
			{
#line 849 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType = new ValueType(ValueType::Type::VOIDPTR);
#line 850 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType->m_bConst = m_bConst;
#line 851 "../../../Source/Core/AST/TypeRef.nll"
				return m_pValueType;
			}

		}
#line 854 "../../../Source/Core/AST/TypeRef.nll"
		return 0;
	}

#line 857 "../../../Source/Core/AST/TypeRef.nll"
	bool TypeRef::IsIntegral()
	{
#line 859 "../../../Source/Core/AST/TypeRef.nll"
		Project* pProject = GetProject();
#line 860 "../../../Source/Core/AST/TypeRef.nll"
		if (pProject == 0 || pProject->m_pValidator == 0)
#line 861 "../../../Source/Core/AST/TypeRef.nll"
			return IsInt() || IsBool() || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UNICHAR;
#line 862 "../../../Source/Core/AST/TypeRef.nll"
		ValueType* pValueType = GetRecursiveValueType(pProject->m_pValidator->m_pResolver);
#line 863 "../../../Source/Core/AST/TypeRef.nll"
		if (pValueType->m_eType == ValueType::Type::ENUM_DECL_VALUE)
#line 864 "../../../Source/Core/AST/TypeRef.nll"
			return true;
#line 865 "../../../Source/Core/AST/TypeRef.nll"
		return IsInt() || IsBool() || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UNICHAR;
	}

#line 869 "../../../Source/Core/AST/TypeRef.nll"
	bool TypeRef::IsInt()
	{
#line 871 "../../../Source/Core/AST/TypeRef.nll"
		return m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT8 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT16 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT32 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT64 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT8 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT16 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT32;
	}

#line 882 "../../../Source/Core/AST/TypeRef.nll"
	bool TypeRef::IsBool()
	{
#line 884 "../../../Source/Core/AST/TypeRef.nll"
		return m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_BOOL;
	}

#line 887 "../../../Source/Core/AST/TypeRef.nll"
	bool TypeRef::IsFloat()
	{
#line 889 "../../../Source/Core/AST/TypeRef.nll"
		return m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_FLOAT;
	}

#line 892 "../../../Source/Core/AST/TypeRef.nll"
	bool TypeRef::IsDouble()
	{
#line 894 "../../../Source/Core/AST/TypeRef.nll"
		return m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DOUBLE;
	}

#line 3 "../../../Source/Core/AST/TypeRef.nll"
	TypeRef::~TypeRef()
	{
		if (m_pGenericTypeRefVector) delete m_pGenericTypeRefVector;
		if (m_pCloneToken) delete m_pCloneToken;
	}

}

