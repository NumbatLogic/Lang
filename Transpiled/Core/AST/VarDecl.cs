#line 1 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
namespace NumbatLogic
{
	class VarDecl : AST
	{
		public TypeRef m_pTypeRef;
		public Token m_pNameToken;
		public AST m_pAssignment;
		public bool m_bInline;
#line 10 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		public Vector<AST> m_pArraySizeVector;
#line 12 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		public Token m_pOwnedNameToken;
#line 14 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		public VarDecl()
		{
			m_bInline = false;
			m_eType = AST.Type.AST_VAR_DECL;
		}

		public static VarDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, bool bInline)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 24 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			TypeRef pTypeRef = TypeRef.TryCreate(pTokenContainer, pTempOffset);
			if (pTypeRef == null)
			{
#line 26 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				return null;
			}
			Token pNameToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
			if (pNameToken == null)
			{
#line 30 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				return null;
			}
#line 31 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			VarDecl pVarDecl = new VarDecl();
#line 35 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			Token pSquareBracketLeftToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_LEFT);
			while (pSquareBracketLeftToken != null)
			{
				if (pVarDecl.m_pArraySizeVector == null)
					pVarDecl.m_pArraySizeVector = new Vector<AST>();
#line 41 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 43 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				AST pArraySize = AST.TryCreateExpression(pTokenContainer, pTempOffset);
				if (pArraySize == null)
				{
					Console.Log("unable to parse array size...");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					Assert.Plz(false);
					return null;
				}
#line 52 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				Token pSquareBracketRightToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_RIGHT);
				if (pSquareBracketRightToken == null)
				{
					Console.Log("unable to parse closing square bracket");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					Assert.Plz(false);
					return null;
				}
#line 61 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 63 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pVarDecl.m_pArraySizeVector.PushBack(pArraySize);
				NumbatLogic.AST __830257000 = pArraySize;
#line 64 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pArraySize = null;
#line 64 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pVarDecl.AddChild(__830257000);
#line 66 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pSquareBracketLeftToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_LEFT);
			}
#line 69 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			AST pAssignment = null;
			Token pEqualsToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_EQUALS);
			if (pEqualsToken != null)
			{
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 75 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pAssignment = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 77 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				if (pAssignment == null)
				{
					Console.Log("expected to parse assignment...");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					Assert.Plz(false);
					return null;
				}
			}
