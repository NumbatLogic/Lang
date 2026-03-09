#include "FunctionCall.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "ParamCall.hpp"
#include "../../../../LangShared/InternalString/CPP/InternalString.hpp"
#include "../../../../LangShared/Console/CPP/Console.hpp"
#include "../../../../LangShared/Assert/CPP/Assert.hpp"
#include "AST.hpp"
#include "OperatorExpr.hpp"
#include "../ValueType.hpp"
#include "ClassDecl.hpp"
#include "EnumDecl.hpp"
#include "../Validator.hpp"
#include "../../../../LangShared/Vector/CPP/Vector.hpp"
#include "../Semantic/Symbol.hpp"
#include "../Semantic/Resolver.hpp"
#include "MemberVarDecl.hpp"
#include "VarDecl.hpp"
#include "TypeRef.hpp"
#include "MemberFunctionDecl.hpp"
#include "DelegateDecl.hpp"
#include "FunctionDecl.hpp"
#include "ParamDecl.hpp"
#include "../../../../LangShared/Transpiled/Vector/OwnedVector.hpp"
#include "../../../../LangShared/ExternalString/CPP/ExternalString.hpp"
#include "GenericTypeDecl.hpp"
#include "../OutputBuilder.hpp"

namespace NumbatLogic
{
	class AST;
	class OffsetDatum;
	class Token;
	class TokenContainer;
	class ParamCall;
	class InternalString;
	class Console;
	class Assert;
	class FunctionCall;
	class OperatorExpr;
	class EnumDecl;
	class Validator;
	template <class T>
	class Vector;
	class Symbol;
	class Resolver;
	class MemberVarDecl;
	class ValueType;
	class TypeRef;
	class FunctionDecl;
	class MemberFunctionDecl;
	class DelegateDecl;
	class ParamDecl;
	class VarDecl;
	class ClassDecl;
	template <class T>
	class OwnedVector;
	class GenericTypeDecl;
	class ExternalString;
	class OutputBuilder;
}
#line 1 "../../../Source/Core/AST/FunctionCall.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/FunctionCall.nll"
#line 9 "../../../Source/Core/AST/FunctionCall.nll"
	FunctionCall* FunctionCall::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
		Token* pNameToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
#line 14 "../../../Source/Core/AST/FunctionCall.nll"
		if (pNameToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 15 "../../../Source/Core/AST/FunctionCall.nll"
			return 0;
		}
#line 16 "../../../Source/Core/AST/FunctionCall.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 18 "../../../Source/Core/AST/FunctionCall.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT) == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 19 "../../../Source/Core/AST/FunctionCall.nll"
			return 0;
		}
		ParamCall* pParamCall = ParamCall::TryCreate(pTokenContainer, pTempOffset);
#line 22 "../../../Source/Core/AST/FunctionCall.nll"
		if (pParamCall == 0)
		{
			InternalString* sTemp = new InternalString("expected ParamCall ");
#line 25 "../../../Source/Core/AST/FunctionCall.nll"
			sTemp->Append(pTokenContainer->StringifyOffset(pTempOffset));
#line 26 "../../../Source/Core/AST/FunctionCall.nll"
			Console::Log(sTemp->GetExternalString());
#line 27 "../../../Source/Core/AST/FunctionCall.nll"
			Assert::Plz(false);
			if (sTemp) delete sTemp;
			if (pTempOffset) delete pTempOffset;
			if (pParamCall) delete pParamCall;
#line 28 "../../../Source/Core/AST/FunctionCall.nll"
			return 0;
		}
		FunctionCall* pFunctionCall = new FunctionCall();
#line 33 "../../../Source/Core/AST/FunctionCall.nll"
		pFunctionCall->m_eType = AST::Type::AST_FUNCTION_CALL;
#line 34 "../../../Source/Core/AST/FunctionCall.nll"
		pFunctionCall->m_pFirstToken = pNameToken;
#line 35 "../../../Source/Core/AST/FunctionCall.nll"
		pFunctionCall->m_sMangledName = pNameToken->GetString();
#line 36 "../../../Source/Core/AST/FunctionCall.nll"
		pFunctionCall->m_pParamCall = pParamCall;
		NumbatLogic::ParamCall* __1502716703 = pParamCall;
#line 38 "../../../Source/Core/AST/FunctionCall.nll"
		pParamCall = 0;
#line 38 "../../../Source/Core/AST/FunctionCall.nll"
		pFunctionCall->AddChild(__1502716703);
#line 41 "../../../Source/Core/AST/FunctionCall.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::FunctionCall* __2079883043 = pFunctionCall;
#line 42 "../../../Source/Core/AST/FunctionCall.nll"
		pFunctionCall = 0;
		if (pTempOffset) delete pTempOffset;
		if (pParamCall) delete pParamCall;
