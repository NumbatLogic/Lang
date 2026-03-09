#line 1 "../../../Source/Core/AST/VarDecl.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/VarDecl.nll"
	class VarDecl : AST
	{
#line 6 "../../../Source/Core/AST/VarDecl.nll"
		public TypeRef m_pTypeRef;
#line 7 "../../../Source/Core/AST/VarDecl.nll"
		public Token m_pNameToken;
#line 8 "../../../Source/Core/AST/VarDecl.nll"
		public AST m_pAssignment;
#line 9 "../../../Source/Core/AST/VarDecl.nll"
		public bool m_bInline;
#line 11 "../../../Source/Core/AST/VarDecl.nll"
		public Vector<AST> m_pArraySizeVector;
#line 13 "../../../Source/Core/AST/VarDecl.nll"
		public Token m_pOwnedNameToken;
#line 15 "../../../Source/Core/AST/VarDecl.nll"
		public VarDecl()
		{
#line 17 "../../../Source/Core/AST/VarDecl.nll"
			m_bInline = false;
#line 18 "../../../Source/Core/AST/VarDecl.nll"
			m_eType = AST.Type.AST_VAR_DECL;
		}

#line 21 "../../../Source/Core/AST/VarDecl.nll"
		public static VarDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, bool bInline)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			TypeRef pTypeRef = TypeRef.TryCreate(pTokenContainer, pTempOffset);
#line 26 "../../../Source/Core/AST/VarDecl.nll"
			if (pTypeRef == null)
			{
#line 27 "../../../Source/Core/AST/VarDecl.nll"
				return null;
			}
			Token pNameToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
#line 30 "../../../Source/Core/AST/VarDecl.nll"
			if (pNameToken == null)
			{
#line 31 "../../../Source/Core/AST/VarDecl.nll"
				return null;
			}
#line 32 "../../../Source/Core/AST/VarDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			VarDecl pVarDecl = new VarDecl();
			Token pSquareBracketLeftToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_LEFT);
#line 37 "../../../Source/Core/AST/VarDecl.nll"
			while (pSquareBracketLeftToken != null)
			{
#line 39 "../../../Source/Core/AST/VarDecl.nll"
				if (pVarDecl.m_pArraySizeVector == null)
#line 40 "../../../Source/Core/AST/VarDecl.nll"
					pVarDecl.m_pArraySizeVector = new Vector<AST>();
#line 42 "../../../Source/Core/AST/VarDecl.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				AST pArraySize = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 45 "../../../Source/Core/AST/VarDecl.nll"
				if (pArraySize == null)
				{
#line 47 "../../../Source/Core/AST/VarDecl.nll"
					Console.Log("unable to parse array size...");
#line 48 "../../../Source/Core/AST/VarDecl.nll"
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 49 "../../../Source/Core/AST/VarDecl.nll"
					Assert.Plz(false);
#line 50 "../../../Source/Core/AST/VarDecl.nll"
					return null;
				}
				Token pSquareBracketRightToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_RIGHT);
#line 54 "../../../Source/Core/AST/VarDecl.nll"
				if (pSquareBracketRightToken == null)
				{
#line 56 "../../../Source/Core/AST/VarDecl.nll"
					Console.Log("unable to parse closing square bracket");
#line 57 "../../../Source/Core/AST/VarDecl.nll"
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 58 "../../../Source/Core/AST/VarDecl.nll"
					Assert.Plz(false);
#line 59 "../../../Source/Core/AST/VarDecl.nll"
					return null;
				}
#line 62 "../../../Source/Core/AST/VarDecl.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 64 "../../../Source/Core/AST/VarDecl.nll"
				pVarDecl.m_pArraySizeVector.PushBack(pArraySize);
				NumbatLogic.AST __830257000 = pArraySize;
#line 65 "../../../Source/Core/AST/VarDecl.nll"
				pArraySize = null;
#line 65 "../../../Source/Core/AST/VarDecl.nll"
				pVarDecl.AddChild(__830257000);
#line 67 "../../../Source/Core/AST/VarDecl.nll"
				pSquareBracketLeftToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_LEFT);
			}
			AST pAssignment = null;
			Token pEqualsToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_EQUALS);
