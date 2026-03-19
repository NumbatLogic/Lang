#line 1 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
namespace NumbatLogic
{
	class FunctionCall : AST
	{
		public string m_sMangledName;
		public ParamCall m_pParamCall;
#line 8 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		public static FunctionCall TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 12 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			Token pNameToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
			if (pNameToken == null)
			{
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
				return null;
			}
#line 15 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT) == null)
			{
#line 18 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
				return null;
			}
			ParamCall pParamCall = ParamCall.TryCreate(pTokenContainer, pTempOffset);
			if (pParamCall == null)
			{
				InternalString sTemp = new InternalString("expected ParamCall ");
				sTemp.Append(pTokenContainer.StringifyOffset(pTempOffset));
				Console.Log(sTemp.GetExternalString());
				Assert.Plz(false);
				return null;
			}
#line 30 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			FunctionCall pFunctionCall = new FunctionCall();
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			pFunctionCall.m_eType = AST.Type.AST_FUNCTION_CALL;
			pFunctionCall.m_pFirstToken = pNameToken;
			pFunctionCall.m_sMangledName = pNameToken.GetString();
			pFunctionCall.m_pParamCall = pParamCall;
			NumbatLogic.ParamCall __1502716703 = pParamCall;
			pParamCall = null;
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			pFunctionCall.AddChild(__1502716703);
#line 40 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.FunctionCall __2079883043 = pFunctionCall;
#line 41 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			pFunctionCall = null;
#line 41 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			return __2079883043;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			string sName = m_pFirstToken.GetString();
#line 48 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			AST pBase = this;
			if (pParent != null)
			{
				if (pParent.GetOperatorType() == OperatorExpr.OperatorType.MEMBER_ACCESS && pParent.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
				{
					AddClassDeclReference(pParent.m_pLeft.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
					pBase = pParent.m_pLeft.m_pValueType.m_pClassDecl;
				}
				else
#line 56 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
					if (pParent.GetOperatorType() == OperatorExpr.OperatorType.SCOPE_RESOLUTION)
					{
						if (pParent.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL)
						{
							AddClassDeclReference(pParent.m_pLeft.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
							pBase = pParent.m_pLeft.m_pValueType.m_pClassDecl;
						}
						else
#line 63 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
							if (pParent.m_pLeft.m_pValueType.m_eType == ValueType.Type.ENUM_DECL)
							{
								pBase = pParent.m_pLeft.m_pValueType.m_pEnumDecl;
							}
							else
							{
								pValidator.AddError("Unexpected left of ::", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
								return;
							}
					}
			}
#line 77 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			base.Validate(pValidator, pParent);
#line 79 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			AST pResolverAST = null;
#line 81 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			bool bResolverCallableAmbiguous = false;
			int nCallableCandidatesFromResolver = 0;
#line 84 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			Vector<Symbol> pCandidates = new Vector<Symbol>();
			pValidator.m_pResolver.ResolveFromNode(pBase, sName, pCandidates);
#line 87 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			Vector<Symbol> pCallable = new Vector<Symbol>();
			for (int i = 0; i < pCandidates.GetSize(); i++)
			{
				Symbol pSym = pCandidates.Get(i);
				if (pSym.m_eKind == Symbol.Kind.FUNCTION || pSym.m_eKind == Symbol.Kind.METHOD || pSym.m_eKind == Symbol.Kind.DELEGATE)
				{
#line 95 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
					pCallable.PushBack(pSym);
					nCallableCandidatesFromResolver = nCallableCandidatesFromResolver + 1;
				}
				else
#line 98 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
					if (pSym.m_eKind == Symbol.Kind.VAR && pSym.m_pDeclAST != null && pSym.m_pDeclAST.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
					{
#line 101 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
						MemberVarDecl pMVD = (MemberVarDecl)(pSym.m_pDeclAST);
						if (pMVD.m_pVarDecl != null && pMVD.m_pVarDecl.m_pTypeRef != null)
						{
							ValueType pVT = pMVD.m_pVarDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
							if (pVT != null && pVT.m_eType == ValueType.Type.DELEGATE_DECL_VALUE)
							{
								pCallable.PushBack(pSym);
								nCallableCandidatesFromResolver = nCallableCandidatesFromResolver + 1;
							}
						}
					}
			}
#line 116 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			if (pCallable.GetSize() > 1 && m_pParamCall != null)
			{
				int nArgCount = 0;
				AST pArg = m_pParamCall.m_pFirstChild;
				while (pArg != null)
				{
					nArgCount++;
					pArg = pArg.m_pNextSibling;
				}
#line 126 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
				Vector<Symbol> pFiltered = new Vector<Symbol>();
				for (int i = 0; i < pCallable.GetSize(); i++)
				{
					Symbol pSym = pCallable.Get(i);
					AST pDeclAST = pSym.m_pDeclAST;
					FunctionDecl pFD = null;
#line 133 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
					if (pDeclAST != null)
					{
						if (pDeclAST.m_eType == AST.Type.AST_FUNCTION_DECL)
						{
							pFD = (FunctionDecl)(pDeclAST);
						}
						else
#line 139 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
							if (pDeclAST.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL)
							{
								MemberFunctionDecl pMFD = (MemberFunctionDecl)(pDeclAST);
								if (pMFD.m_pFunctionDecl != null)
									pFD = pMFD.m_pFunctionDecl;
							}
							else
#line 145 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
								if (pDeclAST.m_eType == AST.Type.DELEGATE_DECL)
								{
									DelegateDecl pDD = (DelegateDecl)(pDeclAST);
									if (pDD.m_pFunctionDecl != null)
										pFD = pDD.m_pFunctionDecl;
								}
								else
#line 151 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
									if (pDeclAST.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
									{
										MemberVarDecl pMVD = (MemberVarDecl)(pDeclAST);
										if (pMVD.m_pVarDecl != null && pMVD.m_pVarDecl.m_pTypeRef != null)
										{
											ValueType pVT = pMVD.m_pVarDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
											if (pVT != null && pVT.m_eType == ValueType.Type.DELEGATE_DECL_VALUE && pVT.m_pDelegateDecl != null)
												pFD = pVT.m_pDelegateDecl.m_pFunctionDecl;
										}
									}
					}
#line 163 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
					int nMinParams = 0;
					int nMaxParams = 0;
#line 166 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
					if (pFD != null && pFD.m_pParamDecl != null)
					{
						AST pDeclChild = pFD.m_pParamDecl.m_pFirstChild;
						while (pDeclChild != null)
						{
							if (pDeclChild.m_eType == AST.Type.AST_VAR_DECL)
							{
								nMaxParams++;
								VarDecl pVarDecl = (VarDecl)(pDeclChild);
								if (pVarDecl.m_pAssignment == null)
									nMinParams++;
							}
#line 179 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
							pDeclChild = pDeclChild.m_pNextSibling;
						}
					}
#line 184 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
					if (pFD == null || pFD.m_pParamDecl == null)
					{
						nMinParams = 0;
						nMaxParams = 0;
					}
#line 190 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
					if (nArgCount >= nMinParams && nArgCount <= nMaxParams)
						pFiltered.PushBack(pSym);
				}
#line 194 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
				if (pFiltered.GetSize() == 1)
				{
					Symbol pSymbol = pFiltered.Get(0);
					if (pSymbol.m_pDeclAST != null)
						pResolverAST = pSymbol.m_pDeclAST;
				}
				else
#line 200 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
					if (pFiltered.GetSize() > 1)
					{
#line 208 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
						Vector<Symbol> pBest = new Vector<Symbol>();
						int nBestScore = -1;
#line 211 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
						for (int i = 0; i < pFiltered.GetSize(); i++)
						{
							Symbol pSym = pFiltered.Get(i);
							AST pDeclAST = pSym.m_pDeclAST;
							FunctionDecl pFD = null;
#line 217 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
							if (pDeclAST != null)
							{
								if (pDeclAST.m_eType == AST.Type.AST_FUNCTION_DECL)
								{
									pFD = (FunctionDecl)(pDeclAST);
								}
								else
#line 223 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
									if (pDeclAST.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL)
									{
										MemberFunctionDecl pMFD = (MemberFunctionDecl)(pDeclAST);
										if (pMFD.m_pFunctionDecl != null)
											pFD = pMFD.m_pFunctionDecl;
									}
									else
#line 229 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
										if (pDeclAST.m_eType == AST.Type.DELEGATE_DECL)
										{
											DelegateDecl pDD = (DelegateDecl)(pDeclAST);
											if (pDD.m_pFunctionDecl != null)
												pFD = pDD.m_pFunctionDecl;
										}
										else
#line 235 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
											if (pDeclAST.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
											{
												MemberVarDecl pMVD = (MemberVarDecl)(pDeclAST);
												if (pMVD.m_pVarDecl != null && pMVD.m_pVarDecl.m_pTypeRef != null)
												{
													ValueType pVT = pMVD.m_pVarDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
													if (pVT != null && pVT.m_eType == ValueType.Type.DELEGATE_DECL_VALUE && pVT.m_pDelegateDecl != null)
														pFD = pVT.m_pDelegateDecl.m_pFunctionDecl;
												}
											}
							}
#line 252 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
							bool bTypeOk = true;
							if (pFD != null && pFD.m_pParamDecl != null)
								bTypeOk = pFD.m_pParamDecl.ValidateParamCall(m_pParamCall, pValidator, true);
#line 256 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
							if (!bTypeOk)
								continue;
#line 262 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
							int nScore = 0;
							if (pFD != null && pFD.m_pParamDecl != null)
							{
								int nIndex = 0;
								AST pCallChild = m_pParamCall.m_pFirstChild;
								AST pDeclChild = pFD.m_pParamDecl.m_pFirstChild;
#line 269 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
								while (true)
								{
									if (pCallChild == null || pDeclChild == null)
										break;
#line 274 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
									if (pDeclChild.m_eType != AST.Type.AST_VAR_DECL)
										break;
#line 277 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
									VarDecl pVarDecl = (VarDecl)(pDeclChild);
									ValueType pValueType = pVarDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
									if (pValueType == null || pCallChild.m_pValueType == null)
									{
#line 280 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
										break;
									}
									ValueType pArgVT = pCallChild.m_pValueType;
#line 285 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
									if (pArgVT.m_eType == pValueType.m_eType && pArgVT.m_eType != ValueType.Type.CLASS_DECL_VALUE && pArgVT.m_ePointerType == pValueType.m_ePointerType)
									{
#line 289 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
										nScore += 2;
									}
									else
#line 291 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
										if (pArgVT.m_eType == ValueType.Type.CLASS_DECL_VALUE && pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
										{
#line 294 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
											ClassDecl pFromClass = pArgVT.m_pClassDecl;
											ClassDecl pToClass = pValueType.m_pClassDecl;
#line 298 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
											if (pFromClass == pToClass && pArgVT.m_ePointerType == pValueType.m_ePointerType)
											{
#line 301 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
												nScore += 3;
											}
											else
											{
#line 308 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
												int nDistance = -1;
												int nWalk = 0;
												ClassDecl pWalk = pFromClass;
												while (pWalk != null)
												{
													if (pWalk == pToClass)
													{
														nDistance = nWalk;
														break;
													}
#line 319 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
													if (pWalk.m_pBaseTypeRef == null)
														break;
#line 322 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
													AST pBaseAST = pWalk.m_pBaseTypeRef.m_pFoundType;
													if (pBaseAST == null || pBaseAST.m_eType != AST.Type.AST_CLASS_DECL)
														break;
#line 326 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
													pWalk = (ClassDecl)(pBaseAST);
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
									pCallChild = pCallChild.m_pNextSibling;
									pDeclChild = pDeclChild.m_pNextSibling;
								}
							}
#line 350 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
							if (nScore > nBestScore)
							{
								pBest.Clear();
								pBest.PushBack(pSym);
								nBestScore = nScore;
							}
							else
#line 356 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
								if (nScore == nBestScore)
								{
									pBest.PushBack(pSym);
								}
						}
#line 362 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
						if (pBest.GetSize() == 1 && nBestScore >= 0)
						{
							Symbol pSymbol = pBest.Get(0);
							if (pSymbol.m_pDeclAST != null)
								pResolverAST = pSymbol.m_pDeclAST;
						}
						else
#line 368 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
							if (pBest.GetSize() > 1 && nBestScore >= 0)
							{
#line 372 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
								pCallable.Clear();
								for (int i = 0; i < pBest.GetSize(); i++)
								{
									pCallable.PushBack(pBest.Get(i));
								}
							}
					}
			}
#line 383 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			if (pCallable.GetSize() == 1 && pResolverAST == null)
			{
				Symbol pSymbol = pCallable.Get(0);
				if (pSymbol.m_pDeclAST != null)
					pResolverAST = pSymbol.m_pDeclAST;
			}
			else
#line 389 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
				if (pCallable.GetSize() > 1 && pResolverAST == null)
					bResolverCallableAmbiguous = true;
#line 392 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			AST pAST = pResolverAST;
			if (pAST == null)
			{
				if (bResolverCallableAmbiguous)
				{
					InternalString sAmbiguous = new InternalString("Ambiguous function call (multiple overloads in scope): ");
					sAmbiguous.Append(sName);
					pValidator.AddError(sAmbiguous.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				}
				else
				{
					InternalString sTemp = new InternalString("Func Unbeknownst! ");
					sTemp.Append(sName);
					sTemp.Append(" parent is: ");
					pBase.StringifyType(sTemp);
					if (pBase.m_eType == AST.Type.AST_CLASS_DECL)
					{
						ClassDecl pClassDecl = (ClassDecl)(pBase);
						sTemp.Append(" ");
						pClassDecl.AppendFullyQualifiedName(AST.Language.NLL, sTemp);
					}
					pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				}
				return;
			}
#line 418 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			FunctionDecl pFunctionDecl = null;
#line 421 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			if (pAST.m_eType == AST.Type.AST_VAR_DECL)
			{
				VarDecl pVarDecl = (VarDecl)(pAST);
				ValueType pValueType = pVarDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
				if (pValueType != null)
				{
					if (pValueType.m_eType == ValueType.Type.DELEGATE_DECL_VALUE)
					{
						if (pValueType.m_pDelegateDecl == null)
						{
							InternalString sTemp = new InternalString("DELEGATE_DECL_VALUE does not have m_pDelegateDecl set???");
							pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
							return;
						}
#line 436 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
						pFunctionDecl = pValueType.m_pDelegateDecl.m_pFunctionDecl;
					}
				}
			}
			else
#line 440 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
				if (pAST.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
				{
					MemberVarDecl pMVD = (MemberVarDecl)(pAST);
					if (pMVD.m_pVarDecl != null && pMVD.m_pVarDecl.m_pTypeRef != null)
					{
						ValueType pValueType = pMVD.m_pVarDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
						if (pValueType != null && pValueType.m_eType == ValueType.Type.DELEGATE_DECL_VALUE)
						{
							if (pValueType.m_pDelegateDecl == null)
							{
								InternalString sTemp = new InternalString("DELEGATE_DECL_VALUE does not have m_pDelegateDecl set???");
								pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
								return;
							}
							pFunctionDecl = pValueType.m_pDelegateDecl.m_pFunctionDecl;
						}
					}
				}
#line 459 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			if (pAST.m_eType == AST.Type.AST_FUNCTION_DECL)
			{
				pFunctionDecl = (FunctionDecl)(pAST);
			}
			else
#line 463 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
				if (pAST.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL)
				{
					MemberFunctionDecl pMFD = (MemberFunctionDecl)(pAST);
					if (pMFD.m_pFunctionDecl != null)
						pFunctionDecl = pMFD.m_pFunctionDecl;
				}
#line 470 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			if (pFunctionDecl == null)
			{
				InternalString sTemp = new InternalString("Is not a function? ");
				sTemp.Append(sName);
				sTemp.Append(" ");
				pAST.StringifyType(sTemp);
				pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				return;
			}
#line 481 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			if (pParent != null && pParent.m_pLeft != null)
			{
				ValueType pLeftValueType = pParent.m_pLeft.m_pValueType;
				if (pLeftValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE && pLeftValueType.m_pGenericValueTypeVector != null && pLeftValueType.m_pGenericValueTypeVector.GetSize() > 0)
				{
#line 487 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
					if (pLeftValueType.m_pGenericValueTypeVector.GetSize() != pLeftValueType.m_pClassDecl.m_pGenericTypeDeclVector.GetSize())
					{
						InternalString sTemp2 = new InternalString("Mismatched generics? ");
						pLeftValueType.StringifyType(sTemp2);
						sTemp2.Append(" ");
						sTemp2.AppendInt(pLeftValueType.m_pGenericValueTypeVector.GetSize());
						sTemp2.Append(" != ");
						sTemp2.Append(pLeftValueType.m_pClassDecl.m_pNameToken.GetString());
						sTemp2.Append(" ");
						sTemp2.AppendInt(pLeftValueType.m_pClassDecl.m_pGenericTypeDeclVector.GetSize());
						pValidator.AddError(sTemp2.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
						return;
					}
#line 501 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
					for (int i = 0; i < pLeftValueType.m_pGenericValueTypeVector.GetSize(); i++)
					{
						ValueType pGenericValueType = pLeftValueType.m_pGenericValueTypeVector.Get(i).Clone();
						GenericTypeDecl pGenericTypeDecl = pLeftValueType.m_pClassDecl.m_pGenericTypeDeclVector.Get(i);
#line 506 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
						if (ExternalString.Equal(pGenericTypeDecl.m_pFirstToken.GetString(), pFunctionDecl.m_pTypeRef.m_pTypeToken.GetString()))
						{
							NumbatLogic.ValueType __2182339513 = pGenericValueType;
#line 508 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
							pGenericValueType = null;
#line 508 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
							m_pValueType = __2182339513;
							m_pValueType.m_ePointerType = pFunctionDecl.m_pTypeRef.m_ePointerType;
						}
					}
				}
			}
#line 515 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			if (m_pValueType == null)
			{
				m_pValueType = pFunctionDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
			}
#line 522 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			if (m_pValueType == null)
			{
				InternalString sTemp = new InternalString("could not get valuetype for some reason ");
				sTemp.Append(pFunctionDecl.m_pTypeRef.m_pTypeToken.GetString());
#line 529 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
				pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
			}
#line 534 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
			if (m_pParamCall.m_pFirstChild == null)
			{
				if (pFunctionDecl.m_pParamDecl.m_pFirstChild != null)
				{
					pValidator.AddError("Params needed for function call?", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
					return;
				}
			}
			else
			{
				if (!pFunctionDecl.m_pParamDecl.ValidateParamCall(m_pParamCall, pValidator, true))
				{
#line 545 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
					return;
				}
			}
		}

#line 549 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			pOutputBuilder.m_sOut.Append(m_sMangledName);
			m_pParamCall.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/FunctionCall.nll"
		public FunctionCall()
		{
		}

	}
}

