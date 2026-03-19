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
		public Vector<DecoratorCall> m_pDecoratorCallVector;
#line 15 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		public VarDecl()
		{
			m_bInline = false;
			m_eType = AST.Type.AST_VAR_DECL;
			m_pDecoratorCallVector = new Vector<DecoratorCall>();
		}

		public static VarDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, bool bInline)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 26 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			TypeRef pTypeRef = TypeRef.TryCreate(pTokenContainer, pTempOffset);
			if (pTypeRef == null)
			{
#line 28 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				return null;
			}
			VarDecl pVarDecl = new VarDecl();
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			OwnedVector<DecoratorCall> pOwnedDecoratorCallVector = new OwnedVector<DecoratorCall>();
			while (true)
			{
				DecoratorCall pDecoratorCall = DecoratorCall.TryCreate(pTokenContainer, pTempOffset);
				if (pDecoratorCall == null)
				{
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
					break;
				}
				NumbatLogic.DecoratorCall __1592839567 = pDecoratorCall;
#line 39 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pDecoratorCall = null;
#line 39 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pOwnedDecoratorCallVector.PushBack(__1592839567);
			}
#line 42 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			while (pOwnedDecoratorCallVector.GetSize() > 0)
			{
				DecoratorCall pDecoratorCall = pOwnedDecoratorCallVector.PopFront();
				pDecoratorCall.m_pParent = pVarDecl;
				DecoratorCall pTemp = pDecoratorCall;
				pVarDecl.m_pDecoratorCallVector.PushBack(pTemp);
				NumbatLogic.DecoratorCall __1592905165 = pDecoratorCall;
#line 48 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pDecoratorCall = null;
#line 48 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pVarDecl.AddChild(__1592905165);
			}
#line 51 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			Token pNameToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
			if (pNameToken == null)
			{
#line 53 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				return null;
			}
#line 54 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 56 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			Token pSquareBracketLeftToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_LEFT);
			while (pSquareBracketLeftToken != null)
			{
				if (pVarDecl.m_pArraySizeVector == null)
					pVarDecl.m_pArraySizeVector = new Vector<AST>();
#line 62 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 64 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				AST pArraySize = AST.TryCreateExpression(pTokenContainer, pTempOffset);
				if (pArraySize == null)
				{
					Console.Log("unable to parse array size...");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					Assert.Plz(false);
					return null;
				}
#line 73 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				Token pSquareBracketRightToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_RIGHT);
				if (pSquareBracketRightToken == null)
				{
					Console.Log("unable to parse closing square bracket");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					Assert.Plz(false);
					return null;
				}
#line 82 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 84 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pVarDecl.m_pArraySizeVector.PushBack(pArraySize);
				NumbatLogic.AST __830388199 = pArraySize;
#line 85 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pArraySize = null;
#line 85 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pVarDecl.AddChild(__830388199);
#line 87 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pSquareBracketLeftToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_LEFT);
			}
#line 90 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			AST pAssignment = null;
			Token pEqualsToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_EQUALS);
			if (pEqualsToken != null)
			{
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 96 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pAssignment = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 98 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				if (pAssignment == null)
				{
					Console.Log("expected to parse assignment...");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					Assert.Plz(false);
					return null;
				}
			}
#line 107 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			if (!bInline)
			{
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
				{
#line 110 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
					return null;
				}
#line 111 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			}
#line 115 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pVarDecl.m_bStatement = bInline == false;
			pVarDecl.m_pFirstToken = pTypeRef.m_pFirstToken;
			pVarDecl.m_pTypeRef = pTypeRef;
			pVarDecl.m_pNameToken = pNameToken;
			pVarDecl.m_pAssignment = pAssignment;
			pVarDecl.m_bInline = bInline;
			NumbatLogic.TypeRef __967647720 = pTypeRef;
			pTypeRef = null;
#line 122 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pVarDecl.AddChild(__967647720);
			if (pAssignment != null)
			{
				NumbatLogic.AST __183884758 = pAssignment;
#line 124 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pAssignment = null;
#line 124 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				pVarDecl.AddChild(__183884758);
			}
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.VarDecl __2972113237 = pVarDecl;
#line 127 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pVarDecl = null;
#line 127 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			return __2972113237;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
#line 134 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			if (m_pParent.m_eType != AST.Type.AST_MEMBER_VAR_DECL && m_pParent.m_eType != AST.Type.AST_PARAM_DECL)
				pValidator.AddVarDecl(this);
#line 137 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			ValueType pValueType = m_pTypeRef.CreateValueType(pValidator.m_pResolver);
			if (pValueType == null)
			{
				pValidator.AddError("Unknown ValueType for TypeRef", m_pTypeRef.m_pFirstToken.m_sFileName, m_pTypeRef.m_pFirstToken.m_nLine, m_pTypeRef.m_pFirstToken.m_nColumn);
				return;
			}
#line 144 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			if (m_pAssignment != null)
			{
				if (m_pAssignment.m_pValueType == null)
				{
					pValidator.AddError("Unknown assignment?", m_pAssignment.m_pFirstToken.m_sFileName, m_pAssignment.m_pFirstToken.m_nLine, m_pAssignment.m_pFirstToken.m_nColumn);
					return;
				}
#line 152 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				if (m_pArraySizeVector != null && m_pAssignment.m_pValueType.m_eType != ValueType.Type.STATIC_ARRAY || m_pArraySizeVector == null && m_pAssignment.m_pValueType.m_eType == ValueType.Type.STATIC_ARRAY)
				{
#line 155 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
					pValidator.AddError("Can only assign a static array to a vardecl with array size", m_pAssignment.m_pFirstToken.m_sFileName, m_pAssignment.m_pFirstToken.m_nLine, m_pAssignment.m_pFirstToken.m_nColumn);
					return;
				}
#line 159 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				if (!m_pAssignment.m_pValueType.ValidateAssignable(pValueType, pValidator, m_pAssignment.m_pFirstToken))
				{
#line 160 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
					return;
				}
				if (pValueType.m_ePointerType != TypeRef.PointerType.OWNED && m_pAssignment.m_pValueType.m_ePointerType == TypeRef.PointerType.OWNED_PREASSSIGN)
				{
					pValidator.AddError("Can't assign an owned pointer to a non-owned variable", m_pAssignment.m_pFirstToken.m_sFileName, m_pAssignment.m_pFirstToken.m_nLine, m_pAssignment.m_pFirstToken.m_nColumn);
					return;
				}
#line 168 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				if (pValueType.m_ePointerType == TypeRef.PointerType.OWNED && (m_pAssignment.m_pValueType.m_ePointerType != TypeRef.PointerType.OWNED_PREASSSIGN && m_pAssignment.m_pValueType.m_eType != ValueType.Type.NULL_VALUE))
				{
					pValidator.AddError("Expected right side of = to be OWNED_PREASSSIGN (result of own)", m_pAssignment.m_pFirstToken.m_sFileName, m_pAssignment.m_pFirstToken.m_nLine, m_pAssignment.m_pFirstToken.m_nColumn);
					return;
				}
				else
#line 173 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
					if (m_pAssignment.m_pValueType.m_ePointerType == TypeRef.PointerType.TRANSITON)
					{
						pValidator.AddError("Cannot store a TRANSITION pointer (need to `own` it)", m_pAssignment.m_pFirstToken.m_sFileName, m_pAssignment.m_pFirstToken.m_nLine, m_pAssignment.m_pFirstToken.m_nColumn);
						return;
					}
			}
		}

