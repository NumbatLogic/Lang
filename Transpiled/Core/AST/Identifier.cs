#line 1 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
namespace NumbatLogic
{
	class Identifier : AST
	{
		public Token m_pNameToken;
#line 7 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
		public static Identifier TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 11 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
			Token pToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
			if (pToken == null)
			{
#line 13 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
				return null;
			}
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
			Identifier pIdentifier = new Identifier();
			pIdentifier.m_eType = AST.Type.AST_IDENTIFIER;
			pIdentifier.m_pNameToken = pToken;
			pIdentifier.m_pFirstToken = pToken;
#line 21 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.Identifier __4180376026 = pIdentifier;
			pIdentifier = null;
#line 23 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
			return __4180376026;
		}

		public override AST BaseClone()
		{
			Identifier pIdentifier = new Identifier();
			pIdentifier.m_eType = m_eType;
			pIdentifier.m_pNameToken = m_pNameToken;
			pIdentifier.m_pFirstToken = m_pFirstToken;
			NumbatLogic.Identifier __4180441624 = pIdentifier;
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
			pIdentifier = null;
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
			return __4180441624;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			string sName = m_pNameToken.GetString();
#line 40 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
			AST pContextParent = (pParent != null) ? (AST)(pParent) : m_pParent;
#line 42 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
			AST pAST = null;
			AST pBase = this;
			bool bResolverAmbiguous = false;
			if (pContextParent != null)
			{
#line 50 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
				if (pContextParent.m_eType == AST.Type.AST_ARRAY_LOOKUP)
				{
					ArrayLookup pAL = (ArrayLookup)(pContextParent);
					if (pAL.m_pExpression == this)
					{
						AST pWalk = pAL.m_pParent;
						while (pWalk != null && pBase == this)
						{
							if (pWalk.m_eType == AST.Type.AST_OPERATOR_EXPR)
							{
								OperatorExpr pOpWalk = (OperatorExpr)(pWalk);
								bool bRightIsArrayLookupOrMulLeft = (pOpWalk.m_pRight == pAL);
								if (!bRightIsArrayLookupOrMulLeft && pOpWalk.m_pRight != null && pOpWalk.m_pRight.m_eType == AST.Type.AST_OPERATOR_EXPR)
								{
									OperatorExpr pRightOp = (OperatorExpr)(pOpWalk.m_pRight);
									bRightIsArrayLookupOrMulLeft = (pRightOp.m_pLeft == pAL);
								}
								if (pOpWalk.GetOperatorType() == OperatorExpr.OperatorType.SCOPE_RESOLUTION && pOpWalk.m_pLeft != null && bRightIsArrayLookupOrMulLeft)
								{
#line 70 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
									if (pOpWalk.m_pLeft.m_pValueType == null)
										pOpWalk.m_pLeft.Validate(pValidator, pOpWalk);
									if (pOpWalk.m_pLeft.m_pValueType != null)
									{
										if (pOpWalk.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL || pOpWalk.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
										{
#line 77 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
											AddClassDeclReference(pOpWalk.m_pLeft.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
											pBase = pOpWalk.m_pLeft.m_pValueType.m_pClassDecl;
											break;
										}
										else
#line 81 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
											if (pOpWalk.m_pLeft.m_pValueType.m_eType == ValueType.Type.ENUM_DECL)
											{
												pBase = pOpWalk.m_pLeft.m_pValueType.m_pEnumDecl;
												break;
											}
									}
								}
							}
							pWalk = pWalk.m_pParent;
						}
					}
				}
				if (pContextParent.m_eType == AST.Type.AST_OPERATOR_EXPR)
				{
					OperatorExpr pOpContext = (OperatorExpr)(pContextParent);
					if (pOpContext.GetOperatorType() == OperatorExpr.OperatorType.MEMBER_ACCESS && pOpContext.m_pLeft != null && pOpContext.m_pLeft.m_pValueType != null && pOpContext.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
					{
						AddClassDeclReference(pOpContext.m_pLeft.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
						pBase = pOpContext.m_pLeft.m_pValueType.m_pClassDecl;
					}
					else
#line 101 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
						if (pOpContext.GetOperatorType() == OperatorExpr.OperatorType.SCOPE_RESOLUTION && pOpContext.m_pLeft != null && pOpContext.m_pLeft.m_pValueType != null)
						{
							if (pOpContext.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL)
							{
								AddClassDeclReference(pOpContext.m_pLeft.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
								pBase = pOpContext.m_pLeft.m_pValueType.m_pClassDecl;
							}
							else
#line 108 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
								if (pOpContext.m_pLeft.m_pValueType.m_eType == ValueType.Type.ENUM_DECL)
								{
									pBase = pOpContext.m_pLeft.m_pValueType.m_pEnumDecl;
								}
								else
#line 112 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
									if (pOpContext.m_pLeft.m_pValueType.m_eType == ValueType.Type.NAMESPACE_NODE)
									{
										Vector<NamespaceDecl> pNamespaceDeclVector = pOpContext.m_pLeft.m_pValueType.m_pNamespaceNode.m_pNamespaceDeclVector;
										Vector<Symbol> pCandidates = new Vector<Symbol>();
										Vector<Symbol> pRelevant = new Vector<Symbol>();
										for (int i = 0; i < pNamespaceDeclVector.GetSize(); i++)
										{
											NamespaceDecl pNamespaceDecl = pNamespaceDeclVector.Get(i);
											pCandidates.Clear();
											pValidator.m_pResolver.ResolveFromNode(pNamespaceDecl, sName, pCandidates);
											pRelevant.Clear();
											for (int j = 0; j < pCandidates.GetSize(); j++)
											{
												Symbol pSym = pCandidates.Get(j);
												if (pSym.m_eKind == Symbol.Kind.CLASS || pSym.m_eKind == Symbol.Kind.ENUM || pSym.m_eKind == Symbol.Kind.VAR || pSym.m_eKind == Symbol.Kind.PARAM || pSym.m_eKind == Symbol.Kind.FUNCTION || pSym.m_eKind == Symbol.Kind.METHOD || pSym.m_eKind == Symbol.Kind.DELEGATE || pSym.m_eKind == Symbol.Kind.ENUM_VALUE || pSym.m_eKind == Symbol.Kind.NAMESPACE)
												{
#line 136 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
													pRelevant.PushBack(pSym);
												}
											}
											if (pRelevant.GetSize() == 1 && pRelevant.Get(0).m_pDeclAST != null)
											{
												pAST = pRelevant.Get(0).m_pDeclAST;
												break;
											}
											if (pRelevant.GetSize() > 1)
											{
												bResolverAmbiguous = true;
												break;
											}
										}
									}
									else
									{
										pValidator.AddError("Unexpected left of ::", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
										return;
									}
						}
				}
			}
#line 160 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
			if (pAST == null)
			{
				Vector<Symbol> pCandidates = new Vector<Symbol>();
				pValidator.m_pResolver.ResolveFromNode(pBase, sName, pCandidates);
#line 165 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
				Vector<Symbol> pRelevant = new Vector<Symbol>();
				for (int i = 0; i < pCandidates.GetSize(); i++)
				{
					Symbol pSym = pCandidates.Get(i);
					if (pSym.m_eKind == Symbol.Kind.CLASS || pSym.m_eKind == Symbol.Kind.ENUM || pSym.m_eKind == Symbol.Kind.VAR || pSym.m_eKind == Symbol.Kind.PARAM || pSym.m_eKind == Symbol.Kind.FUNCTION || pSym.m_eKind == Symbol.Kind.METHOD || pSym.m_eKind == Symbol.Kind.DELEGATE || pSym.m_eKind == Symbol.Kind.ENUM_VALUE || pSym.m_eKind == Symbol.Kind.NAMESPACE)
					{
#line 179 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
						pRelevant.PushBack(pSym);
					}
				}
#line 183 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
				if (pRelevant.GetSize() == 1)
				{
					Symbol pSymbol = pRelevant.Get(0);
					if (pSymbol.m_pDeclAST != null)
						pAST = pSymbol.m_pDeclAST;
				}
				else
#line 189 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
					if (pRelevant.GetSize() > 1)
						bResolverAmbiguous = true;
			}
#line 193 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
			if (pAST == null)
			{
				if (bResolverAmbiguous)
				{
					InternalString sAmbiguous = new InternalString("Ambiguous identifier (multiple declarations in scope): ");
					sAmbiguous.Append(sName);
					pValidator.AddError(sAmbiguous.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				}
				else
				{
					InternalString sTemp = new InternalString("Identifier Unbeknownst! ");
					sTemp.Append(sName);
					if (pContextParent != null)
						sTemp.Append(" has parent");
					sTemp.Append(" base: ");
					pBase.StringifyType(sTemp);
					pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				}
				return;
			}
#line 214 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
			if (pAST.m_eType == AST.Type.AST_CLASS_DECL)
			{
				m_pValueType = new ValueType(ValueType.Type.CLASS_DECL);
				m_pValueType.m_pClassDecl = (ClassDecl)(pAST);
#line 220 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
				AddClassDeclReference(m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
#line 223 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
				AST pCheckParent = m_pParent;
				AST pCurrent = this;
				for (int i = 0; i < 5; i++)
				{
					if (pCheckParent == null)
						break;
					if (pCheckParent.m_eType == AST.Type.AST_VAR_DECL)
					{
						VarDecl pVarDecl = (VarDecl)(pCheckParent);
#line 233 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
						bool bInArraySize = false;
						if (pVarDecl.m_pArraySizeVector != null)
						{
							for (int j = 0; j < pVarDecl.m_pArraySizeVector.GetSize(); j++)
							{
								if (pCurrent == pVarDecl.m_pArraySizeVector.Get(j))
								{
									bInArraySize = true;
									break;
								}
							}
						}
#line 247 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
						if (bInArraySize && pVarDecl.m_pParent != null && pVarDecl.m_pParent.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
							AddClassDeclReference(m_pValueType.m_pClassDecl, AST.OutputFile.HEADER, false);
#line 251 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
						if (pCurrent == pVarDecl.m_pAssignment && pVarDecl.m_pParent != null && pVarDecl.m_pParent.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
						{
							MemberVarDecl pMemberVarDecl = (MemberVarDecl)(pVarDecl.m_pParent);
							if (pMemberVarDecl.m_bStatic)
								AddClassDeclReference(m_pValueType.m_pClassDecl, AST.OutputFile.HEADER, false);
						}
#line 258 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
						break;
					}
#line 261 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
					pCurrent = pCheckParent;
					pCheckParent = pCheckParent.m_pParent;
				}
#line 265 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
				return;
			}
			else
#line 267 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
				if (pAST.m_eType == AST.Type.AST_MEMBER_CLASS_DECL)
				{
					MemberClassDecl pMemberClassDecl = (MemberClassDecl)(pAST);
					if (pMemberClassDecl.m_pClassDecl != null)
					{
						m_pValueType = new ValueType(ValueType.Type.CLASS_DECL);
						m_pValueType.m_pClassDecl = pMemberClassDecl.m_pClassDecl;
						AddClassDeclReference(m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
					}
					return;
				}
#line 279 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
			if (pAST.m_eType == AST.Type.AST_ENUM_DECL)
			{
				m_pValueType = new ValueType(ValueType.Type.ENUM_DECL);
				m_pValueType.m_pEnumDecl = (EnumDecl)(pAST);
				return;
			}
			else
#line 285 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
				if (pAST.m_eType == AST.Type.AST_MEMBER_ENUM_DECL)
				{
					MemberEnumDecl pMemberEnum = (MemberEnumDecl)(pAST);
					if (pMemberEnum.m_pEnumDecl != null)
					{
						m_pValueType = new ValueType(ValueType.Type.ENUM_DECL);
						m_pValueType.m_pEnumDecl = pMemberEnum.m_pEnumDecl;
						return;
					}
				}
#line 296 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
			if (pAST.m_eType == AST.Type.ENUM_DECL_VALUE)
			{
				m_pValueType = new ValueType(ValueType.Type.ENUM_DECL_VALUE);
				m_pValueType.m_pEnumDeclValue = (EnumDeclValue)(pAST);
				return;
			}
#line 303 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
			if (pAST.m_eType == AST.Type.AST_VAR_DECL)
			{
				VarDecl pVarDecl = (VarDecl)(pAST);
				m_pValueType = pVarDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
#line 308 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
				if (m_pValueType == null)
				{
					pValidator.AddError("Could not create ValueType for VarDecl", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
					return;
				}
#line 315 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
				if (m_pValueType.m_eType == ValueType.Type.GENERIC_TYPE_DECL_VALUE)
				{
					if (pParent != null)
					{
						if (pParent.GetOperatorType() == OperatorExpr.OperatorType.MEMBER_ACCESS && pParent.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
						{
							if (pParent.m_pLeft.m_pValueType.m_pGenericValueTypeVector != null)
							{
								if (pParent.m_pLeft.m_pValueType.m_pGenericValueTypeVector.GetSize() > 0)
								{
									ValueType pGenericValueType = pParent.m_pLeft.m_pValueType.m_pGenericValueTypeVector.Get(0);
									if (pGenericValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
									{
										ValueType pOldValueType;
										NumbatLogic.ValueType __865702733 = m_pValueType;
#line 329 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
										m_pValueType = null;
#line 329 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
										pOldValueType = __865702733;
										m_pValueType = pGenericValueType.Clone();
										m_pValueType.m_ePointerType = pOldValueType.m_ePointerType;
									}
								}
							}
						}
					}
				}
#line 340 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
				return;
			}
			else
#line 342 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
				if (pAST.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
				{
					MemberVarDecl pMemberVarDecl = (MemberVarDecl)(pAST);
					if (pMemberVarDecl.m_pVarDecl != null)
					{
						VarDecl pVarDecl = pMemberVarDecl.m_pVarDecl;
						m_pValueType = pVarDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
#line 350 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
						if (m_pValueType == null)
						{
							pValidator.AddError("Could not create ValueType for MemberVarDecl", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
							return;
						}
#line 357 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
						if (m_pValueType.m_eType == ValueType.Type.GENERIC_TYPE_DECL_VALUE)
						{
							if (pParent != null)
							{
								if (pParent.GetOperatorType() == OperatorExpr.OperatorType.MEMBER_ACCESS && pParent.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
								{
									if (pParent.m_pLeft.m_pValueType.m_pGenericValueTypeVector != null)
									{
										if (pParent.m_pLeft.m_pValueType.m_pGenericValueTypeVector.GetSize() > 0)
										{
											ValueType pGenericValueType = pParent.m_pLeft.m_pValueType.m_pGenericValueTypeVector.Get(0);
											if (pGenericValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
											{
												ValueType pOldValueType;
												NumbatLogic.ValueType __866030720 = m_pValueType;
#line 371 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
												m_pValueType = null;
#line 371 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
												pOldValueType = __866030720;
												m_pValueType = pGenericValueType.Clone();
												m_pValueType.m_ePointerType = pOldValueType.m_ePointerType;
											}
										}
									}
								}
							}
						}
#line 381 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
						return;
					}
				}
#line 385 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
			if (pAST.m_eType == AST.Type.AST_FUNCTION_DECL)
			{
				m_pValueType = new ValueType(ValueType.Type.FUNCTION_DECL);
				m_pValueType.m_pFunctionDecl = (FunctionDecl)(pAST);
				return;
			}
			else
#line 391 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
				if (pAST.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL)
				{
					MemberFunctionDecl pMFD = (MemberFunctionDecl)(pAST);
					if (pMFD.m_pFunctionDecl != null)
					{
						m_pValueType = new ValueType(ValueType.Type.FUNCTION_DECL);
						m_pValueType.m_pFunctionDecl = pMFD.m_pFunctionDecl;
						return;
					}
				}
#line 402 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
			if (pAST.m_eType == AST.Type.NAMESPACE_DECL)
			{
				m_pValueType = new ValueType(ValueType.Type.NAMESPACE_NODE);
				m_pValueType.m_pNamespaceNode = ((NamespaceDecl)(pAST)).m_pNamespaceNode;
				return;
			}
			{
#line 410 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
				InternalString sTemp = new InternalString("say what? ");
				pAST.StringifyType(sTemp);
				pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
			}
#line 415 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
			base.Validate(pValidator, pParent);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			m_pNameToken.Stringify(pOutputBuilder.m_sOut);
		}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/Identifier.nll"
		public Identifier()
		{
		}

	}
}

