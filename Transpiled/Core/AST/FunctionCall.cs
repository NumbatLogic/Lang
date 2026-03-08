#line 1 "../../../Source/Core/AST/FunctionCall.nll"
namespace NumbatLogic
{
	class FunctionCall : AST
	{
		public string m_sMangledName;
		public ParamCall m_pParamCall;
		public static FunctionCall TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pNameToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
			if (pNameToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT) == null)
			{
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
			FunctionCall pFunctionCall = new FunctionCall();
			pFunctionCall.m_eType = AST.Type.AST_FUNCTION_CALL;
			pFunctionCall.m_pFirstToken = pNameToken;
			pFunctionCall.m_sMangledName = pNameToken.GetString();
			pFunctionCall.m_pParamCall = pParamCall;
			NumbatLogic.ParamCall __1502716703 = pParamCall;
			pParamCall = null;
			pFunctionCall.AddChild(__1502716703);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.FunctionCall __2079883043 = pFunctionCall;
			pFunctionCall = null;
			return __2079883043;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			string sName = m_pFirstToken.GetString();
			AST pBase = this;
			AST pChild = this;
			if (pParent != null)
			{
				if (pParent.GetOperatorType() == OperatorExpr.OperatorType.MEMBER_ACCESS && pParent.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
				{
					AddClassDeclReference(pParent.m_pLeft.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
					pBase = pParent.m_pLeft.m_pValueType.m_pClassDecl;
					pChild = null;
				}
				else
					if (pParent.GetOperatorType() == OperatorExpr.OperatorType.SCOPE_RESOLUTION)
					{
						if (pParent.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL)
						{
							AddClassDeclReference(pParent.m_pLeft.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
							pBase = pParent.m_pLeft.m_pValueType.m_pClassDecl;
							pChild = null;
						}
						else
							if (pParent.m_pLeft.m_pValueType.m_eType == ValueType.Type.ENUM_DECL)
							{
								pBase = pParent.m_pLeft.m_pValueType.m_pEnumDecl;
								pChild = null;
							}
							else
							{
								pValidator.AddError("Unexpected left of ::", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
								return;
							}
					}
			}
			base.Validate(pValidator, pParent);
			AST pResolverAST = null;
			bool bResolverCallableAmbiguous = false;
			int nCallableCandidatesFromResolver = 0;
			Vector<Symbol> pCandidates = new Vector<Symbol>();
			pValidator.m_pResolver.ResolveFromNode(pBase, sName, pCandidates);
			Vector<Symbol> pCallable = new Vector<Symbol>();
			for (int i = 0; i < pCandidates.GetSize(); i++)
			{
				Symbol pSym = pCandidates.Get(i);
				if (pSym.m_eKind == Symbol.Kind.FUNCTION || pSym.m_eKind == Symbol.Kind.METHOD || pSym.m_eKind == Symbol.Kind.DELEGATE)
				{
					pCallable.PushBack(pSym);
					nCallableCandidatesFromResolver = nCallableCandidatesFromResolver + 1;
				}
				else
					if (pSym.m_eKind == Symbol.Kind.VAR && pSym.m_pDeclAST != null && pSym.m_pDeclAST.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
					{
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
			if (pCallable.GetSize() > 1 && m_pParamCall != null)
			{
				int nArgCount = 0;
				AST pArg = m_pParamCall.m_pFirstChild;
				while (pArg != null)
				{
					nArgCount++;
					pArg = pArg.m_pNextSibling;
				}
				Vector<Symbol> pFiltered = new Vector<Symbol>();
				for (int i = 0; i < pCallable.GetSize(); i++)
				{
					Symbol pSym = pCallable.Get(i);
					AST pDeclAST = pSym.m_pDeclAST;
					FunctionDecl pFD = null;
					if (pDeclAST != null)
					{
						if (pDeclAST.m_eType == AST.Type.AST_FUNCTION_DECL)
						{
							pFD = (FunctionDecl)(pDeclAST);
						}
						else
							if (pDeclAST.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL)
							{
								MemberFunctionDecl pMFD = (MemberFunctionDecl)(pDeclAST);
								if (pMFD.m_pFunctionDecl != null)
									pFD = pMFD.m_pFunctionDecl;
							}
							else
								if (pDeclAST.m_eType == AST.Type.DELEGATE_DECL)
								{
									DelegateDecl pDD = (DelegateDecl)(pDeclAST);
									if (pDD.m_pFunctionDecl != null)
										pFD = pDD.m_pFunctionDecl;
								}
								else
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
					int nMinParams = 0;
					int nMaxParams = 0;
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
							pDeclChild = pDeclChild.m_pNextSibling;
						}
					}
					if (pFD == null || pFD.m_pParamDecl == null)
					{
						nMinParams = 0;
						nMaxParams = 0;
					}
					if (nArgCount >= nMinParams && nArgCount <= nMaxParams)
						pFiltered.PushBack(pSym);
				}
				if (pFiltered.GetSize() == 1)
				{
					Symbol pSymbol = pFiltered.Get(0);
					if (pSymbol.m_pDeclAST != null)
						pResolverAST = pSymbol.m_pDeclAST;
				}
				else
					if (pFiltered.GetSize() > 1)
					{
						Vector<Symbol> pBest = new Vector<Symbol>();
						int nBestScore = -1;
						for (int i = 0; i < pFiltered.GetSize(); i++)
						{
							Symbol pSym = pFiltered.Get(i);
							AST pDeclAST = pSym.m_pDeclAST;
							FunctionDecl pFD = null;
							if (pDeclAST != null)
							{
								if (pDeclAST.m_eType == AST.Type.AST_FUNCTION_DECL)
								{
									pFD = (FunctionDecl)(pDeclAST);
								}
								else
									if (pDeclAST.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL)
									{
										MemberFunctionDecl pMFD = (MemberFunctionDecl)(pDeclAST);
										if (pMFD.m_pFunctionDecl != null)
											pFD = pMFD.m_pFunctionDecl;
									}
									else
										if (pDeclAST.m_eType == AST.Type.DELEGATE_DECL)
										{
											DelegateDecl pDD = (DelegateDecl)(pDeclAST);
											if (pDD.m_pFunctionDecl != null)
												pFD = pDD.m_pFunctionDecl;
										}
										else
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
							bool bTypeOk = true;
							if (pFD != null && pFD.m_pParamDecl != null)
								bTypeOk = pFD.m_pParamDecl.ValidateParamCall(m_pParamCall, pValidator, true);
							if (!bTypeOk)
								continue;
							int nScore = 0;
							if (pFD != null && pFD.m_pParamDecl != null)
							{
								int nIndex = 0;
								AST pCallChild = m_pParamCall.m_pFirstChild;
								AST pDeclChild = pFD.m_pParamDecl.m_pFirstChild;
								while (true)
								{
									if (pCallChild == null || pDeclChild == null)
										break;
									if (pDeclChild.m_eType != AST.Type.AST_VAR_DECL)
										break;
									VarDecl pVarDecl = (VarDecl)(pDeclChild);
									ValueType pValueType = pVarDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
									if (pValueType == null || pCallChild.m_pValueType == null)
									{
										break;
									}
									ValueType pArgVT = pCallChild.m_pValueType;
									if (pArgVT.m_eType == pValueType.m_eType && pArgVT.m_eType != ValueType.Type.CLASS_DECL_VALUE && pArgVT.m_ePointerType == pValueType.m_ePointerType)
									{
										nScore += 2;
									}
									else
										if (pArgVT.m_eType == ValueType.Type.CLASS_DECL_VALUE && pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
										{
											ClassDecl pFromClass = pArgVT.m_pClassDecl;
											ClassDecl pToClass = pValueType.m_pClassDecl;
											if (pFromClass == pToClass && pArgVT.m_ePointerType == pValueType.m_ePointerType)
											{
												nScore += 3;
											}
											else
											{
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
													if (pWalk.m_pBaseTypeRef == null)
														break;
													AST pBaseAST = pWalk.m_pBaseTypeRef.m_pFoundType;
													if (pBaseAST == null || pBaseAST.m_eType != AST.Type.AST_CLASS_DECL)
														break;
													pWalk = (ClassDecl)(pBaseAST);
													nWalk++;
												}
												if (nDistance >= 0)
												{
													if (nDistance == 0)
														nScore += 3;
													else
														if (nDistance == 1)
															nScore += 2;
														else
															nScore += 1;
												}
											}
										}
									nIndex++;
									pCallChild = pCallChild.m_pNextSibling;
									pDeclChild = pDeclChild.m_pNextSibling;
								}
							}
							if (nScore > nBestScore)
							{
								pBest.Clear();
								pBest.PushBack(pSym);
								nBestScore = nScore;
							}
							else
								if (nScore == nBestScore)
								{
									pBest.PushBack(pSym);
								}
						}
						if (pBest.GetSize() == 1 && nBestScore >= 0)
						{
							Symbol pSymbol = pBest.Get(0);
							if (pSymbol.m_pDeclAST != null)
								pResolverAST = pSymbol.m_pDeclAST;
						}
						else
							if (pBest.GetSize() > 1 && nBestScore >= 0)
							{
								pCallable.Clear();
								for (int i = 0; i < pBest.GetSize(); i++)
								{
									pCallable.PushBack(pBest.Get(i));
								}
							}
					}
			}
			if (pCallable.GetSize() == 1 && pResolverAST == null)
			{
				Symbol pSymbol = pCallable.Get(0);
				if (pSymbol.m_pDeclAST != null)
					pResolverAST = pSymbol.m_pDeclAST;
			}
			else
				if (pCallable.GetSize() > 1 && pResolverAST == null)
					bResolverCallableAmbiguous = true;
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
						pClassDecl.AppendFullyQualifiedName(sTemp);
					}
					pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				}
				return;
			}
			FunctionDecl pFunctionDecl = null;
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
						pFunctionDecl = pValueType.m_pDelegateDecl.m_pFunctionDecl;
					}
				}
			}
			else
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
			if (pAST.m_eType == AST.Type.AST_FUNCTION_DECL)
			{
				pFunctionDecl = (FunctionDecl)(pAST);
			}
			else
				if (pAST.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL)
				{
					MemberFunctionDecl pMFD = (MemberFunctionDecl)(pAST);
					if (pMFD.m_pFunctionDecl != null)
						pFunctionDecl = pMFD.m_pFunctionDecl;
				}
			if (pFunctionDecl == null)
			{
				InternalString sTemp = new InternalString("Is not a function? ");
				sTemp.Append(sName);
				sTemp.Append(" ");
				pAST.StringifyType(sTemp);
				pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				return;
			}
			if (pParent != null && pParent.m_pLeft != null)
			{
				ValueType pLeftValueType = pParent.m_pLeft.m_pValueType;
				if (pLeftValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE && pLeftValueType.m_pGenericValueTypeVector != null && pLeftValueType.m_pGenericValueTypeVector.GetSize() > 0)
				{
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
					for (int i = 0; i < pLeftValueType.m_pGenericValueTypeVector.GetSize(); i++)
					{
						ValueType pGenericValueType = pLeftValueType.m_pGenericValueTypeVector.Get(i).Clone();
						GenericTypeDecl pGenericTypeDecl = pLeftValueType.m_pClassDecl.m_pGenericTypeDeclVector.Get(i);
						if (ExternalString.Equal(pGenericTypeDecl.m_pFirstToken.GetString(), pFunctionDecl.m_pTypeRef.m_pTypeToken.GetString()))
						{
							NumbatLogic.ValueType __2182405106 = pGenericValueType;
							pGenericValueType = null;
							m_pValueType = __2182405106;
							m_pValueType.m_ePointerType = pFunctionDecl.m_pTypeRef.m_ePointerType;
						}
					}
				}
			}
			if (m_pValueType == null)
			{
				m_pValueType = pFunctionDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
			}
			if (m_pValueType == null)
			{
				InternalString sTemp = new InternalString("could not get valuetype for some reason ");
				sTemp.Append(pFunctionDecl.m_pTypeRef.m_pTypeToken.GetString());
				pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
			}
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
					return;
				}
			}
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder out)
		{
			out.m_sOut.Append(m_sMangledName);
			m_pParamCall.Stringify(eLanguage, eOutputFile, 0, out);
		}

		public FunctionCall()
		{
		}

	}
}