#line 72 "../../../Source/Core/AST/VarDecl.nll"
			if (pEqualsToken != null)
			{
#line 74 "../../../Source/Core/AST/VarDecl.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 76 "../../../Source/Core/AST/VarDecl.nll"
				pAssignment = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 78 "../../../Source/Core/AST/VarDecl.nll"
				if (pAssignment == null)
				{
#line 80 "../../../Source/Core/AST/VarDecl.nll"
					Console.Log("expected to parse assignment...");
#line 81 "../../../Source/Core/AST/VarDecl.nll"
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 82 "../../../Source/Core/AST/VarDecl.nll"
					Assert.Plz(false);
#line 83 "../../../Source/Core/AST/VarDecl.nll"
					return null;
				}
			}
#line 87 "../../../Source/Core/AST/VarDecl.nll"
			if (!bInline)
			{
#line 89 "../../../Source/Core/AST/VarDecl.nll"
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
				{
#line 90 "../../../Source/Core/AST/VarDecl.nll"
					return null;
				}
#line 91 "../../../Source/Core/AST/VarDecl.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			}
#line 95 "../../../Source/Core/AST/VarDecl.nll"
			pVarDecl.m_bStatement = bInline == false;
#line 96 "../../../Source/Core/AST/VarDecl.nll"
			pVarDecl.m_pFirstToken = pTypeRef.m_pFirstToken;
#line 97 "../../../Source/Core/AST/VarDecl.nll"
			pVarDecl.m_pTypeRef = pTypeRef;
#line 98 "../../../Source/Core/AST/VarDecl.nll"
			pVarDecl.m_pNameToken = pNameToken;
#line 99 "../../../Source/Core/AST/VarDecl.nll"
			pVarDecl.m_pAssignment = pAssignment;
#line 100 "../../../Source/Core/AST/VarDecl.nll"
			pVarDecl.m_bInline = bInline;
			NumbatLogic.TypeRef __967516521 = pTypeRef;
#line 102 "../../../Source/Core/AST/VarDecl.nll"
			pTypeRef = null;
#line 102 "../../../Source/Core/AST/VarDecl.nll"
			pVarDecl.AddChild(__967516521);
#line 103 "../../../Source/Core/AST/VarDecl.nll"
			if (pAssignment != null)
			{
				NumbatLogic.AST __183753559 = pAssignment;
#line 104 "../../../Source/Core/AST/VarDecl.nll"
				pAssignment = null;
#line 104 "../../../Source/Core/AST/VarDecl.nll"
				pVarDecl.AddChild(__183753559);
			}
#line 106 "../../../Source/Core/AST/VarDecl.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.VarDecl __2971982038 = pVarDecl;
#line 107 "../../../Source/Core/AST/VarDecl.nll"
			pVarDecl = null;
#line 107 "../../../Source/Core/AST/VarDecl.nll"
			return __2971982038;
		}

#line 110 "../../../Source/Core/AST/VarDecl.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 112 "../../../Source/Core/AST/VarDecl.nll"
			base.Validate(pValidator, pParent);
#line 114 "../../../Source/Core/AST/VarDecl.nll"
			if (m_pParent.m_eType != AST.Type.AST_MEMBER_VAR_DECL && m_pParent.m_eType != AST.Type.AST_PARAM_DECL)
#line 115 "../../../Source/Core/AST/VarDecl.nll"
				pValidator.AddVarDecl(this);
			ValueType pValueType = m_pTypeRef.CreateValueType(pValidator.m_pResolver);
#line 118 "../../../Source/Core/AST/VarDecl.nll"
			if (pValueType == null)
			{
#line 120 "../../../Source/Core/AST/VarDecl.nll"
				pValidator.AddError("Unknown ValueType for TypeRef", m_pTypeRef.m_pFirstToken.m_sFileName, m_pTypeRef.m_pFirstToken.m_nLine, m_pTypeRef.m_pFirstToken.m_nColumn);
#line 121 "../../../Source/Core/AST/VarDecl.nll"
				return;
			}
