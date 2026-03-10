#line 1 "../../../Source/Core/AST/Identifier.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/Identifier.nll"
	class Identifier : AST
	{
#line 5 "../../../Source/Core/AST/Identifier.nll"
		public Token m_pNameToken;
#line 7 "../../../Source/Core/AST/Identifier.nll"
		public static Identifier TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 9 "../../../Source/Core/AST/Identifier.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 11 "../../../Source/Core/AST/Identifier.nll"
			Token pToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
#line 12 "../../../Source/Core/AST/Identifier.nll"
			if (pToken == null)
			{
#line 13 "../../../Source/Core/AST/Identifier.nll"
				return null;
			}
#line 14 "../../../Source/Core/AST/Identifier.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 16 "../../../Source/Core/AST/Identifier.nll"
			Identifier pIdentifier = new Identifier();
#line 17 "../../../Source/Core/AST/Identifier.nll"
			pIdentifier.m_eType = AST.Type.AST_IDENTIFIER;
#line 18 "../../../Source/Core/AST/Identifier.nll"
			pIdentifier.m_pNameToken = pToken;
#line 19 "../../../Source/Core/AST/Identifier.nll"
			pIdentifier.m_pFirstToken = pToken;
#line 21 "../../../Source/Core/AST/Identifier.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.Identifier __4180376026 = pIdentifier;
#line 23 "../../../Source/Core/AST/Identifier.nll"
			pIdentifier = null;
#line 23 "../../../Source/Core/AST/Identifier.nll"
			return __4180376026;
		}

#line 26 "../../../Source/Core/AST/Identifier.nll"
		public override AST BaseClone()
		{
#line 28 "../../../Source/Core/AST/Identifier.nll"
			Identifier pIdentifier = new Identifier();
#line 29 "../../../Source/Core/AST/Identifier.nll"
			pIdentifier.m_eType = m_eType;
#line 30 "../../../Source/Core/AST/Identifier.nll"
			pIdentifier.m_pNameToken = m_pNameToken;
#line 31 "../../../Source/Core/AST/Identifier.nll"
			pIdentifier.m_pFirstToken = m_pFirstToken;
			NumbatLogic.Identifier __4180441624 = pIdentifier;
#line 32 "../../../Source/Core/AST/Identifier.nll"
			pIdentifier = null;
#line 32 "../../../Source/Core/AST/Identifier.nll"
			return __4180441624;
		}

#line 35 "../../../Source/Core/AST/Identifier.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 37 "../../../Source/Core/AST/Identifier.nll"
			string sName = m_pNameToken.GetString();
#line 40 "../../../Source/Core/AST/Identifier.nll"
			AST pContextParent = (pParent != null) ? (AST)(pParent) : m_pParent;
#line 42 "../../../Source/Core/AST/Identifier.nll"
			AST pAST = null;
#line 43 "../../../Source/Core/AST/Identifier.nll"
			AST pBase = this;
#line 44 "../../../Source/Core/AST/Identifier.nll"
			bool bResolverAmbiguous = false;
