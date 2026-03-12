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
		m_pGenericTypeRefVector = new Vector<TypeRef*>();
		m_bConst = false;
		m_bRef = false;
	}

	TypeRef* TypeRef::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 36 "../../../Source/Core/AST/TypeRef.nll"
		bool bConst = false;
		Token* pConstToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_CONST);
		if (pConstToken != 0)
		{
			bConst = true;
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		}
#line 44 "../../../Source/Core/AST/TypeRef.nll"
		bool bRef = false;
		Token* pRefToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_REF);
		if (pRefToken != 0)
		{
			bRef = true;
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		}
#line 52 "../../../Source/Core/AST/TypeRef.nll"
		Token* pTypeToken = pTokenContainer->Peek(pTempOffset);
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
		if (pConstToken != 0)
			pTypeRef->m_pFirstToken = pConstToken;
		pTypeRef->m_bConst = bConst;
		pTypeRef->m_pTypeToken = pTypeToken;
		pTypeRef->m_pChildTypeRef = 0;
		pTypeRef->m_ePointerType = PointerType::SHARED;
#line 85 "../../../Source/Core/AST/TypeRef.nll"
		pTypeRef->m_bRef = bRef;
#line 87 "../../../Source/Core/AST/TypeRef.nll"
		if (pTypeToken->m_eType == Token::Type::TOKEN_IDENTIFIER)
		{
			Token* pAngleBracketLeft = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_ANGLE_BRACKET_LEFT);
			if (pAngleBracketLeft != 0)
			{
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 94 "../../../Source/Core/AST/TypeRef.nll"
				while (true)
				{
					if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_ANGLE_BRACKET_RIGHT) != 0)
					{
						pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
						break;
					}
#line 102 "../../../Source/Core/AST/TypeRef.nll"
					TypeRef* pGenericTypeRef = TypeRef::TryCreate(pTokenContainer, pTempOffset);
					if (pGenericTypeRef == 0)
					{
						Console::Log("expected inner TypeRef");
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
					if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_COMMA) == 0)
					{
						InternalString* sTemp = new InternalString("expected comma ");
						sTemp->Append(pTokenContainer->StringifyOffset(pTempOffset));
						Console::Log(sTemp->GetExternalString());
						Assert::Plz(false);
						if (sTemp) delete sTemp;
					}
