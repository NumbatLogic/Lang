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
#line 1 "../../../Source/Core/AST/Identifier.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/Identifier.nll"
#line 8 "../../../Source/Core/AST/Identifier.nll"
	Identifier* Identifier::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
#line 13 "../../../Source/Core/AST/Identifier.nll"
		if (pToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 14 "../../../Source/Core/AST/Identifier.nll"
			return 0;
		}
#line 15 "../../../Source/Core/AST/Identifier.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
		Identifier* pIdentifier = new Identifier();
#line 18 "../../../Source/Core/AST/Identifier.nll"
		pIdentifier->m_eType = AST::Type::AST_IDENTIFIER;
#line 19 "../../../Source/Core/AST/Identifier.nll"
		pIdentifier->m_pNameToken = pToken;
#line 20 "../../../Source/Core/AST/Identifier.nll"
		pIdentifier->m_pFirstToken = pToken;
#line 22 "../../../Source/Core/AST/Identifier.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::Identifier* __4180376026 = pIdentifier;
#line 24 "../../../Source/Core/AST/Identifier.nll"
		pIdentifier = 0;
		if (pTempOffset) delete pTempOffset;
#line 24 "../../../Source/Core/AST/Identifier.nll"
		return __4180376026;
	}

#line 27 "../../../Source/Core/AST/Identifier.nll"
	AST* Identifier::BaseClone()
	{
		Identifier* pIdentifier = new Identifier();
#line 30 "../../../Source/Core/AST/Identifier.nll"
		pIdentifier->m_eType = m_eType;
#line 31 "../../../Source/Core/AST/Identifier.nll"
		pIdentifier->m_pNameToken = m_pNameToken;
#line 32 "../../../Source/Core/AST/Identifier.nll"
		pIdentifier->m_pFirstToken = m_pFirstToken;
		NumbatLogic::Identifier* __4180441624 = pIdentifier;
#line 33 "../../../Source/Core/AST/Identifier.nll"
		pIdentifier = 0;
#line 33 "../../../Source/Core/AST/Identifier.nll"
		return __4180441624;
	}

#line 36 "../../../Source/Core/AST/Identifier.nll"
	void Identifier::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		const char* sName = m_pNameToken->GetString();
		AST* pContextParent = (pParent != 0) ? (AST*)(pParent) : m_pParent;
		AST* pAST = 0;
		AST* pBase = this;
		AST* pChild = this;
		bool bResolverAmbiguous = false;
