#line 1 "../../../Source/Core/AST/FunctionCall.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/FunctionCall.nll"
	class FunctionCall : AST
	{
#line 5 "../../../Source/Core/AST/FunctionCall.nll"
		public string m_sMangledName;
#line 6 "../../../Source/Core/AST/FunctionCall.nll"
		public ParamCall m_pParamCall;
#line 8 "../../../Source/Core/AST/FunctionCall.nll"
		public static FunctionCall TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 10 "../../../Source/Core/AST/FunctionCall.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 12 "../../../Source/Core/AST/FunctionCall.nll"
			Token pNameToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
#line 13 "../../../Source/Core/AST/FunctionCall.nll"
			if (pNameToken == null)
			{
#line 14 "../../../Source/Core/AST/FunctionCall.nll"
				return null;
			}
#line 15 "../../../Source/Core/AST/FunctionCall.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 17 "../../../Source/Core/AST/FunctionCall.nll"
			if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT) == null)
			{
#line 18 "../../../Source/Core/AST/FunctionCall.nll"
				return null;
			}
#line 20 "../../../Source/Core/AST/FunctionCall.nll"
			ParamCall pParamCall = ParamCall.TryCreate(pTokenContainer, pTempOffset);
#line 21 "../../../Source/Core/AST/FunctionCall.nll"
			if (pParamCall == null)
			{
#line 23 "../../../Source/Core/AST/FunctionCall.nll"
				InternalString sTemp = new InternalString("expected ParamCall ");
#line 24 "../../../Source/Core/AST/FunctionCall.nll"
				sTemp.Append(pTokenContainer.StringifyOffset(pTempOffset));
#line 25 "../../../Source/Core/AST/FunctionCall.nll"
				Console.Log(sTemp.GetExternalString());
#line 26 "../../../Source/Core/AST/FunctionCall.nll"
				Assert.Plz(false);
#line 27 "../../../Source/Core/AST/FunctionCall.nll"
				return null;
			}
#line 30 "../../../Source/Core/AST/FunctionCall.nll"
			FunctionCall pFunctionCall = new FunctionCall();
#line 32 "../../../Source/Core/AST/FunctionCall.nll"
			pFunctionCall.m_eType = AST.Type.AST_FUNCTION_CALL;
#line 33 "../../../Source/Core/AST/FunctionCall.nll"
			pFunctionCall.m_pFirstToken = pNameToken;
#line 34 "../../../Source/Core/AST/FunctionCall.nll"
			pFunctionCall.m_sMangledName = pNameToken.GetString();
#line 35 "../../../Source/Core/AST/FunctionCall.nll"
			pFunctionCall.m_pParamCall = pParamCall;
			NumbatLogic.ParamCall __1502716703 = pParamCall;
#line 37 "../../../Source/Core/AST/FunctionCall.nll"
			pParamCall = null;
#line 37 "../../../Source/Core/AST/FunctionCall.nll"
			pFunctionCall.AddChild(__1502716703);
#line 40 "../../../Source/Core/AST/FunctionCall.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.FunctionCall __2079883043 = pFunctionCall;
#line 41 "../../../Source/Core/AST/FunctionCall.nll"
			pFunctionCall = null;
#line 41 "../../../Source/Core/AST/FunctionCall.nll"
			return __2079883043;
		}

#line 44 "../../../Source/Core/AST/FunctionCall.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 46 "../../../Source/Core/AST/FunctionCall.nll"
			string sName = m_pFirstToken.GetString();
#line 48 "../../../Source/Core/AST/FunctionCall.nll"
			AST pBase = this;