#line 86 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			if (!bInline)
			{
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
				{
#line 89 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
					return null;
				}
#line 90 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			}
#line 94 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pVarDecl.m_bStatement = bInline == false;
			pVarDecl.m_pFirstToken = pTypeRef.m_pFirstToken;
			pVarDecl.m_pTypeRef = pTypeRef;
			pVarDecl.m_pNameToken = pNameToken;
			pVarDecl.m_pAssignment = pAssignment;
			pVarDecl.m_bInline = bInline;
			NumbatLogic.TypeRef __967516521 = pTypeRef;
			pTypeRef = null;
#line 101 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pVarDecl.AddChild(__967516521);
			if (pAssignment != null)
			{
				NumbatLogic.AST __183753559 = pAssignment;
#line 103 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pAssignment = null;
#line 103 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pVarDecl.AddChild(__183753559);
			}
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.VarDecl __2971982038 = pVarDecl;
#line 106 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pVarDecl = null;
#line 106 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			return __2971982038;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
#line 113 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			if (m_pParent.m_eType != AST.Type.AST_MEMBER_VAR_DECL && m_pParent.m_eType != AST.Type.AST_PARAM_DECL)
				pValidator.AddVarDecl(this);
#line 116 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			ValueType pValueType = m_pTypeRef.CreateValueType(pValidator.m_pResolver);
			if (pValueType == null)
			{
				pValidator.AddError("Unknown ValueType for TypeRef", m_pTypeRef.m_pFirstToken.m_sFileName, m_pTypeRef.m_pFirstToken.m_nLine, m_pTypeRef.m_pFirstToken.m_nColumn);
				return;
			}
#line 123 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			if (m_pAssignment != null)
			{
				if (m_pAssignment.m_pValueType == null)
				{
					pValidator.AddError("Unknown assignment?", m_pAssignment.m_pFirstToken.m_sFileName, m_pAssignment.m_pFirstToken.m_nLine, m_pAssignment.m_pFirstToken.m_nColumn);
					return;
				}
#line 131 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				if (m_pArraySizeVector != null && m_pAssignment.m_pValueType.m_eType != ValueType.Type.STATIC_ARRAY || m_pArraySizeVector == null && m_pAssignment.m_pValueType.m_eType == ValueType.Type.STATIC_ARRAY)
				{
#line 134 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
					pValidator.AddError("Can only assign a static array to a vardecl with array size", m_pAssignment.m_pFirstToken.m_sFileName, m_pAssignment.m_pFirstToken.m_nLine, m_pAssignment.m_pFirstToken.m_nColumn);
					return;
				}
#line 138 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				if (!m_pAssignment.m_pValueType.ValidateAssignable(pValueType, pValidator, m_pAssignment.m_pFirstToken))
				{
#line 139 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
					return;
				}
				if (pValueType.m_ePointerType != TypeRef.PointerType.OWNED && m_pAssignment.m_pValueType.m_ePointerType == TypeRef.PointerType.OWNED_PREASSSIGN)
				{
					pValidator.AddError("Can't assign an owned pointer to a non-owned variable", m_pAssignment.m_pFirstToken.m_sFileName, m_pAssignment.m_pFirstToken.m_nLine, m_pAssignment.m_pFirstToken.m_nColumn);
					return;
				}
#line 147 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				if (pValueType.m_ePointerType == TypeRef.PointerType.OWNED && (m_pAssignment.m_pValueType.m_ePointerType != TypeRef.PointerType.OWNED_PREASSSIGN && m_pAssignment.m_pValueType.m_eType != ValueType.Type.NULL_VALUE))
				{
					pValidator.AddError("Expected right side of = to be OWNED_PREASSSIGN (result of own)", m_pAssignment.m_pFirstToken.m_sFileName, m_pAssignment.m_pFirstToken.m_nLine, m_pAssignment.m_pFirstToken.m_nColumn);
					return;
				}
				else
#line 152 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
					if (m_pAssignment.m_pValueType.m_ePointerType == TypeRef.PointerType.TRANSITON)
					{
						pValidator.AddError("Cannot store a TRANSITION pointer (need to `own` it)", m_pAssignment.m_pFirstToken.m_sFileName, m_pAssignment.m_pFirstToken.m_nLine, m_pAssignment.m_pFirstToken.m_nColumn);
						return;
					}
			}
		}

#line 162 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			if (nDepth > 0 && m_pFirstToken != null)
				pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 169 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			if (eLanguage == AST.Language.CS)
			{
				if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_PARAM_DECL)
				{
					bool bBefore = m_pTypeRef.m_bConst;
					m_pTypeRef.m_bConst = false;
					m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
					m_pTypeRef.m_bConst = bBefore;
				}
				else
				{
					bool bBefore = m_pTypeRef.m_bConst;
					if (m_pArraySizeVector != null && bBefore)
					{
						m_pTypeRef.m_bConst = false;
						pOutputBuilder.m_sOut.Append("readonly ");
					}
					m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
					m_pTypeRef.m_bConst = bBefore;
				}