#line 122 "../../../Source/Core/AST/TypeRef.nll"
					pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
					if (pGenericTypeRef) delete pGenericTypeRef;
				}
			}
		}
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_DOUBLE_COLON) != 0)
		{
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 131 "../../../Source/Core/AST/TypeRef.nll"
			TypeRef* pChildTypeRef = TypeRef::TryCreate(pTokenContainer, pTempOffset);
			if (pChildTypeRef == 0)
			{
				InternalString* sTemp = new InternalString("expected child TypeRef... ");
				sTemp->Append(pTokenContainer->StringifyOffset(pTempOffset));
				Console::Log(sTemp->GetExternalString());
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
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				pTypeRef->m_ePointerType = PointerType::OWNED;
			}
			else
#line 154 "../../../Source/Core/AST/TypeRef.nll"
				if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_STAR_DOUBLE) != 0)
				{
					pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
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
		if (m_pFoundType != 0 && m_pFoundType->m_eType == AST::Type::AST_CLASS_DECL)
			return (ClassDecl*)(m_pFoundType);
		return 0;
	}

	void TypeRef::ValidateClassDecl(Validator* pValidator, ClassDecl* pClassDecl, TypeRef* pThisOrChild)
	{
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
						if (pParentParent != 0)
						{
							if (pParentParent->m_eType == AST::Type::AST_NEW_EXP)
								AddClassDeclReference(pClassDecl, AST::OutputFile::SOURCE, false);
#line 202 "../../../Source/Core/AST/TypeRef.nll"
							AST* pParentParentParent = pParentParent->m_pParent;
							if (pParentParentParent != 0)
							{
#line 207 "../../../Source/Core/AST/TypeRef.nll"
								if (pParentParentParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
									AddClassDeclReference(pClassDecl, AST::OutputFile::HEADER, false);
								else
#line 209 "../../../Source/Core/AST/TypeRef.nll"
									if (pParentParentParent->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
										AddClassDeclReference(pClassDecl, AST::OutputFile::HEADER, true);
									else
										AddClassDeclReference(pClassDecl, AST::OutputFile::SOURCE, true);
							}
						}
					}
				}
				else
				{
					AST::OutputFile eOutputFile = AST::OutputFile::SOURCE;
					bool bForwardReference = pThisOrChild->m_pChildTypeRef == 0 && m_pGenericTypeRefVector->GetSize() == 0;
#line 222 "../../../Source/Core/AST/TypeRef.nll"
					AST* pParentParent = m_pParent->m_pParent;
					if (pParentParent != 0)
					{
						if (pParentParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL || pParentParent->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
						{
							eOutputFile = AST::OutputFile::HEADER;
						}
						else
						{
							AST* pParentParentParent = pParentParent->m_pParent;
							if (pParentParentParent != 0)
							{
								AST* pParentParentParentParent = pParentParentParent->m_pParent;
								if (pParentParentParentParent != 0)
								{
									if (m_pParent->m_eType == AST::Type::AST_VAR_DECL && pParentParent->m_eType == AST::Type::AST_PARAM_DECL && (pParentParentParent->m_eType == AST::Type::AST_FUNCTION_DECL && pParentParentParentParent->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL || pParentParentParent->m_eType == AST::Type::AST_TOR_DECL || (pParentParentParent->m_eType == AST::Type::AST_FUNCTION_DECL && pParentParentParentParent->m_eType == AST::Type::DELEGATE_DECL)))
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

	void TypeRef::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		if (m_pTypeToken->m_eType == Token::Type::TOKEN_IDENTIFIER)
		{
			AST* pType = 0;
			bool bResolverTypeAmbiguous = false;
			const char* sTypeName = m_pTypeToken->GetString();
#line 262 "../../../Source/Core/AST/TypeRef.nll"
			TypeRef* pParentTypeRef = 0;
			if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_TYPE_REF)
			{
				pParentTypeRef = (TypeRef*)(m_pParent);
				if (pParentTypeRef->m_pChildTypeRef != this)
					pParentTypeRef = 0;
			}
#line 270 "../../../Source/Core/AST/TypeRef.nll"
			Vector<Symbol*>* pCandidates = new Vector<Symbol*>();
			AST* pResolverBase = this;
			if (pParentTypeRef != 0 && pParentTypeRef->m_pFoundType != 0)
				pResolverBase = pParentTypeRef->m_pFoundType;
			pValidator->m_pResolver->ResolveFromNode(pResolverBase, sTypeName, pCandidates);
#line 276 "../../../Source/Core/AST/TypeRef.nll"
			Vector<Symbol*>* pTypeLike = new Vector<Symbol*>();
			for (int i = 0; i < pCandidates->GetSize(); i++)
			{
				Symbol* pSym = pCandidates->Get(i);
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
				if (pSymbol->m_pDeclAST != 0)
				{
					pType = pSymbol->m_pDeclAST;
					m_pFoundType = pType;
				}
			}
			else
#line 299 "../../../Source/Core/AST/TypeRef.nll"
				if (pTypeLike->GetSize() > 1)
					bResolverTypeAmbiguous = true;
#line 302 "../../../Source/Core/AST/TypeRef.nll"
			if (pType == 0)
			{
				if (bResolverTypeAmbiguous)
				{
					InternalString* sAmbiguous = new InternalString("Ambiguous type (multiple declarations in scope): ");
					sAmbiguous->Append(sTypeName);
					pValidator->AddError(sAmbiguous->GetExternalString(), m_pTypeToken->m_sFileName, m_pTypeToken->m_nLine, m_pTypeToken->m_nColumn);
					if (sAmbiguous) delete sAmbiguous;
				}
				else
				{
#line 312 "../../../Source/Core/AST/TypeRef.nll"
					InternalString* sTemp = new InternalString("Unknown type: ");
					sTemp->Append(sTypeName);
#line 315 "../../../Source/Core/AST/TypeRef.nll"
					TypeRef* pSubParentTypeRef = 0;
					if (m_pParent->m_eType == AST::Type::AST_TYPE_REF)
					{
						pSubParentTypeRef = (TypeRef*)(m_pParent);
						if (pSubParentTypeRef->m_pChildTypeRef != this)
							pSubParentTypeRef = 0;
					}
					if (pSubParentTypeRef != 0 && pSubParentTypeRef->m_pFoundType != 0)
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
			if (pType->m_eType == AST::Type::AST_CLASS_DECL)
			{
				ClassDecl* pClassDecl = (ClassDecl*)(pType);
				ValidateClassDecl(pValidator, pClassDecl, this);
#line 334 "../../../Source/Core/AST/TypeRef.nll"
				if (m_pChildTypeRef != 0)
				{
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
						pValidator->AddError("Namespace typeref musttt have a child???", m_pTypeToken->m_sFileName, m_pTypeToken->m_nLine, m_pTypeToken->m_nColumn);
						if (pCandidates) delete pCandidates;
						if (pTypeLike) delete pTypeLike;
#line 348 "../../../Source/Core/AST/TypeRef.nll"
						return;
					}
#line 351 "../../../Source/Core/AST/TypeRef.nll"
					if (m_pChildTypeRef->m_pTypeToken->m_eType != Token::Type::TOKEN_IDENTIFIER)
					{
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
					if (pType->m_eType == AST::Type::AST_ENUM_DECL)
					{
					}
					else
						if (pType->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
						{
						}
						else
#line 369 "../../../Source/Core/AST/TypeRef.nll"
							if (pType->m_eType == AST::Type::AST_MEMBER_ENUM_DECL)
							{
							}
							else
								if (pType->m_eType == AST::Type::AST_GENERIC_TYPE_DECL)
								{
								}
								else
									if (pType->m_eType == AST::Type::DELEGATE_DECL)
									{
									}
									else
									{
#line 383 "../../../Source/Core/AST/TypeRef.nll"
										InternalString* sTemp = new InternalString("Found type, but it's not a AST_CLASS_DECL, AST_MEMBER_CLASS_DECL, NAMESPACE_DECL, AST_ENUM_DECL, AST_MEMBER_ENUM_DECL, AST_GENERIC_TYPE_DECL or DELEGATE_DECL! Got: ");
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
				pValidator->AddError("Not identifier but has child type ref???", m_pTypeToken->m_sFileName, m_pTypeToken->m_nLine, m_pTypeToken->m_nColumn);
				return;
			}
		}
#line 402 "../../../Source/Core/AST/TypeRef.nll"
		for (int i = 0; i < m_pGenericTypeRefVector->GetSize(); i++)
		{
			TypeRef* pGenericTypeRef = m_pGenericTypeRefVector->Get(i);
			pGenericTypeRef->Validate(pValidator, 0);
		}
#line 410 "../../../Source/Core/AST/TypeRef.nll"
		AST::Validate(pValidator, pParent);
	}

	TypeRef* TypeRef::Clone()
	{
		TypeRef* pTypeRef = new TypeRef();
		pTypeRef->m_pCloneToken = m_pTypeToken->Clone();
		pTypeRef->m_bConst = m_bConst;
		pTypeRef->m_pFirstToken = pTypeRef->m_pCloneToken;
		pTypeRef->m_pTypeToken = pTypeRef->m_pCloneToken;
		pTypeRef->m_pFoundType = m_pFoundType;
#line 422 "../../../Source/Core/AST/TypeRef.nll"
		for (int i = 0; i < m_pGenericTypeRefVector->GetSize(); i++)
		{
			TypeRef* pGenericTypeRef = m_pGenericTypeRefVector->Get(i)->Clone();
			pTypeRef->m_pGenericTypeRefVector->PushBack(pGenericTypeRef);
			NumbatLogic::TypeRef* __3769232678 = pGenericTypeRef;
#line 426 "../../../Source/Core/AST/TypeRef.nll"
			pGenericTypeRef = 0;
#line 426 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef->AddChild(__3769232678);
			if (pGenericTypeRef) delete pGenericTypeRef;
		}
		pTypeRef->m_pChildTypeRef = 0;
		if (m_pChildTypeRef != 0)
		{
			TypeRef* pChildTypeRef = m_pChildTypeRef->Clone();
			pTypeRef->m_pChildTypeRef = pChildTypeRef;
			NumbatLogic::TypeRef* __2008520584 = pChildTypeRef;
#line 434 "../../../Source/Core/AST/TypeRef.nll"
			pChildTypeRef = 0;
#line 434 "../../../Source/Core/AST/TypeRef.nll"
			pTypeRef->AddChild(__2008520584);
			if (pChildTypeRef) delete pChildTypeRef;
		}
		pTypeRef->m_ePointerType = m_ePointerType;
		NumbatLogic::TypeRef* __992497841 = pTypeRef;
		pTypeRef = 0;
#line 439 "../../../Source/Core/AST/TypeRef.nll"
		return __992497841;
	}

	AST* TypeRef::BaseClone()
	{
		return Clone();
	}

	void TypeRef::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		if (m_bConst)
		{
			bool bOutput = true;
#line 454 "../../../Source/Core/AST/TypeRef.nll"
			if (eLanguage == AST::Language::CS)
			{
				bOutput = false;
				Project* pProject = GetProject();
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
							break;
						}

					}
				}
			}
			if (bOutput)
				pOutputBuilder->m_sOut->AppendString("const ");
		}
#line 484 "../../../Source/Core/AST/TypeRef.nll"
		if (eLanguage == AST::Language::CPP)
		{
			if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UNICHAR)
				pOutputBuilder->m_sOut->Append("unsigned short");
			else
#line 488 "../../../Source/Core/AST/TypeRef.nll"
				if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_STRING)
				{
					if (m_bConst)
						pOutputBuilder->m_sOut->Append("char*");
					else
						pOutputBuilder->m_sOut->Append("const char*");
				}
				else
#line 495 "../../../Source/Core/AST/TypeRef.nll"
					if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT)
						pOutputBuilder->m_sOut->Append("unsigned int");
					else
#line 497 "../../../Source/Core/AST/TypeRef.nll"
						if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT8)
							pOutputBuilder->m_sOut->Append("unsigned char");
						else
#line 499 "../../../Source/Core/AST/TypeRef.nll"
							if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT16)
								pOutputBuilder->m_sOut->Append("unsigned short");
							else
#line 501 "../../../Source/Core/AST/TypeRef.nll"
								if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT32)
									pOutputBuilder->m_sOut->Append("unsigned int");
								else
#line 503 "../../../Source/Core/AST/TypeRef.nll"
									if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT64)
										pOutputBuilder->m_sOut->Append("unsigned long long");
									else
#line 505 "../../../Source/Core/AST/TypeRef.nll"
										if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT32)
											pOutputBuilder->m_sOut->Append("int");
										else