#line 45 "../../../Source/Core/AST/Identifier.nll"
			if (pContextParent != null)
			{
#line 50 "../../../Source/Core/AST/Identifier.nll"
				if (pContextParent.m_eType == AST.Type.AST_ARRAY_LOOKUP)
				{
#line 52 "../../../Source/Core/AST/Identifier.nll"
					ArrayLookup pAL = (ArrayLookup)(pContextParent);
#line 53 "../../../Source/Core/AST/Identifier.nll"
					if (pAL.m_pExpression == this)
					{
#line 55 "../../../Source/Core/AST/Identifier.nll"
						AST pWalk = pAL.m_pParent;
#line 56 "../../../Source/Core/AST/Identifier.nll"
						while (pWalk != null && pBase == this)
						{
#line 58 "../../../Source/Core/AST/Identifier.nll"
							if (pWalk.m_eType == AST.Type.AST_OPERATOR_EXPR)
							{
#line 60 "../../../Source/Core/AST/Identifier.nll"
								OperatorExpr pOpWalk = (OperatorExpr)(pWalk);
#line 61 "../../../Source/Core/AST/Identifier.nll"
								bool bRightIsArrayLookupOrMulLeft = (pOpWalk.m_pRight == pAL);
#line 62 "../../../Source/Core/AST/Identifier.nll"
								if (!bRightIsArrayLookupOrMulLeft && pOpWalk.m_pRight != null && pOpWalk.m_pRight.m_eType == AST.Type.AST_OPERATOR_EXPR)
								{
#line 64 "../../../Source/Core/AST/Identifier.nll"
									OperatorExpr pRightOp = (OperatorExpr)(pOpWalk.m_pRight);
#line 65 "../../../Source/Core/AST/Identifier.nll"
									bRightIsArrayLookupOrMulLeft = (pRightOp.m_pLeft == pAL);
								}
#line 67 "../../../Source/Core/AST/Identifier.nll"
								if (pOpWalk.GetOperatorType() == OperatorExpr.OperatorType.SCOPE_RESOLUTION && pOpWalk.m_pLeft != null && bRightIsArrayLookupOrMulLeft)
								{
#line 70 "../../../Source/Core/AST/Identifier.nll"
									if (pOpWalk.m_pLeft.m_pValueType == null)
#line 71 "../../../Source/Core/AST/Identifier.nll"
										pOpWalk.m_pLeft.Validate(pValidator, pOpWalk);
#line 72 "../../../Source/Core/AST/Identifier.nll"
									if (pOpWalk.m_pLeft.m_pValueType != null)
									{
#line 74 "../../../Source/Core/AST/Identifier.nll"
										if (pOpWalk.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL || pOpWalk.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
										{
#line 77 "../../../Source/Core/AST/Identifier.nll"
											AddClassDeclReference(pOpWalk.m_pLeft.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
#line 78 "../../../Source/Core/AST/Identifier.nll"
											pBase = pOpWalk.m_pLeft.m_pValueType.m_pClassDecl;
#line 79 "../../../Source/Core/AST/Identifier.nll"
											break;
										}
										else
#line 81 "../../../Source/Core/AST/Identifier.nll"
											if (pOpWalk.m_pLeft.m_pValueType.m_eType == ValueType.Type.ENUM_DECL)
											{
#line 83 "../../../Source/Core/AST/Identifier.nll"
												pBase = pOpWalk.m_pLeft.m_pValueType.m_pEnumDecl;
#line 84 "../../../Source/Core/AST/Identifier.nll"
												break;
											}
									}
								}
							}
#line 89 "../../../Source/Core/AST/Identifier.nll"
							pWalk = pWalk.m_pParent;
						}
					}
				}
#line 93 "../../../Source/Core/AST/Identifier.nll"
				if (pContextParent.m_eType == AST.Type.AST_OPERATOR_EXPR)
				{
#line 95 "../../../Source/Core/AST/Identifier.nll"
					OperatorExpr pOpContext = (OperatorExpr)(pContextParent);
#line 96 "../../../Source/Core/AST/Identifier.nll"
					if (pOpContext.GetOperatorType() == OperatorExpr.OperatorType.MEMBER_ACCESS && pOpContext.m_pLeft != null && pOpContext.m_pLeft.m_pValueType != null && pOpContext.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
					{
#line 98 "../../../Source/Core/AST/Identifier.nll"
						AddClassDeclReference(pOpContext.m_pLeft.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
#line 99 "../../../Source/Core/AST/Identifier.nll"
						pBase = pOpContext.m_pLeft.m_pValueType.m_pClassDecl;
					}
					else
#line 101 "../../../Source/Core/AST/Identifier.nll"
						if (pOpContext.GetOperatorType() == OperatorExpr.OperatorType.SCOPE_RESOLUTION && pOpContext.m_pLeft != null && pOpContext.m_pLeft.m_pValueType != null)
						{
#line 103 "../../../Source/Core/AST/Identifier.nll"
							if (pOpContext.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL)
							{
#line 105 "../../../Source/Core/AST/Identifier.nll"
								AddClassDeclReference(pOpContext.m_pLeft.m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
#line 106 "../../../Source/Core/AST/Identifier.nll"
								pBase = pOpContext.m_pLeft.m_pValueType.m_pClassDecl;
							}
							else
#line 108 "../../../Source/Core/AST/Identifier.nll"
								if (pOpContext.m_pLeft.m_pValueType.m_eType == ValueType.Type.ENUM_DECL)
								{
#line 110 "../../../Source/Core/AST/Identifier.nll"
									pBase = pOpContext.m_pLeft.m_pValueType.m_pEnumDecl;
								}
								else
#line 112 "../../../Source/Core/AST/Identifier.nll"
									if (pOpContext.m_pLeft.m_pValueType.m_eType == ValueType.Type.NAMESPACE_NODE)
									{
#line 114 "../../../Source/Core/AST/Identifier.nll"
										Vector<NamespaceDecl> pNamespaceDeclVector = pOpContext.m_pLeft.m_pValueType.m_pNamespaceNode.m_pNamespaceDeclVector;
#line 115 "../../../Source/Core/AST/Identifier.nll"
										Vector<Symbol> pCandidates = new Vector<Symbol>();
#line 116 "../../../Source/Core/AST/Identifier.nll"
										Vector<Symbol> pRelevant = new Vector<Symbol>();
#line 117 "../../../Source/Core/AST/Identifier.nll"
										for (int i = 0; i < pNamespaceDeclVector.GetSize(); i++)
										{
#line 119 "../../../Source/Core/AST/Identifier.nll"
											NamespaceDecl pNamespaceDecl = pNamespaceDeclVector.Get(i);
#line 120 "../../../Source/Core/AST/Identifier.nll"
											pCandidates.Clear();
#line 121 "../../../Source/Core/AST/Identifier.nll"
											pValidator.m_pResolver.ResolveFromNode(pNamespaceDecl, sName, pCandidates);
#line 122 "../../../Source/Core/AST/Identifier.nll"
											pRelevant.Clear();
#line 123 "../../../Source/Core/AST/Identifier.nll"
											for (int j = 0; j < pCandidates.GetSize(); j++)
											{
#line 125 "../../../Source/Core/AST/Identifier.nll"
												Symbol pSym = pCandidates.Get(j);
#line 126 "../../../Source/Core/AST/Identifier.nll"
												if (pSym.m_eKind == Symbol.Kind.CLASS || pSym.m_eKind == Symbol.Kind.ENUM || pSym.m_eKind == Symbol.Kind.VAR || pSym.m_eKind == Symbol.Kind.PARAM || pSym.m_eKind == Symbol.Kind.FUNCTION || pSym.m_eKind == Symbol.Kind.METHOD || pSym.m_eKind == Symbol.Kind.DELEGATE || pSym.m_eKind == Symbol.Kind.ENUM_VALUE || pSym.m_eKind == Symbol.Kind.NAMESPACE)
												{
#line 136 "../../../Source/Core/AST/Identifier.nll"
													pRelevant.PushBack(pSym);
												}
											}
#line 139 "../../../Source/Core/AST/Identifier.nll"
											if (pRelevant.GetSize() == 1 && pRelevant.Get(0).m_pDeclAST != null)
											{
#line 141 "../../../Source/Core/AST/Identifier.nll"
												pAST = pRelevant.Get(0).m_pDeclAST;
#line 142 "../../../Source/Core/AST/Identifier.nll"
												break;
											}
#line 144 "../../../Source/Core/AST/Identifier.nll"
											if (pRelevant.GetSize() > 1)
											{
#line 146 "../../../Source/Core/AST/Identifier.nll"
												bResolverAmbiguous = true;
#line 147 "../../../Source/Core/AST/Identifier.nll"
												break;
											}
										}
									}
									else
									{
#line 153 "../../../Source/Core/AST/Identifier.nll"
										pValidator.AddError("Unexpected left of ::", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
#line 154 "../../../Source/Core/AST/Identifier.nll"
										return;
									}
						}
				}
			}
#line 160 "../../../Source/Core/AST/Identifier.nll"
			if (pAST == null)
			{
#line 162 "../../../Source/Core/AST/Identifier.nll"
				Vector<Symbol> pCandidates = new Vector<Symbol>();
#line 163 "../../../Source/Core/AST/Identifier.nll"
				pValidator.m_pResolver.ResolveFromNode(pBase, sName, pCandidates);
#line 165 "../../../Source/Core/AST/Identifier.nll"
				Vector<Symbol> pRelevant = new Vector<Symbol>();
#line 166 "../../../Source/Core/AST/Identifier.nll"
				for (int i = 0; i < pCandidates.GetSize(); i++)
				{
#line 168 "../../../Source/Core/AST/Identifier.nll"
					Symbol pSym = pCandidates.Get(i);
#line 169 "../../../Source/Core/AST/Identifier.nll"
					if (pSym.m_eKind == Symbol.Kind.CLASS || pSym.m_eKind == Symbol.Kind.ENUM || pSym.m_eKind == Symbol.Kind.VAR || pSym.m_eKind == Symbol.Kind.PARAM || pSym.m_eKind == Symbol.Kind.FUNCTION || pSym.m_eKind == Symbol.Kind.METHOD || pSym.m_eKind == Symbol.Kind.DELEGATE || pSym.m_eKind == Symbol.Kind.ENUM_VALUE || pSym.m_eKind == Symbol.Kind.NAMESPACE)
					{
#line 179 "../../../Source/Core/AST/Identifier.nll"
						pRelevant.PushBack(pSym);
					}
				}
#line 183 "../../../Source/Core/AST/Identifier.nll"
				if (pRelevant.GetSize() == 1)
				{
#line 185 "../../../Source/Core/AST/Identifier.nll"
					Symbol pSymbol = pRelevant.Get(0);
#line 186 "../../../Source/Core/AST/Identifier.nll"
					if (pSymbol.m_pDeclAST != null)
#line 187 "../../../Source/Core/AST/Identifier.nll"
						pAST = pSymbol.m_pDeclAST;
				}
				else
#line 189 "../../../Source/Core/AST/Identifier.nll"
					if (pRelevant.GetSize() > 1)
#line 190 "../../../Source/Core/AST/Identifier.nll"
						bResolverAmbiguous = true;
			}
#line 193 "../../../Source/Core/AST/Identifier.nll"
			if (pAST == null)
			{
#line 195 "../../../Source/Core/AST/Identifier.nll"
				if (bResolverAmbiguous)
				{
#line 197 "../../../Source/Core/AST/Identifier.nll"
					InternalString sAmbiguous = new InternalString("Ambiguous identifier (multiple declarations in scope): ");
#line 198 "../../../Source/Core/AST/Identifier.nll"
					sAmbiguous.Append(sName);
#line 199 "../../../Source/Core/AST/Identifier.nll"
					pValidator.AddError(sAmbiguous.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				}
				else
				{
#line 203 "../../../Source/Core/AST/Identifier.nll"
					InternalString sTemp = new InternalString("Identifier Unbeknownst! ");
#line 204 "../../../Source/Core/AST/Identifier.nll"
					sTemp.Append(sName);
#line 205 "../../../Source/Core/AST/Identifier.nll"
					if (pContextParent != null)
#line 206 "../../../Source/Core/AST/Identifier.nll"
						sTemp.Append(" has parent");
#line 207 "../../../Source/Core/AST/Identifier.nll"
					sTemp.Append(" base: ");
#line 208 "../../../Source/Core/AST/Identifier.nll"
					pBase.StringifyType(sTemp);
#line 209 "../../../Source/Core/AST/Identifier.nll"
					pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				}
#line 211 "../../../Source/Core/AST/Identifier.nll"
				return;
			}
#line 214 "../../../Source/Core/AST/Identifier.nll"
			if (pAST.m_eType == AST.Type.AST_CLASS_DECL)
			{
#line 216 "../../../Source/Core/AST/Identifier.nll"
				m_pValueType = new ValueType(ValueType.Type.CLASS_DECL);
#line 217 "../../../Source/Core/AST/Identifier.nll"
				m_pValueType.m_pClassDecl = (ClassDecl)(pAST);
#line 220 "../../../Source/Core/AST/Identifier.nll"
				AddClassDeclReference(m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
#line 223 "../../../Source/Core/AST/Identifier.nll"
				AST pCheckParent = m_pParent;
#line 224 "../../../Source/Core/AST/Identifier.nll"
				AST pCurrent = this;
#line 225 "../../../Source/Core/AST/Identifier.nll"
				for (int i = 0; i < 5; i++)
				{
#line 227 "../../../Source/Core/AST/Identifier.nll"
					if (pCheckParent == null)
#line 228 "../../../Source/Core/AST/Identifier.nll"
						break;
#line 229 "../../../Source/Core/AST/Identifier.nll"
					if (pCheckParent.m_eType == AST.Type.AST_VAR_DECL)
					{
#line 231 "../../../Source/Core/AST/Identifier.nll"
						VarDecl pVarDecl = (VarDecl)(pCheckParent);
#line 233 "../../../Source/Core/AST/Identifier.nll"
						bool bInArraySize = false;
#line 234 "../../../Source/Core/AST/Identifier.nll"
						if (pVarDecl.m_pArraySizeVector != null)
						{
#line 236 "../../../Source/Core/AST/Identifier.nll"
							for (int j = 0; j < pVarDecl.m_pArraySizeVector.GetSize(); j++)
							{
#line 238 "../../../Source/Core/AST/Identifier.nll"
								if (pCurrent == pVarDecl.m_pArraySizeVector.Get(j))
								{
#line 240 "../../../Source/Core/AST/Identifier.nll"
									bInArraySize = true;
#line 241 "../../../Source/Core/AST/Identifier.nll"
									break;
								}
							}
						}
#line 247 "../../../Source/Core/AST/Identifier.nll"
						if (bInArraySize && pVarDecl.m_pParent != null && pVarDecl.m_pParent.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
#line 248 "../../../Source/Core/AST/Identifier.nll"
							AddClassDeclReference(m_pValueType.m_pClassDecl, AST.OutputFile.HEADER, false);
#line 251 "../../../Source/Core/AST/Identifier.nll"
						if (pCurrent == pVarDecl.m_pAssignment && pVarDecl.m_pParent != null && pVarDecl.m_pParent.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
						{
#line 253 "../../../Source/Core/AST/Identifier.nll"
							MemberVarDecl pMemberVarDecl = (MemberVarDecl)(pVarDecl.m_pParent);
#line 254 "../../../Source/Core/AST/Identifier.nll"
							if (pMemberVarDecl.m_bStatic)
#line 255 "../../../Source/Core/AST/Identifier.nll"
								AddClassDeclReference(m_pValueType.m_pClassDecl, AST.OutputFile.HEADER, false);
						}
#line 258 "../../../Source/Core/AST/Identifier.nll"
						break;
					}
#line 261 "../../../Source/Core/AST/Identifier.nll"
					pCurrent = pCheckParent;
#line 262 "../../../Source/Core/AST/Identifier.nll"
					pCheckParent = pCheckParent.m_pParent;
				}
#line 265 "../../../Source/Core/AST/Identifier.nll"
				return;
			}
			else
#line 267 "../../../Source/Core/AST/Identifier.nll"
				if (pAST.m_eType == AST.Type.AST_MEMBER_CLASS_DECL)
				{
#line 269 "../../../Source/Core/AST/Identifier.nll"
					MemberClassDecl pMemberClassDecl = (MemberClassDecl)(pAST);
#line 270 "../../../Source/Core/AST/Identifier.nll"
					if (pMemberClassDecl.m_pClassDecl != null)
					{
#line 272 "../../../Source/Core/AST/Identifier.nll"
						m_pValueType = new ValueType(ValueType.Type.CLASS_DECL);
#line 273 "../../../Source/Core/AST/Identifier.nll"
						m_pValueType.m_pClassDecl = pMemberClassDecl.m_pClassDecl;
#line 274 "../../../Source/Core/AST/Identifier.nll"
						AddClassDeclReference(m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
					}
#line 276 "../../../Source/Core/AST/Identifier.nll"
					return;
				}
#line 279 "../../../Source/Core/AST/Identifier.nll"
			if (pAST.m_eType == AST.Type.AST_ENUM_DECL)
			{
#line 281 "../../../Source/Core/AST/Identifier.nll"
				m_pValueType = new ValueType(ValueType.Type.ENUM_DECL);
#line 282 "../../../Source/Core/AST/Identifier.nll"
				m_pValueType.m_pEnumDecl = (EnumDecl)(pAST);
#line 283 "../../../Source/Core/AST/Identifier.nll"
				return;
			}
			else
#line 285 "../../../Source/Core/AST/Identifier.nll"
				if (pAST.m_eType == AST.Type.AST_MEMBER_ENUM_DECL)
				{
#line 287 "../../../Source/Core/AST/Identifier.nll"
					MemberEnumDecl pMemberEnum = (MemberEnumDecl)(pAST);
#line 288 "../../../Source/Core/AST/Identifier.nll"
					if (pMemberEnum.m_pEnumDecl != null)
					{
#line 290 "../../../Source/Core/AST/Identifier.nll"
						m_pValueType = new ValueType(ValueType.Type.ENUM_DECL);
#line 291 "../../../Source/Core/AST/Identifier.nll"
						m_pValueType.m_pEnumDecl = pMemberEnum.m_pEnumDecl;
#line 292 "../../../Source/Core/AST/Identifier.nll"
						return;
					}
				}
#line 296 "../../../Source/Core/AST/Identifier.nll"
			if (pAST.m_eType == AST.Type.ENUM_DECL_VALUE)
			{
#line 298 "../../../Source/Core/AST/Identifier.nll"
				m_pValueType = new ValueType(ValueType.Type.ENUM_DECL_VALUE);
#line 299 "../../../Source/Core/AST/Identifier.nll"
				m_pValueType.m_pEnumDeclValue = (EnumDeclValue)(pAST);
#line 300 "../../../Source/Core/AST/Identifier.nll"
				return;
			}
#line 303 "../../../Source/Core/AST/Identifier.nll"
			if (pAST.m_eType == AST.Type.AST_VAR_DECL)
			{
#line 305 "../../../Source/Core/AST/Identifier.nll"
				VarDecl pVarDecl = (VarDecl)(pAST);
#line 306 "../../../Source/Core/AST/Identifier.nll"
				m_pValueType = pVarDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
#line 308 "../../../Source/Core/AST/Identifier.nll"
				if (m_pValueType == null)
				{
#line 310 "../../../Source/Core/AST/Identifier.nll"
					pValidator.AddError("Could not create ValueType for VarDecl", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
#line 311 "../../../Source/Core/AST/Identifier.nll"
					return;
				}
#line 315 "../../../Source/Core/AST/Identifier.nll"
				if (m_pValueType.m_eType == ValueType.Type.GENERIC_TYPE_DECL_VALUE)
				{
#line 317 "../../../Source/Core/AST/Identifier.nll"
					if (pParent != null)
					{
#line 319 "../../../Source/Core/AST/Identifier.nll"
						if (pParent.GetOperatorType() == OperatorExpr.OperatorType.MEMBER_ACCESS && pParent.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
						{
#line 321 "../../../Source/Core/AST/Identifier.nll"
							if (pParent.m_pLeft.m_pValueType.m_pGenericValueTypeVector != null)
							{
#line 323 "../../../Source/Core/AST/Identifier.nll"
								if (pParent.m_pLeft.m_pValueType.m_pGenericValueTypeVector.GetSize() > 0)
								{
#line 325 "../../../Source/Core/AST/Identifier.nll"
									ValueType pGenericValueType = pParent.m_pLeft.m_pValueType.m_pGenericValueTypeVector.Get(0);
#line 326 "../../../Source/Core/AST/Identifier.nll"
									if (pGenericValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
									{
#line 328 "../../../Source/Core/AST/Identifier.nll"
										ValueType pOldValueType;
										NumbatLogic.ValueType __865702733 = m_pValueType;
#line 329 "../../../Source/Core/AST/Identifier.nll"
										m_pValueType = null;
#line 329 "../../../Source/Core/AST/Identifier.nll"
										pOldValueType = __865702733;
#line 330 "../../../Source/Core/AST/Identifier.nll"
										m_pValueType = pGenericValueType.Clone();
#line 331 "../../../Source/Core/AST/Identifier.nll"
										m_pValueType.m_ePointerType = pOldValueType.m_ePointerType;
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
				if (pAST.m_eType == AST.Type.AST_MEMBER_VAR_DECL)
				{
#line 344 "../../../Source/Core/AST/Identifier.nll"
					MemberVarDecl pMemberVarDecl = (MemberVarDecl)(pAST);
#line 345 "../../../Source/Core/AST/Identifier.nll"
					if (pMemberVarDecl.m_pVarDecl != null)
					{
#line 347 "../../../Source/Core/AST/Identifier.nll"
						VarDecl pVarDecl = pMemberVarDecl.m_pVarDecl;
#line 348 "../../../Source/Core/AST/Identifier.nll"
						m_pValueType = pVarDecl.m_pTypeRef.CreateValueType(pValidator.m_pResolver);
#line 350 "../../../Source/Core/AST/Identifier.nll"
						if (m_pValueType == null)
						{
#line 352 "../../../Source/Core/AST/Identifier.nll"
							pValidator.AddError("Could not create ValueType for MemberVarDecl", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
#line 353 "../../../Source/Core/AST/Identifier.nll"
							return;
						}
#line 357 "../../../Source/Core/AST/Identifier.nll"
						if (m_pValueType.m_eType == ValueType.Type.GENERIC_TYPE_DECL_VALUE)
						{
#line 359 "../../../Source/Core/AST/Identifier.nll"
							if (pParent != null)
							{
#line 361 "../../../Source/Core/AST/Identifier.nll"
								if (pParent.GetOperatorType() == OperatorExpr.OperatorType.MEMBER_ACCESS && pParent.m_pLeft.m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
								{
#line 363 "../../../Source/Core/AST/Identifier.nll"
									if (pParent.m_pLeft.m_pValueType.m_pGenericValueTypeVector != null)
									{
#line 365 "../../../Source/Core/AST/Identifier.nll"
										if (pParent.m_pLeft.m_pValueType.m_pGenericValueTypeVector.GetSize() > 0)
										{
#line 367 "../../../Source/Core/AST/Identifier.nll"
											ValueType pGenericValueType = pParent.m_pLeft.m_pValueType.m_pGenericValueTypeVector.Get(0);
#line 368 "../../../Source/Core/AST/Identifier.nll"
											if (pGenericValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
											{
#line 370 "../../../Source/Core/AST/Identifier.nll"
												ValueType pOldValueType;
												NumbatLogic.ValueType __866030720 = m_pValueType;
#line 371 "../../../Source/Core/AST/Identifier.nll"
												m_pValueType = null;
#line 371 "../../../Source/Core/AST/Identifier.nll"
												pOldValueType = __866030720;
#line 372 "../../../Source/Core/AST/Identifier.nll"
												m_pValueType = pGenericValueType.Clone();
#line 373 "../../../Source/Core/AST/Identifier.nll"
												m_pValueType.m_ePointerType = pOldValueType.m_ePointerType;
											}
										}
									}
								}
							}
						}
#line 381 "../../../Source/Core/AST/Identifier.nll"
						return;
					}
				}
#line 385 "../../../Source/Core/AST/Identifier.nll"
			if (pAST.m_eType == AST.Type.AST_FUNCTION_DECL)
			{
#line 387 "../../../Source/Core/AST/Identifier.nll"
				m_pValueType = new ValueType(ValueType.Type.FUNCTION_DECL);
#line 388 "../../../Source/Core/AST/Identifier.nll"
				m_pValueType.m_pFunctionDecl = (FunctionDecl)(pAST);
#line 389 "../../../Source/Core/AST/Identifier.nll"
				return;
			}
			else
#line 391 "../../../Source/Core/AST/Identifier.nll"
				if (pAST.m_eType == AST.Type.AST_MEMBER_FUNCTION_DECL)
				{
#line 393 "../../../Source/Core/AST/Identifier.nll"
					MemberFunctionDecl pMFD = (MemberFunctionDecl)(pAST);
#line 394 "../../../Source/Core/AST/Identifier.nll"
					if (pMFD.m_pFunctionDecl != null)
					{
#line 396 "../../../Source/Core/AST/Identifier.nll"
						m_pValueType = new ValueType(ValueType.Type.FUNCTION_DECL);
#line 397 "../../../Source/Core/AST/Identifier.nll"
						m_pValueType.m_pFunctionDecl = pMFD.m_pFunctionDecl;
#line 398 "../../../Source/Core/AST/Identifier.nll"
						return;
					}
				}
#line 402 "../../../Source/Core/AST/Identifier.nll"
			if (pAST.m_eType == AST.Type.NAMESPACE_DECL)
			{
#line 404 "../../../Source/Core/AST/Identifier.nll"
				m_pValueType = new ValueType(ValueType.Type.NAMESPACE_NODE);
#line 405 "../../../Source/Core/AST/Identifier.nll"
				m_pValueType.m_pNamespaceNode = ((NamespaceDecl)(pAST)).m_pNamespaceNode;
#line 406 "../../../Source/Core/AST/Identifier.nll"
				return;
			}
			{
#line 410 "../../../Source/Core/AST/Identifier.nll"
				InternalString sTemp = new InternalString("say what? ");
#line 411 "../../../Source/Core/AST/Identifier.nll"
				pAST.StringifyType(sTemp);
#line 412 "../../../Source/Core/AST/Identifier.nll"
				pValidator.AddError(sTemp.GetExternalString(), m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
			}
#line 415 "../../../Source/Core/AST/Identifier.nll"
			base.Validate(pValidator, pParent);
		}

#line 418 "../../../Source/Core/AST/Identifier.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 420 "../../../Source/Core/AST/Identifier.nll"
			m_pNameToken.Stringify(pOutputBuilder.m_sOut);
		}

#line 3 "../../../Source/Core/AST/Identifier.nll"
		public Identifier()
		{
		}

	}
}

