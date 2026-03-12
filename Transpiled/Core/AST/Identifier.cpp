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
#include "../OutputBuilder.hpp"

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
	class OutputBuilder;
}
#line 0 "../../../Source/Core/AST/Identifier.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/Identifier.nll"
#line 7 "../../../Source/Core/AST/Identifier.nll"
	Identifier* Identifier::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 11 "../../../Source/Core/AST/Identifier.nll"
		Token* pToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
		if (pToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 13 "../../../Source/Core/AST/Identifier.nll"
			return 0;
		}
#line 14 "../../../Source/Core/AST/Identifier.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 16 "../../../Source/Core/AST/Identifier.nll"
		Identifier* pIdentifier = new Identifier();
		pIdentifier->m_eType = AST::Type::AST_IDENTIFIER;
		pIdentifier->m_pNameToken = pToken;
		pIdentifier->m_pFirstToken = pToken;
#line 21 "../../../Source/Core/AST/Identifier.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::Identifier* __4180376026 = pIdentifier;
		pIdentifier = 0;
		if (pTempOffset) delete pTempOffset;
#line 23 "../../../Source/Core/AST/Identifier.nll"
		return __4180376026;
	}

	AST* Identifier::BaseClone()
	{
		Identifier* pIdentifier = new Identifier();
		pIdentifier->m_eType = m_eType;
		pIdentifier->m_pNameToken = m_pNameToken;
		pIdentifier->m_pFirstToken = m_pFirstToken;
		NumbatLogic::Identifier* __4180441624 = pIdentifier;
#line 32 "../../../Source/Core/AST/Identifier.nll"
		pIdentifier = 0;
#line 32 "../../../Source/Core/AST/Identifier.nll"
		return __4180441624;
	}

	void Identifier::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		const char* sName = m_pNameToken->GetString();
#line 40 "../../../Source/Core/AST/Identifier.nll"
		AST* pContextParent = (pParent != 0) ? (AST*)(pParent) : m_pParent;