#line 47 "../../../Source/Core/AST/Identifier.nll"
		if (pContextParent != 0)
		{
#line 52 "../../../Source/Core/AST/Identifier.nll"
			if (pContextParent->m_eType == AST::Type::AST_ARRAY_LOOKUP)
			{
				ArrayLookup* pAL = (ArrayLookup*)(pContextParent);
#line 55 "../../../Source/Core/AST/Identifier.nll"
				if (pAL->m_pExpression == this)
				{
					AST* pWalk = pAL->m_pParent;
#line 58 "../../../Source/Core/AST/Identifier.nll"
					while (pWalk != 0 && pBase == this)
					{
#line 60 "../../../Source/Core/AST/Identifier.nll"
						if (pWalk->m_eType == AST::Type::AST_OPERATOR_EXPR)
						{
							OperatorExpr* pOpWalk = (OperatorExpr*)(pWalk);
							bool bRightIsArrayLookupOrMulLeft = (pOpWalk->m_pRight == pAL);
#line 64 "../../../Source/Core/AST/Identifier.nll"
							if (!bRightIsArrayLookupOrMulLeft && pOpWalk->m_pRight != 0 && pOpWalk->m_pRight->m_eType == AST::Type::AST_OPERATOR_EXPR)
							{
								OperatorExpr* pRightOp = (OperatorExpr*)(pOpWalk->m_pRight);
#line 67 "../../../Source/Core/AST/Identifier.nll"
								bRightIsArrayLookupOrMulLeft = (pRightOp->m_pLeft == pAL);
							}
#line 69 "../../../Source/Core/AST/Identifier.nll"
							if (pOpWalk->GetOperatorType() == OperatorExpr::OperatorType::SCOPE_RESOLUTION && pOpWalk->m_pLeft != 0 && bRightIsArrayLookupOrMulLeft)
							{
#line 72 "../../../Source/Core/AST/Identifier.nll"
								if (pOpWalk->m_pLeft->m_pValueType == 0)
#line 73 "../../../Source/Core/AST/Identifier.nll"
									pOpWalk->m_pLeft->Validate(pValidator, pOpWalk);
#line 74 "../../../Source/Core/AST/Identifier.nll"
								if (pOpWalk->m_pLeft->m_pValueType != 0)
								{
#line 76 "../../../Source/Core/AST/Identifier.nll"
									if (pOpWalk->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL || pOpWalk->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
									{
#line 79 "../../../Source/Core/AST/Identifier.nll"
										AddClassDeclReference(pOpWalk->m_pLeft->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
#line 80 "../../../Source/Core/AST/Identifier.nll"
										pBase = pOpWalk->m_pLeft->m_pValueType->m_pClassDecl;
#line 81 "../../../Source/Core/AST/Identifier.nll"
										pChild = 0;
#line 82 "../../../Source/Core/AST/Identifier.nll"
										break;
									}
									else
#line 84 "../../../Source/Core/AST/Identifier.nll"
										if (pOpWalk->m_pLeft->m_pValueType->m_eType == ValueType::Type::ENUM_DECL)
										{
#line 86 "../../../Source/Core/AST/Identifier.nll"
											pBase = pOpWalk->m_pLeft->m_pValueType->m_pEnumDecl;
#line 87 "../../../Source/Core/AST/Identifier.nll"
											pChild = 0;
#line 88 "../../../Source/Core/AST/Identifier.nll"
											break;
										}
								}
							}
						}
#line 93 "../../../Source/Core/AST/Identifier.nll"
						pWalk = pWalk->m_pParent;
					}
				}
			}
#line 97 "../../../Source/Core/AST/Identifier.nll"
			if (pContextParent->m_eType == AST::Type::AST_OPERATOR_EXPR)
			{
				OperatorExpr* pOpContext = (OperatorExpr*)(pContextParent);
#line 100 "../../../Source/Core/AST/Identifier.nll"
				if (pOpContext->GetOperatorType() == OperatorExpr::OperatorType::MEMBER_ACCESS && pOpContext->m_pLeft != 0 && pOpContext->m_pLeft->m_pValueType != 0 && pOpContext->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
				{
#line 102 "../../../Source/Core/AST/Identifier.nll"
					AddClassDeclReference(pOpContext->m_pLeft->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
#line 103 "../../../Source/Core/AST/Identifier.nll"
					pBase = pOpContext->m_pLeft->m_pValueType->m_pClassDecl;
#line 104 "../../../Source/Core/AST/Identifier.nll"
					pChild = 0;
				}
				else
#line 106 "../../../Source/Core/AST/Identifier.nll"
					if (pOpContext->GetOperatorType() == OperatorExpr::OperatorType::SCOPE_RESOLUTION && pOpContext->m_pLeft != 0 && pOpContext->m_pLeft->m_pValueType != 0)
					{
#line 108 "../../../Source/Core/AST/Identifier.nll"
						if (pOpContext->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL)
						{
#line 110 "../../../Source/Core/AST/Identifier.nll"
							AddClassDeclReference(pOpContext->m_pLeft->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
#line 111 "../../../Source/Core/AST/Identifier.nll"
							pBase = pOpContext->m_pLeft->m_pValueType->m_pClassDecl;
#line 112 "../../../Source/Core/AST/Identifier.nll"
							pChild = 0;
						}
						else
#line 114 "../../../Source/Core/AST/Identifier.nll"
							if (pOpContext->m_pLeft->m_pValueType->m_eType == ValueType::Type::ENUM_DECL)
							{
#line 116 "../../../Source/Core/AST/Identifier.nll"
								pBase = pOpContext->m_pLeft->m_pValueType->m_pEnumDecl;
#line 117 "../../../Source/Core/AST/Identifier.nll"
								pChild = 0;
							}
							else
#line 119 "../../../Source/Core/AST/Identifier.nll"
								if (pOpContext->m_pLeft->m_pValueType->m_eType == ValueType::Type::NAMESPACE_NODE)
								{
									Vector<NamespaceDecl*>* pNamespaceDeclVector = pOpContext->m_pLeft->m_pValueType->m_pNamespaceNode->m_pNamespaceDeclVector;
									Vector<Symbol*>* pCandidates = new Vector<Symbol*>();
									Vector<Symbol*>* pRelevant = new Vector<Symbol*>();
#line 124 "../../../Source/Core/AST/Identifier.nll"
									for (int i = 0; i < pNamespaceDeclVector->GetSize(); i++)
									{
										NamespaceDecl* pNamespaceDecl = pNamespaceDeclVector->Get(i);
#line 127 "../../../Source/Core/AST/Identifier.nll"
										pCandidates->Clear();
#line 128 "../../../Source/Core/AST/Identifier.nll"
										pValidator->m_pResolver->ResolveFromNode(pNamespaceDecl, sName, pCandidates);
#line 129 "../../../Source/Core/AST/Identifier.nll"
										pRelevant->Clear();
#line 130 "../../../Source/Core/AST/Identifier.nll"
										for (int j = 0; j < pCandidates->GetSize(); j++)
										{
											Symbol* pSym = pCandidates->Get(j);
#line 133 "../../../Source/Core/AST/Identifier.nll"
											if (pSym->m_eKind == Symbol::Kind::CLASS || pSym->m_eKind == Symbol::Kind::ENUM || pSym->m_eKind == Symbol::Kind::VAR || pSym->m_eKind == Symbol::Kind::PARAM || pSym->m_eKind == Symbol::Kind::FUNCTION || pSym->m_eKind == Symbol::Kind::METHOD || pSym->m_eKind == Symbol::Kind::DELEGATE || pSym->m_eKind == Symbol::Kind::ENUM_VALUE || pSym->m_eKind == Symbol::Kind::NAMESPACE)
											{
#line 143 "../../../Source/Core/AST/Identifier.nll"
												pRelevant->PushBack(pSym);
											}
										}
#line 146 "../../../Source/Core/AST/Identifier.nll"
										if (pRelevant->GetSize() == 1 && pRelevant->Get(0)->m_pDeclAST != 0)
										{
#line 148 "../../../Source/Core/AST/Identifier.nll"
											pAST = pRelevant->Get(0)->m_pDeclAST;
#line 149 "../../../Source/Core/AST/Identifier.nll"
											break;
										}
#line 151 "../../../Source/Core/AST/Identifier.nll"
										if (pRelevant->GetSize() > 1)
										{
#line 153 "../../../Source/Core/AST/Identifier.nll"
											bResolverAmbiguous = true;
#line 154 "../../../Source/Core/AST/Identifier.nll"
											break;
										}
									}
									if (pCandidates) delete pCandidates;
									if (pRelevant) delete pRelevant;
								}
								else
								{
#line 160 "../../../Source/Core/AST/Identifier.nll"
									pValidator->AddError("Unexpected left of ::", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
#line 161 "../../../Source/Core/AST/Identifier.nll"
									return;
								}
					}
			}
		}
#line 167 "../../../Source/Core/AST/Identifier.nll"
		if (pAST == 0)
		{
			Vector<Symbol*>* pCandidates = new Vector<Symbol*>();
#line 170 "../../../Source/Core/AST/Identifier.nll"
			pValidator->m_pResolver->ResolveFromNode(pBase, sName, pCandidates);
			Vector<Symbol*>* pRelevant = new Vector<Symbol*>();
#line 173 "../../../Source/Core/AST/Identifier.nll"
			for (int i = 0; i < pCandidates->GetSize(); i++)
			{
				Symbol* pSym = pCandidates->Get(i);
#line 176 "../../../Source/Core/AST/Identifier.nll"
				if (pSym->m_eKind == Symbol::Kind::CLASS || pSym->m_eKind == Symbol::Kind::ENUM || pSym->m_eKind == Symbol::Kind::VAR || pSym->m_eKind == Symbol::Kind::PARAM || pSym->m_eKind == Symbol::Kind::FUNCTION || pSym->m_eKind == Symbol::Kind::METHOD || pSym->m_eKind == Symbol::Kind::DELEGATE || pSym->m_eKind == Symbol::Kind::ENUM_VALUE || pSym->m_eKind == Symbol::Kind::NAMESPACE)
				{
#line 186 "../../../Source/Core/AST/Identifier.nll"
					pRelevant->PushBack(pSym);
				}
			}
#line 190 "../../../Source/Core/AST/Identifier.nll"
			if (pRelevant->GetSize() == 1)
			{
				Symbol* pSymbol = pRelevant->Get(0);
#line 193 "../../../Source/Core/AST/Identifier.nll"
				if (pSymbol->m_pDeclAST != 0)
#line 194 "../../../Source/Core/AST/Identifier.nll"
					pAST = pSymbol->m_pDeclAST;
			}
			else
#line 196 "../../../Source/Core/AST/Identifier.nll"
				if (pRelevant->GetSize() > 1)
#line 197 "../../../Source/Core/AST/Identifier.nll"
					bResolverAmbiguous = true;
			if (pCandidates) delete pCandidates;
			if (pRelevant) delete pRelevant;
		}
#line 200 "../../../Source/Core/AST/Identifier.nll"
		if (pAST == 0)
		{
#line 202 "../../../Source/Core/AST/Identifier.nll"
			if (bResolverAmbiguous)
			{
				InternalString* sAmbiguous = new InternalString("Ambiguous identifier (multiple declarations in scope): ");
#line 205 "../../../Source/Core/AST/Identifier.nll"
				sAmbiguous->Append(sName);
#line 206 "../../../Source/Core/AST/Identifier.nll"
				pValidator->AddError(sAmbiguous->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				if (sAmbiguous) delete sAmbiguous;
			}
			else
			{
				InternalString* sTemp = new InternalString("Identifier Unbeknownst! ");
#line 211 "../../../Source/Core/AST/Identifier.nll"
				sTemp->Append(sName);
#line 212 "../../../Source/Core/AST/Identifier.nll"
				if (pContextParent != 0)
#line 213 "../../../Source/Core/AST/Identifier.nll"
					sTemp->Append(" has parent");
#line 214 "../../../Source/Core/AST/Identifier.nll"
				sTemp->Append(" base: ");
#line 215 "../../../Source/Core/AST/Identifier.nll"
				pBase->StringifyType(sTemp);
#line 216 "../../../Source/Core/AST/Identifier.nll"
				pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				if (sTemp) delete sTemp;
			}
#line 218 "../../../Source/Core/AST/Identifier.nll"
			return;
		}
#line 221 "../../../Source/Core/AST/Identifier.nll"
		if (pAST->m_eType == AST::Type::AST_CLASS_DECL)
		{
#line 223 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType = new ValueType(ValueType::Type::CLASS_DECL);
#line 224 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType->m_pClassDecl = (ClassDecl*)(pAST);
#line 227 "../../../Source/Core/AST/Identifier.nll"
			AddClassDeclReference(m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
			AST* pCheckParent = m_pParent;
			AST* pCurrent = this;
#line 232 "../../../Source/Core/AST/Identifier.nll"
			for (int i = 0; i < 5; i++)
			{
#line 234 "../../../Source/Core/AST/Identifier.nll"
				if (pCheckParent == 0)
#line 235 "../../../Source/Core/AST/Identifier.nll"
					break;
#line 236 "../../../Source/Core/AST/Identifier.nll"
				if (pCheckParent->m_eType == AST::Type::AST_VAR_DECL)
				{
					VarDecl* pVarDecl = (VarDecl*)(pCheckParent);
					bool bInArraySize = false;
#line 241 "../../../Source/Core/AST/Identifier.nll"
					if (pVarDecl->m_pArraySizeVector != 0)
					{
#line 243 "../../../Source/Core/AST/Identifier.nll"
						for (int j = 0; j < pVarDecl->m_pArraySizeVector->GetSize(); j++)
						{
#line 245 "../../../Source/Core/AST/Identifier.nll"
							if (pCurrent == pVarDecl->m_pArraySizeVector->Get(j))
							{
#line 247 "../../../Source/Core/AST/Identifier.nll"
								bInArraySize = true;
#line 248 "../../../Source/Core/AST/Identifier.nll"
								break;
							}
						}
					}
#line 254 "../../../Source/Core/AST/Identifier.nll"
					if (bInArraySize && pVarDecl->m_pParent != 0 && pVarDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
#line 255 "../../../Source/Core/AST/Identifier.nll"
						AddClassDeclReference(m_pValueType->m_pClassDecl, AST::OutputFile::HEADER, false);
#line 258 "../../../Source/Core/AST/Identifier.nll"
					if (pCurrent == pVarDecl->m_pAssignment && pVarDecl->m_pParent != 0 && pVarDecl->m_pParent->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
					{
						MemberVarDecl* pMemberVarDecl = (MemberVarDecl*)(pVarDecl->m_pParent);
#line 261 "../../../Source/Core/AST/Identifier.nll"
						if (pMemberVarDecl->m_bStatic)
#line 262 "../../../Source/Core/AST/Identifier.nll"
							AddClassDeclReference(m_pValueType->m_pClassDecl, AST::OutputFile::HEADER, false);
					}
#line 265 "../../../Source/Core/AST/Identifier.nll"
					break;
				}
#line 268 "../../../Source/Core/AST/Identifier.nll"
				pCurrent = pCheckParent;
#line 269 "../../../Source/Core/AST/Identifier.nll"
				pCheckParent = pCheckParent->m_pParent;
			}
#line 272 "../../../Source/Core/AST/Identifier.nll"
			return;
		}
		else
#line 274 "../../../Source/Core/AST/Identifier.nll"
			if (pAST->m_eType == AST::Type::AST_MEMBER_CLASS_DECL)
			{
				MemberClassDecl* pMemberClassDecl = (MemberClassDecl*)(pAST);
#line 277 "../../../Source/Core/AST/Identifier.nll"
				if (pMemberClassDecl->m_pClassDecl != 0)
				{
#line 279 "../../../Source/Core/AST/Identifier.nll"
					m_pValueType = new ValueType(ValueType::Type::CLASS_DECL);
#line 280 "../../../Source/Core/AST/Identifier.nll"
					m_pValueType->m_pClassDecl = pMemberClassDecl->m_pClassDecl;
#line 281 "../../../Source/Core/AST/Identifier.nll"
					AddClassDeclReference(m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
				}
#line 283 "../../../Source/Core/AST/Identifier.nll"
				return;
			}
#line 286 "../../../Source/Core/AST/Identifier.nll"
		if (pAST->m_eType == AST::Type::AST_ENUM_DECL)
		{
#line 288 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType = new ValueType(ValueType::Type::ENUM_DECL);
#line 289 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType->m_pEnumDecl = (EnumDecl*)(pAST);
#line 290 "../../../Source/Core/AST/Identifier.nll"
			return;
		}
		else
#line 292 "../../../Source/Core/AST/Identifier.nll"
			if (pAST->m_eType == AST::Type::AST_MEMBER_ENUM_DECL)
			{
				MemberEnumDecl* pMemberEnum = (MemberEnumDecl*)(pAST);
#line 295 "../../../Source/Core/AST/Identifier.nll"
				if (pMemberEnum->m_pEnumDecl != 0)
				{
#line 297 "../../../Source/Core/AST/Identifier.nll"
					m_pValueType = new ValueType(ValueType::Type::ENUM_DECL);
#line 298 "../../../Source/Core/AST/Identifier.nll"
					m_pValueType->m_pEnumDecl = pMemberEnum->m_pEnumDecl;
#line 299 "../../../Source/Core/AST/Identifier.nll"
					return;
				}
			}
#line 303 "../../../Source/Core/AST/Identifier.nll"
		if (pAST->m_eType == AST::Type::ENUM_DECL_VALUE)
		{
#line 305 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType = new ValueType(ValueType::Type::ENUM_DECL_VALUE);
#line 306 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType->m_pEnumDeclValue = (EnumDeclValue*)(pAST);
#line 307 "../../../Source/Core/AST/Identifier.nll"
			return;
		}
#line 310 "../../../Source/Core/AST/Identifier.nll"
		if (pAST->m_eType == AST::Type::AST_VAR_DECL)
		{
			VarDecl* pVarDecl = (VarDecl*)(pAST);
#line 313 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType = pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
#line 315 "../../../Source/Core/AST/Identifier.nll"
			if (m_pValueType == 0)
			{
#line 317 "../../../Source/Core/AST/Identifier.nll"
				pValidator->AddError("Could not create ValueType for VarDecl", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
#line 318 "../../../Source/Core/AST/Identifier.nll"
				return;
			}
#line 322 "../../../Source/Core/AST/Identifier.nll"
			if (m_pValueType->m_eType == ValueType::Type::GENERIC_TYPE_DECL_VALUE)
			{
#line 324 "../../../Source/Core/AST/Identifier.nll"
				if (pParent != 0)
				{
#line 326 "../../../Source/Core/AST/Identifier.nll"
					if (pParent->GetOperatorType() == OperatorExpr::OperatorType::MEMBER_ACCESS && pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
					{
#line 328 "../../../Source/Core/AST/Identifier.nll"
						if (pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector != 0)
						{
#line 330 "../../../Source/Core/AST/Identifier.nll"
							if (pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector->GetSize() > 0)
							{
								ValueType* pGenericValueType = pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector->Get(0);
#line 333 "../../../Source/Core/AST/Identifier.nll"
								if (pGenericValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
								{
									ValueType* pOldValueType = 0;
									NumbatLogic::ValueType* __865768328 = m_pValueType;
#line 336 "../../../Source/Core/AST/Identifier.nll"
									m_pValueType = 0;
#line 336 "../../../Source/Core/AST/Identifier.nll"
									pOldValueType = __865768328;
#line 337 "../../../Source/Core/AST/Identifier.nll"
									m_pValueType = pGenericValueType->Clone();
#line 338 "../../../Source/Core/AST/Identifier.nll"
									m_pValueType->m_ePointerType = pOldValueType->m_ePointerType;
									if (pOldValueType) delete pOldValueType;
								}
							}
						}
					}
				}
			}
#line 347 "../../../Source/Core/AST/Identifier.nll"
			return;
		}
		else
#line 349 "../../../Source/Core/AST/Identifier.nll"
			if (pAST->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
			{
				MemberVarDecl* pMemberVarDecl = (MemberVarDecl*)(pAST);
#line 352 "../../../Source/Core/AST/Identifier.nll"
				if (pMemberVarDecl->m_pVarDecl != 0)
				{
					VarDecl* pVarDecl = pMemberVarDecl->m_pVarDecl;
#line 355 "../../../Source/Core/AST/Identifier.nll"
					m_pValueType = pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
#line 357 "../../../Source/Core/AST/Identifier.nll"
					if (m_pValueType == 0)
					{
#line 359 "../../../Source/Core/AST/Identifier.nll"
						pValidator->AddError("Could not create ValueType for MemberVarDecl", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
#line 360 "../../../Source/Core/AST/Identifier.nll"
						return;
					}
#line 364 "../../../Source/Core/AST/Identifier.nll"
					if (m_pValueType->m_eType == ValueType::Type::GENERIC_TYPE_DECL_VALUE)
					{
#line 366 "../../../Source/Core/AST/Identifier.nll"
						if (pParent != 0)
						{
#line 368 "../../../Source/Core/AST/Identifier.nll"
							if (pParent->GetOperatorType() == OperatorExpr::OperatorType::MEMBER_ACCESS && pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
							{
#line 370 "../../../Source/Core/AST/Identifier.nll"
								if (pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector != 0)
								{
#line 372 "../../../Source/Core/AST/Identifier.nll"
									if (pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector->GetSize() > 0)
									{
										ValueType* pGenericValueType = pParent->m_pLeft->m_pValueType->m_pGenericValueTypeVector->Get(0);
#line 375 "../../../Source/Core/AST/Identifier.nll"
										if (pGenericValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
										{
											ValueType* pOldValueType = 0;
											NumbatLogic::ValueType* __866030726 = m_pValueType;
#line 378 "../../../Source/Core/AST/Identifier.nll"
											m_pValueType = 0;
#line 378 "../../../Source/Core/AST/Identifier.nll"
											pOldValueType = __866030726;
#line 379 "../../../Source/Core/AST/Identifier.nll"
											m_pValueType = pGenericValueType->Clone();
#line 380 "../../../Source/Core/AST/Identifier.nll"
											m_pValueType->m_ePointerType = pOldValueType->m_ePointerType;
											if (pOldValueType) delete pOldValueType;
										}
									}
								}
							}
						}
					}
#line 388 "../../../Source/Core/AST/Identifier.nll"
					return;
				}
			}
#line 392 "../../../Source/Core/AST/Identifier.nll"
		if (pAST->m_eType == AST::Type::AST_FUNCTION_DECL)
		{
#line 394 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType = new ValueType(ValueType::Type::FUNCTION_DECL);
#line 395 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType->m_pFunctionDecl = (FunctionDecl*)(pAST);
#line 396 "../../../Source/Core/AST/Identifier.nll"
			return;
		}
		else
#line 398 "../../../Source/Core/AST/Identifier.nll"
			if (pAST->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
			{
				MemberFunctionDecl* pMFD = (MemberFunctionDecl*)(pAST);
#line 401 "../../../Source/Core/AST/Identifier.nll"
				if (pMFD->m_pFunctionDecl != 0)
				{
#line 403 "../../../Source/Core/AST/Identifier.nll"
					m_pValueType = new ValueType(ValueType::Type::FUNCTION_DECL);
#line 404 "../../../Source/Core/AST/Identifier.nll"
					m_pValueType->m_pFunctionDecl = pMFD->m_pFunctionDecl;
#line 405 "../../../Source/Core/AST/Identifier.nll"
					return;
				}
			}
#line 409 "../../../Source/Core/AST/Identifier.nll"
		if (pAST->m_eType == AST::Type::NAMESPACE_DECL)
		{
#line 411 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType = new ValueType(ValueType::Type::NAMESPACE_NODE);
#line 412 "../../../Source/Core/AST/Identifier.nll"
			m_pValueType->m_pNamespaceNode = ((NamespaceDecl*)(pAST))->m_pNamespaceNode;
#line 413 "../../../Source/Core/AST/Identifier.nll"
			return;
		}
		{
			InternalString* sTemp = new InternalString("say what? ");
#line 418 "../../../Source/Core/AST/Identifier.nll"
			pAST->StringifyType(sTemp);
#line 419 "../../../Source/Core/AST/Identifier.nll"
			pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			if (sTemp) delete sTemp;
		}
#line 422 "../../../Source/Core/AST/Identifier.nll"
		AST::Validate(pValidator, pParent);
	}

#line 425 "../../../Source/Core/AST/Identifier.nll"
	void Identifier::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 427 "../../../Source/Core/AST/Identifier.nll"
		m_pNameToken->Stringify(pOutputBuilder->m_sOut);
	}

#line 4 "../../../Source/Core/AST/Identifier.nll"
	Identifier::Identifier()
	{
		m_pNameToken = 0;
	}

}