#line 507 "../../../Source/Core/AST/TypeRef.nll"
											if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT16)
												pOutputBuilder->m_sOut->Append("short");
											else
#line 509 "../../../Source/Core/AST/TypeRef.nll"
												if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT8)
													pOutputBuilder->m_sOut->Append("signed char");
												else
#line 511 "../../../Source/Core/AST/TypeRef.nll"
													if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_VOIDPTR)
														pOutputBuilder->m_sOut->Append("void*");
													else
														m_pTypeToken->Stringify(pOutputBuilder->m_sOut);
#line 516 "../../../Source/Core/AST/TypeRef.nll"
			if (m_bRef)
				pOutputBuilder->m_sOut->AppendString("&");
		}
		else
#line 519 "../../../Source/Core/AST/TypeRef.nll"
			if (eLanguage == AST::Language::CS)
			{
				if (m_bRef && eLanguage == AST::Language::CS)
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
			pOutputBuilder->m_sOut->AppendChar('<');
			for (int i = 0; i < m_pGenericTypeRefVector->GetSize(); i++)
			{
				if (i > 0)
					pOutputBuilder->m_sOut->Append(", ");
				TypeRef* pGenericTypeRef = m_pGenericTypeRefVector->Get(i);
				pGenericTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
			if (eLanguage == AST::Language::NLL_DEF)
				pOutputBuilder->m_sOut->AppendChar('!');
			pOutputBuilder->m_sOut->AppendChar('>');
		}
#line 567 "../../../Source/Core/AST/TypeRef.nll"
		if (m_pChildTypeRef != 0)
		{
			switch (eLanguage)
			{
				case AST::Language::NLL:
				case AST::Language::NLL_DEF:
				case AST::Language::CPP:
				{
					pOutputBuilder->m_sOut->Append("::");
					break;
				}

				case AST::Language::CS:
				{
#line 580 "../../../Source/Core/AST/TypeRef.nll"
					pOutputBuilder->m_sOut->AppendChar('.');
					break;
				}

			}
#line 584 "../../../Source/Core/AST/TypeRef.nll"
			m_pChildTypeRef->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}
#line 587 "../../../Source/Core/AST/TypeRef.nll"
		TypeRef* pFinalChildTypeRef = this;
		while (pFinalChildTypeRef->m_pChildTypeRef != 0)
		{
			pFinalChildTypeRef = pFinalChildTypeRef->m_pChildTypeRef;
		}
#line 593 "../../../Source/Core/AST/TypeRef.nll"
		if (pFinalChildTypeRef->m_pTypeToken->m_eType == Token::Type::TOKEN_IDENTIFIER)
		{
			AST* pType = pFinalChildTypeRef->m_pFoundType;
#line 598 "../../../Source/Core/AST/TypeRef.nll"
			const char* sxAppendString = "";
#line 600 "../../../Source/Core/AST/TypeRef.nll"
			if (eLanguage == AST::Language::CPP && pType != 0 && pType->m_eType == AST::Type::AST_CLASS_DECL)
				sxAppendString = "*";
#line 603 "../../../Source/Core/AST/TypeRef.nll"
			if (eLanguage == AST::Language::CPP && pType != 0 && pType->m_eType == AST::Type::DELEGATE_DECL)
				sxAppendString = "*";
#line 611 "../../../Source/Core/AST/TypeRef.nll"
			if (m_pParent != 0)
			{
				if (m_pParent->m_eType == AST::Type::AST_NEW_EXP)
					sxAppendString = "";
#line 616 "../../../Source/Core/AST/TypeRef.nll"
				if (m_pParent->m_eType == AST::Type::AST_TYPE_REF)
				{
					TypeRef* pParentTypeRef = (TypeRef*)(m_pParent);
					if (pParentTypeRef->m_pChildTypeRef == this)
						sxAppendString = "";
				}
#line 623 "../../../Source/Core/AST/TypeRef.nll"
				if (m_pParent->m_eType == AST::Type::AST_CLASS_DECL)
				{
					ClassDecl* pParentClassDecl = (ClassDecl*)(m_pParent);
					if (pParentClassDecl->m_pBaseTypeRef == this)
						sxAppendString = "";
				}
#line 630 "../../../Source/Core/AST/TypeRef.nll"
				pOutputBuilder->m_sOut->AppendString(sxAppendString);
			}
		}
	}

	ValueType* TypeRef::GetRecursiveValueType(Resolver* pResolver)
	{
		if (m_pValueType == 0)
			SetValueType(pResolver);
#line 640 "../../../Source/Core/AST/TypeRef.nll"
		if (m_pChildTypeRef != 0)
			return m_pChildTypeRef->GetRecursiveValueType(pResolver);
#line 643 "../../../Source/Core/AST/TypeRef.nll"
		return m_pValueType;
	}