#line 124 "../../../Source/Core/AST/VarDecl.nll"
			if (m_pAssignment != null)
			{
#line 126 "../../../Source/Core/AST/VarDecl.nll"
				if (m_pAssignment.m_pValueType == null)
				{
#line 128 "../../../Source/Core/AST/VarDecl.nll"
					pValidator.AddError("Unknown assignment?", m_pAssignment.m_pFirstToken.m_sFileName, m_pAssignment.m_pFirstToken.m_nLine, m_pAssignment.m_pFirstToken.m_nColumn);
#line 129 "../../../Source/Core/AST/VarDecl.nll"
					return;
				}
#line 132 "../../../Source/Core/AST/VarDecl.nll"
				if (m_pArraySizeVector != null && m_pAssignment.m_pValueType.m_eType != ValueType.Type.STATIC_ARRAY || m_pArraySizeVector == null && m_pAssignment.m_pValueType.m_eType == ValueType.Type.STATIC_ARRAY)
				{
#line 135 "../../../Source/Core/AST/VarDecl.nll"
					pValidator.AddError("Can only assign a static array to a vardecl with array size", m_pAssignment.m_pFirstToken.m_sFileName, m_pAssignment.m_pFirstToken.m_nLine, m_pAssignment.m_pFirstToken.m_nColumn);
#line 136 "../../../Source/Core/AST/VarDecl.nll"
					return;
				}
#line 139 "../../../Source/Core/AST/VarDecl.nll"
				if (!m_pAssignment.m_pValueType.ValidateAssignable(pValueType, pValidator, m_pAssignment.m_pFirstToken))
				{
#line 140 "../../../Source/Core/AST/VarDecl.nll"
					return;
				}
#line 142 "../../../Source/Core/AST/VarDecl.nll"
				if (pValueType.m_ePointerType != TypeRef.PointerType.OWNED && m_pAssignment.m_pValueType.m_ePointerType == TypeRef.PointerType.OWNED_PREASSSIGN)
				{
#line 144 "../../../Source/Core/AST/VarDecl.nll"
					pValidator.AddError("Can't assign an owned pointer to a non-owned variable", m_pAssignment.m_pFirstToken.m_sFileName, m_pAssignment.m_pFirstToken.m_nLine, m_pAssignment.m_pFirstToken.m_nColumn);
#line 145 "../../../Source/Core/AST/VarDecl.nll"
					return;
				}
#line 148 "../../../Source/Core/AST/VarDecl.nll"
				if (pValueType.m_ePointerType == TypeRef.PointerType.OWNED && (m_pAssignment.m_pValueType.m_ePointerType != TypeRef.PointerType.OWNED_PREASSSIGN && m_pAssignment.m_pValueType.m_eType != ValueType.Type.NULL_VALUE))
				{
#line 150 "../../../Source/Core/AST/VarDecl.nll"
					pValidator.AddError("Expected right side of = to be OWNED_PREASSSIGN (result of own)", m_pAssignment.m_pFirstToken.m_sFileName, m_pAssignment.m_pFirstToken.m_nLine, m_pAssignment.m_pFirstToken.m_nColumn);
#line 151 "../../../Source/Core/AST/VarDecl.nll"
					return;
				}
				else
#line 153 "../../../Source/Core/AST/VarDecl.nll"
					if (m_pAssignment.m_pValueType.m_ePointerType == TypeRef.PointerType.TRANSITON)
					{
#line 155 "../../../Source/Core/AST/VarDecl.nll"
						pValidator.AddError("Cannot store a TRANSITION pointer (need to `own` it)", m_pAssignment.m_pFirstToken.m_sFileName, m_pAssignment.m_pFirstToken.m_nLine, m_pAssignment.m_pFirstToken.m_nColumn);
#line 156 "../../../Source/Core/AST/VarDecl.nll"
						return;
					}
			}
		}

#line 163 "../../../Source/Core/AST/VarDecl.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 165 "../../../Source/Core/AST/VarDecl.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 168 "../../../Source/Core/AST/VarDecl.nll"
			if (eLanguage == AST.Language.CS)
			{
#line 170 "../../../Source/Core/AST/VarDecl.nll"
				if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_PARAM_DECL)
				{
					bool bBefore = m_pTypeRef.m_bConst;
#line 173 "../../../Source/Core/AST/VarDecl.nll"
					m_pTypeRef.m_bConst = false;
#line 174 "../../../Source/Core/AST/VarDecl.nll"
					m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 175 "../../../Source/Core/AST/VarDecl.nll"
					m_pTypeRef.m_bConst = bBefore;
				}
				else
				{
					bool bBefore = m_pTypeRef.m_bConst;
#line 180 "../../../Source/Core/AST/VarDecl.nll"
					if (m_pArraySizeVector != null && bBefore)
					{
#line 182 "../../../Source/Core/AST/VarDecl.nll"
						m_pTypeRef.m_bConst = false;
#line 183 "../../../Source/Core/AST/VarDecl.nll"
						pOutputBuilder.m_sOut.Append("readonly ");
					}
#line 185 "../../../Source/Core/AST/VarDecl.nll"
					m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 186 "../../../Source/Core/AST/VarDecl.nll"
					m_pTypeRef.m_bConst = bBefore;
				}
