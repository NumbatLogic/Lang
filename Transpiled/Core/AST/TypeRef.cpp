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
#line 1 "../../../Source/Core/AST/TypeRef.nll"
namespace NumbatLogic
{
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
		m_eType = AST::Type::AST_TYPE_REF;
		m_pGenericTypeRefVector = new Vector<TypeRef*>();
		m_bConst = false;
		m_bRef = false;
	}

	TypeRef* TypeRef::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		bool bConst = false;
		Token* pConstToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_CONST);
		if (pConstToken != 0)
		{
			bConst = true;
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		}
		bool bRef = false;
		Token* pRefToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_KEYWORD_REF);
		if (pRefToken != 0)
		{
			bRef = true;
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		}
		Token* pTypeToken = pTokenContainer->Peek(pTempOffset);
		if (pTypeToken == 0 || pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_VOID && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_INT && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_BOOL && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_UNICHAR && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_STRING && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_UINT && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_UINT8 && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_UINT16 && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_UINT32 && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_UINT64 && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_INT8 && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_INT16 && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_INT32 && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_DOUBLE && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_FLOAT && pTypeToken->m_eType != Token::Type::TOKEN_KEYWORD_VOIDPTR && pTypeToken->m_eType != Token::Type::TOKEN_IDENTIFIER)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		TypeRef* pTypeRef = new TypeRef();
		pTypeRef->m_pFirstToken = pTypeToken;
		if (pConstToken != 0)
			pTypeRef->m_pFirstToken = pConstToken;
		pTypeRef->m_bConst = bConst;
		pTypeRef->m_pTypeToken = pTypeToken;
		pTypeRef->m_pChildTypeRef = 0;
		pTypeRef->m_ePointerType = PointerType::SHARED;
		pTypeRef->m_bRef = bRef;
		if (pTypeToken->m_eType == Token::Type::TOKEN_IDENTIFIER)
		{
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
					TypeRef* pGenericTypeRef = TypeRef::TryCreate(pTokenContainer, pTempOffset);
					if (pGenericTypeRef == 0)
					{
						Console::Log("expected inner TypeRef");
						Assert::Plz(false);
					}
					pTypeRef->m_pGenericTypeRefVector->PushBack(pGenericTypeRef);
					NumbatLogic::TypeRef* __3744382558 = pGenericTypeRef;
					pGenericTypeRef = 0;
					pTypeRef->AddChild(__3744382558);
					if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_ANGLE_BRACKET_RIGHT) != 0)
					{
						if (pGenericTypeRef) delete pGenericTypeRef;
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
					pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
					if (pGenericTypeRef) delete pGenericTypeRef;
				}
			}
		}
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_DOUBLE_COLON) != 0)
		{
			pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
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
				return 0;
			}
			pTypeRef->m_pChildTypeRef = pChildTypeRef;
			NumbatLogic::TypeRef* __1983801666 = pChildTypeRef;
			pChildTypeRef = 0;
			pTypeRef->AddChild(__1983801666);
			if (pChildTypeRef) delete pChildTypeRef;
		}
		else
			if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_STAR) != 0)
			{
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				pTypeRef->m_ePointerType = PointerType::OWNED;
			}
			else
				if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_STAR_DOUBLE) != 0)
				{
					pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
					pTypeRef->m_ePointerType = PointerType::TRANSITON;
				}
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::TypeRef* __967910118 = pTypeRef;
		pTypeRef = 0;
		if (pTempOffset) delete pTempOffset;
		return __967910118;
	}

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
			if (m_pParent->m_eType == AST::Type::AST_NEW_EXP)
			{
			}
			else
				if (m_pParent->m_eType == AST::Type::AST_TYPE_REF)
				{
					TypeRef* pSubParentTypeRef = (TypeRef*)(m_pParent);
					AddClassDeclReference(pClassDecl, AST::OutputFile::HEADER, true);
					if (pSubParentTypeRef->m_pChildTypeRef != this)
					{
						AST* pParentParent = m_pParent->m_pParent;
						if (pParentParent != 0)
						{
							if (pParentParent->m_eType == AST::Type::AST_NEW_EXP)
								AddClassDeclReference(pClassDecl, AST::OutputFile::SOURCE, false);
							AST* pParentParentParent = pParentParent->m_pParent;
							if (pParentParentParent != 0)
							{
								if (pParentParentParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
									AddClassDeclReference(pClassDecl, AST::OutputFile::HEADER, false);
								else
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
			pValidator->m_pResolver->ResolveFromNode(pResolverBase, sTypeName, pCandidates);
			Vector<Symbol*>* pTypeLike = new Vector<Symbol*>();
			for (int i = 0; i < pCandidates->GetSize(); i++)
			{
				Symbol* pSym = pCandidates->Get(i);
				if (pSym->m_eKind == Symbol::Kind::CLASS || pSym->m_eKind == Symbol::Kind::ENUM || pSym->m_eKind == Symbol::Kind::GENERIC_PARAM || pSym->m_eKind == Symbol::Kind::DELEGATE || pSym->m_eKind == Symbol::Kind::NAMESPACE)
				{
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
			else
				if (pTypeLike->GetSize() > 1)
					bResolverTypeAmbiguous = true;
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
					InternalString* sTemp = new InternalString("Unknown type: ");
					sTemp->Append(sTypeName);
					TypeRef* pSubParentTypeRef = 0;
					if (m_pParent->m_eType == AST::Type::AST_TYPE_REF)
					{
						pSubParentTypeRef = (TypeRef*)(m_pParent);
						if (pSubParentTypeRef->m_pChildTypeRef != this)
							pSubParentTypeRef = 0;
					}
					if (pSubParentTypeRef != 0 && pSubParentTypeRef->m_pFoundType != 0)
						sTemp->Append(" -- had parent");
					pValidator->AddError(sTemp->GetExternalString(), m_pTypeToken->m_sFileName, m_pTypeToken->m_nLine, m_pTypeToken->m_nColumn);
					if (sTemp) delete sTemp;
				}
				if (pCandidates) delete pCandidates;
				if (pTypeLike) delete pTypeLike;
				return;
			}
			if (pType->m_eType == AST::Type::AST_CLASS_DECL)
			{
				ClassDecl* pClassDecl = (ClassDecl*)(pType);
				ValidateClassDecl(pValidator, pClassDecl, this);
				if (m_pChildTypeRef != 0)
				{
					m_pChildTypeRef->Validate(pValidator, 0);
				}
			}
			else
				if (pType->m_eType == AST::Type::NAMESPACE_DECL)
				{
					if (m_pChildTypeRef == 0)
					{
						pValidator->AddError("Namespace typeref musttt have a child???", m_pTypeToken->m_sFileName, m_pTypeToken->m_nLine, m_pTypeToken->m_nColumn);
						if (pCandidates) delete pCandidates;
						if (pTypeLike) delete pTypeLike;
						return;
					}
					if (m_pChildTypeRef->m_pTypeToken->m_eType != Token::Type::TOKEN_IDENTIFIER)
					{
						pValidator->AddError("child must be IDENTIFIER", m_pChildTypeRef->m_pTypeToken->m_sFileName, m_pChildTypeRef->m_pTypeToken->m_nLine, m_pChildTypeRef->m_pTypeToken->m_nColumn);
						if (pCandidates) delete pCandidates;
						if (pTypeLike) delete pTypeLike;
						return;
					}
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
										InternalString* sTemp = new InternalString("Found type, but it's not a AST_CLASS_DECL, AST_MEMBER_CLASS_DECL, NAMESPACE_DECL, AST_ENUM_DECL, AST_MEMBER_ENUM_DECL, AST_GENERIC_TYPE_DECL or DELEGATE_DECL! Got: ");
										pType->StringifyType(sTemp);
										pValidator->AddError(sTemp->GetExternalString(), m_pTypeToken->m_sFileName, m_pTypeToken->m_nLine, m_pTypeToken->m_nColumn);
										if (sTemp) delete sTemp;
									}
			if (pCandidates) delete pCandidates;
			if (pTypeLike) delete pTypeLike;
		}
		else
		{
			if (m_pChildTypeRef != 0)
			{
				pValidator->AddError("Not identifier but has child type ref???", m_pTypeToken->m_sFileName, m_pTypeToken->m_nLine, m_pTypeToken->m_nColumn);
				return;
			}
		}
		for (int i = 0; i < m_pGenericTypeRefVector->GetSize(); i++)
		{
			TypeRef* pGenericTypeRef = m_pGenericTypeRefVector->Get(i);
			pGenericTypeRef->Validate(pValidator, 0);
		}
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
		for (int i = 0; i < m_pGenericTypeRefVector->GetSize(); i++)
		{
			TypeRef* pGenericTypeRef = m_pGenericTypeRefVector->Get(i)->Clone();
			pTypeRef->m_pGenericTypeRefVector->PushBack(pGenericTypeRef);
			NumbatLogic::TypeRef* __3769232678 = pGenericTypeRef;
			pGenericTypeRef = 0;
			pTypeRef->AddChild(__3769232678);
			if (pGenericTypeRef) delete pGenericTypeRef;
		}
		pTypeRef->m_pChildTypeRef = 0;
		if (m_pChildTypeRef != 0)
		{
			TypeRef* pChildTypeRef = m_pChildTypeRef->Clone();
			pTypeRef->m_pChildTypeRef = pChildTypeRef;
			NumbatLogic::TypeRef* __2008520584 = pChildTypeRef;
			pChildTypeRef = 0;
			pTypeRef->AddChild(__2008520584);
			if (pChildTypeRef) delete pChildTypeRef;
		}
		pTypeRef->m_ePointerType = m_ePointerType;
		NumbatLogic::TypeRef* __992497841 = pTypeRef;
		pTypeRef = 0;
		return __992497841;
	}

	AST* TypeRef::BaseClone()
	{
		return Clone();
	}

	void TypeRef::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* out)
	{
		if (m_bConst)
		{
			bool bOutput = true;
			if (eLanguage == AST::Language::CS)
			{
				bOutput = false;
				Project* pProject = GetProject();
				if (pProject != 0 && pProject->m_pValidator != 0)
				{
					ValueType* pValueType = GetRecursiveValueType(pProject->m_pValidator->m_pResolver);
					switch (pValueType->m_eType)
					{
						case ValueType::Type::INT:
						case ValueType::Type::BOOL:
						case ValueType::Type::CHAR:
						case ValueType::Type::UNICHAR:
						case ValueType::Type::ENUM_DECL_VALUE:
						{
							bOutput = true;
							break;
						}

					}
				}
			}
			if (bOutput)
				out->m_sOut->AppendString("const ");
		}
		if (eLanguage == AST::Language::CPP)
		{
			if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UNICHAR)
				out->m_sOut->Append("unsigned short");
			else
				if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_STRING)
				{
					if (m_bConst)
						out->m_sOut->Append("char*");
					else
						out->m_sOut->Append("const char*");
				}
				else
					if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT)
						out->m_sOut->Append("unsigned int");
					else
						if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT8)
							out->m_sOut->Append("unsigned char");
						else
							if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT16)
								out->m_sOut->Append("unsigned short");
							else
								if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT32)
									out->m_sOut->Append("unsigned int");
								else
									if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT64)
										out->m_sOut->Append("unsigned long long");
									else
										if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT32)
											out->m_sOut->Append("int");
										else
											if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT16)
												out->m_sOut->Append("short");
											else
												if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT8)
													out->m_sOut->Append("signed char");
												else
													if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_VOIDPTR)
														out->m_sOut->Append("void*");
													else
														m_pTypeToken->Stringify(out->m_sOut);
			if (m_bRef)
				out->m_sOut->AppendString("&");
		}
		else
			if (eLanguage == AST::Language::CS)
			{
				if (m_bRef && eLanguage == AST::Language::CS)
					out->m_sOut->AppendString("ref ");
				switch (m_pTypeToken->m_eType)
				{
					case Token::Type::TOKEN_KEYWORD_UNICHAR:
					{
						out->m_sOut->Append("char");
						break;
					}

					case Token::Type::TOKEN_KEYWORD_STRING:
					{
						out->m_sOut->Append("string");
						break;
					}

					case Token::Type::TOKEN_KEYWORD_VOIDPTR:
					{
						out->m_sOut->Append("object");
						break;
					}

					case Token::Type::TOKEN_KEYWORD_UINT8:
					{
						out->m_sOut->Append("byte");
						break;
					}

					case Token::Type::TOKEN_KEYWORD_UINT16:
					{
						out->m_sOut->Append("ushort");
						break;
					}

					case Token::Type::TOKEN_KEYWORD_UINT32:
					{
						out->m_sOut->Append("uint");
						break;
					}

					case Token::Type::TOKEN_KEYWORD_UINT64:
					{
						out->m_sOut->Append("ulong");
						break;
					}

					case Token::Type::TOKEN_KEYWORD_INT8:
					{
						out->m_sOut->Append("sbyte");
						break;
					}

					case Token::Type::TOKEN_KEYWORD_INT16:
					{
						out->m_sOut->Append("short");
						break;
					}

					case Token::Type::TOKEN_KEYWORD_INT32:
					{
						out->m_sOut->Append("int");
						break;
					}

					default:
					{
						m_pTypeToken->Stringify(out->m_sOut);
						break;
					}

				}
			}
			else
			{
				m_pTypeToken->Stringify(out->m_sOut);
			}
		if (m_pGenericTypeRefVector->GetSize() > 0)
		{
			out->m_sOut->AppendChar('<');
			for (int i = 0; i < m_pGenericTypeRefVector->GetSize(); i++)
			{
				if (i > 0)
					out->m_sOut->Append(", ");
				TypeRef* pGenericTypeRef = m_pGenericTypeRefVector->Get(i);
				pGenericTypeRef->Stringify(eLanguage, eOutputFile, 0, out);
			}
			if (eLanguage == AST::Language::NLL_DEF)
				out->m_sOut->AppendChar('!');
			out->m_sOut->AppendChar('>');
		}
		if (m_pChildTypeRef != 0)
		{
			switch (eLanguage)
			{
				case AST::Language::NLL:
				case AST::Language::NLL_DEF:
				case AST::Language::CPP:
				{
					out->m_sOut->Append("::");
					break;
				}

				case AST::Language::CS:
				{
					out->m_sOut->AppendChar('.');
					break;
				}

			}
			m_pChildTypeRef->Stringify(eLanguage, eOutputFile, 0, out);
		}
		TypeRef* pFinalChildTypeRef = this;
		while (pFinalChildTypeRef->m_pChildTypeRef != 0)
		{
			pFinalChildTypeRef = pFinalChildTypeRef->m_pChildTypeRef;
		}
		if (pFinalChildTypeRef->m_pTypeToken->m_eType == Token::Type::TOKEN_IDENTIFIER)
		{
			const char* sTypeName = pFinalChildTypeRef->m_pTypeToken->GetString();
			AST* pType = pFinalChildTypeRef->m_pFoundType;
			const char* sxAppendString = "";
			if (eLanguage == AST::Language::CPP && pType != 0 && pType->m_eType == AST::Type::AST_CLASS_DECL)
				sxAppendString = "*";
			if (eLanguage == AST::Language::CPP && pType != 0 && pType->m_eType == AST::Type::DELEGATE_DECL)
				sxAppendString = "*";
			if (m_pParent != 0)
			{
				if (m_pParent->m_eType == AST::Type::AST_NEW_EXP)
					sxAppendString = "";
				if (m_pParent->m_eType == AST::Type::AST_TYPE_REF)
				{
					TypeRef* pParentTypeRef = (TypeRef*)(m_pParent);
					if (pParentTypeRef->m_pChildTypeRef == this)
						sxAppendString = "";
				}
				if (m_pParent->m_eType == AST::Type::AST_CLASS_DECL)
				{
					ClassDecl* pParentClassDecl = (ClassDecl*)(m_pParent);
					if (pParentClassDecl->m_pBaseTypeRef == this)
						sxAppendString = "";
				}
				out->m_sOut->AppendString(sxAppendString);
			}
		}
	}

	ValueType* TypeRef::GetRecursiveValueType(Resolver* pResolver)
	{
		if (m_pValueType == 0)
			SetValueType(pResolver);
		if (m_pChildTypeRef != 0)
			return m_pChildTypeRef->GetRecursiveValueType(pResolver);
		return m_pValueType;
	}

	ValueType* TypeRef::CreateValueType(Resolver* pResolver)
	{
		if (m_pValueType == 0)
			SetValueType(pResolver);
		if (m_pChildTypeRef != 0)
			return m_pChildTypeRef->CreateValueType(pResolver);
		if (m_pValueType != 0)
			return m_pValueType->Clone();
		return 0;
	}

	ValueType* TypeRef::SetValueType(Resolver* pResolver)
	{
		switch (m_pTypeToken->m_eType)
		{
			case Token::Type::TOKEN_IDENTIFIER:
			{
				AST* pType = m_pFoundType;
				if (pType == 0 && pResolver != 0)
				{
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
				if (pType != 0)
				{
					if (pType->m_eType == AST::Type::AST_CLASS_DECL)
					{
						m_pValueType = new ValueType(ValueType::Type::CLASS_DECL_VALUE);
						m_pValueType->m_bConst = m_bConst;
						m_pValueType->m_pClassDecl = (ClassDecl*)(pType);
						m_pValueType->m_ePointerType = m_ePointerType;
						for (int i = 0; i < m_pGenericTypeRefVector->GetSize(); i++)
						{
							TypeRef* pGenericTypeRef = m_pGenericTypeRefVector->Get(i);
							ValueType* pGenericValueType = pGenericTypeRef->CreateValueType(pResolver);
							if (pGenericValueType == 0)
							{
								if (pGenericValueType) delete pGenericValueType;
								return 0;
							}
							NumbatLogic::ValueType* __2199059312 = pGenericValueType;
							pGenericValueType = 0;
							m_pValueType->m_pGenericValueTypeVector->PushBack(__2199059312);
							if (pGenericValueType) delete pGenericValueType;
						}
						return m_pValueType;
					}
					if (pType->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
					{
						MemberClassDecl* pMemberClass = (MemberClassDecl*)(pType);
						if (pMemberClass->m_pClassDecl != 0)
						{
							m_pValueType = new ValueType(ValueType::Type::CLASS_DECL_VALUE);
							m_pValueType->m_bConst = m_bConst;
							m_pValueType->m_pClassDecl = pMemberClass->m_pClassDecl;
							m_pValueType->m_ePointerType = m_ePointerType;
							for (int i = 0; i < m_pGenericTypeRefVector->GetSize(); i++)
							{
								TypeRef* pGenericTypeRef = m_pGenericTypeRefVector->Get(i);
								ValueType* pGenericValueType = pGenericTypeRef->CreateValueType(pResolver);
								if (pGenericValueType == 0)
								{
									if (pGenericValueType) delete pGenericValueType;
									return 0;
								}
								NumbatLogic::ValueType* __2199190512 = pGenericValueType;
								pGenericValueType = 0;
								m_pValueType->m_pGenericValueTypeVector->PushBack(__2199190512);
								if (pGenericValueType) delete pGenericValueType;
							}
							return m_pValueType;
						}
					}
					if (pType->m_eType == AST::Type::AST_GENERIC_TYPE_DECL)
					{
						m_pValueType = new ValueType(ValueType::Type::GENERIC_TYPE_DECL_VALUE);
						m_pValueType->m_bConst = m_bConst;
						m_pValueType->m_pGenericTypeDecl = (GenericTypeDecl*)(pType);
						m_pValueType->m_ePointerType = m_ePointerType;
						return m_pValueType;
					}
					if (pType->m_eType == AST::Type::AST_ENUM_DECL)
					{
						m_pValueType = new ValueType(ValueType::Type::ENUM_DECL_VALUE);
						m_pValueType->m_bConst = m_bConst;
						m_pValueType->m_pEnumDecl = (EnumDecl*)(pType);
						return m_pValueType;
					}
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
					if (pType->m_eType == AST::Type::ENUM_DECL_VALUE)
					{
						m_pValueType = new ValueType(ValueType::Type::ENUM_DECL_VALUE);
						m_pValueType->m_bConst = m_bConst;
						m_pValueType->m_pEnumDeclValue = (EnumDeclValue*)(pType);
						return m_pValueType;
					}
					if (pType->m_eType == AST::Type::DELEGATE_DECL)
					{
						m_pValueType = new ValueType(ValueType::Type::DELEGATE_DECL_VALUE);
						m_pValueType->m_bConst = m_bConst;
						m_pValueType->m_pDelegateDecl = (DelegateDecl*)(pType);
						return m_pValueType;
					}
				}
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
				m_pValueType = new ValueType(ValueType::Type::INT);
				m_pValueType->m_bConst = m_bConst;
				return m_pValueType;
			}

			case Token::Type::TOKEN_KEYWORD_STRING:
			{
				m_pValueType = new ValueType(ValueType::Type::STRING);
				m_pValueType->m_bConst = m_bConst;
				return m_pValueType;
			}

			case Token::Type::TOKEN_KEYWORD_BOOL:
			{
				m_pValueType = new ValueType(ValueType::Type::BOOL);
				m_pValueType->m_bConst = m_bConst;
				return m_pValueType;
			}

			case Token::Type::TOKEN_KEYWORD_UNICHAR:
			{
				m_pValueType = new ValueType(ValueType::Type::UNICHAR);
				m_pValueType->m_bConst = m_bConst;
				return m_pValueType;
			}

			case Token::Type::TOKEN_KEYWORD_VOID:
			{
				m_pValueType = new ValueType(ValueType::Type::VOID);
				m_pValueType->m_bConst = m_bConst;
				return m_pValueType;
			}

			case Token::Type::TOKEN_KEYWORD_VOIDPTR:
			{
				m_pValueType = new ValueType(ValueType::Type::VOIDPTR);
				m_pValueType->m_bConst = m_bConst;
				return m_pValueType;
			}

		}
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

	bool TypeRef::IsInt()
	{
		return m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT8 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT16 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT32 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT64 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT8 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT16 || m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT32;
	}

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

	TypeRef::~TypeRef()
	{
		if (m_pGenericTypeRefVector) delete m_pGenericTypeRefVector;
		if (m_pCloneToken) delete m_pCloneToken;
	}

}

