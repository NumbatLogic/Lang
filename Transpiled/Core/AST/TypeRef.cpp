#include "TypeRef.hpp"
#include "AST.hpp"
#include "../../../Shared/CPP/Vector.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "../../../Shared/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "../../../Shared/CPP/InternalString.hpp"
#include "../Validator.hpp"
#include "../ValueType.hpp"
#include "../../Shared/OwnedVector.hpp"

namespace NumberDuck
{
	namespace Secret
	{
		class TypeRef;
		class OffsetDatum;
		class Token;
		class InternalString;
		class AST;
		class ClassDecl;
		class NamespaceDecl;
		class ValueType;
		class GenericTypeDecl;
		class EnumDecl;
		class EnumDeclValue;
		class DelegateDecl;
	}
}
namespace NumberDuck
{
	namespace Secret
	{
		TypeRef::TypeRef()
		{
			m_bConst = false;
			m_pTypeToken = 0;
			m_pGenericTypeRefVector = 0;
			m_pChildTypeRef = 0;
			m_ePointerType = PointerType::SHARED;
			m_pCloneToken = 0;
			m_pFoundType = 0;
			m_eType = AST::Type::AST_TYPE_REF;
			m_pGenericTypeRefVector = new Vector<TypeRef*>();
			m_bConst = false;
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
							NumbatLogic::Assert::Plz(false);
						}
						pTypeRef->m_pGenericTypeRefVector->PushBack(pGenericTypeRef);
						{
							NumberDuck::Secret::TypeRef* __1546460495 = pGenericTypeRef;
							pGenericTypeRef = 0;
							pTypeRef->AddChild(__1546460495);
						}
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
							NumbatLogic::Assert::Plz(false);
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
					NumbatLogic::Assert::Plz(false);
					{
						if (sTemp) delete sTemp;
						if (pChildTypeRef) delete pChildTypeRef;
						if (pTempOffset) delete pTempOffset;
						if (pTypeRef) delete pTypeRef;
						return 0;
					}
				}
				pTypeRef->m_pChildTypeRef = pChildTypeRef;
				{
					NumberDuck::Secret::TypeRef* __3774142037 = pChildTypeRef;
					pChildTypeRef = 0;
					pTypeRef->AddChild(__3774142037);
				}
				if (pChildTypeRef) delete pChildTypeRef;
			}
			else if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_STAR) != 0)
			{
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				pTypeRef->m_ePointerType = PointerType::OWNED;
			}
			else if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_STAR_DOUBLE) != 0)
			{
				pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
				pTypeRef->m_ePointerType = PointerType::TRANSITON;
			}
			pOffsetDatum->Set(pTempOffset);
			{
				NumberDuck::Secret::TypeRef* __3079357496 = pTypeRef;
				pTypeRef = 0;
				{
					if (pTempOffset) delete pTempOffset;
					return __3079357496;
				}
			}
		}

		void TypeRef::ValidateClassDecl(Validator* pValidator, ClassDecl* pClassDecl, TypeRef* pThisOrChild)
		{
			if (m_pParent != 0)
			{
				if (m_pParent->m_eType == AST::Type::AST_NEW_EXP)
				{
					AddClassDeclReference(pClassDecl, AST::OutputFile::SOURCE, false);
				}
				else if (m_pParent->m_eType == AST::Type::AST_TYPE_REF)
				{
					TypeRef* pParentTypeRef = (TypeRef*)(m_pParent);
					AddClassDeclReference(pClassDecl, AST::OutputFile::HEADER, true);
					if (pParentTypeRef->m_pChildTypeRef != this)
					{
						AST* pParentParent = m_pParent->m_pParent;
						if (pParentParent != 0)
						{
							if (pParentParent->m_eType == AST::Type::AST_NEW_EXP)
								AddClassDeclReference(pClassDecl, AST::OutputFile::SOURCE, false);
							AST* pParentParentParent = pParentParent->m_pParent;
							if (pParentParentParent != 0)
							{
								if (pParentParentParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL || pParentParentParent->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
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
									if (m_pParent->m_eType == AST::Type::AST_VAR_DECL && pParentParent->m_eType == AST::Type::AST_PARAM_DECL && (pParentParentParent->m_eType == AST::Type::AST_FUNCTION_DECL && pParentParentParentParent->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL || pParentParentParent->m_eType == AST::Type::AST_TOR_DECL))
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
			TypeRef* pParentTypeRef = 0;
			if (m_pParent->m_eType == AST::Type::AST_TYPE_REF)
			{
				pParentTypeRef = (TypeRef*)(m_pParent);
				if (pParentTypeRef->m_pChildTypeRef != this)
					pParentTypeRef = 0;
			}
			if (m_pTypeToken->m_eType == Token::Type::TOKEN_IDENTIFIER)
			{
				const char* sTypeName = m_pTypeToken->GetString();
				if (pParentTypeRef != 0 && pParentTypeRef->m_pFoundType != 0)
					m_pFoundType = pParentTypeRef->m_pFoundType->FindByName(sTypeName, 0);
				else
					m_pFoundType = FindByName(sTypeName, this);
				AST* pType = m_pFoundType;
				if (pType == 0)
				{
					InternalString* sTemp = new InternalString("Unknown type: ");
					sTemp->Append(sTypeName);
					if (pParentTypeRef != 0 && pParentTypeRef->m_pFoundType != 0)
						sTemp->Append(" -- had parent");
					pValidator->AddError(sTemp->GetExternalString(), m_pTypeToken->m_sFileName, m_pTypeToken->m_nLine, m_pTypeToken->m_nColumn);
					{
						if (sTemp) delete sTemp;
						return;
					}
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
				else if (pType->m_eType == AST::Type::NAMESPACE_DECL)
				{
					NamespaceDecl* pNamespaceDecl = (NamespaceDecl*)(pType);
					if (m_pChildTypeRef == 0)
					{
						pValidator->AddError("Namespace typeref musttt have a child???", m_pTypeToken->m_sFileName, m_pTypeToken->m_nLine, m_pTypeToken->m_nColumn);
						return;
					}
					if (m_pChildTypeRef->m_pTypeToken->m_eType != Token::Type::TOKEN_IDENTIFIER)
					{
						pValidator->AddError("child must be IDENTIFIER", m_pChildTypeRef->m_pTypeToken->m_sFileName, m_pChildTypeRef->m_pTypeToken->m_nLine, m_pChildTypeRef->m_pTypeToken->m_nColumn);
						return;
					}
					m_pChildTypeRef->Validate(pValidator, 0);
				}
				else if (pType->m_eType == AST::Type::AST_ENUM_DECL)
				{
				}
				else if (pType->m_eType == AST::Type::AST_GENERIC_TYPE_DECL)
				{
				}
				else if (pType->m_eType == AST::Type::DELEGATE_DECL)
				{
				}
				else
				{
					InternalString* sTemp = new InternalString("Found type, but it's not a AST_CLASS_DECL, AST_ENUM_DECL, AST_GENERIC_TYPE_DECL or TOKEN_KEYWORD_DELEGATE! Got: ");
					pType->StringifyType(sTemp);
					pValidator->AddError(sTemp->GetExternalString(), m_pTypeToken->m_sFileName, m_pTypeToken->m_nLine, m_pTypeToken->m_nColumn);
					if (sTemp) delete sTemp;
				}
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
			for (int i = 0; i < m_pGenericTypeRefVector->GetSize(); i++)
			{
				TypeRef* pGenericTypeRef = m_pGenericTypeRefVector->Get(i)->Clone();
				pTypeRef->m_pGenericTypeRefVector->PushBack(pGenericTypeRef);
				{
					NumberDuck::Secret::TypeRef* __1546460495 = pGenericTypeRef;
					pGenericTypeRef = 0;
					pTypeRef->AddChild(__1546460495);
				}
				if (pGenericTypeRef) delete pGenericTypeRef;
			}
			pTypeRef->m_pChildTypeRef = 0;
			if (m_pChildTypeRef != 0)
			{
				TypeRef* pChildTypeRef = m_pChildTypeRef->Clone();
				pTypeRef->m_pChildTypeRef = pChildTypeRef;
				{
					NumberDuck::Secret::TypeRef* __3774142037 = pChildTypeRef;
					pChildTypeRef = 0;
					pTypeRef->AddChild(__3774142037);
				}
				if (pChildTypeRef) delete pChildTypeRef;
			}
			pTypeRef->m_ePointerType = m_ePointerType;
			{
				NumberDuck::Secret::TypeRef* __3079357496 = pTypeRef;
				pTypeRef = 0;
				return __3079357496;
			}
		}

		AST* TypeRef::BaseClone()
		{
			return Clone();
		}

		void TypeRef::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
		{
			if (m_bConst)
			{
				bool bOutput = true;
				if (eLanguage == AST::Language::CS)
				{
					bOutput = false;
					ValueType* pValueType = GetRecursiveValueType();
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
				if (bOutput)
					sOut->AppendString("const ");
			}
			if (eLanguage == AST::Language::CPP)
			{
				if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UNICHAR)
					sOut->Append("unsigned short");
				else if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_STRING)
					sOut->Append("const char*");
				else if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT)
					sOut->Append("unsigned int");
				else if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT8)
					sOut->Append("unsigned char");
				else if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT16)
					sOut->Append("unsigned short");
				else if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT32)
					sOut->Append("unsigned int");
				else if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_UINT64)
					sOut->Append("unsigned long long");
				else if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT32)
					sOut->Append("int");
				else if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_INT16)
					sOut->Append("short");
				else if (m_pTypeToken->m_eType == Token::Type::TOKEN_KEYWORD_VOIDPTR)
					sOut->Append("void*");
				else
					m_pTypeToken->Stringify(sOut);
			}
			else if (eLanguage == AST::Language::CS)
			{
				switch (m_pTypeToken->m_eType)
				{
					case Token::Type::TOKEN_KEYWORD_UNICHAR:
					{
						sOut->Append("char");
						break;
					}

					case Token::Type::TOKEN_KEYWORD_STRING:
					{
						sOut->Append("string");
						break;
					}

					case Token::Type::TOKEN_KEYWORD_VOIDPTR:
					{
						sOut->Append("object");
						break;
					}

					case Token::Type::TOKEN_KEYWORD_UINT8:
					{
						sOut->Append("byte");
						break;
					}

					case Token::Type::TOKEN_KEYWORD_UINT16:
					{
						sOut->Append("ushort");
						break;
					}

					case Token::Type::TOKEN_KEYWORD_UINT32:
					{
						sOut->Append("uint");
						break;
					}

					case Token::Type::TOKEN_KEYWORD_UINT64:
					{
						sOut->Append("ulong");
						break;
					}

					case Token::Type::TOKEN_KEYWORD_INT8:
					{
						sOut->Append("sbyte");
						break;
					}

					case Token::Type::TOKEN_KEYWORD_INT16:
					{
						sOut->Append("short");
						break;
					}

					case Token::Type::TOKEN_KEYWORD_INT32:
					{
						sOut->Append("int");
						break;
					}

					default:
					{
						m_pTypeToken->Stringify(sOut);
						break;
					}

				}
			}
			else
			{
				m_pTypeToken->Stringify(sOut);
			}
			if (m_pGenericTypeRefVector->GetSize() > 0)
			{
				sOut->AppendChar('<');
				for (int i = 0; i < m_pGenericTypeRefVector->GetSize(); i++)
				{
					if (i > 0)
						sOut->Append(", ");
					TypeRef* pGenericTypeRef = m_pGenericTypeRefVector->Get(i);
					pGenericTypeRef->Stringify(eLanguage, eOutputFile, 0, sOut);
				}
				if (eLanguage == AST::Language::NLL_DEF)
					sOut->AppendChar('!');
				sOut->AppendChar('>');
			}
			if (m_pChildTypeRef != 0)
			{
				switch (eLanguage)
				{
					case AST::Language::NLL:
					case AST::Language::NLL_DEF:
					case AST::Language::CPP:
					{
						sOut->Append("::");
						break;
					}

					case AST::Language::CS:
					{
						sOut->AppendChar('.');
						break;
					}

				}
				m_pChildTypeRef->Stringify(eLanguage, eOutputFile, 0, sOut);
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
				if (pType == 0)
					pType = FindByName(sTypeName, pFinalChildTypeRef);
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
					sOut->AppendString(sxAppendString);
				}
			}
		}

		ValueType* TypeRef::GetRecursiveValueType()
		{
			if (m_pValueType == 0)
				SetValueType();
			if (m_pChildTypeRef != 0)
				return m_pChildTypeRef->GetRecursiveValueType();
			return m_pValueType;
		}

		ValueType* TypeRef::CreateValueType()
		{
			if (m_pValueType == 0)
				SetValueType();
			if (m_pChildTypeRef != 0)
				return m_pChildTypeRef->CreateValueType();
			if (m_pValueType != 0)
				return m_pValueType->Clone();
			return 0;
		}

		ValueType* TypeRef::SetValueType()
		{
			TypeRef* pParentTypeRef = 0;
			if (m_pParent->m_eType == AST::Type::AST_TYPE_REF)
			{
				pParentTypeRef = (TypeRef*)(m_pParent);
				if (pParentTypeRef->m_pChildTypeRef != this)
					pParentTypeRef = 0;
			}
			switch (m_pTypeToken->m_eType)
			{
				case Token::Type::TOKEN_IDENTIFIER:
				{
					const char* sTypeName = m_pTypeToken->GetString();
					if (pParentTypeRef != 0 && pParentTypeRef->m_pFoundType != 0)
						m_pFoundType = pParentTypeRef->m_pFoundType->FindByName(sTypeName, 0);
					else
						m_pFoundType = FindByName(sTypeName, this);
					AST* pType = m_pFoundType;
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
								ValueType* pGenericValueType = pGenericTypeRef->CreateValueType();
								if (pGenericValueType == 0)
								{
									if (pGenericValueType) delete pGenericValueType;
									return 0;
								}
								{
									NumberDuck::Secret::ValueType* __19552071 = pGenericValueType;
									pGenericValueType = 0;
									m_pValueType->m_pGenericValueTypeVector->PushBack(__19552071);
								}
								if (pGenericValueType) delete pGenericValueType;
							}
							return m_pValueType;
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

		TypeRef::~TypeRef()
		{
			if (m_pGenericTypeRefVector) delete m_pGenericTypeRefVector;
			if (m_pCloneToken) delete m_pCloneToken;
		}

	}
}