#line 190 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				if (m_pArraySizeVector != null)
				{
					pOutputBuilder.m_sOut.AppendChar('[');
#line 195 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
					pOutputBuilder.m_sOut.AppendChar(']');
				}
			}
			else
			{
				m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
			pOutputBuilder.m_sOut.AppendChar(' ');
#line 205 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_MEMBER_VAR_DECL && eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
			{
				AST pParentParent = m_pParent.m_pParent;
				if (pParentParent == null || pParentParent.m_eType != AST.Type.AST_CLASS_DECL)
				{
					Assert.Plz(false);
				}
#line 213 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				ClassDecl pClassDecl = (ClassDecl)(pParentParent);
				pOutputBuilder.m_sOut.AppendString(pClassDecl.m_pNameToken.GetString());
				pOutputBuilder.m_sOut.AppendString("::");
			}
#line 218 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pOutputBuilder.m_sOut.AppendString(m_pNameToken.GetString());
#line 220 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			if (m_pArraySizeVector != null && eLanguage != AST.Language.CS)
			{
				for (int i = 0; i < m_pArraySizeVector.GetSize(); i++)
				{
					AST pArraySize = m_pArraySizeVector.Get(i);
					pOutputBuilder.m_sOut.AppendChar('[');
					pArraySize.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
					pOutputBuilder.m_sOut.AppendChar(']');
				}
			}
#line 231 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			MemberVarDecl pMemberVarDecl = (m_pParent != null && m_pParent.m_eType == AST.Type.AST_MEMBER_VAR_DECL) ? (MemberVarDecl)(m_pParent) : null;
			bool bStatic = pMemberVarDecl != null && pMemberVarDecl.m_bStatic;
#line 234 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			if (m_pAssignment != null)
			{
				bool bArrayAssignment = m_pArraySizeVector != null;
#line 238 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				bool bDoIt = true;
#line 240 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				if (eLanguage == AST.Language.CPP)
				{
					if (pMemberVarDecl != null)
					{
						if (eOutputFile == AST.OutputFile.HEADER)
						{
#line 247 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
							if (!(bStatic && m_pTypeRef.m_bConst && m_pTypeRef.IsIntegral() && !bArrayAssignment))
								bDoIt = false;
						}
						else
						{
							if (bStatic && m_pTypeRef.m_bConst && m_pTypeRef.IsIntegral() && !bArrayAssignment)
								bDoIt = false;
						}
					}
					else
					{
#line 259 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
						if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_PARAM_DECL && eOutputFile == AST.OutputFile.SOURCE)
							bDoIt = false;
					}
				}
#line 264 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				if (bDoIt)
				{
					pOutputBuilder.m_sOut.AppendString(" = ");
					m_pAssignment.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				}
			}
			else
			{
				if (!m_bInline)
				{
					string sxToAppend = null;
					if (eOutputFile == AST.OutputFile.SOURCE && eLanguage != AST.Language.NLL && eLanguage != AST.Language.NLL_DEF)
					{
						if (m_pParent.m_eType != AST.Type.AST_MEMBER_VAR_DECL)
						{
							if (m_pArraySizeVector == null)
							{
								if (m_pTypeRef.IsInt())
									sxToAppend = " = 0";
								else
#line 283 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
									if (m_pTypeRef.IsBool())
										sxToAppend = " = false";
									else
#line 285 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
										if (m_pTypeRef.IsFloat())
											sxToAppend = " = 0.0f";
										else
#line 287 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
											if (m_pTypeRef.IsDouble())
												sxToAppend = " = 0.0";
							}
						}
					}
#line 293 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
					if (sxToAppend != null)
					{
						pOutputBuilder.m_sOut.AppendString(sxToAppend);
					}
					else
					{
						if (eLanguage == AST.Language.CPP)
						{
							if (eOutputFile == AST.OutputFile.SOURCE)
							{
								Project pProject = GetProject();
								ValueType pValueType = m_pTypeRef.CreateValueType(pProject.m_pValidator.m_pResolver);
#line 306 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
								if (pValueType != null && pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE && m_pArraySizeVector == null)
									pOutputBuilder.m_sOut.AppendString(" = 0");
#line 309 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
								if (bStatic && m_pTypeRef.IsIntegral())
									pOutputBuilder.m_sOut.AppendString(" = 0");
							}
						}
#line 314 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
						if (eLanguage == AST.Language.CS && m_pArraySizeVector != null)
						{
							pOutputBuilder.m_sOut.AppendString(" = new ");
							m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 319 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
							for (int i = 0; i < m_pArraySizeVector.GetSize(); i++)
							{
								AST pArraySize = m_pArraySizeVector.Get(i);
								pOutputBuilder.m_sOut.AppendChar('[');
								pArraySize.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
								pOutputBuilder.m_sOut.AppendChar(']');
							}
						}
					}
				}
			}
#line 331 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			if (!m_bInline)
				pOutputBuilder.m_sOut.AppendString(";\n");
		}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		~VarDecl()
		{
		}

	}
}