#line 49 "../../../Source/Core/AST/FunctionCall.nll"
			if (pParent != null)
			{
#line 51 "../../../Source/Core/AST/FunctionCall.nll"
				if (pParent.GetOperatorType() == OperatorExpr.OperatorType.MEMBER_ACCESS && pParent.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
				{
#line 53 "../../../Source/Core/AST/FunctionCall.nll"
					AddClassDeclReference(pParent.m_pLeft.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
#line 54 "../../../Source/Core/AST/FunctionCall.nll"
					pBase = pParent.m_pLeft.m_pValueType.m_pClassDecl;
				}
				else
#line 56 "../../../Source/Core/AST/FunctionCall.nll"
					if (pParent.GetOperatorType() == OperatorExpr.OperatorType.SCOPE_RESOLUTION)
					{
#line 58 "../../../Source/Core/AST/FunctionCall.nll"
						if (pParent.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL)
						{
#line 60 "../../../Source/Core/AST/FunctionCall.nll"
							AddClassDeclReference(pParent.m_pLeft.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
#line 61 "../../../Source/Core/AST/FunctionCall.nll"
							pBase = pParent.m_pLeft.m_pValueType.m_pClassDecl;
						}
						else
#line 63 "../../../Source/Core/AST/FunctionCall.nll"
							if (pParent.m_pLeft.m_pValueType.m_eType == ValueType.Type.ENUM_DECL)
							{
#line 65 "../../../Source/Core/AST/FunctionCall.nll"
								pBase = pParent.m_pLeft.m_pValueType.m_pEnumDecl;
							}
							else
							{
#line 69 "../../../Source/Core/AST/FunctionCall.nll"
								pValidator.AddError("Unexpected left of ::", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
#line 70 "../../../Source/Core/AST/FunctionCall.nll"
								return;
							}
					}
			}
#line 77 "../../../Source/Core/AST/FunctionCall.nll"
			base.Validate(pValidator, pParent);
#line 79 "../../../Source/Core/AST/FunctionCall.nll"
			AST pResolverAST = null;
#line 81 "../../../Source/Core/AST/FunctionCall.nll"
			bool bResolverCallableAmbiguous = false;
#line 82 "../../../Source/Core/AST/FunctionCall.nll"
			int nCallableCandidatesFromResolver = 0;
#line 84 "../../../Source/Core/AST/FunctionCall.nll"
			Vector<Symbol> pCandidates = new Vector<Symbol>();
#line 85 "../../../Source/Core/AST/FunctionCall.nll"
			pValidator.m_pResolver.ResolveFromNode(pBase, sName, pCandidates);
#line 87 "../../../Source/Core/AST/FunctionCall.nll"
			Vector<Symbol> pCallable = new Vector<Symbol>();
#line 88 "../../../Source/Core/AST/FunctionCall.nll"
			for (int i = 0; i < pCandidates.GetSize(); i++)
			{
#line 90 "../../../Source/Core/AST/FunctionCall.nll"
				Symbol pSym = pCandidates.Get(i);
#line 91 "../../../Source/Core/AST/FunctionCall.nll"
				if (pSym.m_eKind == Symbol.Kind.FUNCTION || pSym.m_eKind == Symbol.Kind.METHOD || pSym.m_eKind == Symbol.Kind.DELEGATE)
				{
#line 95 "../../../Source/Core/AST/FunctionCall.nll"
					pCallable.PushBack(pSym);
#line 96 "../../../Source/Core/AST/FunctionCall.nll"
					nCallableCandidatesFromResolver = nCallableCandidatesFromResolver + 1;
				}
				else
#line 98 "../../../Source/Core/AST/FunctionCall.nll"
					if (pSym.m_eKind == Symbol.Kind.VAR && pSym.m_pDeclAST != null && pSym.m_pDeclAST.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
					{
#line 101 "../../../Source/Core/AST/FunctionCall.nll"
						MemberVarDecl pMVD = (MemberVarDecl)(pSym.m_pDeclAST);
#line 102 "../../../Source/Core/AST/FunctionCall.nll"
						if (pMVD.m_pVarDecl != null && pMVD.m_pVarDecl.m_pTypeRef != null)
						{
#line 104 "../../../Source/Core/AST/FunctionCall.nll"
							ValueType pVT = pMVD.m_pVarDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
#line 105 "../../../Source/Core/AST/FunctionCall.nll"
							if (pVT != null && pVT.m_eType == ValueType.Type.DELEGATE_DECL_VALUE)
							{
#line 107 "../../../Source/Core/AST/FunctionCall.nll"
								pCallable.PushBack(pSym);
#line 108 "../../../Source/Core/AST/FunctionCall.nll"
								nCallableCandidatesFromResolver = nCallableCandidatesFromResolver + 1;
							}
						}
					}
			}
#line 116 "../../../Source/Core/AST/FunctionCall.nll"
			if (pCallable.GetSize() > 1 && m_pParamCall != null)
			{
#line 118 "../../../Source/Core/AST/FunctionCall.nll"
				int nArgCount = 0;
#line 119 "../../../Source/Core/AST/FunctionCall.nll"
				AST pArg = m_pParamCall.m_pFirstChild;
#line 120 "../../../Source/Core/AST/FunctionCall.nll"
				while (pArg != null)
				{
#line 122 "../../../Source/Core/AST/FunctionCall.nll"
					nArgCount++;
#line 123 "../../../Source/Core/AST/FunctionCall.nll"
					pArg = pArg.m_pNextSibling;
				}
#line 126 "../../../Source/Core/AST/FunctionCall.nll"
				Vector<Symbol> pFiltered = new Vector<Symbol>();
#line 127 "../../../Source/Core/AST/FunctionCall.nll"
				for (int i = 0; i < pCallable.GetSize(); i++)
				{
#line 129 "../../../Source/Core/AST/FunctionCall.nll"
					Symbol pSym = pCallable.Get(i);
#line 130 "../../../Source/Core/AST/FunctionCall.nll"
					AST pDeclAST = pSym.m_pDeclAST;
#line 131 "../../../Source/Core/AST/FunctionCall.nll"
					FunctionDecl pFD = null;
#line 133 "../../../Source/Core/AST/FunctionCall.nll"
					if (pDeclAST != null)
					{
#line 135 "../../../Source/Core/AST/FunctionCall.nll"
						if (pDeclAST.m_eType == AST.Type.AST_FUNCTION_DECL)
						{
#line 137 "../../../Source/Core/AST/FunctionCall.nll"
							pFD = (FunctionDecl)(pDeclAST);
						}
						else
#line 139 "../../../Source/Core/AST/FunctionCall.nll"
							if (pDeclAST.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL)
							{
#line 141 "../../../Source/Core/AST/FunctionCall.nll"
								MemberFunctionDecl pMFD = (MemberFunctionDecl)(pDeclAST);
#line 142 "../../../Source/Core/AST/FunctionCall.nll"
								if (pMFD.m_pFunctionDecl != null)
#line 143 "../../../Source/Core/AST/FunctionCall.nll"
									pFD = pMFD.m_pFunctionDecl;
							}
							else
#line 145 "../../../Source/Core/AST/FunctionCall.nll"
								if (pDeclAST.m_eType == AST.Type.DELEGATE_DECL)
								{
#line 147 "../../../Source/Core/AST/FunctionCall.nll"
									DelegateDecl pDD = (DelegateDecl)(pDeclAST);
#line 148 "../../../Source/Core/AST/FunctionCall.nll"
									if (pDD.m_pFunctionDecl != null)
#line 149 "../../../Source/Core/AST/FunctionCall.nll"
										pFD = pDD.m_pFunctionDecl;
								}
								else
#line 151 "../../../Source/Core/AST/FunctionCall.nll"
									if (pDeclAST.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
									{
#line 153 "../../../Source/Core/AST/FunctionCall.nll"
										MemberVarDecl pMVD = (MemberVarDecl)(pDeclAST);
#line 154 "../../../Source/Core/AST/FunctionCall.nll"
										if (pMVD.m_pVarDecl != null && pMVD.m_pVarDecl.m_pTypeRef != null)
										{
#line 156 "../../../Source/Core/AST/FunctionCall.nll"
											ValueType pVT = pMVD.m_pVarDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
#line 157 "../../../Source/Core/AST/FunctionCall.nll"
											if (pVT != null && pVT.m_eType == ValueType.Type.DELEGATE_DECL_VALUE && pVT.m_pDelegateDecl != null)
#line 158 "../../../Source/Core/AST/FunctionCall.nll"
												pFD = pVT.m_pDelegateDecl.m_pFunctionDecl;
										}
									}
					}
#line 163 "../../../Source/Core/AST/FunctionCall.nll"
					int nMinParams = 0;
#line 164 "../../../Source/Core/AST/FunctionCall.nll"
					int nMaxParams = 0;
#line 166 "../../../Source/Core/AST/FunctionCall.nll"
					if (pFD != null && pFD.m_pParamDecl != null)
					{
#line 168 "../../../Source/Core/AST/FunctionCall.nll"
						AST pDeclChild = pFD.m_pParamDecl.m_pFirstChild;
#line 169 "../../../Source/Core/AST/FunctionCall.nll"
						while (pDeclChild != null)
						{
#line 171 "../../../Source/Core/AST/FunctionCall.nll"
							if (pDeclChild.m_eType == AST.Type.AST_VAR_DECL)
							{
#line 173 "../../../Source/Core/AST/FunctionCall.nll"
								nMaxParams++;
#line 174 "../../../Source/Core/AST/FunctionCall.nll"
								VarDecl pVarDecl = (VarDecl)(pDeclChild);
#line 175 "../../../Source/Core/AST/FunctionCall.nll"
								if (pVarDecl.m_pAssignment == null)
#line 176 "../../../Source/Core/AST/FunctionCall.nll"
									nMinParams++;
							}
#line 179 "../../../Source/Core/AST/FunctionCall.nll"
							pDeclChild = pDeclChild.m_pNextSibling;
						}
					}
#line 184 "../../../Source/Core/AST/FunctionCall.nll"
					if (pFD == null || pFD.m_pParamDecl == null)
					{
#line 186 "../../../Source/Core/AST/FunctionCall.nll"
						nMinParams = 0;
#line 187 "../../../Source/Core/AST/FunctionCall.nll"
						nMaxParams = 0;
					}
#line 190 "../../../Source/Core/AST/FunctionCall.nll"
					if (nArgCount >= nMinParams && nArgCount <= nMaxParams)
#line 191 "../../../Source/Core/AST/FunctionCall.nll"
						pFiltered.PushBack(pSym);
				}
#line 194 "../../../Source/Core/AST/FunctionCall.nll"
				if (pFiltered.GetSize() == 1)
				{
#line 196 "../../../Source/Core/AST/FunctionCall.nll"
					Symbol pSymbol = pFiltered.Get(0);
#line 197 "../../../Source/Core/AST/FunctionCall.nll"
					if (pSymbol.m_pDeclAST != null)
#line 198 "../../../Source/Core/AST/FunctionCall.nll"
						pResolverAST = pSymbol.m_pDeclAST;
				}
				else
#line 200 "../../../Source/Core/AST/FunctionCall.nll"
					if (pFiltered.GetSize() > 1)
					{
#line 208 "../../../Source/Core/AST/FunctionCall.nll"
						Vector<Symbol> pBest = new Vector<Symbol>();
#line 209 "../../../Source/Core/AST/FunctionCall.nll"
						int nBestScore = -1;
#line 211 "../../../Source/Core/AST/FunctionCall.nll"
						for (int i = 0; i < pFiltered.GetSize(); i++)
						{
#line 213 "../../../Source/Core/AST/FunctionCall.nll"
							Symbol pSym = pFiltered.Get(i);
#line 214 "../../../Source/Core/AST/FunctionCall.nll"
							AST pDeclAST = pSym.m_pDeclAST;
#line 215 "../../../Source/Core/AST/FunctionCall.nll"
							FunctionDecl pFD = null;
#line 217 "../../../Source/Core/AST/FunctionCall.nll"
							if (pDeclAST != null)
							{
#line 219 "../../../Source/Core/AST/FunctionCall.nll"
								if (pDeclAST.m_eType == AST.Type.AST_FUNCTION_DECL)
								{
#line 221 "../../../Source/Core/AST/FunctionCall.nll"
									pFD = (FunctionDecl)(pDeclAST);
								}
								else
#line 223 "../../../Source/Core/AST/FunctionCall.nll"
									if (pDeclAST.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL)
									{
#line 225 "../../../Source/Core/AST/FunctionCall.nll"
										MemberFunctionDecl pMFD = (MemberFunctionDecl)(pDeclAST);
#line 226 "../../../Source/Core/AST/FunctionCall.nll"
										if (pMFD.m_pFunctionDecl != null)
#line 227 "../../../Source/Core/AST/FunctionCall.nll"
											pFD = pMFD.m_pFunctionDecl;
									}
									else
#line 229 "../../../Source/Core/AST/FunctionCall.nll"
										if (pDeclAST.m_eType == AST.Type.DELEGATE_DECL)
										{
#line 231 "../../../Source/Core/AST/FunctionCall.nll"
											DelegateDecl pDD = (DelegateDecl)(pDeclAST);
#line 232 "../../../Source/Core/AST/FunctionCall.nll"
											if (pDD.m_pFunctionDecl != null)
#line 233 "../../../Source/Core/AST/FunctionCall.nll"
												pFD = pDD.m_pFunctionDecl;
										}
										else
#line 235 "../../../Source/Core/AST/FunctionCall.nll"
											if (pDeclAST.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
											{
#line 237 "../../../Source/Core/AST/FunctionCall.nll"
												MemberVarDecl pMVD = (MemberVarDecl)(pDeclAST);
#line 238 "../../../Source/Core/AST/FunctionCall.nll"
												if (pMVD.m_pVarDecl != null && pMVD.m_pVarDecl.m_pTypeRef != null)
												{
#line 240 "../../../Source/Core/AST/FunctionCall.nll"
													ValueType pVT = pMVD.m_pVarDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
#line 241 "../../../Source/Core/AST/FunctionCall.nll"
													if (pVT != null && pVT.m_eType == ValueType.Type.DELEGATE_DECL_VALUE && pVT.m_pDelegateDecl != null)
#line 242 "../../../Source/Core/AST/FunctionCall.nll"
														pFD = pVT.m_pDelegateDecl.m_pFunctionDecl;
												}
											}
							}
#line 252 "../../../Source/Core/AST/FunctionCall.nll"
							bool bTypeOk = true;
#line 253 "../../../Source/Core/AST/FunctionCall.nll"
							if (pFD != null && pFD.m_pParamDecl != null)
#line 254 "../../../Source/Core/AST/FunctionCall.nll"
								bTypeOk = pFD.m_pParamDecl.ValidateParamCall(m_pParamCall, pValidator, true);
#line 256 "../../../Source/Core/AST/FunctionCall.nll"
							if (!bTypeOk)
#line 257 "../../../Source/Core/AST/FunctionCall.nll"
								continue;
#line 262 "../../../Source/Core/AST/FunctionCall.nll"
							int nScore = 0;
#line 263 "../../../Source/Core/AST/FunctionCall.nll"
							if (pFD != null && pFD.m_pParamDecl != null)
							{
#line 265 "../../../Source/Core/AST/FunctionCall.nll"
								int nIndex = 0;
#line 266 "../../../Source/Core/AST/FunctionCall.nll"
								AST pCallChild = m_pParamCall.m_pFirstChild;
#line 267 "../../../Source/Core/AST/FunctionCall.nll"
								AST pDeclChild = pFD.m_pParamDecl.m_pFirstChild;
#line 269 "../../../Source/Core/AST/FunctionCall.nll"
								while (true)
								{
#line 271 "../../../Source/Core/AST/FunctionCall.nll"
									if (pCallChild == null || pDeclChild == null)
#line 272 "../../../Source/Core/AST/FunctionCall.nll"
										break;
#line 274 "../../../Source/Core/AST/FunctionCall.nll"
									if (pDeclChild.m_eType != AST.Type.AST_VAR_DECL)
#line 275 "../../../Source/Core/AST/FunctionCall.nll"
										break;
#line 277 "../../../Source/Core/AST/FunctionCall.nll"
									VarDecl pVarDecl = (VarDecl)(pDeclChild);
#line 278 "../../../Source/Core/AST/FunctionCall.nll"
									ValueType pValueType = pVarDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
#line 279 "../../../Source/Core/AST/FunctionCall.nll"
									if (pValueType == null || pCallChild.m_pValueType == null)
									{
#line 280 "../../../Source/Core/AST/FunctionCall.nll"
										break;
									}
#line 282 "../../../Source/Core/AST/FunctionCall.nll"
									ValueType pArgVT = pCallChild.m_pValueType;
#line 285 "../../../Source/Core/AST/FunctionCall.nll"
									if (pArgVT.m_eType == pValueType.m_eType && pArgVT.m_eType != ValueType.Type.CLASS_DECL_VALUE && pArgVT.m_ePointerType == pValueType.m_ePointerType)
									{
#line 289 "../../../Source/Core/AST/FunctionCall.nll"
										nScore += 2;
									}
									else
#line 291 "../../../Source/Core/AST/FunctionCall.nll"
										if (pArgVT.m_eType == ValueType.Type.CLASS_DECL_VALUE && pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
										{
#line 294 "../../../Source/Core/AST/FunctionCall.nll"
											ClassDecl pFromClass = pArgVT.m_pClassDecl;
#line 295 "../../../Source/Core/AST/FunctionCall.nll"
											ClassDecl pToClass = pValueType.m_pClassDecl;
#line 298 "../../../Source/Core/AST/FunctionCall.nll"
											if (pFromClass == pToClass && pArgVT.m_ePointerType == pValueType.m_ePointerType)
											{
#line 301 "../../../Source/Core/AST/FunctionCall.nll"
												nScore += 3;
											}
											else
											{
#line 308 "../../../Source/Core/AST/FunctionCall.nll"
												int nDistance = -1;
#line 309 "../../../Source/Core/AST/FunctionCall.nll"
												int nWalk = 0;
#line 310 "../../../Source/Core/AST/FunctionCall.nll"
												ClassDecl pWalk = pFromClass;
#line 311 "../../../Source/Core/AST/FunctionCall.nll"
												while (pWalk != null)
												{
#line 313 "../../../Source/Core/AST/FunctionCall.nll"
													if (pWalk == pToClass)
													{
#line 315 "../../../Source/Core/AST/FunctionCall.nll"
														nDistance = nWalk;
#line 316 "../../../Source/Core/AST/FunctionCall.nll"
														break;
													}
#line 319 "../../../Source/Core/AST/FunctionCall.nll"
													if (pWalk.m_pBaseTypeRef == null)
#line 320 "../../../Source/Core/AST/FunctionCall.nll"
														break;
#line 322 "../../../Source/Core/AST/FunctionCall.nll"
													AST pBaseAST = pWalk.m_pBaseTypeRef.m_pFoundType;
#line 323 "../../../Source/Core/AST/FunctionCall.nll"
													if (pBaseAST == null || pBaseAST.m_eType != AST.Type.AST_CLASS_DECL)
#line 324 "../../../Source/Core/AST/FunctionCall.nll"
														break;
#line 326 "../../../Source/Core/AST/FunctionCall.nll"
													pWalk = (ClassDecl)(pBaseAST);
#line 327 "../../../Source/Core/AST/FunctionCall.nll"
													nWalk++;
												}
#line 330 "../../../Source/Core/AST/FunctionCall.nll"
												if (nDistance >= 0)
												{
#line 334 "../../../Source/Core/AST/FunctionCall.nll"
													if (nDistance == 0)
#line 335 "../../../Source/Core/AST/FunctionCall.nll"
														nScore += 3;
													else
#line 336 "../../../Source/Core/AST/FunctionCall.nll"
														if (nDistance == 1)
#line 337 "../../../Source/Core/AST/FunctionCall.nll"
															nScore += 2;
														else
#line 339 "../../../Source/Core/AST/FunctionCall.nll"
															nScore += 1;
												}
											}
										}
#line 344 "../../../Source/Core/AST/FunctionCall.nll"
									nIndex++;
#line 345 "../../../Source/Core/AST/FunctionCall.nll"
									pCallChild = pCallChild.m_pNextSibling;
#line 346 "../../../Source/Core/AST/FunctionCall.nll"
									pDeclChild = pDeclChild.m_pNextSibling;
								}
							}
#line 350 "../../../Source/Core/AST/FunctionCall.nll"
							if (nScore > nBestScore)
							{
#line 352 "../../../Source/Core/AST/FunctionCall.nll"
								pBest.Clear();
#line 353 "../../../Source/Core/AST/FunctionCall.nll"
								pBest.PushBack(pSym);
#line 354 "../../../Source/Core/AST/FunctionCall.nll"
								nBestScore = nScore;
							}
							else
#line 356 "../../../Source/Core/AST/FunctionCall.nll"
								if (nScore == nBestScore)
								{
#line 358 "../../../Source/Core/AST/FunctionCall.nll"
									pBest.PushBack(pSym);
								}
						}
#line 362 "../../../Source/Core/AST/FunctionCall.nll"
						if (pBest.GetSize() == 1 && nBestScore >= 0)
						{
#line 364 "../../../Source/Core/AST/FunctionCall.nll"
							Symbol pSymbol = pBest.Get(0);
#line 365 "../../../Source/Core/AST/FunctionCall.nll"
							if (pSymbol.m_pDeclAST != null)
#line 366 "../../../Source/Core/AST/FunctionCall.nll"
								pResolverAST = pSymbol.m_pDeclAST;
						}
						else
#line 368 "../../../Source/Core/AST/FunctionCall.nll"
							if (pBest.GetSize() > 1 && nBestScore >= 0)
							{
#line 372 "../../../Source/Core/AST/FunctionCall.nll"
								pCallable.Clear();
#line 373 "../../../Source/Core/AST/FunctionCall.nll"
								for (int i = 0; i < pBest.GetSize(); i++)
								{
#line 375 "../../../Source/Core/AST/FunctionCall.nll"
									pCallable.PushBack(pBest.Get(i));
								}
							}
					}
			}
#line 383 "../../../Source/Core/AST/FunctionCall.nll"
			if (pCallable.GetSize() == 1 && pResolverAST == null)
			{
#line 385 "../../../Source/Core/AST/FunctionCall.nll"
				Symbol pSymbol = pCallable.Get(0);
#line 386 "../../../Source/Core/AST/FunctionCall.nll"
				if (pSymbol.m_pDeclAST != null)
#line 387 "../../../Source/Core/AST/FunctionCall.nll"
					pResolverAST = pSymbol.m_pDeclAST;
			}
			else
#line 389 "../../../Source/Core/AST/FunctionCall.nll"
				if (pCallable.GetSize() > 1 && pResolverAST == null)
#line 390 "../../../Source/Core/AST/FunctionCall.nll"
					bResolverCallableAmbiguous = true;
#line 392 "../../../Source/Core/AST/FunctionCall.nll"
			AST pAST = pResolverAST;
#line 393 "../../../Source/Core/AST/FunctionCall.nll"
			if (pAST == null)
			{
#line 395 "../../../Source/Core/AST/FunctionCall.nll"
				if (bResolverCallableAmbiguous)
				{
#line 397 "../../../Source/Core/AST/FunctionCall.nll"
					InternalString sAmbiguous = new InternalString("Ambiguous function call (multiple overloads in scope): ");
#line 398 "../../../Source/Core/AST/FunctionCall.nll"
					sAmbiguous.Append(sName);
#line 399 "../../../Source/Core/AST/FunctionCall.nll"
					pValidator.AddError(sAmbiguous.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				}
				else
				{
#line 403 "../../../Source/Core/AST/FunctionCall.nll"
					InternalString sTemp = new InternalString("Func Unbeknownst! ");
#line 404 "../../../Source/Core/AST/FunctionCall.nll"
					sTemp.Append(sName);
#line 405 "../../../Source/Core/AST/FunctionCall.nll"
					sTemp.Append(" parent is: ");
#line 406 "../../../Source/Core/AST/FunctionCall.nll"
					pBase.StringifyType(sTemp);
#line 407 "../../../Source/Core/AST/FunctionCall.nll"
					if (pBase.m_eType == AST.Type.AST_CLASS_DECL)
					{
#line 409 "../../../Source/Core/AST/FunctionCall.nll"
						ClassDecl pClassDecl = (ClassDecl)(pBase);
#line 410 "../../../Source/Core/AST/FunctionCall.nll"
						sTemp.Append(" ");
#line 411 "../../../Source/Core/AST/FunctionCall.nll"
						pClassDecl.AppendFullyQualifiedName(sTemp);
					}
#line 413 "../../../Source/Core/AST/FunctionCall.nll"
					pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				}
#line 415 "../../../Source/Core/AST/FunctionCall.nll"
				return;
			}
#line 418 "../../../Source/Core/AST/FunctionCall.nll"
			FunctionDecl pFunctionDecl = null;
#line 421 "../../../Source/Core/AST/FunctionCall.nll"
			if (pAST.m_eType == AST.Type.AST_VAR_DECL)
			{
#line 423 "../../../Source/Core/AST/FunctionCall.nll"
				VarDecl pVarDecl = (VarDecl)(pAST);
#line 424 "../../../Source/Core/AST/FunctionCall.nll"
				ValueType pValueType = pVarDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
#line 425 "../../../Source/Core/AST/FunctionCall.nll"
				if (pValueType != null)
				{
#line 427 "../../../Source/Core/AST/FunctionCall.nll"
					if (pValueType.m_eType == ValueType.Type.DELEGATE_DECL_VALUE)
					{
#line 429 "../../../Source/Core/AST/FunctionCall.nll"
						if (pValueType.m_pDelegateDecl == null)
						{
#line 431 "../../../Source/Core/AST/FunctionCall.nll"
							InternalString sTemp = new InternalString("DELEGATE_DECL_VALUE does not have m_pDelegateDecl set???");
#line 432 "../../../Source/Core/AST/FunctionCall.nll"
							pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
#line 433 "../../../Source/Core/AST/FunctionCall.nll"
							return;
						}
#line 436 "../../../Source/Core/AST/FunctionCall.nll"
						pFunctionDecl = pValueType.m_pDelegateDecl.m_pFunctionDecl;
					}
				}
			}
			else
#line 440 "../../../Source/Core/AST/FunctionCall.nll"
				if (pAST.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
				{
#line 442 "../../../Source/Core/AST/FunctionCall.nll"
					MemberVarDecl pMVD = (MemberVarDecl)(pAST);
#line 443 "../../../Source/Core/AST/FunctionCall.nll"
					if (pMVD.m_pVarDecl != null && pMVD.m_pVarDecl.m_pTypeRef != null)
					{
#line 445 "../../../Source/Core/AST/FunctionCall.nll"
						ValueType pValueType = pMVD.m_pVarDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
#line 446 "../../../Source/Core/AST/FunctionCall.nll"
						if (pValueType != null && pValueType.m_eType == ValueType.Type.DELEGATE_DECL_VALUE)
						{
#line 448 "../../../Source/Core/AST/FunctionCall.nll"
							if (pValueType.m_pDelegateDecl == null)
							{
#line 450 "../../../Source/Core/AST/FunctionCall.nll"
								InternalString sTemp = new InternalString("DELEGATE_DECL_VALUE does not have m_pDelegateDecl set???");
#line 451 "../../../Source/Core/AST/FunctionCall.nll"
								pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
#line 452 "../../../Source/Core/AST/FunctionCall.nll"
								return;
							}
#line 454 "../../../Source/Core/AST/FunctionCall.nll"
							pFunctionDecl = pValueType.m_pDelegateDecl.m_pFunctionDecl;
						}
					}
				}
#line 459 "../../../Source/Core/AST/FunctionCall.nll"
			if (pAST.m_eType == AST.Type.AST_FUNCTION_DECL)
			{
#line 461 "../../../Source/Core/AST/FunctionCall.nll"
				pFunctionDecl = (FunctionDecl)(pAST);
			}
			else
#line 463 "../../../Source/Core/AST/FunctionCall.nll"
				if (pAST.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL)
				{
#line 465 "../../../Source/Core/AST/FunctionCall.nll"
					MemberFunctionDecl pMFD = (MemberFunctionDecl)(pAST);
#line 466 "../../../Source/Core/AST/FunctionCall.nll"
					if (pMFD.m_pFunctionDecl != null)
#line 467 "../../../Source/Core/AST/FunctionCall.nll"
						pFunctionDecl = pMFD.m_pFunctionDecl;
				}
#line 470 "../../../Source/Core/AST/FunctionCall.nll"
			if (pFunctionDecl == null)
			{
#line 472 "../../../Source/Core/AST/FunctionCall.nll"
				InternalString sTemp = new InternalString("Is not a function? ");
#line 473 "../../../Source/Core/AST/FunctionCall.nll"
				sTemp.Append(sName);
#line 474 "../../../Source/Core/AST/FunctionCall.nll"
				sTemp.Append(" ");
#line 475 "../../../Source/Core/AST/FunctionCall.nll"
				pAST.StringifyType(sTemp);
#line 476 "../../../Source/Core/AST/FunctionCall.nll"
				pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
#line 477 "../../../Source/Core/AST/FunctionCall.nll"
				return;
			}
#line 481 "../../../Source/Core/AST/FunctionCall.nll"
			if (pParent != null && pParent.m_pLeft != null)
			{
#line 483 "../../../Source/Core/AST/FunctionCall.nll"
				ValueType pLeftValueType = pParent.m_pLeft.m_pValueType;
#line 484 "../../../Source/Core/AST/FunctionCall.nll"
				if (pLeftValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE && pLeftValueType.m_pGenericValueTypeVector != null && pLeftValueType.m_pGenericValueTypeVector.GetSize() > 0)
				{
#line 487 "../../../Source/Core/AST/FunctionCall.nll"
					if (pLeftValueType.m_pGenericValueTypeVector.GetSize() != pLeftValueType.m_pClassDecl.m_pGenericTypeDeclVector.GetSize())
					{
#line 489 "../../../Source/Core/AST/FunctionCall.nll"
						InternalString sTemp2 = new InternalString("Mismatched generics? ");
#line 490 "../../../Source/Core/AST/FunctionCall.nll"
						pLeftValueType.StringifyType(sTemp2);
#line 491 "../../../Source/Core/AST/FunctionCall.nll"
						sTemp2.Append(" ");
#line 492 "../../../Source/Core/AST/FunctionCall.nll"
						sTemp2.AppendInt(pLeftValueType.m_pGenericValueTypeVector.GetSize());
#line 493 "../../../Source/Core/AST/FunctionCall.nll"
						sTemp2.Append(" != ");
#line 494 "../../../Source/Core/AST/FunctionCall.nll"
						sTemp2.Append(pLeftValueType.m_pClassDecl.m_pNameToken.GetString());
#line 495 "../../../Source/Core/AST/FunctionCall.nll"
						sTemp2.Append(" ");
#line 496 "../../../Source/Core/AST/FunctionCall.nll"
						sTemp2.AppendInt(pLeftValueType.m_pClassDecl.m_pGenericTypeDeclVector.GetSize());
#line 497 "../../../Source/Core/AST/FunctionCall.nll"
						pValidator.AddError(sTemp2.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
#line 498 "../../../Source/Core/AST/FunctionCall.nll"
						return;
					}
#line 501 "../../../Source/Core/AST/FunctionCall.nll"
					for (int i = 0; i < pLeftValueType.m_pGenericValueTypeVector.GetSize(); i++)
					{
#line 503 "../../../Source/Core/AST/FunctionCall.nll"
						ValueType pGenericValueType = pLeftValueType.m_pGenericValueTypeVector.Get(i).Clone();
#line 504 "../../../Source/Core/AST/FunctionCall.nll"
						GenericTypeDecl pGenericTypeDecl = pLeftValueType.m_pClassDecl.m_pGenericTypeDeclVector.Get(i);
#line 506 "../../../Source/Core/AST/FunctionCall.nll"
						if (ExternalString.Equal(pGenericTypeDecl.m_pFirstToken.GetString(), pFunctionDecl.m_pTypeRef.m_pTypeToken.GetString()))
						{
							NumbatLogic.ValueType __2182339513 = pGenericValueType;
#line 508 "../../../Source/Core/AST/FunctionCall.nll"
							pGenericValueType = null;
#line 508 "../../../Source/Core/AST/FunctionCall.nll"
							m_pValueType = __2182339513;
#line 509 "../../../Source/Core/AST/FunctionCall.nll"
							m_pValueType.m_ePointerType = pFunctionDecl.m_pTypeRef.m_ePointerType;
						}
					}
				}
			}
#line 515 "../../../Source/Core/AST/FunctionCall.nll"
			if (m_pValueType == null)
			{
#line 517 "../../../Source/Core/AST/FunctionCall.nll"
				m_pValueType = pFunctionDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
			}
#line 522 "../../../Source/Core/AST/FunctionCall.nll"
			if (m_pValueType == null)
			{
#line 524 "../../../Source/Core/AST/FunctionCall.nll"
				InternalString sTemp = new InternalString("could not get valuetype for some reason ");
#line 525 "../../../Source/Core/AST/FunctionCall.nll"
				sTemp.Append(pFunctionDecl.m_pTypeRef.m_pTypeToken.GetString());
#line 529 "../../../Source/Core/AST/FunctionCall.nll"
				pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
			}
#line 534 "../../../Source/Core/AST/FunctionCall.nll"
			if (m_pParamCall.m_pFirstChild == null)
			{
#line 536 "../../../Source/Core/AST/FunctionCall.nll"
				if (pFunctionDecl.m_pParamDecl.m_pFirstChild != null)
				{
#line 538 "../../../Source/Core/AST/FunctionCall.nll"
					pValidator.AddError("Params needed for function call?", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
#line 539 "../../../Source/Core/AST/FunctionCall.nll"
					return;
				}
			}
			else
			{
#line 544 "../../../Source/Core/AST/FunctionCall.nll"
				if (!pFunctionDecl.m_pParamDecl.ValidateParamCall(m_pParamCall, pValidator, true))
				{
#line 545 "../../../Source/Core/AST/FunctionCall.nll"
					return;
				}
			}
		}

#line 549 "../../../Source/Core/AST/FunctionCall.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 551 "../../../Source/Core/AST/FunctionCall.nll"
			pOutputBuilder.m_sOut.Append(m_sMangledName);
#line 552 "../../../Source/Core/AST/FunctionCall.nll"
			m_pParamCall.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}

#line 3 "../../../Source/Core/AST/FunctionCall.nll"
		public FunctionCall()
		{
		}

	}
}

