namespace NumbatLogic
{
	class VarDecl : AST
	{
		public TypeRef m_pTypeRef;
		public Token m_pNameToken;
		public AST m_pAssignment;
		public bool m_bInline;
		public Vector<AST> m_pArraySizeVector;
		public Token m_pOwnedNameToken;
		public VarDecl()
		{
			m_bInline = false;
			m_eType = AST.Type.AST_VAR_DECL;
		}

		public static VarDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, bool bInline)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			TypeRef pTypeRef = TypeRef.TryCreate(pTokenContainer, pTempOffset);
			if (pTypeRef == null)
			{
				return null;
			}
			Token pNameToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
			if (pNameToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			VarDecl pVarDecl = new VarDecl();
			Token pSquareBracketLeftToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_LEFT);
			while (pSquareBracketLeftToken != null)
			{
				if (pVarDecl.m_pArraySizeVector == null)
					pVarDecl.m_pArraySizeVector = new Vector<AST>();
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				AST pArraySize = AST.TryCreateExpression(pTokenContainer, pTempOffset);
				if (pArraySize == null)
				{
					Console.Log("unable to parse array size...");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
					return null;
				}
				Token pSquareBracketRightToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_RIGHT);
				if (pSquareBracketRightToken == null)
				{
					Console.Log("unable to parse closing square bracket");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
					return null;
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				pVarDecl.m_pArraySizeVector.PushBack(pArraySize);
				NumbatLogic.AST __2791872840 = pArraySize;
				pArraySize = null;
				pVarDecl.AddChild(__2791872840);
				pSquareBracketLeftToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SQUARE_BRACKET_LEFT);
			}
			AST pAssignment = null;
			Token pEqualsToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_EQUALS);
			if (pEqualsToken != null)
			{
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				pAssignment = AST.TryCreateExpression(pTokenContainer, pTempOffset);
				if (pAssignment == null)
				{
					Console.Log("expected to parse assignment...");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
					return null;
				}
			}
			if (!bInline)
			{
				if (pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON) == null)
				{
					return null;
				}
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			}
			pVarDecl.m_bStatement = bInline == false;
			pVarDecl.m_pFirstToken = pTypeRef.m_pFirstToken;
			pVarDecl.m_pTypeRef = pTypeRef;
			pVarDecl.m_pNameToken = pNameToken;
			pVarDecl.m_pAssignment = pAssignment;
			pVarDecl.m_bInline = bInline;
			NumbatLogic.TypeRef __1893385717 = pTypeRef;
			pTypeRef = null;
			pVarDecl.AddChild(__1893385717);
			if (pAssignment != null)
			{
				NumbatLogic.AST __242532869 = pAssignment;
				pAssignment = null;
				pVarDecl.AddChild(__242532869);
			}
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.VarDecl __4040389889 = pVarDecl;
			pVarDecl = null;
			return __4040389889;
		}

		public override AST FindByName(string sxName, AST pCallingChild)
		{
			if (ExternalString.Equal(sxName, m_pNameToken.GetString()))
				return this;
			return base.FindByName(sxName, pCallingChild);
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			if (m_pParent.m_eType != AST.Type.AST_MEMBER_VAR_DECL && m_pParent.m_eType != AST.Type.AST_PARAM_DECL)
				pValidator.AddVarDecl(this);
			ValueType pValueType = m_pTypeRef.CreateValueType();
			if (pValueType == null)
			{
				pValidator.AddError("Unknown ValueType for TypeRef", m_pTypeRef.m_pFirstToken.m_sFileName, m_pTypeRef.m_pFirstToken.m_nLine, m_pTypeRef.m_pFirstToken.m_nColumn);
				return;
			}
			if (m_pAssignment != null)
			{
				if (m_pAssignment.m_pValueType == null)
				{
					pValidator.AddError("Unknown assignment?", m_pAssignment.m_pFirstToken.m_sFileName, m_pAssignment.m_pFirstToken.m_nLine, m_pAssignment.m_pFirstToken.m_nColumn);
					return;
				}
				if (m_pArraySizeVector != null && m_pAssignment.m_pValueType.m_eType != ValueType.Type.STATIC_ARRAY || m_pArraySizeVector == null && m_pAssignment.m_pValueType.m_eType == ValueType.Type.STATIC_ARRAY)
				{
					pValidator.AddError("Can only assign a static array to a vardecl with array size", m_pAssignment.m_pFirstToken.m_sFileName, m_pAssignment.m_pFirstToken.m_nLine, m_pAssignment.m_pFirstToken.m_nColumn);
					return;
				}
				if (!m_pAssignment.m_pValueType.ValidateAssignable(pValueType, pValidator, m_pAssignment.m_pFirstToken))
				{
					return;
				}
				if (pValueType.m_ePointerType != TypeRef.PointerType.OWNED && m_pAssignment.m_pValueType.m_ePointerType == TypeRef.PointerType.OWNED_PREASSSIGN)
				{
					pValidator.AddError("Can't assign an owned pointer to a non-owned variable", m_pAssignment.m_pFirstToken.m_sFileName, m_pAssignment.m_pFirstToken.m_nLine, m_pAssignment.m_pFirstToken.m_nColumn);
					return;
				}
				if (pValueType.m_ePointerType == TypeRef.PointerType.OWNED && (m_pAssignment.m_pValueType.m_ePointerType != TypeRef.PointerType.OWNED_PREASSSIGN && m_pAssignment.m_pValueType.m_eType != ValueType.Type.NULL_VALUE))
				{
					pValidator.AddError("Expected right side of = to be OWNED_PREASSSIGN (result of own)", m_pAssignment.m_pFirstToken.m_sFileName, m_pAssignment.m_pFirstToken.m_nLine, m_pAssignment.m_pFirstToken.m_nColumn);
					return;
				}
				else
					if (m_pAssignment.m_pValueType.m_ePointerType == TypeRef.PointerType.TRANSITON)
					{
						pValidator.AddError("Cannot store a TRANSITION pointer (need to `own` it)", m_pAssignment.m_pFirstToken.m_sFileName, m_pAssignment.m_pFirstToken.m_nLine, m_pAssignment.m_pFirstToken.m_nColumn);
						return;
					}
			}
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			Util.Pad(nDepth, sOut);
			if (eLanguage == AST.Language.CS)
			{
				if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_PARAM_DECL)
				{
					bool bBefore = m_pTypeRef.m_bConst;
					m_pTypeRef.m_bConst = false;
					m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, sOut);
					m_pTypeRef.m_bConst = bBefore;
				}
				else
				{
					bool bBefore = m_pTypeRef.m_bConst;
					if (m_pArraySizeVector != null && bBefore)
					{
						m_pTypeRef.m_bConst = false;
						sOut.Append("readonly ");
					}
					m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, sOut);
					m_pTypeRef.m_bConst = bBefore;
				}
				if (m_pArraySizeVector != null)
				{
					sOut.AppendChar('[');
					sOut.AppendChar(']');
				}
			}
			else
			{
				m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, sOut);
			}
			sOut.AppendChar(' ');
			if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_MEMBER_VAR_DECL && eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
			{
				AST pParentParent = m_pParent.m_pParent;
				if (pParentParent == null || pParentParent.m_eType != AST.Type.AST_CLASS_DECL)
				{
					NumbatLogic.Assert.Plz(false);
				}
				ClassDecl pClassDecl = (ClassDecl)(pParentParent);
				sOut.AppendString(pClassDecl.m_pNameToken.GetString());
				sOut.AppendString("::");
			}
			sOut.AppendString(m_pNameToken.GetString());
			if (m_pArraySizeVector != null && eLanguage != AST.Language.CS)
			{
				for (int i = 0; i < m_pArraySizeVector.GetSize(); i++)
				{
					AST pArraySize = m_pArraySizeVector.Get(i);
					sOut.AppendChar('[');
					pArraySize.Stringify(eLanguage, eOutputFile, 0, sOut);
					sOut.AppendChar(']');
				}
			}
			MemberVarDecl pMemberVarDecl = (m_pParent != null && m_pParent.m_eType == AST.Type.AST_MEMBER_VAR_DECL) ? (MemberVarDecl)(m_pParent) : null;
			bool bStatic = pMemberVarDecl != null && pMemberVarDecl.m_bStatic;
			if (m_pAssignment != null)
			{
				bool bArrayAssignment = m_pArraySizeVector != null;
				bool bDoIt = true;
				if (eLanguage == AST.Language.CPP)
				{
					if (pMemberVarDecl != null)
					{
						if (eOutputFile == AST.OutputFile.HEADER)
						{
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
						if (m_pParent != null && m_pParent.m_eType == AST.Type.AST_PARAM_DECL && eOutputFile == AST.OutputFile.SOURCE)
							bDoIt = false;
					}
				}
				if (bDoIt)
				{
					sOut.AppendString(" = ");
					m_pAssignment.Stringify(eLanguage, eOutputFile, 0, sOut);
				}
			}
			else
			{
				if (!m_bInline && eLanguage == AST.Language.CPP)
				{
					if (eOutputFile == AST.OutputFile.SOURCE)
					{
						ValueType pValueType = m_pTypeRef.CreateValueType();
						if (pValueType != null && pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE && m_pArraySizeVector == null)
							sOut.AppendString(" = 0");
						if (bStatic && m_pTypeRef.IsIntegral())
							sOut.AppendString(" = 0");
					}
				}
				if (!m_bInline && eLanguage == AST.Language.CS && m_pArraySizeVector != null)
				{
					sOut.AppendString(" = new ");
					m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, sOut);
					for (int i = 0; i < m_pArraySizeVector.GetSize(); i++)
					{
						AST pArraySize = m_pArraySizeVector.Get(i);
						sOut.AppendChar('[');
						pArraySize.Stringify(eLanguage, eOutputFile, 0, sOut);
						sOut.AppendChar(']');
					}
				}
			}
			if (!m_bInline)
				sOut.AppendString(";\n");
		}

		~VarDecl()
		{
		}

	}
}

