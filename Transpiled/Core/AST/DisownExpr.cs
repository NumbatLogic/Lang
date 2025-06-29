namespace NumbatLogic
{
	class DisownExpr : AST
	{
		public AST m_pExpression;
		public InternalString m_sTempVarName;
		public DisownExpr()
		{
			m_eType = AST.Type.AST_DISOWN_EXP;
		}

		public static DisownExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pDisownToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_DISOWN);
			if (pDisownToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pExpression == null)
			{
				Console.Log("expected expresssion");
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			DisownExpr pDisownExpr = new DisownExpr();
			pDisownExpr.m_pFirstToken = pDisownToken;
			pDisownExpr.m_pExpression = pExpression;
			NumbatLogic.AST __2860403603 = pExpression;
			pExpression = null;
			pDisownExpr.AddChild(__2860403603);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.DisownExpr __1761905829 = pDisownExpr;
			pDisownExpr = null;
			return __1761905829;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			if (m_pExpression.m_pValueType == null)
			{
				pValidator.AddError("No valuetype for expression???", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
				return;
			}
			if (m_pExpression.m_pValueType.m_eType != ValueType.Type.CLASS_DECL_VALUE && m_pExpression.m_pValueType.m_eType != ValueType.Type.GENERIC_TYPE_DECL_VALUE)
			{
				pValidator.AddError("Expected right side of Disown to be a CLASS_DECL_VALUE or GENERIC_TYPE_DECL_VALUE", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
				return;
			}
			if (m_pExpression.m_pValueType.m_ePointerType != TypeRef.PointerType.OWNED)
			{
				pValidator.AddError("Expected right side of Disown to be a OWNED type", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
				return;
			}
			m_pValueType = m_pExpression.m_pValueType.Clone();
			m_pValueType.m_ePointerType = TypeRef.PointerType.TRANSITON;
			if (m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
			{
				if (m_pValueType.m_pClassDecl == null)
				{
					pValidator.AddError("Can't disown unbeknownst thing (ClassDecl)", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
					return;
				}
			}
			else
				if (m_pValueType.m_eType == ValueType.Type.GENERIC_TYPE_DECL_VALUE)
				{
					if (m_pValueType.m_pGenericTypeDecl == null)
					{
						pValidator.AddError("Can't disown unbeknownst thing (GenericTypeDecl)", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
						return;
					}
				}
			AST pParentStatement = GetParentStatement();
			if (pParentStatement == null)
			{
				pValidator.AddError("Can'd find disown parent???", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
				return;
			}
			InternalString sTempName = new InternalString("");
			m_pExpression.Stringify(AST.Language.CPP, AST.OutputFile.SOURCE, 0, sTempName);
			sTempName.AppendInt(pParentStatement.m_pFirstToken.m_nLine);
			uint nHash = Util.BadHash(sTempName);
			sTempName.Set("__");
			sTempName.AppendUint32(nHash);
			AST pParentParent = pParentStatement.m_pParent;
			{
				TypeRef pTypeRef = m_pValueType.CreateTypeRef();
				Token pNameToken = new Token();
				pNameToken.m_eType = Token.Type.TOKEN_IDENTIFIER;
				pNameToken.m_sValue = new InternalString(sTempName.GetExternalString());
				AST pAssignment = m_pExpression.BaseClone();
				VarDecl pTempVarDecl = new VarDecl();
				pTempVarDecl.m_pFirstToken = pTypeRef.m_pFirstToken;
				pTempVarDecl.m_pTypeRef = pTypeRef;
				pTempVarDecl.m_pNameToken = pNameToken;
				NumbatLogic.Token __2589041192 = pNameToken;
				pNameToken = null;
				pTempVarDecl.m_pOwnedNameToken = __2589041192;
				pTempVarDecl.m_pAssignment = pAssignment;
				NumbatLogic.TypeRef __802834809 = pTypeRef;
				pTypeRef = null;
				pTempVarDecl.AddChild(__802834809);
				NumbatLogic.AST __1114918871 = pAssignment;
				pAssignment = null;
				pTempVarDecl.AddChild(__1114918871);
				NumbatLogic.VarDecl __1656425058 = pTempVarDecl;
				pTempVarDecl = null;
				pParentParent.AddChildBefore(__1656425058, pParentStatement);
			}
			{
				AST pLeft = m_pExpression.BaseClone();
				NullExpr pRight = new NullExpr();
				Token pOperatorToken = new Token();
				pOperatorToken.m_eType = Token.Type.TOKEN_EQUALS;
				OperatorExpr pOperatorExpr = new OperatorExpr();
				pOperatorExpr.m_eType = AST.Type.AST_OPERATOR_EXPR;
				pOperatorExpr.m_pFirstToken = pLeft.m_pFirstToken;
				pOperatorExpr.m_pOperatorToken = pOperatorToken;
				NumbatLogic.Token __1410729535 = pOperatorToken;
				pOperatorToken = null;
				pOperatorExpr.m_pOwnedOperatorToken = __1410729535;
				pOperatorExpr.m_pLeft = pLeft;
				pOperatorExpr.m_pRight = pRight;
				NumbatLogic.AST __1926080510 = pLeft;
				pLeft = null;
				pOperatorExpr.AddChild(__1926080510);
				NumbatLogic.NullExpr __3954022087 = pRight;
				pRight = null;
				pOperatorExpr.AddChild(__3954022087);
				ExpressionStmt pExpressionStmt = new ExpressionStmt();
				pExpressionStmt.m_pFirstToken = pOperatorExpr.m_pFirstToken;
				pExpressionStmt.m_pExpression = pOperatorExpr;
				NumbatLogic.OperatorExpr __1650736823 = pOperatorExpr;
				pOperatorExpr = null;
				pExpressionStmt.AddChild(__1650736823);
				NumbatLogic.ExpressionStmt __1385987715 = pExpressionStmt;
				pExpressionStmt = null;
				pParentParent.AddChildBefore(__1385987715, pParentStatement);
			}
			NumbatLogic.InternalString __1093496711 = sTempName;
			sTempName = null;
			m_sTempVarName = __1093496711;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			if (m_sTempVarName != null)
			{
				sOut.Append(m_sTempVarName.GetExternalString());
				return;
			}
			if (eLanguage == AST.Language.NLL)
			{
				sOut.Append("disown ");
			}
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, sOut);
		}

		~DisownExpr()
		{
		}

	}
}

