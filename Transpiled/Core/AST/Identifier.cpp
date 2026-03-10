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
		Token* pToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
#line 12 "../../../Source/Core/AST/Identifier.nll"
		if (pToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 13 "../../../Source/Core/AST/Identifier.nll"
			return 0;
		}
#line 14 "../../../Source/Core/AST/Identifier.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		Identifier* pIdentifier = new Identifier();
#line 17 "../../../Source/Core/AST/Identifier.nll"
		pIdentifier->m_eType = AST::Type::AST_IDENTIFIER;
#line 18 "../../../Source/Core/AST/Identifier.nll"
		pIdentifier->m_pNameToken = pToken;
#line 19 "../../../Source/Core/AST/Identifier.nll"
		pIdentifier->m_pFirstToken = pToken;
#line 21 "../../../Source/Core/AST/Identifier.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::Identifier* __4180376026 = pIdentifier;
#line 23 "../../../Source/Core/AST/Identifier.nll"
		pIdentifier = 0;
		if (pTempOffset) delete pTempOffset;
#line 23 "../../../Source/Core/AST/Identifier.nll"
		return __4180376026;
	}

#line 26 "../../../Source/Core/AST/Identifier.nll"
	AST* Identifier::BaseClone()
	{
		Identifier* pIdentifier = new Identifier();
#line 29 "../../../Source/Core/AST/Identifier.nll"
		pIdentifier->m_eType = m_eType;
#line 30 "../../../Source/Core/AST/Identifier.nll"
		pIdentifier->m_pNameToken = m_pNameToken;
#line 31 "../../../Source/Core/AST/Identifier.nll"
		pIdentifier->m_pFirstToken = m_pFirstToken;
		NumbatLogic::Identifier* __4180441624 = pIdentifier;
#line 32 "../../../Source/Core/AST/Identifier.nll"
		pIdentifier = 0;
#line 32 "../../../Source/Core/AST/Identifier.nll"
		return __4180441624;
	}

#line 35 "../../../Source/Core/AST/Identifier.nll"
	void Identifier::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		const char* sName = m_pNameToken->GetString();
		AST* pContextParent = (pParent != 0) ? (AST*)(pParent) : m_pParent;
		AST* pAST = 0;
		AST* pBase = this;
		AST* pChild = this;
		bool bResolverAmbiguous = false;