#line 42 "../../../Source/Core/AST/FunctionCall.nll"
		return __2079883043;
	}

#line 45 "../../../Source/Core/AST/FunctionCall.nll"
	void FunctionCall::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		const char* sName = m_pFirstToken->GetString();
		AST* pBase = this;
		AST* pChild = this;
#line 51 "../../../Source/Core/AST/FunctionCall.nll"
		if (pParent != 0)
		{
#line 53 "../../../Source/Core/AST/FunctionCall.nll"
			if (pParent->GetOperatorType() == OperatorExpr::OperatorType::MEMBER_ACCESS && pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
			{
#line 55 "../../../Source/Core/AST/FunctionCall.nll"
				AddClassDeclReference(pParent->m_pLeft->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
#line 56 "../../../Source/Core/AST/FunctionCall.nll"
				pBase = pParent->m_pLeft->m_pValueType->m_pClassDecl;
#line 57 "../../../Source/Core/AST/FunctionCall.nll"
				pChild = 0;
			}
			else
#line 59 "../../../Source/Core/AST/FunctionCall.nll"
				if (pParent->GetOperatorType() == OperatorExpr::OperatorType::SCOPE_RESOLUTION)
				{
#line 61 "../../../Source/Core/AST/FunctionCall.nll"
					if (pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL)
					{
#line 63 "../../../Source/Core/AST/FunctionCall.nll"
						AddClassDeclReference(pParent->m_pLeft->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
#line 64 "../../../Source/Core/AST/FunctionCall.nll"
						pBase = pParent->m_pLeft->m_pValueType->m_pClassDecl;
#line 65 "../../../Source/Core/AST/FunctionCall.nll"
						pChild = 0;
					}
					else
#line 67 "../../../Source/Core/AST/FunctionCall.nll"
						if (pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::ENUM_DECL)
						{
#line 69 "../../../Source/Core/AST/FunctionCall.nll"
							pBase = pParent->m_pLeft->m_pValueType->m_pEnumDecl;
#line 70 "../../../Source/Core/AST/FunctionCall.nll"
							pChild = 0;
						}
						else
						{
#line 74 "../../../Source/Core/AST/FunctionCall.nll"
							pValidator->AddError("Unexpected left of ::", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
#line 75 "../../../Source/Core/AST/FunctionCall.nll"
							return;
						}
				}
		}
#line 82 "../../../Source/Core/AST/FunctionCall.nll"
		AST::Validate(pValidator, pParent);
		AST* pResolverAST = 0;
		bool bResolverCallableAmbiguous = false;
		int nCallableCandidatesFromResolver = 0;
		Vector<Symbol*>* pCandidates = new Vector<Symbol*>();
#line 90 "../../../Source/Core/AST/FunctionCall.nll"
		pValidator->m_pResolver->ResolveFromNode(pBase, sName, pCandidates);
		Vector<Symbol*>* pCallable = new Vector<Symbol*>();
#line 93 "../../../Source/Core/AST/FunctionCall.nll"
		for (int i = 0; i < pCandidates->GetSize(); i++)
		{
			Symbol* pSym = pCandidates->Get(i);
#line 96 "../../../Source/Core/AST/FunctionCall.nll"
			if (pSym->m_eKind == Symbol::Kind::FUNCTION || pSym->m_eKind == Symbol::Kind::METHOD || pSym->m_eKind == Symbol::Kind::DELEGATE)
			{
#line 100 "../../../Source/Core/AST/FunctionCall.nll"
				pCallable->PushBack(pSym);
#line 101 "../../../Source/Core/AST/FunctionCall.nll"
				nCallableCandidatesFromResolver = nCallableCandidatesFromResolver + 1;
			}
			else
#line 103 "../../../Source/Core/AST/FunctionCall.nll"
				if (pSym->m_eKind == Symbol::Kind::VAR && pSym->m_pDeclAST != 0 && pSym->m_pDeclAST->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
				{
					MemberVarDecl* pMVD = (MemberVarDecl*)(pSym->m_pDeclAST);
#line 107 "../../../Source/Core/AST/FunctionCall.nll"
					if (pMVD->m_pVarDecl != 0 && pMVD->m_pVarDecl->m_pTypeRef != 0)
					{
						ValueType* pVT = pMVD->m_pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
#line 110 "../../../Source/Core/AST/FunctionCall.nll"
						if (pVT != 0 && pVT->m_eType == ValueType::Type::DELEGATE_DECL_VALUE)
						{
#line 112 "../../../Source/Core/AST/FunctionCall.nll"
							pCallable->PushBack(pSym);
#line 113 "../../../Source/Core/AST/FunctionCall.nll"
							nCallableCandidatesFromResolver = nCallableCandidatesFromResolver + 1;
						}
						if (pVT) delete pVT;
					}
				}
		}
#line 121 "../../../Source/Core/AST/FunctionCall.nll"
		if (pCallable->GetSize() > 1 && m_pParamCall != 0)
		{
			int nArgCount = 0;
			AST* pArg = m_pParamCall->m_pFirstChild;
#line 125 "../../../Source/Core/AST/FunctionCall.nll"
			while (pArg != 0)
			{
#line 127 "../../../Source/Core/AST/FunctionCall.nll"
				nArgCount++;
#line 128 "../../../Source/Core/AST/FunctionCall.nll"
				pArg = pArg->m_pNextSibling;
			}
			Vector<Symbol*>* pFiltered = new Vector<Symbol*>();
#line 132 "../../../Source/Core/AST/FunctionCall.nll"
			for (int i = 0; i < pCallable->GetSize(); i++)
			{
				Symbol* pSym = pCallable->Get(i);
				AST* pDeclAST = pSym->m_pDeclAST;
				FunctionDecl* pFD = 0;
#line 138 "../../../Source/Core/AST/FunctionCall.nll"
				if (pDeclAST != 0)
				{
#line 140 "../../../Source/Core/AST/FunctionCall.nll"
					if (pDeclAST->m_eType == AST::Type::AST_FUNCTION_DECL)
					{
#line 142 "../../../Source/Core/AST/FunctionCall.nll"
						pFD = (FunctionDecl*)(pDeclAST);
					}
					else
#line 144 "../../../Source/Core/AST/FunctionCall.nll"
						if (pDeclAST->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
						{
							MemberFunctionDecl* pMFD = (MemberFunctionDecl*)(pDeclAST);
#line 147 "../../../Source/Core/AST/FunctionCall.nll"
							if (pMFD->m_pFunctionDecl != 0)
#line 148 "../../../Source/Core/AST/FunctionCall.nll"
								pFD = pMFD->m_pFunctionDecl;
						}
						else
#line 150 "../../../Source/Core/AST/FunctionCall.nll"
							if (pDeclAST->m_eType == AST::Type::DELEGATE_DECL)
							{
								DelegateDecl* pDD = (DelegateDecl*)(pDeclAST);
#line 153 "../../../Source/Core/AST/FunctionCall.nll"
								if (pDD->m_pFunctionDecl != 0)
#line 154 "../../../Source/Core/AST/FunctionCall.nll"
									pFD = pDD->m_pFunctionDecl;
							}
							else
#line 156 "../../../Source/Core/AST/FunctionCall.nll"
								if (pDeclAST->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
								{
									MemberVarDecl* pMVD = (MemberVarDecl*)(pDeclAST);
#line 159 "../../../Source/Core/AST/FunctionCall.nll"
									if (pMVD->m_pVarDecl != 0 && pMVD->m_pVarDecl->m_pTypeRef != 0)
									{
										ValueType* pVT = pMVD->m_pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
#line 162 "../../../Source/Core/AST/FunctionCall.nll"
										if (pVT != 0 && pVT->m_eType == ValueType::Type::DELEGATE_DECL_VALUE && pVT->m_pDelegateDecl != 0)
#line 163 "../../../Source/Core/AST/FunctionCall.nll"
											pFD = pVT->m_pDelegateDecl->m_pFunctionDecl;
										if (pVT) delete pVT;
									}
								}
				}
				int nMinParams = 0;
				int nMaxParams = 0;
#line 171 "../../../Source/Core/AST/FunctionCall.nll"
				if (pFD != 0 && pFD->m_pParamDecl != 0)
				{
					AST* pDeclChild = pFD->m_pParamDecl->m_pFirstChild;
#line 174 "../../../Source/Core/AST/FunctionCall.nll"
					while (pDeclChild != 0)
					{
#line 176 "../../../Source/Core/AST/FunctionCall.nll"
						if (pDeclChild->m_eType == AST::Type::AST_VAR_DECL)
						{
#line 178 "../../../Source/Core/AST/FunctionCall.nll"
							nMaxParams++;
							VarDecl* pVarDecl = (VarDecl*)(pDeclChild);
#line 180 "../../../Source/Core/AST/FunctionCall.nll"
							if (pVarDecl->m_pAssignment == 0)
#line 181 "../../../Source/Core/AST/FunctionCall.nll"
								nMinParams++;
						}
#line 184 "../../../Source/Core/AST/FunctionCall.nll"
						pDeclChild = pDeclChild->m_pNextSibling;
					}
				}
#line 189 "../../../Source/Core/AST/FunctionCall.nll"
				if (pFD == 0 || pFD->m_pParamDecl == 0)
				{
#line 191 "../../../Source/Core/AST/FunctionCall.nll"
					nMinParams = 0;
#line 192 "../../../Source/Core/AST/FunctionCall.nll"
					nMaxParams = 0;
				}
#line 195 "../../../Source/Core/AST/FunctionCall.nll"
				if (nArgCount >= nMinParams && nArgCount <= nMaxParams)
#line 196 "../../../Source/Core/AST/FunctionCall.nll"
					pFiltered->PushBack(pSym);
			}
#line 199 "../../../Source/Core/AST/FunctionCall.nll"
			if (pFiltered->GetSize() == 1)
			{
				Symbol* pSymbol = pFiltered->Get(0);
#line 202 "../../../Source/Core/AST/FunctionCall.nll"
				if (pSymbol->m_pDeclAST != 0)
#line 203 "../../../Source/Core/AST/FunctionCall.nll"
					pResolverAST = pSymbol->m_pDeclAST;
			}
			else
#line 205 "../../../Source/Core/AST/FunctionCall.nll"
				if (pFiltered->GetSize() > 1)
				{
					Vector<Symbol*>* pBest = new Vector<Symbol*>();
					int nBestScore = -1;
#line 216 "../../../Source/Core/AST/FunctionCall.nll"
					for (int i = 0; i < pFiltered->GetSize(); i++)
					{
						Symbol* pSym = pFiltered->Get(i);
						AST* pDeclAST = pSym->m_pDeclAST;
						FunctionDecl* pFD = 0;
#line 222 "../../../Source/Core/AST/FunctionCall.nll"
						if (pDeclAST != 0)
						{
#line 224 "../../../Source/Core/AST/FunctionCall.nll"
							if (pDeclAST->m_eType == AST::Type::AST_FUNCTION_DECL)
							{
#line 226 "../../../Source/Core/AST/FunctionCall.nll"
								pFD = (FunctionDecl*)(pDeclAST);
							}
							else
#line 228 "../../../Source/Core/AST/FunctionCall.nll"
								if (pDeclAST->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
								{
									MemberFunctionDecl* pMFD = (MemberFunctionDecl*)(pDeclAST);
#line 231 "../../../Source/Core/AST/FunctionCall.nll"
									if (pMFD->m_pFunctionDecl != 0)
#line 232 "../../../Source/Core/AST/FunctionCall.nll"
										pFD = pMFD->m_pFunctionDecl;
								}
								else
#line 234 "../../../Source/Core/AST/FunctionCall.nll"
									if (pDeclAST->m_eType == AST::Type::DELEGATE_DECL)
									{
										DelegateDecl* pDD = (DelegateDecl*)(pDeclAST);
#line 237 "../../../Source/Core/AST/FunctionCall.nll"
										if (pDD->m_pFunctionDecl != 0)
#line 238 "../../../Source/Core/AST/FunctionCall.nll"
											pFD = pDD->m_pFunctionDecl;
									}
									else
#line 240 "../../../Source/Core/AST/FunctionCall.nll"
										if (pDeclAST->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
										{
											MemberVarDecl* pMVD = (MemberVarDecl*)(pDeclAST);
#line 243 "../../../Source/Core/AST/FunctionCall.nll"
											if (pMVD->m_pVarDecl != 0 && pMVD->m_pVarDecl->m_pTypeRef != 0)
											{
												ValueType* pVT = pMVD->m_pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
#line 246 "../../../Source/Core/AST/FunctionCall.nll"
												if (pVT != 0 && pVT->m_eType == ValueType::Type::DELEGATE_DECL_VALUE && pVT->m_pDelegateDecl != 0)
#line 247 "../../../Source/Core/AST/FunctionCall.nll"
													pFD = pVT->m_pDelegateDecl->m_pFunctionDecl;
												if (pVT) delete pVT;
											}
										}
						}
						bool bTypeOk = true;
#line 258 "../../../Source/Core/AST/FunctionCall.nll"
						if (pFD != 0 && pFD->m_pParamDecl != 0)
#line 259 "../../../Source/Core/AST/FunctionCall.nll"
							bTypeOk = pFD->m_pParamDecl->ValidateParamCall(m_pParamCall, pValidator, true);
#line 261 "../../../Source/Core/AST/FunctionCall.nll"
						if (!bTypeOk)
#line 262 "../../../Source/Core/AST/FunctionCall.nll"
							continue;
						int nScore = 0;
#line 268 "../../../Source/Core/AST/FunctionCall.nll"
						if (pFD != 0 && pFD->m_pParamDecl != 0)
						{
							int nIndex = 0;
							AST* pCallChild = m_pParamCall->m_pFirstChild;
							AST* pDeclChild = pFD->m_pParamDecl->m_pFirstChild;
#line 274 "../../../Source/Core/AST/FunctionCall.nll"
							while (true)
							{
#line 276 "../../../Source/Core/AST/FunctionCall.nll"
								if (pCallChild == 0 || pDeclChild == 0)
#line 277 "../../../Source/Core/AST/FunctionCall.nll"
									break;
#line 279 "../../../Source/Core/AST/FunctionCall.nll"
								if (pDeclChild->m_eType != AST::Type::AST_VAR_DECL)
#line 280 "../../../Source/Core/AST/FunctionCall.nll"
									break;
								VarDecl* pVarDecl = (VarDecl*)(pDeclChild);
								ValueType* pValueType = pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
#line 284 "../../../Source/Core/AST/FunctionCall.nll"
								if (pValueType == 0 || pCallChild->m_pValueType == 0)
								{
									if (pValueType) delete pValueType;
#line 285 "../../../Source/Core/AST/FunctionCall.nll"
									break;
								}
								ValueType* pArgVT = pCallChild->m_pValueType;
#line 290 "../../../Source/Core/AST/FunctionCall.nll"
								if (pArgVT->m_eType == pValueType->m_eType && pArgVT->m_eType != ValueType::Type::CLASS_DECL_VALUE && pArgVT->m_ePointerType == pValueType->m_ePointerType)
								{
#line 294 "../../../Source/Core/AST/FunctionCall.nll"
									nScore += 2;
								}
								else
#line 296 "../../../Source/Core/AST/FunctionCall.nll"
									if (pArgVT->m_eType == ValueType::Type::CLASS_DECL_VALUE && pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
									{
										ClassDecl* pFromClass = pArgVT->m_pClassDecl;
										ClassDecl* pToClass = pValueType->m_pClassDecl;
#line 303 "../../../Source/Core/AST/FunctionCall.nll"
										if (pFromClass == pToClass && pArgVT->m_ePointerType == pValueType->m_ePointerType)
										{
#line 306 "../../../Source/Core/AST/FunctionCall.nll"
											nScore += 3;
										}
										else
										{
											int nDistance = -1;
											int nWalk = 0;
											ClassDecl* pWalk = pFromClass;
#line 316 "../../../Source/Core/AST/FunctionCall.nll"
											while (pWalk != 0)
											{
#line 318 "../../../Source/Core/AST/FunctionCall.nll"
												if (pWalk == pToClass)
												{
#line 320 "../../../Source/Core/AST/FunctionCall.nll"
													nDistance = nWalk;
#line 321 "../../../Source/Core/AST/FunctionCall.nll"
													break;
												}
#line 324 "../../../Source/Core/AST/FunctionCall.nll"
												if (pWalk->m_pBaseTypeRef == 0)
#line 325 "../../../Source/Core/AST/FunctionCall.nll"
													break;
												AST* pBaseAST = pWalk->m_pBaseTypeRef->m_pFoundType;
#line 328 "../../../Source/Core/AST/FunctionCall.nll"
												if (pBaseAST == 0 || pBaseAST->m_eType != AST::Type::AST_CLASS_DECL)
#line 329 "../../../Source/Core/AST/FunctionCall.nll"
													break;
#line 331 "../../../Source/Core/AST/FunctionCall.nll"
												pWalk = (ClassDecl*)(pBaseAST);
#line 332 "../../../Source/Core/AST/FunctionCall.nll"
												nWalk++;
											}
#line 335 "../../../Source/Core/AST/FunctionCall.nll"
											if (nDistance >= 0)
											{
#line 339 "../../../Source/Core/AST/FunctionCall.nll"
												if (nDistance == 0)
#line 340 "../../../Source/Core/AST/FunctionCall.nll"
													nScore += 3;
												else
#line 341 "../../../Source/Core/AST/FunctionCall.nll"
													if (nDistance == 1)
#line 342 "../../../Source/Core/AST/FunctionCall.nll"
														nScore += 2;
													else
#line 344 "../../../Source/Core/AST/FunctionCall.nll"
														nScore += 1;
											}
										}
									}
#line 349 "../../../Source/Core/AST/FunctionCall.nll"
								nIndex++;
#line 350 "../../../Source/Core/AST/FunctionCall.nll"
								pCallChild = pCallChild->m_pNextSibling;
#line 351 "../../../Source/Core/AST/FunctionCall.nll"
								pDeclChild = pDeclChild->m_pNextSibling;
								if (pValueType) delete pValueType;
							}
						}
#line 355 "../../../Source/Core/AST/FunctionCall.nll"
						if (nScore > nBestScore)
						{
#line 357 "../../../Source/Core/AST/FunctionCall.nll"
							pBest->Clear();
#line 358 "../../../Source/Core/AST/FunctionCall.nll"
							pBest->PushBack(pSym);
#line 359 "../../../Source/Core/AST/FunctionCall.nll"
							nBestScore = nScore;
						}
						else
#line 361 "../../../Source/Core/AST/FunctionCall.nll"
							if (nScore == nBestScore)
							{
#line 363 "../../../Source/Core/AST/FunctionCall.nll"
								pBest->PushBack(pSym);
							}
					}
#line 367 "../../../Source/Core/AST/FunctionCall.nll"
					if (pBest->GetSize() == 1 && nBestScore >= 0)
					{
						Symbol* pSymbol = pBest->Get(0);
#line 370 "../../../Source/Core/AST/FunctionCall.nll"
						if (pSymbol->m_pDeclAST != 0)
#line 371 "../../../Source/Core/AST/FunctionCall.nll"
							pResolverAST = pSymbol->m_pDeclAST;
					}
					else
#line 373 "../../../Source/Core/AST/FunctionCall.nll"
						if (pBest->GetSize() > 1 && nBestScore >= 0)
						{
#line 377 "../../../Source/Core/AST/FunctionCall.nll"
							pCallable->Clear();
#line 378 "../../../Source/Core/AST/FunctionCall.nll"
							for (int i = 0; i < pBest->GetSize(); i++)
							{
#line 380 "../../../Source/Core/AST/FunctionCall.nll"
								pCallable->PushBack(pBest->Get(i));
							}
						}
					if (pBest) delete pBest;
				}
			if (pFiltered) delete pFiltered;
		}
#line 388 "../../../Source/Core/AST/FunctionCall.nll"
		if (pCallable->GetSize() == 1 && pResolverAST == 0)
		{
			Symbol* pSymbol = pCallable->Get(0);
#line 391 "../../../Source/Core/AST/FunctionCall.nll"
			if (pSymbol->m_pDeclAST != 0)
#line 392 "../../../Source/Core/AST/FunctionCall.nll"
				pResolverAST = pSymbol->m_pDeclAST;
		}
		else
#line 394 "../../../Source/Core/AST/FunctionCall.nll"
			if (pCallable->GetSize() > 1 && pResolverAST == 0)
#line 395 "../../../Source/Core/AST/FunctionCall.nll"
				bResolverCallableAmbiguous = true;
		AST* pAST = pResolverAST;
#line 398 "../../../Source/Core/AST/FunctionCall.nll"
		if (pAST == 0)
		{
#line 400 "../../../Source/Core/AST/FunctionCall.nll"
			if (bResolverCallableAmbiguous)
			{
				InternalString* sAmbiguous = new InternalString("Ambiguous function call (multiple overloads in scope): ");
#line 403 "../../../Source/Core/AST/FunctionCall.nll"
				sAmbiguous->Append(sName);
#line 404 "../../../Source/Core/AST/FunctionCall.nll"
				pValidator->AddError(sAmbiguous->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				if (sAmbiguous) delete sAmbiguous;
			}
			else
			{
				InternalString* sTemp = new InternalString("Func Unbeknownst! ");
#line 409 "../../../Source/Core/AST/FunctionCall.nll"
				sTemp->Append(sName);
#line 410 "../../../Source/Core/AST/FunctionCall.nll"
				sTemp->Append(" parent is: ");
#line 411 "../../../Source/Core/AST/FunctionCall.nll"
				pBase->StringifyType(sTemp);
#line 412 "../../../Source/Core/AST/FunctionCall.nll"
				if (pBase->m_eType == AST::Type::AST_CLASS_DECL)
				{
					ClassDecl* pClassDecl = (ClassDecl*)(pBase);
#line 415 "../../../Source/Core/AST/FunctionCall.nll"
					sTemp->Append(" ");
#line 416 "../../../Source/Core/AST/FunctionCall.nll"
					pClassDecl->AppendFullyQualifiedName(sTemp);
				}
#line 418 "../../../Source/Core/AST/FunctionCall.nll"
				pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				if (sTemp) delete sTemp;
			}
			if (pCandidates) delete pCandidates;
			if (pCallable) delete pCallable;
#line 420 "../../../Source/Core/AST/FunctionCall.nll"
			return;
		}
		FunctionDecl* pFunctionDecl = 0;
#line 426 "../../../Source/Core/AST/FunctionCall.nll"
		if (pAST->m_eType == AST::Type::AST_VAR_DECL)
		{
			VarDecl* pVarDecl = (VarDecl*)(pAST);
			ValueType* pValueType = pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
#line 430 "../../../Source/Core/AST/FunctionCall.nll"
			if (pValueType != 0)
			{
#line 432 "../../../Source/Core/AST/FunctionCall.nll"
				if (pValueType->m_eType == ValueType::Type::DELEGATE_DECL_VALUE)
				{
#line 434 "../../../Source/Core/AST/FunctionCall.nll"
					if (pValueType->m_pDelegateDecl == 0)
					{
						InternalString* sTemp = new InternalString("DELEGATE_DECL_VALUE does not have m_pDelegateDecl set???");
#line 437 "../../../Source/Core/AST/FunctionCall.nll"
						pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
						if (sTemp) delete sTemp;
						if (pValueType) delete pValueType;
						if (pCandidates) delete pCandidates;
						if (pCallable) delete pCallable;
#line 438 "../../../Source/Core/AST/FunctionCall.nll"
						return;
					}
#line 441 "../../../Source/Core/AST/FunctionCall.nll"
					pFunctionDecl = pValueType->m_pDelegateDecl->m_pFunctionDecl;
				}
			}
			if (pValueType) delete pValueType;
		}
		else
#line 445 "../../../Source/Core/AST/FunctionCall.nll"
			if (pAST->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
			{
				MemberVarDecl* pMVD = (MemberVarDecl*)(pAST);
#line 448 "../../../Source/Core/AST/FunctionCall.nll"
				if (pMVD->m_pVarDecl != 0 && pMVD->m_pVarDecl->m_pTypeRef != 0)
				{
					ValueType* pValueType = pMVD->m_pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
#line 451 "../../../Source/Core/AST/FunctionCall.nll"
					if (pValueType != 0 && pValueType->m_eType == ValueType::Type::DELEGATE_DECL_VALUE)
					{
#line 453 "../../../Source/Core/AST/FunctionCall.nll"
						if (pValueType->m_pDelegateDecl == 0)
						{
							InternalString* sTemp = new InternalString("DELEGATE_DECL_VALUE does not have m_pDelegateDecl set???");
#line 456 "../../../Source/Core/AST/FunctionCall.nll"
							pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
							if (sTemp) delete sTemp;
							if (pValueType) delete pValueType;
							if (pCandidates) delete pCandidates;
							if (pCallable) delete pCallable;
#line 457 "../../../Source/Core/AST/FunctionCall.nll"
							return;
						}
#line 459 "../../../Source/Core/AST/FunctionCall.nll"
						pFunctionDecl = pValueType->m_pDelegateDecl->m_pFunctionDecl;
					}
					if (pValueType) delete pValueType;
				}
			}
#line 464 "../../../Source/Core/AST/FunctionCall.nll"
		if (pAST->m_eType == AST::Type::AST_FUNCTION_DECL)
		{
#line 466 "../../../Source/Core/AST/FunctionCall.nll"
			pFunctionDecl = (FunctionDecl*)(pAST);
		}
		else
#line 468 "../../../Source/Core/AST/FunctionCall.nll"
			if (pAST->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
			{
				MemberFunctionDecl* pMFD = (MemberFunctionDecl*)(pAST);
#line 471 "../../../Source/Core/AST/FunctionCall.nll"
				if (pMFD->m_pFunctionDecl != 0)
#line 472 "../../../Source/Core/AST/FunctionCall.nll"
					pFunctionDecl = pMFD->m_pFunctionDecl;
			}
#line 475 "../../../Source/Core/AST/FunctionCall.nll"
		if (pFunctionDecl == 0)
		{
			InternalString* sTemp = new InternalString("Is not a function? ");
#line 478 "../../../Source/Core/AST/FunctionCall.nll"
			sTemp->Append(sName);
#line 479 "../../../Source/Core/AST/FunctionCall.nll"
			sTemp->Append(" ");
#line 480 "../../../Source/Core/AST/FunctionCall.nll"
			pAST->StringifyType(sTemp);
#line 481 "../../../Source/Core/AST/FunctionCall.nll"
			pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			if (sTemp) delete sTemp;
			if (pCandidates) delete pCandidates;
			if (pCallable) delete pCallable;
#line 482 "../../../Source/Core/AST/FunctionCall.nll"
			return;
		}
#line 486 "../../../Source/Core/AST/FunctionCall.nll"
		if (pParent != 0 && pParent->m_pLeft != 0)
		{
			ValueType* pLeftValueType = pParent->m_pLeft->m_pValueType;
#line 489 "../../../Source/Core/AST/FunctionCall.nll"
			if (pLeftValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE && pLeftValueType->m_pGenericValueTypeVector != 0 && pLeftValueType->m_pGenericValueTypeVector->GetSize() > 0)
			{
#line 492 "../../../Source/Core/AST/FunctionCall.nll"
				if (pLeftValueType->m_pGenericValueTypeVector->GetSize() != pLeftValueType->m_pClassDecl->m_pGenericTypeDeclVector->GetSize())
				{
					InternalString* sTemp2 = new InternalString("Mismatched generics? ");
#line 495 "../../../Source/Core/AST/FunctionCall.nll"
					pLeftValueType->StringifyType(sTemp2);
#line 496 "../../../Source/Core/AST/FunctionCall.nll"
					sTemp2->Append(" ");
#line 497 "../../../Source/Core/AST/FunctionCall.nll"
					sTemp2->AppendInt(pLeftValueType->m_pGenericValueTypeVector->GetSize());
#line 498 "../../../Source/Core/AST/FunctionCall.nll"
					sTemp2->Append(" != ");
#line 499 "../../../Source/Core/AST/FunctionCall.nll"
					sTemp2->Append(pLeftValueType->m_pClassDecl->m_pNameToken->GetString());
#line 500 "../../../Source/Core/AST/FunctionCall.nll"
					sTemp2->Append(" ");
#line 501 "../../../Source/Core/AST/FunctionCall.nll"
					sTemp2->AppendInt(pLeftValueType->m_pClassDecl->m_pGenericTypeDeclVector->GetSize());
#line 502 "../../../Source/Core/AST/FunctionCall.nll"
					pValidator->AddError(sTemp2->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
					if (sTemp2) delete sTemp2;
					if (pCandidates) delete pCandidates;
					if (pCallable) delete pCallable;
#line 503 "../../../Source/Core/AST/FunctionCall.nll"
					return;
				}
#line 506 "../../../Source/Core/AST/FunctionCall.nll"
				for (int i = 0; i < pLeftValueType->m_pGenericValueTypeVector->GetSize(); i++)
				{
					ValueType* pGenericValueType = pLeftValueType->m_pGenericValueTypeVector->Get(i)->Clone();
					GenericTypeDecl* pGenericTypeDecl = pLeftValueType->m_pClassDecl->m_pGenericTypeDeclVector->Get(i);
#line 511 "../../../Source/Core/AST/FunctionCall.nll"
					if (ExternalString::Equal(pGenericTypeDecl->m_pFirstToken->GetString(), pFunctionDecl->m_pTypeRef->m_pTypeToken->GetString()))
					{
						NumbatLogic::ValueType* __2182405106 = pGenericValueType;
#line 513 "../../../Source/Core/AST/FunctionCall.nll"
						pGenericValueType = 0;
#line 513 "../../../Source/Core/AST/FunctionCall.nll"
						m_pValueType = __2182405106;
#line 514 "../../../Source/Core/AST/FunctionCall.nll"
						m_pValueType->m_ePointerType = pFunctionDecl->m_pTypeRef->m_ePointerType;
					}
					if (pGenericValueType) delete pGenericValueType;
				}
			}
		}
#line 520 "../../../Source/Core/AST/FunctionCall.nll"
		if (m_pValueType == 0)
		{
#line 522 "../../../Source/Core/AST/FunctionCall.nll"
			m_pValueType = pFunctionDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
		}
#line 527 "../../../Source/Core/AST/FunctionCall.nll"
		if (m_pValueType == 0)
		{
			InternalString* sTemp = new InternalString("could not get valuetype for some reason ");
#line 530 "../../../Source/Core/AST/FunctionCall.nll"
			sTemp->Append(pFunctionDecl->m_pTypeRef->m_pTypeToken->GetString());
#line 534 "../../../Source/Core/AST/FunctionCall.nll"
			pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			if (sTemp) delete sTemp;
		}
#line 539 "../../../Source/Core/AST/FunctionCall.nll"
		if (m_pParamCall->m_pFirstChild == 0)
		{
#line 541 "../../../Source/Core/AST/FunctionCall.nll"
			if (pFunctionDecl->m_pParamDecl->m_pFirstChild != 0)
			{
#line 543 "../../../Source/Core/AST/FunctionCall.nll"
				pValidator->AddError("Params needed for function call?", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				if (pCandidates) delete pCandidates;
				if (pCallable) delete pCallable;
#line 544 "../../../Source/Core/AST/FunctionCall.nll"
				return;
			}
		}
		else
		{
#line 549 "../../../Source/Core/AST/FunctionCall.nll"
			if (!pFunctionDecl->m_pParamDecl->ValidateParamCall(m_pParamCall, pValidator, true))
			{
				if (pCandidates) delete pCandidates;
				if (pCallable) delete pCallable;
#line 550 "../../../Source/Core/AST/FunctionCall.nll"
				return;
			}
		}
		if (pCandidates) delete pCandidates;
		if (pCallable) delete pCallable;
	}

#line 554 "../../../Source/Core/AST/FunctionCall.nll"
	void FunctionCall::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
#line 556 "../../../Source/Core/AST/FunctionCall.nll"
		pOutputBuilder->m_sOut->Append(m_sMangledName);
#line 557 "../../../Source/Core/AST/FunctionCall.nll"
		m_pParamCall->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
	}

#line 4 "../../../Source/Core/AST/FunctionCall.nll"
	FunctionCall::FunctionCall()
	{
		m_sMangledName = 0;
		m_pParamCall = 0;
	}

}