#line 42 "../../../Source/Core/AST/Identifier.nll"
		AST* pAST = 0;
		AST* pBase = this;
		bool bResolverAmbiguous = false;
		if (pContextParent != 0)
		{
#line 50 "../../../Source/Core/AST/Identifier.nll"
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
							if (pOpWalk->GetOperatorType() == OperatorExpr::OperatorType::SCOPE_RESOLUTION && pOpWalk->m_pLeft != 0 && bRightIsArrayLookupOrMulLeft)
							{
#line 70 "../../../Source/Core/AST/Identifier.nll"
								if (pOpWalk->m_pLeft->m_pValueType == 0)
									pOpWalk->m_pLeft->Validate(pValidator, pOpWalk);
								if (pOpWalk->m_pLeft->m_pValueType != 0)
								{
									if (pOpWalk->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL || pOpWalk->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
									{
#line 77 "../../../Source/Core/AST/Identifier.nll"
										AddClassDeclReference(pOpWalk->m_pLeft->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
										pBase = pOpWalk->m_pLeft->m_pValueType->m_pClassDecl;
										break;
									}
									else
#line 81 "../../../Source/Core/AST/Identifier.nll"
										if (pOpWalk->m_pLeft->m_pValueType->m_eType == ValueType::Type::ENUM_DECL)
										{
											pBase = pOpWalk->m_pLeft->m_pValueType->m_pEnumDecl;
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
				if (pOpContext->GetOperatorType() == OperatorExpr::OperatorType::MEMBER_ACCESS && pOpContext->m_pLeft != 0 && pOpContext->m_pLeft->m_pValueType != 0 && pOpContext->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
				{
					AddClassDeclReference(pOpContext->m_pLeft->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
					pBase = pOpContext->m_pLeft->m_pValueType->m_pClassDecl;
				}
				else
#line 101 "../../../Source/Core/AST/Identifier.nll"
					if (pOpContext->GetOperatorType() == OperatorExpr::OperatorType::SCOPE_RESOLUTION && pOpContext->m_pLeft != 0 && pOpContext->m_pLeft->m_pValueType != 0)
					{
						if (pOpContext->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL)
						{
							AddClassDeclReference(pOpContext->m_pLeft->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
							pBase = pOpContext->m_pLeft->m_pValueType->m_pClassDecl;
						}
						else
#line 108 "../../../Source/Core/AST/Identifier.nll"
							if (pOpContext->m_pLeft->m_pValueType->m_eType == ValueType::Type::ENUM_DECL)
							{
								pBase = pOpContext->m_pLeft->m_pValueType->m_pEnumDecl;
							}
							else
#line 112 "../../../Source/Core/AST/Identifier.nll"
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
#line 136 "../../../Source/Core/AST/Identifier.nll"
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
#line 153 "../../../Source/Core/AST/Identifier.nll"
									pValidator->AddError("Unexpected left of ::", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
									return;
								}
					}
			}
		}
#line 160 "../../../Source/Core/AST/Identifier.nll"
		if (pAST == 0)
		{
			Vector<Symbol*>* pCandidates = new Vector<Symbol*>();
			pValidator->m_pResolver->ResolveFromNode(pBase, sName, pCandidates);
#line 165 "../../../Source/Core/AST/Identifier.nll"
			Vector<Symbol*>* pRelevant = new Vector<Symbol*>();
			for (int i = 0; i < pCandidates->GetSize(); i++)
			{
				Symbol* pSym = pCandidates->Get(i);
				if (pSym->m_eKind == Symbol::Kind::CLASS || pSym->m_eKind == Symbol::Kind::ENUM || pSym->m_eKind == Symbol::Kind::VAR || pSym->m_eKind == Symbol::Kind::PARAM || pSym->m_eKind == Symbol::Kind::FUNCTION || pSym->m_eKind == Symbol::Kind::METHOD || pSym->m_eKind == Symbol::Kind::DELEGATE || pSym->m_eKind == Symbol::Kind::ENUM_VALUE || pSym->m_eKind == Symbol::Kind::NAMESPACE)
				{
#line 179 "../../../Source/Core/AST/Identifier.nll"
					pRelevant->PushBack(pSym);
				}
			}
#line 183 "../../../Source/Core/AST/Identifier.nll"
			if (pRelevant->GetSize() == 1)
			{
				Symbol* pSymbol = pRelevant->Get(0);
				if (pSymbol->m_pDeclAST != 0)
					pAST = pSymbol->m_pDeclAST;
			}
			else
#line 189 "../../../Source/Core/AST/Identifier.nll"
				if (pRelevant->GetSize() > 1)
					bResolverAmbiguous = true;
			if (pCandidates) delete pCandidates;
			if (pRelevant) delete pRelevant;
		}
#line 193 "../../../Source/Core/AST/Identifier.nll"
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
#line 203 "../../../Source/Core/AST/Identifier.nll"
				InternalString* sTemp = new InternalString("Identifier Unbeknownst! ");
				sTemp->Append(sName);
				if (pContextParent != 0)
					sTemp->Append(" has parent");
				sTemp->Append(" base: ");
				pBase->StringifyType(sTemp);
				pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				if (sTemp) delete sTemp;
			}
#line 211 "../../../Source/Core/AST/Identifier.nll"
			return;
		}
#line 214 "../../../Source/Core/AST/Identifier.nll"
		if (pAST->m_eType == AST::Type::AST_CLASS_DECL)
		{
			m_pValueType = new ValueType(ValueType::Type::CLASS_DECL);
			m_pValueType->m_pClassDecl = (ClassDecl*)(pAST);
#line 220 "../../../Source/Core/AST/Identifier.nll"
			AddClassDeclReference(m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
#line 223 "../../../Source/Core/AST/Identifier.nll"
			AST* pCheckParent = m_pParent;
			AST* pCurrent = this;
			for (int i = 0; i < 5; i++)
			{
				if (pCheckParent == 0)
					break;
				if (pCheckParent->m_eType == AST::Type::AST_VAR_DECL)
				{
					VarDecl* pVarDecl = (VarDecl*)(pCheckParent);
#line 233 "../../../Source/Core/AST/Identifier.nll"
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
#line 247 "../../../Source/Core/AST/Identifier.nll"
					if (bInArraySize && pVarDecl->m_pParent != 0 && pVarDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
						AddClassDeclReference(m_pValueType->m_pClassDecl, AST::OutputFile::HEADER, false);
#line 251 "../../../Source/Core/AST/Identifier.nll"
					if (pCurrent == pVarDecl->m_pAssignment && pVarDecl->m_pParent != 0 && pVarDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
					{
						MemberVarDecl* pMemberVarDecl = (MemberVarDecl*)(pVarDecl->m_pParent);
						if (pMemberVarDecl->m_bStatic)
							AddClassDeclReference(m_pValueType->m_pClassDecl, AST::OutputFile::HEADER, false);
					}
#line 258 "../../../Source/Core/AST/Identifier.nll"
					break;
				}
#line 261 "../../../Source/Core/AST/Identifier.nll"
				pCurrent = pCheckParent;
				pCheckParent = pCheckParent->m_pParent;
			}
#line 265 "../../../Source/Core/AST/Identifier.nll"
			return;
		}
		else
#line 267 "../../../Source/Core/AST/Identifier.nll"
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
#line 279 "../../../Source/Core/AST/Identifier.nll"
		if (pAST->m_eType == AST::Type::AST_ENUM_DECL)
		{
			m_pValueType = new ValueType(ValueType::Type::ENUM_DECL);
			m_pValueType->m_pEnumDecl = (EnumDecl*)(pAST);
			return;
		}
		else
#line 285 "../../../Source/Core/AST/Identifier.nll"
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
#line 296 "../../../Source/Core/AST/Identifier.nll"
		if (pAST->m_eType == AST::Type::ENUM_DECL_VALUE)
		{
			m_pValueType = new ValueType(ValueType::Type::ENUM_DECL_VALUE);
			m_pValueType->m_pEnumDeclValue = (EnumDeclValue*)(pAST);
			return;
		}
#line 303 "../../../Source/Core/AST/Identifier.nll"
		if (pAST->m_eType == AST::Type::AST_VAR_DECL)
		{
			VarDecl* pVarDecl = (VarDecl*)(pAST);
			m_pValueType = pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
#line 308 "../../../Source/Core/AST/Identifier.nll"
			if (m_pValueType == 0)
			{
				pValidator->AddError("Could not create ValueType for VarDecl", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				return;
			}
#line 315 "../../../Source/Core/AST/Identifier.nll"
			if (m_pValueType->m_eType == ValueType::Type::GENERIC_TYPE_DECL_VALUE)
			{
				if (pParent != 0)
				{
					if (pParent->GetOperatorType() == OperatorExpr::OperatorType::MEMBER_ACCESS && pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
					{
						if (pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector != 0)
						{
							if (pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector->GetSize() > 0)
							{
								ValueType* pGenericValueType = pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector->Get(0);
								if (pGenericValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
								{
									ValueType* pOldValueType = 0;
									NumbatLogic::ValueType* __865702733 = m_pValueType;
#line 329 "../../../Source/Core/AST/Identifier.nll"
									m_pValueType = 0;
#line 329 "../../../Source/Core/AST/Identifier.nll"
									pOldValueType = __865702733;
									m_pValueType = pGenericValueType->Clone();
									m_pValueType->m_ePointerType = pOldValueType->m_ePointerType;
									if (pOldValueType) delete pOldValueType;
								}
							}
						}
					}
				}
			}
#line 340 "../../../Source/Core/AST/Identifier.nll"
			return;
		}
		else
#line 342 "../../../Source/Core/AST/Identifier.nll"
			if (pAST->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
			{
				MemberVarDecl* pMemberVarDecl = (MemberVarDecl*)(pAST);
				if (pMemberVarDecl->m_pVarDecl != 0)
				{
					VarDecl* pVarDecl = pMemberVarDecl->m_pVarDecl;
					m_pValueType = pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
#line 350 "../../../Source/Core/AST/Identifier.nll"
					if (m_pValueType == 0)
					{
						pValidator->AddError("Could not create ValueType for MemberVarDecl", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
						return;
					}
#line 357 "../../../Source/Core/AST/Identifier.nll"
					if (m_pValueType->m_eType == ValueType::Type::GENERIC_TYPE_DECL_VALUE)
					{
						if (pParent != 0)
						{
							if (pParent->GetOperatorType() == OperatorExpr::OperatorType::MEMBER_ACCESS && pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
							{
								if (pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector != 0)
								{
									if (pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector->GetSize() > 0)
									{
										ValueType* pGenericValueType = pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector->Get(0);
										if (pGenericValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
										{
											ValueType* pOldValueType = 0;
											NumbatLogic::ValueType* __866030720 = m_pValueType;
#line 371 "../../../Source/Core/AST/Identifier.nll"
											m_pValueType = 0;
#line 371 "../../../Source/Core/AST/Identifier.nll"
											pOldValueType = __866030720;
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
#line 385 "../../../Source/Core/AST/Identifier.nll"
		if (pAST->m_eType == AST::Type::AST_FUNCTION_DECL)
		{
			m_pValueType = new ValueType(ValueType::Type::FUNCTION_DECL);
			m_pValueType->m_pFunctionDecl = (FunctionDecl*)(pAST);
			return;
		}
		else
#line 391 "../../../Source/Core/AST/Identifier.nll"
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
#line 402 "../../../Source/Core/AST/Identifier.nll"
		if (pAST->m_eType == AST::Type::NAMESPACE_DECL)
		{
			m_pValueType = new ValueType(ValueType::Type::NAMESPACE_NODE);
			m_pValueType->m_pNamespaceNode = ((NamespaceDecl*)(pAST))->m_pNamespaceNode;
			return;
		}
		{
#line 410 "../../../Source/Core/AST/Identifier.nll"
			InternalString* sTemp = new InternalString("say what? ");
			pAST->StringifyType(sTemp);
			pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			if (sTemp) delete sTemp;
		}
		AST::Validate(pValidator, pParent);
	}

	void Identifier::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		m_pNameToken->Stringify(pOutputBuilder->m_sOut);
	}

#line 3 "../../../Source/Core/AST/Identifier.nll"
	Identifier::Identifier()
	{
		m_pNameToken = 0;
	}

}