#line 189 "../../../Source/Core/AST/VarDecl.nll"
				if (m_pArraySizeVector != null)
				{
#line 191 "../../../Source/Core/AST/VarDecl.nll"
					pOutputBuilder.m_sOut.AppendChar('[');
#line 194 "../../../Source/Core/AST/VarDecl.nll"
					pOutputBuilder.m_sOut.AppendChar(']');
				}
			}
			else
			{
#line 199 "../../../Source/Core/AST/VarDecl.nll"
				m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
#line 201 "../../../Source/Core/AST/VarDecl.nll"
			pOutputBuilder.m_sOut.AppendChar(' ');
#line 204 "../../../Source/Core/AST/VarDecl.nll"
			if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_MEMBER_VAR_DECL && eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
			{
				AST pParentParent = m_pParent.m_pParent;
#line 207 "../../../Source/Core/AST/VarDecl.nll"
				if (pParentParent == null || pParentParent.m_eType != AST.Type.AST_CLASS_DECL)
				{
#line 209 "../../../Source/Core/AST/VarDecl.nll"
					Assert.Plz(false);
				}
				ClassDecl pClassDecl = (ClassDecl)(pParentParent);
#line 213 "../../../Source/Core/AST/VarDecl.nll"
				pOutputBuilder.m_sOut.AppendString(pClassDecl.m_pNameToken.GetString());
#line 214 "../../../Source/Core/AST/VarDecl.nll"
				pOutputBuilder.m_sOut.AppendString("::");
			}
#line 217 "../../../Source/Core/AST/VarDecl.nll"
			pOutputBuilder.m_sOut.AppendString(m_pNameToken.GetString());
#line 219 "../../../Source/Core/AST/VarDecl.nll"
			if (m_pArraySizeVector != null && eLanguage != AST.Language.CS)
			{
#line 221 "../../../Source/Core/AST/VarDecl.nll"
				for (int i = 0; i < m_pArraySizeVector.GetSize(); i++)
				{
					AST pArraySize = m_pArraySizeVector.Get(i);
#line 224 "../../../Source/Core/AST/VarDecl.nll"
					pOutputBuilder.m_sOut.AppendChar('[');
#line 225 "../../../Source/Core/AST/VarDecl.nll"
					pArraySize.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 226 "../../../Source/Core/AST/VarDecl.nll"
					pOutputBuilder.m_sOut.AppendChar(']');
				}
			}
			MemberVarDecl pMemberVarDecl = (m_pParent != null && m_pParent.m_eType == AST.Type.AST_MEMBER_VAR_DECL) ? (MemberVarDecl)(m_pParent) : null;
			bool bStatic = pMemberVarDecl != null && pMemberVarDecl.m_bStatic;
#line 233 "../../../Source/Core/AST/VarDecl.nll"
			if (m_pAssignment != null)
			{
				bool bArrayAssignment = m_pArraySizeVector != null;
				bool bDoIt = true;
#line 239 "../../../Source/Core/AST/VarDecl.nll"
				if (eLanguage == AST.Language.CPP)
				{
#line 241 "../../../Source/Core/AST/VarDecl.nll"
					if (pMemberVarDecl != null)
					{
#line 243 "../../../Source/Core/AST/VarDecl.nll"
						if (eOutputFile == AST.OutputFile.HEADER)
						{
#line 246 "../../../Source/Core/AST/VarDecl.nll"
							if (!(bStatic && m_pTypeRef.m_bConst && m_pTypeRef.IsIntegral() && !bArrayAssignment))
#line 247 "../../../Source/Core/AST/VarDecl.nll"
								bDoIt = false;
						}
						else
						{
#line 251 "../../../Source/Core/AST/VarDecl.nll"
							if (bStatic && m_pTypeRef.m_bConst && m_pTypeRef.IsIntegral() && !bArrayAssignment)
#line 252 "../../../Source/Core/AST/VarDecl.nll"
								bDoIt = false;
						}
					}
					else
					{
#line 258 "../../../Source/Core/AST/VarDecl.nll"
						if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_PARAM_DECL && eOutputFile == AST.OutputFile.SOURCE)
#line 259 "../../../Source/Core/AST/VarDecl.nll"
							bDoIt = false;
					}
				}
#line 263 "../../../Source/Core/AST/VarDecl.nll"
				if (bDoIt)
				{
#line 265 "../../../Source/Core/AST/VarDecl.nll"
					pOutputBuilder.m_sOut.AppendString(" = ");
#line 266 "../../../Source/Core/AST/VarDecl.nll"
					m_pAssignment.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				}
			}
			else
			{
#line 271 "../../../Source/Core/AST/VarDecl.nll"
				if (!m_bInline)
				{
					string sxToAppend = null;
#line 274 "../../../Source/Core/AST/VarDecl.nll"
					if (eOutputFile == AST.OutputFile.SOURCE && eLanguage != AST.Language.NLL && eLanguage != AST.Language.NLL_DEF)
					{
#line 276 "../../../Source/Core/AST/VarDecl.nll"
						if (m_pParent.m_eType != AST.Type.AST_MEMBER_VAR_DECL)
						{
#line 278 "../../../Source/Core/AST/VarDecl.nll"
							if (m_pArraySizeVector == null)
							{
#line 280 "../../../Source/Core/AST/VarDecl.nll"
								if (m_pTypeRef.IsInt())
#line 281 "../../../Source/Core/AST/VarDecl.nll"
									sxToAppend = " = 0";
								else
#line 282 "../../../Source/Core/AST/VarDecl.nll"
									if (m_pTypeRef.IsBool())
#line 283 "../../../Source/Core/AST/VarDecl.nll"
										sxToAppend = " = false";
									else
#line 284 "../../../Source/Core/AST/VarDecl.nll"
										if (m_pTypeRef.IsFloat())
#line 285 "../../../Source/Core/AST/VarDecl.nll"
											sxToAppend = " = 0.0f";
										else
#line 286 "../../../Source/Core/AST/VarDecl.nll"
											if (m_pTypeRef.IsDouble())
#line 287 "../../../Source/Core/AST/VarDecl.nll"
												sxToAppend = " = 0.0";
							}
						}
					}
#line 292 "../../../Source/Core/AST/VarDecl.nll"
					if (sxToAppend != null)
					{
#line 294 "../../../Source/Core/AST/VarDecl.nll"
						pOutputBuilder.m_sOut.AppendString(sxToAppend);
					}
					else
					{
#line 298 "../../../Source/Core/AST/VarDecl.nll"
						if (eLanguage == AST.Language.CPP)
						{
#line 300 "../../../Source/Core/AST/VarDecl.nll"
							if (eOutputFile == AST.OutputFile.SOURCE)
							{
								Project pProject = GetProject();
								ValueType pValueType = m_pTypeRef.CreateValueType(pProject.m_pValidator.m_pResolver);
#line 305 "../../../Source/Core/AST/VarDecl.nll"
								if (pValueType != null && pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE && m_pArraySizeVector == null)
#line 306 "../../../Source/Core/AST/VarDecl.nll"
									pOutputBuilder.m_sOut.AppendString(" = 0");
#line 308 "../../../Source/Core/AST/VarDecl.nll"
								if (bStatic && m_pTypeRef.IsIntegral())
#line 309 "../../../Source/Core/AST/VarDecl.nll"
									pOutputBuilder.m_sOut.AppendString(" = 0");
							}
						}
#line 313 "../../../Source/Core/AST/VarDecl.nll"
						if (eLanguage == AST.Language.CS && m_pArraySizeVector != null)
						{
#line 315 "../../../Source/Core/AST/VarDecl.nll"
							pOutputBuilder.m_sOut.AppendString(" = new ");
#line 316 "../../../Source/Core/AST/VarDecl.nll"
							m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 318 "../../../Source/Core/AST/VarDecl.nll"
							for (int i = 0; i < m_pArraySizeVector.GetSize(); i++)
							{
								AST pArraySize = m_pArraySizeVector.Get(i);
#line 321 "../../../Source/Core/AST/VarDecl.nll"
								pOutputBuilder.m_sOut.AppendChar('[');
#line 322 "../../../Source/Core/AST/VarDecl.nll"
								pArraySize.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 323 "../../../Source/Core/AST/VarDecl.nll"
								pOutputBuilder.m_sOut.AppendChar(']');
							}
						}
					}
				}
			}
#line 330 "../../../Source/Core/AST/VarDecl.nll"
			if (!m_bInline)
#line 331 "../../../Source/Core/AST/VarDecl.nll"
				pOutputBuilder.m_sOut.AppendString(";\n");
		}

#line 4 "../../../Source/Core/AST/VarDecl.nll"
		~VarDecl()
		{
		}

	}
}