#line 183 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			if (nDepth > 0 && m_pFirstToken != null)
				pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 190 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
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
#line 211 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				if (m_pArraySizeVector != null)
				{
					pOutputBuilder.m_sOut.AppendChar('[');
#line 216 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
					pOutputBuilder.m_sOut.AppendChar(']');
				}
			}
			else
			{
				m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
#line 224 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pOutputBuilder.m_sOut.AppendChar(' ');
#line 226 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			if (eLanguage == AST.Language.NLL && m_pDecoratorCallVector != null && m_pDecoratorCallVector.GetSize() > 0)
			{
				for (int i = 0; i < m_pDecoratorCallVector.GetSize(); i++)
				{
					DecoratorCall pDecoratorCall = m_pDecoratorCallVector.Get(i);
					pDecoratorCall.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				}
				pOutputBuilder.m_sOut.AppendChar(' ');
			}
#line 237 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_MEMBER_VAR_DECL && eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
			{
				AST pParentParent = m_pParent.m_pParent;
				if (pParentParent == null || pParentParent.m_eType != AST.Type.AST_CLASS_DECL)
				{
					Assert.Plz(false);
				}
#line 245 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				ClassDecl pClassDecl = (ClassDecl)(pParentParent);
				pOutputBuilder.m_sOut.AppendString(pClassDecl.m_pNameToken.GetString());
				pOutputBuilder.m_sOut.AppendString("::");
			}
#line 250 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			pOutputBuilder.m_sOut.AppendString(m_pNameToken.GetString());
#line 252 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
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
#line 263 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			MemberVarDecl pMemberVarDecl = (m_pParent != null && m_pParent.m_eType == AST.Type.AST_MEMBER_VAR_DECL) ? (MemberVarDecl)(m_pParent) : null;
			bool bStatic = pMemberVarDecl != null && pMemberVarDecl.m_bStatic;
#line 266 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			if (m_pAssignment != null)
			{
				bool bArrayAssignment = m_pArraySizeVector != null;
#line 270 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				bool bDoIt = true;
#line 272 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
				if (eLanguage == AST.Language.CPP)
				{
					if (pMemberVarDecl != null)
					{
						if (eOutputFile == AST.OutputFile.HEADER)
						{
#line 279 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
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
#line 291 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
						if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_PARAM_DECL && eOutputFile == AST.OutputFile.SOURCE)
							bDoIt = false;
					}
				}
#line 296 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
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
#line 315 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
									if (m_pTypeRef.IsBool())
										sxToAppend = " = false";
									else
#line 317 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
										if (m_pTypeRef.IsFloat())
											sxToAppend = " = 0.0f";
										else
#line 319 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
											if (m_pTypeRef.IsDouble())
												sxToAppend = " = 0.0";
							}
						}
					}
#line 325 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
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
#line 338 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
								if (pValueType != null && pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE && m_pArraySizeVector == null)
									pOutputBuilder.m_sOut.AppendString(" = 0");
#line 341 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
								if (bStatic && m_pTypeRef.IsIntegral())
									pOutputBuilder.m_sOut.AppendString(" = 0");
							}
						}
#line 346 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
						if (eLanguage == AST.Language.CS && m_pArraySizeVector != null)
						{
							pOutputBuilder.m_sOut.AppendString(" = new ");
							m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 351 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
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
#line 363 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
			if (!m_bInline)
				pOutputBuilder.m_sOut.AppendString(";\n");
		}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/VarDecl.nll"
		~VarDecl()
		{
		}

	}
}