#line 647 "../../../Source/Core/AST/TypeRef.nll"
	ValueType* TypeRef::CreateValueType(Resolver* pResolver)
	{
		if (m_pValueType == 0)
			SetValueType(pResolver);
#line 652 "../../../Source/Core/AST/TypeRef.nll"
		if (m_pChildTypeRef != 0)
			return m_pChildTypeRef->CreateValueType(pResolver);
#line 655 "../../../Source/Core/AST/TypeRef.nll"
		if (m_pValueType != 0)
			return m_pValueType->Clone();
#line 658 "../../../Source/Core/AST/TypeRef.nll"
		return 0;
	}

	ValueType* TypeRef::SetValueType(Resolver* pResolver)
	{
#line 665 "../../../Source/Core/AST/TypeRef.nll"
		switch (m_pTypeToken->m_eType)
		{
			case Token::Type::TOKEN_IDENTIFIER:
			{
#line 670 "../../../Source/Core/AST/TypeRef.nll"
				AST* pType = m_pFoundType;
				if (pType == 0 && pResolver != 0)
				{
#line 674 "../../../Source/Core/AST/TypeRef.nll"
					const char* sTypeName = m_pTypeToken->GetString();
					TypeRef* pParentTypeRef = 0;
					if (m_pParent != 0 && m_pParent->m_eType == AST::Type::AST_TYPE_REF)
					{
						pParentTypeRef = (TypeRef*)(m_pParent);
						if (pParentTypeRef->m_pChildTypeRef != this)
							pParentTypeRef = 0;
					}
					Vector<Symbol*>* pCandidates = new Vector<Symbol*>();
					AST* pResolverBase = this;
					if (pParentTypeRef != 0 && pParentTypeRef->m_pFoundType != 0)
						pResolverBase = pParentTypeRef->m_pFoundType;
					pResolver->ResolveFromNode(pResolverBase, sTypeName, pCandidates);
					Vector<Symbol*>* pTypeLike = new Vector<Symbol*>();
					for (int i = 0; i < pCandidates->GetSize(); i++)
					{
						Symbol* pSym = pCandidates->Get(i);
						if (pSym->m_eKind == Symbol::Kind::CLASS || pSym->m_eKind == Symbol::Kind::ENUM || pSym->m_eKind == Symbol::Kind::GENERIC_PARAM || pSym->m_eKind == Symbol::Kind::DELEGATE || pSym->m_eKind == Symbol::Kind::NAMESPACE)
						{
#line 697 "../../../Source/Core/AST/TypeRef.nll"
							pTypeLike->PushBack(pSym);
						}
					}
					if (pTypeLike->GetSize() == 1)
					{
						Symbol* pSymbol = pTypeLike->Get(0);
						if (pSymbol->m_pDeclAST != 0)
						{
							pType = pSymbol->m_pDeclAST;
							m_pFoundType = pType;
						}
					}
					if (pCandidates) delete pCandidates;
					if (pTypeLike) delete pTypeLike;
				}
#line 711 "../../../Source/Core/AST/TypeRef.nll"
				if (pType != 0)
				{
					if (pType->m_eType == AST::Type::AST_CLASS_DECL)
					{
						m_pValueType = new ValueType(ValueType::Type::CLASS_DECL_VALUE);
						m_pValueType->m_bConst = m_bConst;
						m_pValueType->m_pClassDecl = (ClassDecl*)(pType);
						m_pValueType->m_ePointerType = m_ePointerType;
#line 722 "../../../Source/Core/AST/TypeRef.nll"
						for (int i = 0; i < m_pGenericTypeRefVector->GetSize(); i++)
						{
							TypeRef* pGenericTypeRef = m_pGenericTypeRefVector->Get(i);
#line 726 "../../../Source/Core/AST/TypeRef.nll"
							ValueType* pGenericValueType = pGenericTypeRef->CreateValueType(pResolver);
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
						return m_pValueType;
					}
#line 735 "../../../Source/Core/AST/TypeRef.nll"
					if (pType->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
					{
						MemberClassDecl* pMemberClass = (MemberClassDecl*)(pType);
						if (pMemberClass->m_pClassDecl != 0)
						{
							m_pValueType = new ValueType(ValueType::Type::CLASS_DECL_VALUE);
							m_pValueType->m_bConst = m_bConst;
							m_pValueType->m_pClassDecl = pMemberClass->m_pClassDecl;
							m_pValueType->m_ePointerType = m_ePointerType;
#line 745 "../../../Source/Core/AST/TypeRef.nll"
							for (int i = 0; i < m_pGenericTypeRefVector->GetSize(); i++)
							{
								TypeRef* pGenericTypeRef = m_pGenericTypeRefVector->Get(i);
								ValueType* pGenericValueType = pGenericTypeRef->CreateValueType(pResolver);
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
							return m_pValueType;
						}
					}
#line 758 "../../../Source/Core/AST/TypeRef.nll"
					if (pType->m_eType == AST::Type::AST_GENERIC_TYPE_DECL)
					{
						m_pValueType = new ValueType(ValueType::Type::GENERIC_TYPE_DECL_VALUE);
						m_pValueType->m_bConst = m_bConst;
						m_pValueType->m_pGenericTypeDecl = (GenericTypeDecl*)(pType);
						m_pValueType->m_ePointerType = m_ePointerType;
						return m_pValueType;
					}
#line 767 "../../../Source/Core/AST/TypeRef.nll"
					if (pType->m_eType == AST::Type::AST_ENUM_DECL)
					{
						m_pValueType = new ValueType(ValueType::Type::ENUM_DECL_VALUE);
						m_pValueType->m_bConst = m_bConst;
						m_pValueType->m_pEnumDecl = (EnumDecl*)(pType);
						return m_pValueType;
					}
#line 775 "../../../Source/Core/AST/TypeRef.nll"
					if (pType->m_eType == AST::Type::AST_MEMBER_ENUM_DECL)
					{
						MemberEnumDecl* pMemberEnum = (MemberEnumDecl*)(pType);
						if (pMemberEnum->m_pEnumDecl != 0)
						{
							m_pValueType = new ValueType(ValueType::Type::ENUM_DECL_VALUE);
							m_pValueType->m_bConst = m_bConst;
							m_pValueType->m_pEnumDecl = pMemberEnum->m_pEnumDecl;
							m_pValueType->m_ePointerType = m_ePointerType;
							return m_pValueType;
						}
					}
#line 788 "../../../Source/Core/AST/TypeRef.nll"
					if (pType->m_eType == AST::Type::ENUM_DECL_VALUE)
					{
						m_pValueType = new ValueType(ValueType::Type::ENUM_DECL_VALUE);
						m_pValueType->m_bConst = m_bConst;
						m_pValueType->m_pEnumDeclValue = (EnumDeclValue*)(pType);
						return m_pValueType;
					}
#line 796 "../../../Source/Core/AST/TypeRef.nll"
					if (pType->m_eType == AST::Type::DELEGATE_DECL)
					{
						m_pValueType = new ValueType(ValueType::Type::DELEGATE_DECL_VALUE);
						m_pValueType->m_bConst = m_bConst;
						m_pValueType->m_pDelegateDecl = (DelegateDecl*)(pType);
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
				m_pValueType->m_bConst = m_bConst;
				return m_pValueType;
			}

			case Token::Type::TOKEN_KEYWORD_STRING:
			{
#line 825 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType = new ValueType(ValueType::Type::STRING);
				m_pValueType->m_bConst = m_bConst;
				return m_pValueType;
			}

			case Token::Type::TOKEN_KEYWORD_BOOL:
			{
#line 831 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType = new ValueType(ValueType::Type::BOOL);
				m_pValueType->m_bConst = m_bConst;
				return m_pValueType;
			}

			case Token::Type::TOKEN_KEYWORD_UNICHAR:
			{
#line 837 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType = new ValueType(ValueType::Type::UNICHAR);
				m_pValueType->m_bConst = m_bConst;
				return m_pValueType;
			}

			case Token::Type::TOKEN_KEYWORD_VOID:
			{
#line 843 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType = new ValueType(ValueType::Type::VOID);
				m_pValueType->m_bConst = m_bConst;
				return m_pValueType;
			}

			case Token::Type::TOKEN_KEYWORD_VOIDPTR:
			{
#line 849 "../../../Source/Core/AST/TypeRef.nll"
				m_pValueType = new ValueType(ValueType::Type::VOIDPTR);
				m_pValueType->m_bConst = m_bConst;
				return m_pValueType;
			}

		}
#line 854 "../../../Source/Core/AST/TypeRef.nll"
		return 0;
	}

	bool TypeRef::IsIntegral()
	{
		Project* pProject = GetProject();
		if (pProject == 0 || pProject->m_pValidator == 0)
			return IsInt() || IsBool() || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UNICHAR;
		ValueType* pValueType = GetRecursiveValueType(pProject->m_pValidator->m_pResolver);
		if (pValueType->m_eType == ValueType::Type::ENUM_DECL_VALUE)
			return true;
		return IsInt() || IsBool() || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UNICHAR;
	}

#line 869 "../../../Source/Core/AST/TypeRef.nll"
	bool TypeRef::IsInt()
	{
		return m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT8 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT16 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT32 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT64 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT8 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT16 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT32;
	}

#line 882 "../../../Source/Core/AST/TypeRef.nll"
	bool TypeRef::IsBool()
	{
		return m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_BOOL;
	}

	bool TypeRef::IsFloat()
	{
		return m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_FLOAT;
	}

	bool TypeRef::IsDouble()
	{
		return m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_DOUBLE;
	}

#line 3 "../../../Source/Core/AST/TypeRef.nll"
	TypeRef::~TypeRef()
	{
		if (m_pGenericTypeRefVector) delete m_pGenericTypeRefVector;
		if (m_pCloneToken) delete m_pCloneToken;
	}

}

