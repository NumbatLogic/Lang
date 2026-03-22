#include "FunctionCall.hpp"
#include "../OffsetDatum.hpp"
#include "../TokenContainer.hpp"
#include "../Token.hpp"
#include "ParamCall.hpp"
#include "../../../../LangShared/Source/InternalString/CPP/InternalString.hpp"
#include "../../../../LangShared/Source/Console/CPP/Console.hpp"
#include "../../../../LangShared/Source/Assert/CPP/Assert.hpp"
#include "AST.hpp"
#include "OperatorExpr.hpp"
#include "../ValueType.hpp"
#include "ClassDecl.hpp"
#include "EnumDecl.hpp"
#include "../Validator.hpp"
#include "../../../../LangShared/Source/Vector/CPP/Vector.hpp"
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
#include "../../../../LangShared/Source/ExternalString/CPP/ExternalString.hpp"
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
#line 0 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
namespace NumbatLogic
{
#line 3 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
#line 8 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
	FunctionCall* FunctionCall::TryCreate(TokenContainer* pTokenContainer, OffsetDatum* pOffsetDatum)
	{
		OffsetDatum* pTempOffset = OffsetDatum::Create(pOffsetDatum);
#line 12 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		Token* pNameToken = pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_IDENTIFIER);
		if (pNameToken == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			return 0;
		}
#line 15 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		pTempOffset->m_nOffset = pTempOffset->m_nOffset + 1;
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		if (pTokenContainer->PeekExpect(pTempOffset, Token::Type::TOKEN_PARENTHESIS_LEFT) == 0)
		{
			if (pTempOffset) delete pTempOffset;
#line 18 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			return 0;
		}
		ParamCall* pParamCall = ParamCall::TryCreate(pTokenContainer, pTempOffset);
		if (pParamCall == 0)
		{
			InternalString* sTemp = new InternalString("expected ParamCall ");
			sTemp->Append(pTokenContainer->StringifyOffset(pTempOffset));
			Console::Log(sTemp->GetExternalString());
			Assert::Plz(false);
			if (sTemp) delete sTemp;
			if (pTempOffset) delete pTempOffset;
			if (pParamCall) delete pParamCall;
#line 27 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			return 0;
		}
#line 30 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		FunctionCall* pFunctionCall = new FunctionCall();
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		pFunctionCall->m_eType = AST::Type::AST_FUNCTION_CALL;
		pFunctionCall->m_pFirstToken = pNameToken;
		pFunctionCall->m_sMangledName = pNameToken->GetString();
		pFunctionCall->m_pParamCall = pParamCall;
		NumbatLogic::ParamCall* __1502716703 = pParamCall;
		pParamCall = 0;
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		pFunctionCall->AddChild(__1502716703);
#line 40 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		pOffsetDatum->Set(pTempOffset);
		NumbatLogic::FunctionCall* __2079883043 = pFunctionCall;
#line 41 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		pFunctionCall = 0;
		if (pTempOffset) delete pTempOffset;
		if (pParamCall) delete pParamCall;
#line 41 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		return __2079883043;
	}

