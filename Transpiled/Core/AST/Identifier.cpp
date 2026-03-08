#include "Identifier.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "AST.hpp"
#include "ArrayLookup.hpp"
#include "OperatorExpr.hpp"
#include "../ValueType.hpp"
#include "ClassDecl.hpp"
#include "EnumDecl.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../NamespaceNode.hpp"
#include "../Semantic/Symbol.hpp"
#include "../Validator.hpp"
#include "../Semantic/Resolver.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "VarDecl.hpp"
#include "MemberVarDecl.hpp"
#include "MemberClassDecl.hpp"
#include "MemberEnumDecl.hpp"
#include "TypeRef.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "MemberFunctionDecl.hpp"
#include "NamespaceDecl.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class Identifier;
	class ArrayLookup;
	class OperatorExpr;
	template <class T>
	class Vector;
	class NamespaceDecl;
	class NamespaceNode;
	class Symbol;
	class Validator;
	class Resolver;
	class InternalString;
	class ClassDecl;
	class VarDecl;
	class MemberVarDecl;
	class MemberClassDecl;
	class EnumDecl;
	class MemberEnumDecl;
	class EnumDeclValue;
	class TypeRef;
	template <class T>
	class OwnedVector;
	class ValueType;
	class FunctionDecl;
	class MemberFunctionDecl;
}
namespace NumbatLogic
{
	Identifier* Identifier::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
		if (pToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
			return 0;
		}
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		Identifier* pIdentifier = new Identifier();
		pIdentifier->m_eType = AST::Type::AST_IDENTIFIER;
		pIdentifier->m_pNameToken = pToken;
		pIdentifier->m_pFirstToken = pToken;
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::Identifier* __4180376026 = pIdentifier;
		pIdentifier = 0;
		if (pTempOffset) delete pTempOffset;
		return __4180376026;
	}

	AST* Identifier::BaseClone()
	{
		Identifier* pIdentifier = new Identifier();
		pIdentifier->m_eType = m_eType;
		pIdentifier->m_pNameToken = m_pNameToken;
		pIdentifier->m_pFirstToken = m_pFirstToken;
		NumbatLogic::Identifier* __4180441624 = pIdentifier;
		pIdentifier = 0;
		return __4180441624;
	}

	void Identifier::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		const char* sName = m_pNameToken->GetString();
		AST* pContextParent = (pParent != 0) ? (AST*)(pParent) : m_pParent;
		AST* pAST = 0;
		AST* pBase = this;
		AST* pChild = this;
		bool bResolverAmbiguous = false;
		if (pContextParent != 0)
		{
			if (pContextParent->m_eType == AST::Type::AST_ARRAY_LOOKUP)
			{
				ArrayLookup* pAL = (ArrayLookup*)(pContextParent);
				if (pAL->m_pExpression == this)
				{
					AST* pWalk = pAL->m_pParent;
					while (pWalk != 0 && pBase == this)
					{
						if (pWalk->m_eType == AST::Type::AST_OPERATOR_EXPR)
						{
							OperatorExpr* pOpWalk = (OperatorExpr*)(pWalk);
							bool bRightIsArrayLookupOrMulLeft = (pOpWalk->m_pRight == pAL);
							if (!bRightIsArrayLookupOrMulLeft && pOpWalk->m_pRight != 0 && pOpWalk->m_pRight->m_eType == AST::Type::AST_OPERATOR_EXPR)
							{
								OperatorExpr* pRightOp = (OperatorExpr*)(pOpWalk->m_pRight);
								bRightIsArrayLookupOrMulLeft = (pRightOp->m_pLeft == pAL);
							}
							Token* pOpWalkToken = pOpWalk->GetFirstOperatorToken();
							if (pOpWalkToken != 0 && pOpWalkToken->m_eType == Token::Type::TOKEN_DOUBLE_COLON && pOpWalk->m_pLeft != 0 && bRightIsArrayLookupOrMulLeft)
							{
								if (pOpWalk->m_pLeft->m_pValueType == 0)
									pOpWalk->m_pLeft->Validate(pValidator, pOpWalk);
								if (pOpWalk->m_pLeft->m_pValueType != 0)
								{
									if (pOpWalk->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL || pOpWalk->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
									{
										AddClassDeclReference(pOpWalk->m_pLeft->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
										pBase = pOpWalk->m_pLeft->m_pValueType->m_pClassDecl;
										pChild = 0;
										break;
									}
									else
										if (pOpWalk->m_pLeft->m_pValueType->m_eType == ValueType::Type::ENUM_DECL)
										{
											pBase = pOpWalk->m_pLeft->m_pValueType->m_pEnumDecl;
											pChild = 0;
											break;
										}
								}
							}
						}
						pWalk = pWalk->m_pParent;
					}
				}
			}
			if (pContextParent->m_eType == AST::Type::AST_OPERATOR_EXPR)
			{
				OperatorExpr* pOpContext = (OperatorExpr*)(pContextParent);
				Token* pOpContextToken = pOpContext->GetFirstOperatorToken();
				if (pOpContextToken != 0 && pOpContextToken->m_eType == Token::Type::TOKEN_DOT && pOpContext->m_pLeft != 0 && pOpContext->m_pLeft->m_pValueType != 0 && pOpContext->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
				{
					AddClassDeclReference(pOpContext->m_pLeft->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
					pBase = pOpContext->m_pLeft->m_pValueType->m_pClassDecl;
					pChild = 0;
				}
				else
					if (pOpContextToken != 0 && pOpContextToken->m_eType == Token::Type::TOKEN_DOUBLE_COLON && pOpContext->m_pLeft != 0 && pOpContext->m_pLeft->m_pValueType != 0)
					{
						if (pOpContext->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL)
						{
							AddClassDeclReference(pOpContext->m_pLeft->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
							pBase = pOpContext->m_pLeft->m_pValueType->m_pClassDecl;
							pChild = 0;
						}
						else
							if (pOpContext->m_pLeft->m_pValueType->m_eType == ValueType::Type::ENUM_DECL)
							{
								pBase = pOpContext->m_pLeft->m_pValueType->m_pEnumDecl;
								pChild = 0;
							}
							else
								if (pOpContext->m_pLeft->m_pValueType->m_eType == ValueType::Type::NAMESPACE_NODE)
								{
									Vector<NamespaceDecl*>* pNamespaceDeclVector = pOpContext->m_pLeft->m_pValueType->m_pNamespaceNode->m_pNamespaceDeclVector;
									Vector<Symbol*>* pCandidates = new Vector<Symbol*>();
									Vector<Symbol*>* pRelevant = new Vector<Symbol*>();
									for (int i = 0; i < pNamespaceDeclVector->GetSize(); i++)
									{
										NamespaceDecl* pNamespaceDecl = pNamespaceDeclVector->Get(i);
										pCandidates->Clear();
										pValidator->m_pResolver->ResolveFromNode(pNamespaceDecl, sName, pCandidates);
										pRelevant->Clear();
										for (int j = 0; j < pCandidates->GetSize(); j++)
										{
											Symbol* pSym = pCandidates->Get(j);
											if (pSym->m_eKind == Symbol::Kind::CLASS || pSym->m_eKind == Symbol::Kind::ENUM || pSym->m_eKind == Symbol::Kind::VAR || pSym->m_eKind == Symbol::Kind::PARAM || pSym->m_eKind == Symbol::Kind::FUNCTION || pSym->m_eKind == Symbol::Kind::METHOD || pSym->m_eKind == Symbol::Kind::DELEGATE || pSym->m_eKind == Symbol::Kind::ENUM_VALUE || pSym->m_eKind == Symbol::Kind::NAMESPACE)
											{
												pRelevant->PushBack(pSym);
											}
										}
										if (pRelevant->GetSize() == 1 && pRelevant->Get(0)->m_pDeclAST != 0)
										{
											pAST = pRelevant->Get(0)->m_pDeclAST;
											break;
										}
										if (pRelevant->GetSize() > 1)
										{
											bResolverAmbiguous = true;
											break;
										}
									}
									if (pCandidates) delete pCandidates;
									if (pRelevant) delete pRelevant;
								}
								else
								{
									pValidator->AddError("Unexpected left of ::", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
									return;
								}
					}
			}
		}
		if (pAST == 0)
		{
			Vector<Symbol*>* pCandidates = new Vector<Symbol*>();
			pValidator->m_pResolver->ResolveFromNode(pBase, sName, pCandidates);
			Vector<Symbol*>* pRelevant = new Vector<Symbol*>();
			for (int i = 0; i < pCandidates->GetSize(); i++)
			{
				Symbol* pSym = pCandidates->Get(i);
				if (pSym->m_eKind == Symbol::Kind::CLASS || pSym->m_eKind == Symbol::Kind::ENUM || pSym->m_eKind == Symbol::Kind::VAR || pSym->m_eKind == Symbol::Kind::PARAM || pSym->m_eKind == Symbol::Kind::FUNCTION || pSym->m_eKind == Symbol::Kind::METHOD || pSym->m_eKind == Symbol::Kind::DELEGATE || pSym->m_eKind == Symbol::Kind::ENUM_VALUE || pSym->m_eKind == Symbol::Kind::NAMESPACE)
				{
					pRelevant->PushBack(pSym);
				}
			}
			if (pRelevant->GetSize() == 1)
			{
				Symbol* pSymbol = pRelevant->Get(0);
				if (pSymbol->m_pDeclAST != 0)
					pAST = pSymbol->m_pDeclAST;
			}
			else
				if (pRelevant->GetSize() > 1)
					bResolverAmbiguous = true;
			if (pCandidates) delete pCandidates;
			if (pRelevant) delete pRelevant;
		}
		if (pAST == 0)
		{
			if (bResolverAmbiguous)
			{
				InternalString* sAmbiguous = new InternalString("Ambiguous identifier (multiple declarations in scope): ");
				sAmbiguous->Append(sName);
				pValidator->AddError(sAmbiguous->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				if (sAmbiguous) delete sAmbiguous;
			}
			else
			{
				InternalString* sTemp = new InternalString("Identifier Unbeknownst! ");
				sTemp->Append(sName);
				if (pContextParent != 0)
					sTemp->Append(" has parent");
				sTemp->Append(" base: ");
				pBase->StringifyType(sTemp);
				pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				if (sTemp) delete sTemp;
			}
			return;
		}
		if (pAST->m_eType == AST::Type::AST_CLASS_DECL)
		{
			m_pValueType = new ValueType(ValueType::Type::CLASS_DECL);
			m_pValueType->m_pClassDecl = (ClassDecl*)(pAST);
			AddClassDeclReference(m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
			AST* pCheckParent = m_pParent;
			AST* pCurrent = this;
			for (int i = 0; i < 5; i++)
			{
				if (pCheckParent == 0)
					break;
				if (pCheckParent->m_eType == AST::Type::AST_VAR_DECL)
				{
					VarDecl* pVarDecl = (VarDecl*)(pCheckParent);
					bool bInArraySize = false;
					if (pVarDecl->m_pArraySizeVector != 0)
					{
						for (int j = 0; j < pVarDecl->m_pArraySizeVector->GetSize(); j++)
						{
							if (pCurrent == pVarDecl->m_pArraySizeVector->Get(j))
							{
								bInArraySize = true;
								break;
							}
						}
					}
					if (bInArraySize && pVarDecl->m_pParent != 0 && pVarDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
						AddClassDeclReference(m_pValueType->m_pClassDecl, AST::OutputFile::HEADER, false);
					if (pCurrent == pVarDecl->m_pAssignment && pVarDecl->m_pParent != 0 && pVarDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
					{
						MemberVarDecl* pMemberVarDecl = (MemberVarDecl*)(pVarDecl->m_pParent);
						if (pMemberVarDecl->m_bStatic)
							AddClassDeclReference(m_pValueType->m_pClassDecl, AST::OutputFile::HEADER, false);
					}
					break;
				}
				pCurrent = pCheckParent;
				pCheckParent = pCheckParent->m_pParent;
			}
			return;
		}
		else
			if (pAST->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
			{
				MemberClassDecl* pMemberClassDecl = (MemberClassDecl*)(pAST);
				if (pMemberClassDecl->m_pClassDecl != 0)
				{
					m_pValueType = new ValueType(ValueType::Type::CLASS_DECL);
					m_pValueType->m_pClassDecl = pMemberClassDecl->m_pClassDecl;
					AddClassDeclReference(m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
				}
				return;
			}
		if (pAST->m_eType == AST::Type::AST_ENUM_DECL)
		{
			m_pValueType = new ValueType(ValueType::Type::ENUM_DECL);
			m_pValueType->m_pEnumDecl = (EnumDecl*)(pAST);
			return;
		}
		else
			if (pAST->m_eType == AST::Type::AST_MEMBER_ENUM_DECL)
			{
				MemberEnumDecl* pMemberEnum = (MemberEnumDecl*)(pAST);
				if (pMemberEnum->m_pEnumDecl != 0)
				{
					m_pValueType = new ValueType(ValueType::Type::ENUM_DECL);
					m_pValueType->m_pEnumDecl = pMemberEnum->m_pEnumDecl;
					return;
				}
			}
		if (pAST->m_eType == AST::Type::ENUM_DECL_VALUE)
		{
			m_pValueType = new ValueType(ValueType::Type::ENUM_DECL_VALUE);
			m_pValueType->m_pEnumDeclValue = (EnumDeclValue*)(pAST);
			return;
		}
		if (pAST->m_eType == AST::Type::AST_VAR_DECL)
		{
			VarDecl* pVarDecl = (VarDecl*)(pAST);
			m_pValueType = pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
			if (m_pValueType == 0)
			{
				pValidator->AddError("Could not create ValueType for VarDecl", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				return;
			}
			if (m_pValueType->m_eType == ValueType::Type::GENERIC_TYPE_DECL_VALUE)
			{
				if (pParent != 0)
				{
					Token* pParentOpToken = pParent->GetFirstOperatorToken();
					if (pParentOpToken->m_eType == Token::Type::TOKEN_DOT && pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
					{
						if (pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector != 0)
						{
							if (pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector->GetSize() > 0)
							{
								ValueType* pGenericValueType = pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector->Get(0);
								if (pGenericValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
								{
									ValueType* pOldValueType = 0;
									NumbatLogic::ValueType* __865768331 = m_pValueType;
									m_pValueType = 0;
									pOldValueType = __865768331;
									m_pValueType = pGenericValueType->Clone();
									m_pValueType->m_ePointerType = pOldValueType->m_ePointerType;
									if (pOldValueType) delete pOldValueType;
								}
							}
						}
					}
				}
			}
			return;
		}
		else
			if (pAST->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
			{
				MemberVarDecl* pMemberVarDecl = (MemberVarDecl*)(pAST);
				if (pMemberVarDecl->m_pVarDecl != 0)
				{
					VarDecl* pVarDecl = pMemberVarDecl->m_pVarDecl;
					m_pValueType = pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
					if (m_pValueType == 0)
					{
						pValidator->AddError("Could not create ValueType for MemberVarDecl", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
						return;
					}
					if (m_pValueType->m_eType == ValueType::Type::GENERIC_TYPE_DECL_VALUE)
					{
						if (pParent != 0)
						{
							Token* pParentOpToken = pParent->GetFirstOperatorToken();
							if (pParentOpToken->m_eType == Token::Type::TOKEN_DOT && pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
							{
								if (pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector != 0)
								{
									if (pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector->GetSize() > 0)
									{
										ValueType* pGenericValueType = pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector->Get(0);
										if (pGenericValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
										{
											ValueType* pOldValueType = 0;
											NumbatLogic::ValueType* __866096319 = m_pValueType;
											m_pValueType = 0;
											pOldValueType = __866096319;
											m_pValueType = pGenericValueType->Clone();
											m_pValueType->m_ePointerType = pOldValueType->m_ePointerType;
											if (pOldValueType) delete pOldValueType;
										}
									}
								}
							}
						}
					}
					return;
				}
			}
		if (pAST->m_eType == AST::Type::AST_FUNCTION_DECL)
		{
			m_pValueType = new ValueType(ValueType::Type::FUNCTION_DECL);
			m_pValueType->m_pFunctionDecl = (FunctionDecl*)(pAST);
			return;
		}
		else
			if (pAST->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
			{
				MemberFunctionDecl* pMFD = (MemberFunctionDecl*)(pAST);
				if (pMFD->m_pFunctionDecl != 0)
				{
					m_pValueType = new ValueType(ValueType::Type::FUNCTION_DECL);
					m_pValueType->m_pFunctionDecl = pMFD->m_pFunctionDecl;
					return;
				}
			}
		if (pAST->m_eType == AST::Type::NAMESPACE_DECL)
		{
			m_pValueType = new ValueType(ValueType::Type::NAMESPACE_NODE);
			m_pValueType->m_pNamespaceNode = ((NamespaceDecl*)(pAST))->m_pNamespaceNode;
			return;
		}
		{
			InternalString* sTemp = new InternalString("say what? ");
			pAST->StringifyType(sTemp);
			pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			if (sTemp) delete sTemp;
		}
		AST::Validate(pValidator, pParent);
	}

	void Identifier::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString* sOut)
	{
		m_pNameToken->Stringify(sOut);
	}

	Identifier::Identifier()
	{
		m_pNameToken = 0;
	}

}

