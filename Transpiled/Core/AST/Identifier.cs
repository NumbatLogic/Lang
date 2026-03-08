#line 0 "../../../Source/Core/AST/Identifier.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/Identifier.nll"
	class Identifier : AST
	{
		public Token m_pNameToken;
		public static Identifier TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
			if (pToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			Identifier pIdentifier = new Identifier();
			pIdentifier.m_eType = AST.Type.AST_IDENTIFIER;
			pIdentifier.m_pNameToken = pToken;
			pIdentifier.m_pFirstToken = pToken;
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.Identifier __4180376026 = pIdentifier;
			pIdentifier = null;
			return __4180376026;
		}

		public override AST BaseClone()
		{
			Identifier pIdentifier = new Identifier();
			pIdentifier.m_eType = m_eType;
			pIdentifier.m_pNameToken = m_pNameToken;
			pIdentifier.m_pFirstToken = m_pFirstToken;
			NumbatLogic.Identifier __4180441624 = pIdentifier;
			pIdentifier = null;
			return __4180441624;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			string sName = m_pNameToken.GetString();
			AST pContextParent = (pParent != null) ? (AST)(pParent) : m_pParent;
			AST pAST = null;
			AST pBase = this;
			AST pChild = this;
			bool bResolverAmbiguous = false;
			if (pContextParent != null)
			{
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
									if (pOpWalk.m_pLeft.m_pValueType == null)
										pOpWalk.m_pLeft.Validate(pValidator, pOpWalk);
									if (pOpWalk.m_pLeft.m_pValueType != null)
									{
										if (pOpWalk.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL || pOpWalk.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
										{
											AddClassDeclReference(pOpWalk.m_pLeft.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
											pBase = pOpWalk.m_pLeft.m_pValueType.m_pClassDecl;
											pChild = null;
#line 81 "../../../Source/Core/AST/Identifier.nll"
											break;
										}
										else
											if (pOpWalk.m_pLeft.m_pValueType.m_eType == ValueType.Type.ENUM_DECL)
											{
												pBase = pOpWalk.m_pLeft.m_pValueType.m_pEnumDecl;
												pChild = null;
#line 87 "../../../Source/Core/AST/Identifier.nll"
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
						pChild = null;
					}
					else
						if (pOpContext.GetOperatorType() == OperatorExpr.OperatorType.SCOPE_RESOLUTION && pOpContext.m_pLeft != null && pOpContext.m_pLeft.m_pValueType != null)
						{
							if (pOpContext.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL)
							{
								AddClassDeclReference(pOpContext.m_pLeft.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
								pBase = pOpContext.m_pLeft.m_pValueType.m_pClassDecl;
								pChild = null;
							}
							else
								if (pOpContext.m_pLeft.m_pValueType.m_eType == ValueType.Type.ENUM_DECL)
								{
									pBase = pOpContext.m_pLeft.m_pValueType.m_pEnumDecl;
									pChild = null;
								}
								else
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
													pRelevant.PushBack(pSym);
												}
											}
											if (pRelevant.GetSize() == 1 && pRelevant.Get(0).m_pDeclAST != null)
											{
												pAST = pRelevant.Get(0).m_pDeclAST;
#line 148 "../../../Source/Core/AST/Identifier.nll"
												break;
											}
											if (pRelevant.GetSize() > 1)
											{
												bResolverAmbiguous = true;
#line 153 "../../../Source/Core/AST/Identifier.nll"
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
			if (pAST == null)
			{
				Vector<Symbol> pCandidates = new Vector<Symbol>();
				pValidator.m_pResolver.ResolveFromNode(pBase, sName, pCandidates);
				Vector<Symbol> pRelevant = new Vector<Symbol>();
				for (int i = 0; i < pCandidates.GetSize(); i++)
				{
					Symbol pSym = pCandidates.Get(i);
					if (pSym.m_eKind == Symbol.Kind.CLASS || pSym.m_eKind == Symbol.Kind.ENUM || pSym.m_eKind == Symbol.Kind.VAR || pSym.m_eKind == Symbol.Kind.PARAM || pSym.m_eKind == Symbol.Kind.FUNCTION || pSym.m_eKind == Symbol.Kind.METHOD || pSym.m_eKind == Symbol.Kind.DELEGATE || pSym.m_eKind == Symbol.Kind.ENUM_VALUE || pSym.m_eKind == Symbol.Kind.NAMESPACE)
					{
						pRelevant.PushBack(pSym);
					}
				}
				if (pRelevant.GetSize() == 1)
				{
					Symbol pSymbol = pRelevant.Get(0);
					if (pSymbol.m_pDeclAST != null)
						pAST = pSymbol.m_pDeclAST;
				}
				else
					if (pRelevant.GetSize() > 1)
						bResolverAmbiguous = true;
			}
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
			if (pAST.m_eType == AST.Type.AST_CLASS_DECL)
			{
				m_pValueType = new ValueType(ValueType.Type.CLASS_DECL);
				m_pValueType.m_pClassDecl = (ClassDecl)(pAST);
				AddClassDeclReference(m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
				AST pCheckParent = m_pParent;
				AST pCurrent = this;
				for (int i = 0; i < 5; i++)
				{
					if (pCheckParent == null)
#line 234 "../../../Source/Core/AST/Identifier.nll"
						break;
					if (pCheckParent.m_eType == AST.Type.AST_VAR_DECL)
					{
						VarDecl pVarDecl = (VarDecl)(pCheckParent);
						bool bInArraySize = false;
						if (pVarDecl.m_pArraySizeVector != null)
						{
							for (int j = 0; j < pVarDecl.m_pArraySizeVector.GetSize(); j++)
							{
								if (pCurrent == pVarDecl.m_pArraySizeVector.Get(j))
								{
									bInArraySize = true;
#line 247 "../../../Source/Core/AST/Identifier.nll"
									break;
								}
							}
						}
						if (bInArraySize && pVarDecl.m_pParent != null && pVarDecl.m_pParent.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
							AddClassDeclReference(m_pValueType.m_pClassDecl, AST.OutputFile.HEADER, false);
						if (pCurrent == pVarDecl.m_pAssignment && pVarDecl.m_pParent != null && pVarDecl.m_pParent.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
						{
							MemberVarDecl pMemberVarDecl = (MemberVarDecl)(pVarDecl.m_pParent);
							if (pMemberVarDecl.m_bStatic)
								AddClassDeclReference(m_pValueType.m_pClassDecl, AST.OutputFile.HEADER, false);
						}
#line 264 "../../../Source/Core/AST/Identifier.nll"
						break;
					}
					pCurrent = pCheckParent;
					pCheckParent = pCheckParent.m_pParent;
				}
				return;
			}
			else
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
			if (pAST.m_eType == AST.Type.AST_ENUM_DECL)
			{
				m_pValueType = new ValueType(ValueType.Type.ENUM_DECL);
				m_pValueType.m_pEnumDecl = (EnumDecl)(pAST);
				return;
			}
			else
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
			if (pAST.m_eType == AST.Type.ENUM_DECL_VALUE)
			{
				m_pValueType = new ValueType(ValueType.Type.ENUM_DECL_VALUE);
				m_pValueType.m_pEnumDeclValue = (EnumDeclValue)(pAST);
				return;
			}
			if (pAST.m_eType == AST.Type.AST_VAR_DECL)
			{
				VarDecl pVarDecl = (VarDecl)(pAST);
				m_pValueType = pVarDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
				if (m_pValueType == null)
				{
					pValidator.AddError("Could not create ValueType for VarDecl", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
					return;
				}
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
										NumbatLogic.ValueType __865768328 = m_pValueType;
										m_pValueType = null;
										pOldValueType = __865768328;
										m_pValueType = pGenericValueType.Clone();
										m_pValueType.m_ePointerType = pOldValueType.m_ePointerType;
									}
								}
							}
						}
					}
				}
				return;
			}
			else
				if (pAST.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
				{
					MemberVarDecl pMemberVarDecl = (MemberVarDecl)(pAST);
					if (pMemberVarDecl.m_pVarDecl != null)
					{
						VarDecl pVarDecl = pMemberVarDecl.m_pVarDecl;
						m_pValueType = pVarDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
						if (m_pValueType == null)
						{
							pValidator.AddError("Could not create ValueType for MemberVarDecl", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
							return;
						}
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
												NumbatLogic.ValueType __866030726 = m_pValueType;
												m_pValueType = null;
												pOldValueType = __866030726;
												m_pValueType = pGenericValueType.Clone();
												m_pValueType.m_ePointerType = pOldValueType.m_ePointerType;
											}
										}
									}
								}
							}
						}
						return;
					}
				}
			if (pAST.m_eType == AST.Type.AST_FUNCTION_DECL)
			{
				m_pValueType = new ValueType(ValueType.Type.FUNCTION_DECL);
				m_pValueType.m_pFunctionDecl = (FunctionDecl)(pAST);
				return;
			}
			else
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
			if (pAST.m_eType == AST.Type.NAMESPACE_DECL)
			{
				m_pValueType = new ValueType(ValueType.Type.NAMESPACE_NODE);
				m_pValueType.m_pNamespaceNode = ((NamespaceDecl)(pAST)).m_pNamespaceNode;
				return;
			}
			{
				InternalString sTemp = new InternalString("say what? ");
				pAST.StringifyType(sTemp);
				pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
			}
			base.Validate(pValidator, pParent);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder out)
		{
			m_pNameToken.Stringify(out.m_sOut);
		}

		public Identifier()
		{
		}

	}
}