	void FunctionCall::Validate(Validator* pValidator, OperatorExpr* pParent)
	{
		const char* sName = m_pFirstToken->GetString();
#line 48 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		AST* pBase = this;
		if (pParent != 0)
		{
			if (pParent->GetOperatorType() == OperatorExpr::OperatorType::MEMBER_ACCESS && pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
			{
				AddClassDeclReference(pParent->m_pLeft->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
				pBase = pParent->m_pLeft->m_pValueType->m_pClassDecl;
			}
			else
#line 56 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
				if (pParent->GetOperatorType() == OperatorExpr::OperatorType::SCOPE_RESOLUTION)
				{
					if (pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::CLASS_DECL)
					{
						AddClassDeclReference(pParent->m_pLeft->m_pValueType->m_pClassDecl, AST::OutputFile::SOURCE, false);
						pBase = pParent->m_pLeft->m_pValueType->m_pClassDecl;
					}
					else
#line 63 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
						if (pParent->m_pLeft->m_pValueType->m_eType == ValueType::Type::ENUM_DECL)
						{
							pBase = pParent->m_pLeft->m_pValueType->m_pEnumDecl;
						}
						else
						{
							pValidator->AddError("Unexpected left of ::", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
							return;
						}
				}
		}
#line 77 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		AST::Validate(pValidator, pParent);
#line 79 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		AST* pResolverAST = 0;
#line 81 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		bool bResolverCallableAmbiguous = false;
		int nCallableCandidatesFromResolver = 0;
#line 84 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		Vector<Symbol*>* pCandidates = new Vector<Symbol*>();
		pValidator->m_pResolver->ResolveFromNode(pBase, sName, pCandidates);
#line 87 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		Vector<Symbol*>* pCallable = new Vector<Symbol*>();
		for (int i = 0; i < pCandidates->GetSize(); i++)
		{
			Symbol* pSym = pCandidates->Get(i);
			if (pSym->m_eKind == Symbol::Kind::FUNCTION || pSym->m_eKind == Symbol::Kind::METHOD || pSym->m_eKind == Symbol::Kind::DELEGATE)
			{
#line 95 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
				pCallable->PushBack(pSym);
				nCallableCandidatesFromResolver = nCallableCandidatesFromResolver + 1;
			}
			else
#line 98 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
				if (pSym->m_eKind == Symbol::Kind::VAR && pSym->m_pDeclAST != 0 && pSym->m_pDeclAST->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
				{
#line 101 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
					MemberVarDecl* pMVD = (MemberVarDecl*)(pSym->m_pDeclAST);
					if (pMVD->m_pVarDecl != 0 && pMVD->m_pVarDecl->m_pTypeRef != 0)
					{
						ValueType* pVT = pMVD->m_pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
						if (pVT != 0 && pVT->m_eType == ValueType::Type::DELEGATE_DECL_VALUE)
						{
							pCallable->PushBack(pSym);
							nCallableCandidatesFromResolver = nCallableCandidatesFromResolver + 1;
						}
						if (pVT) delete pVT;
					}
				}
		}
#line 116 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		if (pCallable->GetSize() > 1 && m_pParamCall != 0)
		{
			int nArgCount = 0;
			AST* pArg = m_pParamCall->m_pFirstChild;
			while (pArg != 0)
			{
				nArgCount++;
				pArg = pArg->m_pNextSibling;
			}
#line 126 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			Vector<Symbol*>* pFiltered = new Vector<Symbol*>();
			for (int i = 0; i < pCallable->GetSize(); i++)
			{
				Symbol* pSym = pCallable->Get(i);
				AST* pDeclAST = pSym->m_pDeclAST;
				FunctionDecl* pFD = 0;
#line 133 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
				if (pDeclAST != 0)
				{
					if (pDeclAST->m_eType == AST::Type::AST_FUNCTION_DECL)
					{
						pFD = (FunctionDecl*)(pDeclAST);
					}
					else
#line 139 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
						if (pDeclAST->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
						{
							MemberFunctionDecl* pMFD = (MemberFunctionDecl*)(pDeclAST);
							if (pMFD->m_pFunctionDecl != 0)
								pFD = pMFD->m_pFunctionDecl;
						}
						else
#line 145 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
							if (pDeclAST->m_eType == AST::Type::DELEGATE_DECL)
							{
								DelegateDecl* pDD = (DelegateDecl*)(pDeclAST);
								if (pDD->m_pFunctionDecl != 0)
									pFD = pDD->m_pFunctionDecl;
							}
							else
#line 151 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
								if (pDeclAST->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
								{
									MemberVarDecl* pMVD = (MemberVarDecl*)(pDeclAST);
									if (pMVD->m_pVarDecl != 0 && pMVD->m_pVarDecl->m_pTypeRef != 0)
									{
										ValueType* pVT = pMVD->m_pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
										if (pVT != 0 && pVT->m_eType == ValueType::Type::DELEGATE_DECL_VALUE && pVT->m_pDelegateDecl != 0)
											pFD = pVT->m_pDelegateDecl->m_pFunctionDecl;
										if (pVT) delete pVT;
									}
								}
				}
				int nMinParams = 0;
				int nMaxParams = 0;
#line 166 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
				if (pFD != 0 && pFD->m_pParamDecl != 0)
				{
					AST* pDeclChild = pFD->m_pParamDecl->m_pFirstChild;
					while (pDeclChild != 0)
					{
						if (pDeclChild->m_eType == AST::Type::AST_VAR_DECL)
						{
							nMaxParams++;
							VarDecl* pVarDecl = (VarDecl*)(pDeclChild);
							if (pVarDecl->m_pAssignment == 0)
								nMinParams++;
						}
#line 179 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
						pDeclChild = pDeclChild->m_pNextSibling;
					}
				}
#line 184 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
				if (pFD == 0 || pFD->m_pParamDecl == 0)
				{
					nMinParams = 0;
					nMaxParams = 0;
				}
#line 190 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
				if (nArgCount >= nMinParams && nArgCount <= nMaxParams)
					pFiltered->PushBack(pSym);
			}
#line 194 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			if (pFiltered->GetSize() == 1)
			{
				Symbol* pSymbol = pFiltered->Get(0);
				if (pSymbol->m_pDeclAST != 0)
					pResolverAST = pSymbol->m_pDeclAST;
			}
			else
#line 200 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
				if (pFiltered->GetSize() > 1)
				{
#line 208 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
					Vector<Symbol*>* pBest = new Vector<Symbol*>();
					int nBestScore = -1;
#line 211 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
					for (int i = 0; i < pFiltered->GetSize(); i++)
					{
						Symbol* pSym = pFiltered->Get(i);
						AST* pDeclAST = pSym->m_pDeclAST;
						FunctionDecl* pFD = 0;
#line 217 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
						if (pDeclAST != 0)
						{
							if (pDeclAST->m_eType == AST::Type::AST_FUNCTION_DECL)
							{
								pFD = (FunctionDecl*)(pDeclAST);
							}
							else
#line 223 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
								if (pDeclAST->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
								{
									MemberFunctionDecl* pMFD = (MemberFunctionDecl*)(pDeclAST);
									if (pMFD->m_pFunctionDecl != 0)
										pFD = pMFD->m_pFunctionDecl;
								}
								else
#line 229 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
									if (pDeclAST->m_eType == AST::Type::DELEGATE_DECL)
									{
										DelegateDecl* pDD = (DelegateDecl*)(pDeclAST);
										if (pDD->m_pFunctionDecl != 0)
											pFD = pDD->m_pFunctionDecl;
									}
									else
#line 235 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
										if (pDeclAST->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
										{
											MemberVarDecl* pMVD = (MemberVarDecl*)(pDeclAST);
											if (pMVD->m_pVarDecl != 0 && pMVD->m_pVarDecl->m_pTypeRef != 0)
											{
												ValueType* pVT = pMVD->m_pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
												if (pVT != 0 && pVT->m_eType == ValueType::Type::DELEGATE_DECL_VALUE && pVT->m_pDelegateDecl != 0)
													pFD = pVT->m_pDelegateDecl->m_pFunctionDecl;
												if (pVT) delete pVT;
											}
										}
						}
#line 252 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
						bool bTypeOk = true;
						if (pFD != 0 && pFD->m_pParamDecl != 0)
							bTypeOk = pFD->m_pParamDecl->ValidateParamCall(m_pParamCall, pValidator, true);
#line 256 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
						if (!bTypeOk)
							continue;
#line 262 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
						int nScore = 0;
						if (pFD != 0 && pFD->m_pParamDecl != 0)
						{
							int nIndex = 0;
							AST* pCallChild = m_pParamCall->m_pFirstChild;
							AST* pDeclChild = pFD->m_pParamDecl->m_pFirstChild;
#line 269 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
							while (true)
							{
								if (pCallChild == 0 || pDeclChild == 0)
									break;
#line 274 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
								if (pDeclChild->m_eType != AST::Type::AST_VAR_DECL)
									break;
#line 277 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
								VarDecl* pVarDecl = (VarDecl*)(pDeclChild);
								ValueType* pValueType = pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
								if (pValueType == 0 || pCallChild->m_pValueType == 0)
								{
									if (pValueType) delete pValueType;
#line 280 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
									break;
								}
								ValueType* pArgVT = pCallChild->m_pValueType;
#line 285 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
								if (pArgVT->m_eType == pValueType->m_eType && pArgVT->m_eType != ValueType::Type::CLASS_DECL_VALUE && pArgVT->m_ePointerType == pValueType->m_ePointerType)
								{
#line 289 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
									nScore += 2;
								}
								else
#line 291 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
									if (pArgVT->m_eType == ValueType::Type::CLASS_DECL_VALUE && pValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE)
									{
#line 294 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
										ClassDecl* pFromClass = pArgVT->m_pClassDecl;
										ClassDecl* pToClass = pValueType->m_pClassDecl;
#line 298 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
										if (pFromClass == pToClass && pArgVT->m_ePointerType == pValueType->m_ePointerType)
										{
#line 301 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
											nScore += 3;
										}
										else
										{
#line 308 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
											int nDistance = -1;
											int nWalk = 0;
											ClassDecl* pWalk = pFromClass;
											while (pWalk != 0)
											{
												if (pWalk == pToClass)
												{
													nDistance = nWalk;
													break;
												}
#line 319 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
												if (pWalk->m_pBaseTypeRef == 0)
													break;
#line 322 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
												AST* pBaseAST = pWalk->m_pBaseTypeRef->m_pFoundType;
												if (pBaseAST == 0 || pBaseAST->m_eType != AST::Type::AST_CLASS_DECL)
													break;
#line 326 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
												pWalk = (ClassDecl*)(pBaseAST);
												nWalk++;
											}
#line 330 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
											if (nDistance >= 0)
											{
#line 334 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
												if (nDistance == 0)
													nScore += 3;
												else
#line 336 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
													if (nDistance == 1)
														nScore += 2;
													else
														nScore += 1;
											}
										}
									}
#line 344 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
								nIndex++;
								pCallChild = pCallChild->m_pNextSibling;
								pDeclChild = pDeclChild->m_pNextSibling;
								if (pValueType) delete pValueType;
							}
						}
						if (nScore > nBestScore)
						{
							pBest->Clear();
							pBest->PushBack(pSym);
							nBestScore = nScore;
						}
						else
#line 356 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
							if (nScore == nBestScore)
							{
								pBest->PushBack(pSym);
							}
					}
#line 362 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
					if (pBest->GetSize() == 1 && nBestScore >= 0)
					{
						Symbol* pSymbol = pBest->Get(0);
						if (pSymbol->m_pDeclAST != 0)
							pResolverAST = pSymbol->m_pDeclAST;
					}
					else
#line 368 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
						if (pBest->GetSize() > 1 && nBestScore >= 0)
						{
#line 372 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
							pCallable->Clear();
							for (int i = 0; i < pBest->GetSize(); i++)
							{
								pCallable->PushBack(pBest->Get(i));
							}
						}
					if (pBest) delete pBest;
				}
			if (pFiltered) delete pFiltered;
		}
#line 383 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		if (pCallable->GetSize() == 1 && pResolverAST == 0)
		{
			Symbol* pSymbol = pCallable->Get(0);
			if (pSymbol->m_pDeclAST != 0)
				pResolverAST = pSymbol->m_pDeclAST;
		}
		else
#line 389 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			if (pCallable->GetSize() > 1 && pResolverAST == 0)
				bResolverCallableAmbiguous = true;
#line 392 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		AST* pAST = pResolverAST;
		if (pAST == 0)
		{
			if (bResolverCallableAmbiguous)
			{
				InternalString* sAmbiguous = new InternalString("Ambiguous function call (multiple overloads in scope): ");
				sAmbiguous->Append(sName);
				pValidator->AddError(sAmbiguous->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				if (sAmbiguous) delete sAmbiguous;
			}
			else
			{
#line 403 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
				InternalString* sTemp = new InternalString("Func Unbeknownst! ");
				sTemp->Append(sName);
				sTemp->Append(" parent is: ");
				pBase->StringifyType(sTemp);
				if (pBase->m_eType == AST::Type::AST_CLASS_DECL)
				{
					ClassDecl* pClassDecl = (ClassDecl*)(pBase);
					sTemp->Append(" ");
					pClassDecl->AppendFullyQualifiedName(AST::Language::NLL, sTemp);
				}
				pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				if (sTemp) delete sTemp;
			}
			if (pCandidates) delete pCandidates;
			if (pCallable) delete pCallable;
#line 415 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			return;
		}
#line 418 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		FunctionDecl* pFunctionDecl = 0;
#line 421 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		if (pAST->m_eType == AST::Type::AST_VAR_DECL)
		{
			VarDecl* pVarDecl = (VarDecl*)(pAST);
			ValueType* pValueType = pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
			if (pValueType != 0)
			{
				if (pValueType->m_eType == ValueType::Type::DELEGATE_DECL_VALUE)
				{
					if (pValueType->m_pDelegateDecl == 0)
					{
						InternalString* sTemp = new InternalString("DELEGATE_DECL_VALUE does not have m_pDelegateDecl set???");
						pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
						if (sTemp) delete sTemp;
						if (pValueType) delete pValueType;
						if (pCandidates) delete pCandidates;
						if (pCallable) delete pCallable;
#line 433 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
						return;
					}
#line 436 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
					pFunctionDecl = pValueType->m_pDelegateDecl->m_pFunctionDecl;
				}
			}
			if (pValueType) delete pValueType;
		}
		else
#line 440 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			if (pAST->m_eType == AST::Type::AST_MEMBER_VAR_DECL)
			{
				MemberVarDecl* pMVD = (MemberVarDecl*)(pAST);
				if (pMVD->m_pVarDecl != 0 && pMVD->m_pVarDecl->m_pTypeRef != 0)
				{
					ValueType* pValueType = pMVD->m_pVarDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
					if (pValueType != 0 && pValueType->m_eType == ValueType::Type::DELEGATE_DECL_VALUE)
					{
						if (pValueType->m_pDelegateDecl == 0)
						{
							InternalString* sTemp = new InternalString("DELEGATE_DECL_VALUE does not have m_pDelegateDecl set???");
							pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
							if (sTemp) delete sTemp;
							if (pValueType) delete pValueType;
							if (pCandidates) delete pCandidates;
							if (pCallable) delete pCallable;
#line 452 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
							return;
						}
						pFunctionDecl = pValueType->m_pDelegateDecl->m_pFunctionDecl;
					}
					if (pValueType) delete pValueType;
				}
			}
		if (pAST->m_eType == AST::Type::AST_FUNCTION_DECL)
		{
			pFunctionDecl = (FunctionDecl*)(pAST);
		}
		else
#line 463 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			if (pAST->m_eType == AST::Type::AST_MEMBER_FUNCTION_DECL)
			{
				MemberFunctionDecl* pMFD = (MemberFunctionDecl*)(pAST);
				if (pMFD->m_pFunctionDecl != 0)
					pFunctionDecl = pMFD->m_pFunctionDecl;
			}
#line 470 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		if (pFunctionDecl == 0)
		{
			InternalString* sTemp = new InternalString("Is not a function? ");
			sTemp->Append(sName);
			sTemp->Append(" ");
			pAST->StringifyType(sTemp);
			pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			if (sTemp) delete sTemp;
			if (pCandidates) delete pCandidates;
			if (pCallable) delete pCallable;
#line 477 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			return;
		}
#line 481 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		if (pParent != 0 && pParent->m_pLeft != 0)
		{
			ValueType* pLeftValueType = pParent->m_pLeft->m_pValueType;
			if (pLeftValueType->m_eType == ValueType::Type::CLASS_DECL_VALUE && pLeftValueType->m_pGenericValueTypeVector != 0 && pLeftValueType->m_pGenericValueTypeVector->GetSize() > 0)
			{
#line 487 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
				if (pLeftValueType->m_pGenericValueTypeVector->GetSize() != pLeftValueType->m_pClassDecl->m_pGenericTypeDeclVector->GetSize())
				{
					InternalString* sTemp2 = new InternalString("Mismatched generics? ");
					pLeftValueType->StringifyType(sTemp2);
					sTemp2->Append(" ");
					sTemp2->AppendInt(pLeftValueType->m_pGenericValueTypeVector->GetSize());
					sTemp2->Append(" != ");
					sTemp2->Append(pLeftValueType->m_pClassDecl->m_pNameToken->GetString());
					sTemp2->Append(" ");
					sTemp2->AppendInt(pLeftValueType->m_pClassDecl->m_pGenericTypeDeclVector->GetSize());
					pValidator->AddError(sTemp2->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
					if (sTemp2) delete sTemp2;
					if (pCandidates) delete pCandidates;
					if (pCallable) delete pCallable;
#line 498 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
					return;
				}
#line 501 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
				for (int i = 0; i < pLeftValueType->m_pGenericValueTypeVector->GetSize(); i++)
				{
					ValueType* pGenericValueType = pLeftValueType->m_pGenericValueTypeVector->Get(i)->Clone();
					GenericTypeDecl* pGenericTypeDecl = pLeftValueType->m_pClassDecl->m_pGenericTypeDeclVector->Get(i);
#line 506 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
					if (ExternalString::Equal(pGenericTypeDecl->m_pFirstToken->GetString(), pFunctionDecl->m_pTypeRef->m_pTypeToken->GetString()))
					{
						NumbatLogic::ValueType* __2182339513 = pGenericValueType;
#line 508 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
						pGenericValueType = 0;
#line 508 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
						m_pValueType = __2182339513;
						m_pValueType->m_ePointerType = pFunctionDecl->m_pTypeRef->m_ePointerType;
					}
					if (pGenericValueType) delete pGenericValueType;
				}
			}
		}
		if (m_pValueType == 0)
		{
			m_pValueType = pFunctionDecl->m_pTypeRef->CreateValueType(pValidator->m_pResolver);
		}
#line 522 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		if (m_pValueType == 0)
		{
			InternalString* sTemp = new InternalString("could not get valuetype for some reason ");
			sTemp->Append(pFunctionDecl->m_pTypeRef->m_pTypeToken->GetString());
#line 529 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			pValidator->AddError(sTemp->GetExternalString(), m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
			if (sTemp) delete sTemp;
		}
#line 534 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		if (m_pParamCall->m_pFirstChild == 0)
		{
			if (pFunctionDecl->m_pParamDecl->m_pFirstChild != 0)
			{
				pValidator->AddError("Params needed for function call?", m_pFirstToken->m_sFileName, m_pFirstToken->m_nLine, m_pFirstToken->m_nColumn);
				if (pCandidates) delete pCandidates;
				if (pCallable) delete pCallable;
#line 539 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
				return;
			}
		}
		else
		{
			if (!pFunctionDecl->m_pParamDecl->ValidateParamCall(m_pParamCall, pValidator, true))
			{
				if (pCandidates) delete pCandidates;
				if (pCallable) delete pCallable;
#line 545 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
				return;
			}
		}
		if (pCandidates) delete pCandidates;
		if (pCallable) delete pCallable;
	}

#line 549 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
	void FunctionCall::Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder* pOutputBuilder)
	{
		pOutputBuilder->m_sOut->Append(m_sMangledName);
		m_pParamCall->Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
	}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
	FunctionCall::FunctionCall()
	{
		m_sMangledName = 0;
		m_pParamCall = 0;
	}

}