#line 46 "../../../Source/Core/AST/Identifier.nll"
		if (pContextParent != 0)
		{
#line 51 "../../../Source/Core/AST/Identifier.nll"
			if (pContextParent->m_eType == AST::Type::AST_ARRAY_LOOKUP)
			{
				ArrayLookup* pAL = (ArrayLookup*)(pContextParent);
#line 54 "../../../Source/Core/AST/Identifier.nll"
				if (pAL->m_pExpression == this)
				{
					AST* pWalk = pAL->m_pParent;
#line 57 "../../../Source/Core/AST/Identifier.nll"
					while (pWalk != 0 && pBase == this)
					{
#line 59 "../../../Source/Core/AST/Identifier.nll"
						if (pWalk->m_eType == AST::Type::AST_OPERATOR_EXPR)
						{
							OperatorExpr* pOpWalk = (OperatorExpr*)(pWalk);
							bool bRightIsArrayLookupOrMulLeft = (pOpWalk->m_pRight == pAL);
#line 63 "../../../Source/Core/AST/Identifier.nll"
							if (!bRightIsArrayLookupOrMulLeft && pOpWalk->m_pRight != 0 && pOpWalk->m_pRight->m_eType == AST::Type::AST_OPERATOR_EXPR)
							{
								OperatorExpr* pRightOp = (OperatorExpr*)(pOpWalk->m_pRight);
#line 66 "../../../Source/Core/AST/Identifier.nll"
								bRightIsArrayLookupOrMulLeft = (pRightOp->m_pLeft == pAL);
							}
#line 68 "../../../Source/Core/AST/Identifier.nll"
							if (pOpWalk->GetOperatorType() == OperatorExpr::OperatorType::SCOPE_RESOLUTION && pOpWalk->m_pLeft != 0 && bRightIsArrayLookupOrMulLeft)
							{
#line 71 "../../../Source/Core/AST/Identifier.nll"
								if (pOpWalk->m_pLeft->m_pValueType == 0)
#line 72 "../../../Source/Core/AST/Identifier.nll"
									pOpWalk->m_pLeft->Validate(pValidator, pOpWalk);
#line 73 "../../../Source/Core/AST/Identifier.nll"
								if (pOpWalk->m_pLeft->m_pValueType != 0)
								{
#line 75 "../../../Source/Core/AST/Identifier.nll"
									if (pOpWalk->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL || pOpWalk->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
									{
#line 78 "../../../Source/Core/AST/Identifier.nll"
										AddClassDeclReference(pOpWalk->m_pLeft->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
#line 79 "../../../Source/Core/AST/Identifier.nll"
										pBase = pOpWalk->m_pLeft->m_pValueType->m_pClassDecl;
#line 80 "../../../Source/Core/AST/Identifier.nll"
										pChild = 0;
#line 81 "../../../Source/Core/AST/Identifier.nll"
										break;
									}
									else
#line 83 "../../../Source/Core/AST/Identifier.nll"
										if (pOpWalk->m_pLeft->m_pValueType->m_eType == ValueType::Type::ENUM_DECL)
										{
#line 85 "../../../Source/Core/AST/Identifier.nll"
											pBase = pOpWalk->m_pLeft->m_pValueType->m_pEnumDecl;
#line 86 "../../../Source/Core/AST/Identifier.nll"
											pChild = 0;
#line 87 "../../../Source/Core/AST/Identifier.nll"
											break;
										}
								}
							}
						}
#line 92 "../../../Source/Core/AST/Identifier.nll"
						pWalk = pWalk->m_pParent;
					}
				}
			}
#line 96 "../../../Source/Core/AST/Identifier.nll"
			if (pContextParent->m_eType == AST::Type::AST_OPERATOR_EXPR)
			{
				OperatorExpr* pOpContext = (OperatorExpr*)(pContextParent);
#line 99 "../../../Source/Core/AST/Identifier.nll"
				if (pOpContext->GetOperatorType() == OperatorExpr::OperatorType::MEMBER_ACCESS && pOpContext->m_pLeft != 0 && pOpContext->m_pLeft->m_pValueType != 0 && pOpContext->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
				{
#line 101 "../../../Source/Core/AST/Identifier.nll"
					AddClassDeclReference(pOpContext->m_pLeft->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
#line 102 "../../../Source/Core/AST/Identifier.nll"
					pBase = pOpContext->m_pLeft->m_pValueType->m_pClassDecl;
#line 103 "../../../Source/Core/AST/Identifier.nll"
					pChild = 0;
				}
				else
#line 105 "../../../Source/Core/AST/Identifier.nll"
					if (pOpContext->GetOperatorType() == OperatorExpr::OperatorType::SCOPE_RESOLUTION && pOpContext->m_pLeft != 0 && pOpContext->m_pLeft->m_pValueType != 0)
					{
#line 107 "../../../Source/Core/AST/Identifier.nll"
						if (pOpContext->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL)
						{
#line 109 "../../../Source/Core/AST/Identifier.nll"
							AddClassDeclReference(pOpContext->m_pLeft->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
#line 110 "../../../Source/Core/AST/Identifier.nll"
							pBase = pOpContext->m_pLeft->m_pValueType->m_pClassDecl;
#line 111 "../../../Source/Core/AST/Identifier.nll"
							pChild = 0;
						}
						else
#line 113 "../../../Source/Core/AST/Identifier.nll"
							if (pOpContext->m_pLeft->m_pValueType->m_eType == ValueType::Type::ENUM_DECL)
							{
#line 115 "../../../Source/Core/AST/Identifier.nll"
								pBase = pOpContext->m_pLeft->m_pValueType->m_pEnumDecl;
#line 116 "../../../Source/Core/AST/Identifier.nll"
								pChild = 0;
							}
							else
#line 118 "../../../Source/Core/AST/Identifier.nll"
								if (pOpContext->m_pLeft->m_pValueType->m_eType == ValueType::Type::NAMESPACE_NODE)
								{
									Vector<NamespaceDecl*>* pNamespaceDeclVector = pOpContext->m_pLeft->m_pValueType->m_pNamespaceNode->m_pNamespaceDeclVector;
									Vector<Symbol*>* pCandidates = new Vector<Symbol*>();
									Vector<Symbol*>* pRelevant = new Vector<Symbol*>();
#line 123 "../../../Source/Core/AST/Identifier.nll"
									for (int i = 0; i < pNamespaceDeclVector->GetSize(); i++)
									{
										NamespaceDecl* pNamespaceDecl = pNamespaceDeclVector->Get(i);
#line 126 "../../../Source/Core/AST/Identifier.nll"
										pCandidates->Clear();
#line 127 "../../../Source/Core/AST/Identifier.nll"
										pValidator->m_pResolver->ResolveFromNode(pNamespaceDecl, sName, pCandidates);
#line 128 "../../../Source/Core/AST/Identifier.nll"
										pRelevant->Clear();
#line 129 "../../../Source/Core/AST/Identifier.nll"
										for (int j = 0; j < pCandidates->GetSize(); j++)
										{
											Symbol* pSym = pCandidates->Get(j);
#line 132 "../../../Source/Core/AST/Identifier.nll"
											if (pSym->m_eKind == Symbol::Kind::CLASS || pSym->m_eKind == Symbol::Kind::ENUM || pSym->m_eKind == Symbol::Kind::VAR || pSym->m_eKind == Symbol::Kind::PARAM || pSym->m_eKind == Symbol::Kind::FUNCTION || pSym->m_eKind == Symbol::Kind::METHOD || pSym->m_eKind == Symbol::Kind::DELEGATE || pSym->m_eKind == Symbol::Kind::ENUM_VALUE || pSym->m_eKind == Symbol::Kind::NAMESPACE)
											{
#line 142 "../../../Source/Core/AST/Identifier.nll"
												pRelevant->PushBack(pSym);
											}
										}
#line 145 "../../../Source/Core/AST/Identifier.nll"
										if (pRelevant->GetSize() == 1 && pRelevant->Get(0)->m_pDeclAST != 0)
										{
#line 147 "../../../Source/Core/AST/Identifier.nll"
											pAST = pRelevant->Get(0)->m_pDeclAST;
#line 148 "../../../Source/Core/AST/Identifier.nll"
											break;
										}
#line 150 "../../../Source/Core/AST/Identifier.nll"
										if (pRelevant->GetSize() > 1)
										{
#line 152 "../../../Source/Core/AST/Identifier.nll"
											bResolverAmbiguous = true;
#line 153 "../../../Source/Core/AST/Identifier.nll"
											break;
										}
									}
									if (pCandidates) delete pCandidates;
									if (pRelevant) delete pRelevant;
								}
								else
								{
#line 159 "../../../Source/Core/AST/Identifier.nll"
									pValidator->AddError("Unexpected left of ::", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
#line 160 "../../../Source/Core/AST/Identifier.nll"
									return;
								}
					}
			}
		}
#line 166 "../../../Source/Core/AST/Identifier.nll"
		if (pAST == 0)
		{
			Vector<Symbol*>* pCandidates = new Vector<Symbol*>();
#line 169 "../../../Source/Core/AST/Identifier.nll"
			pValidator->m_pResolver->ResolveFromNode(pBase, sName, pCandidates);
			Vector<Symbol*>* pRelevant = new Vector<Symbol*>();
#line 172 "../../../Source/Core/AST/Identifier.nll"
			for (int i = 0; i < pCandidates->GetSize(); i++)
			{
				Symbol* pSym = pCandidates->Get(i);
#line 175 "../../../Source/Core/AST/Identifier.nll"
				if (pSym->m_eKind == Symbol::Kind::CLASS || pSym->m_eKind == Symbol::Kind::ENUM || pSym->m_eKind == Symbol::Kind::VAR || pSym->m_eKind == Symbol::Kind::PARAM || pSym->m_eKind == Symbol::Kind::FUNCTION || pSym->m_eKind == Symbol::Kind::METHOD || pSym->m_eKind == Symbol::Kind::DELEGATE || pSym->m_eKind == Symbol::Kind::ENUM_VALUE || pSym->m_eKind == Symbol::Kind::NAMESPACE)
				{
#line 185 "../../../Source/Core/AST/Identifier.nll"
					pRelevant->PushBack(pSym);
				}
			}
#line 189 "../../../Source/Core/AST/Identifier.nll"
			if (pRelevant->GetSize() == 1)
			{
				Symbol* pSymbol = pRelevant->Get(0);
#line 192 "../../../Source/Core/AST/Identifier.nll"
				if (pSymbol->m_pDeclAST != 0)
#line 193 "../../../Source/Core/AST/Identifier.nll"
					pAST = pSymbol->m_pDeclAST;
			}
			else
#line 195 "../../../Source/Core/AST/Identifier.nll"
				if (pRelevant->GetSize() > 1)
#line 196 "../../../Source/Core/AST/Identifier.nll"
					bResolverAmbiguous = true;
			if (pCandidates) delete pCandidates;
			if (pRelevant) delete pRelevant;
		}
#line 199 "../../../Source/Core/AST/Identifier.nll"
		if (pAST == 0)
		{
#line 201 "../../../Source/Core/AST/Identifier.nll"
			if (bResolverAmbiguous)
			{
				InternalString* sAmbiguous = new InternalString("Ambiguous identifier (multiple declarations in scope): ");
#line 204 "../../../Source/Core/AST/Identifier.nll"
				sAmbiguous->Append(sName);
#line 205 "../../../Source/Core/AST/Identifier.nll"
				pValidator->AddError(sAmbiguous->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				if (sAmbiguous) delete sAmbiguous;
			}
			else
			{
				InternalString* sTemp = new InternalString("Identifier Unbeknownst! ");
#line 210 "../../../Source/Core/AST/Identifier.nll"
				sTemp->Append(sName);
#line 211 "../../../Source/Core/AST/Identifier.nll"
				if (pContextParent != 0)
#line 212 "../../../Source/Core/AST/Identifier.nll"
					sTemp->Append(" has parent");
#line 213 "../../../Source/Core/AST/Identifier.nll"
				sTemp->Append(" base: ");
#line 214 "../../../Source/Core/AST/Identifier.nll"
				pBase->StringifyType(sTemp);
#line 215 "../../../Source/Core/AST/Identifier.nll"
				pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				if (sTemp) delete sTemp;
			}
#line 217 "../../../Source/Core/AST/Identifier.nll"
			return;
		}
#line 220 "../../../Source/Core/AST/Identifier.nll"
		if (pAST->m_eType == AST::Type::AST_CLASS_DECL)
		{
#line 222 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType = new ValueType(ValueType::Type::CLASS_DECL);
#line 223 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType->m_pClassDecl = (ClassDecl*)(pAST);
#line 226 "../../../Source/Core/AST/Identifier.nll"
			AddClassDeclReference(m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
			AST* pCheckParent = m_pParent;
			AST* pCurrent = this;
#line 231 "../../../Source/Core/AST/Identifier.nll"
			for (int i = 0; i < 5; i++)
			{
#line 233 "../../../Source/Core/AST/Identifier.nll"
				if (pCheckParent == 0)
#line 234 "../../../Source/Core/AST/Identifier.nll"
					break;
#line 235 "../../../Source/Core/AST/Identifier.nll"
				if (pCheckParent->m_eType == AST::Type::AST_VAR_DECL)
				{
					VarDecl* pVarDecl = (VarDecl*)(pCheckParent);
					bool bInArraySize = false;
#line 240 "../../../Source/Core/AST/Identifier.nll"
					if (pVarDecl->m_pArraySizeVector != 0)
					{
#line 242 "../../../Source/Core/AST/Identifier.nll"
						for (int j = 0; j < pVarDecl->m_pArraySizeVector->GetSize(); j++)
						{
#line 244 "../../../Source/Core/AST/Identifier.nll"
							if (pCurrent == pVarDecl->m_pArraySizeVector->Get(j))
							{
#line 246 "../../../Source/Core/AST/Identifier.nll"
								bInArraySize = true;
#line 247 "../../../Source/Core/AST/Identifier.nll"
								break;
							}
						}
					}
#line 253 "../../../Source/Core/AST/Identifier.nll"
					if (bInArraySize && pVarDecl->m_pParent != 0 && pVarDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
#line 254 "../../../Source/Core/AST/Identifier.nll"
						AddClassDeclReference(m_pValueType->m_pClassDecl, AST::OutputFile::HEADER, false);
#line 257 "../../../Source/Core/AST/Identifier.nll"
					if (pCurrent == pVarDecl->m_pAssignment && pVarDecl->m_pParent != 0 && pVarDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
					{
						MemberVarDecl* pMemberVarDecl = (MemberVarDecl*)(pVarDecl->m_pParent);
#line 260 "../../../Source/Core/AST/Identifier.nll"
						if (pMemberVarDecl->m_bStatic)
#line 261 "../../../Source/Core/AST/Identifier.nll"
							AddClassDeclReference(m_pValueType->m_pClassDecl, AST::OutputFile::HEADER, false);
					}
#line 264 "../../../Source/Core/AST/Identifier.nll"
					break;
				}
#line 267 "../../../Source/Core/AST/Identifier.nll"
				pCurrent = pCheckParent;
#line 268 "../../../Source/Core/AST/Identifier.nll"
				pCheckParent = pCheckParent->m_pParent;
			}
#line 271 "../../../Source/Core/AST/Identifier.nll"
			return;
		}
		else
#line 273 "../../../Source/Core/AST/Identifier.nll"
			if (pAST->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
			{
				MemberClassDecl* pMemberClassDecl = (MemberClassDecl*)(pAST);
#line 276 "../../../Source/Core/AST/Identifier.nll"
				if (pMemberClassDecl->m_pClassDecl != 0)
				{
#line 278 "../../../Source/Core/AST/Identifier.nll"
					m_pValueType = new ValueType(ValueType::Type::CLASS_DECL);
#line 279 "../../../Source/Core/AST/Identifier.nll"
					m_pValueType->m_pClassDecl = pMemberClassDecl->m_pClassDecl;
#line 280 "../../../Source/Core/AST/Identifier.nll"
					AddClassDeclReference(m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
				}
#line 282 "../../../Source/Core/AST/Identifier.nll"
				return;
			}
#line 285 "../../../Source/Core/AST/Identifier.nll"
		if (pAST->m_eType == AST::Type::AST_ENUM_DECL)
		{
#line 287 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType = new ValueType(ValueType::Type::ENUM_DECL);
#line 288 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType->m_pEnumDecl = (EnumDecl*)(pAST);
#line 289 "../../../Source/Core/AST/Identifier.nll"
			return;
		}
		else
#line 291 "../../../Source/Core/AST/Identifier.nll"
			if (pAST->m_eType == AST::Type::AST_MEMBER_ENUM_DECL)
			{
				MemberEnumDecl* pMemberEnum = (MemberEnumDecl*)(pAST);
#line 294 "../../../Source/Core/AST/Identifier.nll"
				if (pMemberEnum->m_pEnumDecl != 0)
				{
#line 296 "../../../Source/Core/AST/Identifier.nll"
					m_pValueType = new ValueType(ValueType::Type::ENUM_DECL);
#line 297 "../../../Source/Core/AST/Identifier.nll"
					m_pValueType->m_pEnumDecl = pMemberEnum->m_pEnumDecl;
#line 298 "../../../Source/Core/AST/Identifier.nll"
					return;
				}
			}
#line 302 "../../../Source/Core/AST/Identifier.nll"
		if (pAST->m_eType == AST::Type::ENUM_DECL_VALUE)
		{
#line 304 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType = new ValueType(ValueType::Type::ENUM_DECL_VALUE);
#line 305 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType->m_pEnumDeclValue = (EnumDeclValue*)(pAST);
#line 306 "../../../Source/Core/AST/Identifier.nll"
			return;
		}
#line 309 "../../../Source/Core/AST/Identifier.nll"
		if (pAST->m_eType == AST::Type::AST_VAR_DECL)
		{
			VarDecl* pVarDecl = (VarDecl*)(pAST);
#line 312 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType = pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
#line 314 "../../../Source/Core/AST/Identifier.nll"
			if (m_pValueType == 0)
			{
#line 316 "../../../Source/Core/AST/Identifier.nll"
				pValidator->AddError("Could not create ValueType for VarDecl", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
#line 317 "../../../Source/Core/AST/Identifier.nll"
				return;
			}
#line 321 "../../../Source/Core/AST/Identifier.nll"
			if (m_pValueType->m_eType == ValueType::Type::GENERIC_TYPE_DECL_VALUE)
			{
#line 323 "../../../Source/Core/AST/Identifier.nll"
				if (pParent != 0)
				{
#line 325 "../../../Source/Core/AST/Identifier.nll"
					if (pParent->GetOperatorType() == OperatorExpr::OperatorType::MEMBER_ACCESS && pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
					{
#line 327 "../../../Source/Core/AST/Identifier.nll"
						if (pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector != 0)
						{
#line 329 "../../../Source/Core/AST/Identifier.nll"
							if (pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector->GetSize() > 0)
							{
								ValueType* pGenericValueType = pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector->Get(0);
#line 332 "../../../Source/Core/AST/Identifier.nll"
								if (pGenericValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
								{
									ValueType* pOldValueType = 0;
									NumbatLogic::ValueType* __865768328 = m_pValueType;
#line 335 "../../../Source/Core/AST/Identifier.nll"
									m_pValueType = 0;
#line 335 "../../../Source/Core/AST/Identifier.nll"
									pOldValueType = __865768328;
#line 336 "../../../Source/Core/AST/Identifier.nll"
									m_pValueType = pGenericValueType->Clone();
#line 337 "../../../Source/Core/AST/Identifier.nll"
									m_pValueType->m_ePointerType = pOldValueType->m_ePointerType;
									if (pOldValueType) delete pOldValueType;
								}
							}
						}
					}
				}
			}
#line 346 "../../../Source/Core/AST/Identifier.nll"
			return;
		}
		else
#line 348 "../../../Source/Core/AST/Identifier.nll"
			if (pAST->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
			{
				MemberVarDecl* pMemberVarDecl = (MemberVarDecl*)(pAST);
#line 351 "../../../Source/Core/AST/Identifier.nll"
				if (pMemberVarDecl->m_pVarDecl != 0)
				{
					VarDecl* pVarDecl = pMemberVarDecl->m_pVarDecl;
#line 354 "../../../Source/Core/AST/Identifier.nll"
					m_pValueType = pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
#line 356 "../../../Source/Core/AST/Identifier.nll"
					if (m_pValueType == 0)
					{
#line 358 "../../../Source/Core/AST/Identifier.nll"
						pValidator->AddError("Could not create ValueType for MemberVarDecl", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
#line 359 "../../../Source/Core/AST/Identifier.nll"
						return;
					}
#line 363 "../../../Source/Core/AST/Identifier.nll"
					if (m_pValueType->m_eType == ValueType::Type::GENERIC_TYPE_DECL_VALUE)
					{
#line 365 "../../../Source/Core/AST/Identifier.nll"
						if (pParent != 0)
						{
#line 367 "../../../Source/Core/AST/Identifier.nll"
							if (pParent->GetOperatorType() == OperatorExpr::OperatorType::MEMBER_ACCESS && pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
							{
#line 369 "../../../Source/Core/AST/Identifier.nll"
								if (pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector != 0)
								{
#line 371 "../../../Source/Core/AST/Identifier.nll"
									if (pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector->GetSize() > 0)
									{
										ValueType* pGenericValueType = pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector->Get(0);
#line 374 "../../../Source/Core/AST/Identifier.nll"
										if (pGenericValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
										{
											ValueType* pOldValueType = 0;
											NumbatLogic::ValueType* __866030726 = m_pValueType;
#line 377 "../../../Source/Core/AST/Identifier.nll"
											m_pValueType = 0;
#line 377 "../../../Source/Core/AST/Identifier.nll"
											pOldValueType = __866030726;
#line 378 "../../../Source/Core/AST/Identifier.nll"
											m_pValueType = pGenericValueType->Clone();
#line 379 "../../../Source/Core/AST/Identifier.nll"
											m_pValueType->m_ePointerType = pOldValueType->m_ePointerType;
											if (pOldValueType) delete pOldValueType;
										}
									}
								}
							}
						}
					}
#line 387 "../../../Source/Core/AST/Identifier.nll"
					return;
				}
			}
#line 391 "../../../Source/Core/AST/Identifier.nll"
		if (pAST->m_eType == AST::Type::AST_FUNCTION_DECL)
		{
#line 393 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType = new ValueType(ValueType::Type::FUNCTION_DECL);
#line 394 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType->m_pFunctionDecl = (FunctionDecl*)(pAST);
#line 395 "../../../Source/Core/AST/Identifier.nll"
			return;
		}
		else
#line 397 "../../../Source/Core/AST/Identifier.nll"
			if (pAST->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
			{
				MemberFunctionDecl* pMFD = (MemberFunctionDecl*)(pAST);
#line 400 "../../../Source/Core/AST/Identifier.nll"
				if (pMFD->m_pFunctionDecl != 0)
				{
#line 402 "../../../Source/Core/AST/Identifier.nll"
					m_pValueType = new ValueType(ValueType::Type::FUNCTION_DECL);
#line 403 "../../../Source/Core/AST/Identifier.nll"
					m_pValueType->m_pFunctionDecl = pMFD->m_pFunctionDecl;
#line 404 "../../../Source/Core/AST/Identifier.nll"
					return;
				}
			}
#line 408 "../../../Source/Core/AST/Identifier.nll"
		if (pAST->m_eType == AST::Type::NAMESPACE_DECL)
		{
#line 410 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType = new ValueType(ValueType::Type::NAMESPACE_NODE);
#line 411 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType->m_pNamespaceNode = ((NamespaceDecl*)(pAST))->m_pNamespaceNode;
#line 412 "../../../Source/Core/AST/Identifier.nll"
			return;
		}
		{
			InternalString* sTemp = new InternalString("say what? ");
#line 417 "../../../Source/Core/AST/Identifier.nll"
			pAST->StringifyType(sTemp);
#line 418 "../../../Source/Core/AST/Identifier.nll"
			pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			if (sTemp) delete sTemp;
		}
#line 421 "../../../Source/Core/AST/Identifier.nll"
		AST::Validate(pValidator, pParent);
	}

#line 424 "../../../Source/Core/AST/Identifier.nll"
	void Identifier::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 426 "../../../Source/Core/AST/Identifier.nll"
		m_pNameToken->Stringify(pOutputBuilder->m_sOut);
	}

#line 3 "../../../Source/Core/AST/Identifier.nll"
	Identifier::Identifier()
	{
		m_pNameToken = 0;
	}

}

