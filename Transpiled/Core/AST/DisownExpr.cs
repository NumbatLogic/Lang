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
				{
					return null;
				}
			}
			DisownExpr pDisownExpr = new DisownExpr();
			pDisownExpr.m_pFirstToken = pDisownToken;
			pDisownExpr.m_pExpression = pExpression;
			{
				NumbatLogic.AST __1067118945 = pExpression;
				pExpression = null;
				pDisownExpr.AddChild(__1067118945);
			}
			pOffsetDatum.Set(pTempOffset);
			{
				NumbatLogic.DisownExpr __2180824118 = pDisownExpr;
				pDisownExpr = null;
				{
					return __2180824118;
				}
			}
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
			else if (m_pValueType.m_eType == ValueType.Type.GENERIC_TYPE_DECL_VALUE)
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
			uint nHash = Util.BadHash(sTempName);
			sTempName.Set("__");
			sTempName.AppendUint32(nHash);
			AST pParentParent = pParentStatement.m_pParent;
			Scope pScope = new Scope();
			AST pOwnedParentStatement;
			AST pDisownedScope;
			if (pParentParent.m_pFirstChild == pParentStatement)
			{
				{
					NumbatLogic.AST __1629566089 = pParentParent.m_pFirstChild;
					pParentParent.m_pFirstChild = null;
					pOwnedParentStatement = __1629566089;
				}
				{
					NumbatLogic.Scope __693694853 = pScope;
					pScope = null;
					pParentParent.m_pFirstChild = __693694853;
				}
				pDisownedScope = pParentParent.m_pFirstChild;
			}
			else
			{
				{
					NumbatLogic.AST __411868003 = pParentStatement.m_pPrevSibling.m_pNextSibling;
					pParentStatement.m_pPrevSibling.m_pNextSibling = null;
					pOwnedParentStatement = __411868003;
				}
				{
					NumbatLogic.Scope __693694853 = pScope;
					pScope = null;
					pParentStatement.m_pPrevSibling.m_pNextSibling = __693694853;
				}
				pDisownedScope = pParentStatement.m_pPrevSibling.m_pNextSibling;
				pDisownedScope.m_pPrevSibling = pOwnedParentStatement.m_pPrevSibling;
				pOwnedParentStatement.m_pPrevSibling = null;
			}
			pDisownedScope.m_pParent = pParentParent;
			if (pParentParent.m_pLastChild == pParentStatement)
			{
				pParentParent.m_pLastChild = pDisownedScope;
			}
			else
			{
				{
					NumbatLogic.AST __1356546117 = pParentStatement.m_pNextSibling;
					pParentStatement.m_pNextSibling = null;
					pDisownedScope.m_pNextSibling = __1356546117;
				}
				pDisownedScope.m_pNextSibling.m_pPrevSibling = pDisownedScope;
				pParentStatement.m_pNextSibling = null;
			}
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
				{
					NumbatLogic.Token __1290965399 = pNameToken;
					pNameToken = null;
					pTempVarDecl.m_pOwnedNameToken = __1290965399;
				}
				pTempVarDecl.m_pAssignment = pAssignment;
				{
					NumbatLogic.TypeRef __3079357496 = pTypeRef;
					pTypeRef = null;
					pTempVarDecl.AddChild(__3079357496);
				}
				{
					NumbatLogic.AST __267221586 = pAssignment;
					pAssignment = null;
					pTempVarDecl.AddChild(__267221586);
				}
				{
					NumbatLogic.VarDecl __2352338849 = pTempVarDecl;
					pTempVarDecl = null;
					pDisownedScope.AddChild(__2352338849);
				}
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
				{
					NumbatLogic.Token __3032764722 = pOperatorToken;
					pOperatorToken = null;
					pOperatorExpr.m_pOwnedOperatorToken = __3032764722;
				}
				pOperatorExpr.m_pLeft = pLeft;
				pOperatorExpr.m_pRight = pRight;
				{
					NumbatLogic.AST __2461073728 = pLeft;
					pLeft = null;
					pOperatorExpr.AddChild(__2461073728);
				}
				{
					NumbatLogic.NullExpr __1625873296 = pRight;
					pRight = null;
					pOperatorExpr.AddChild(__1625873296);
				}
				ExpressionStmt pExpressionStmt = new ExpressionStmt();
				pExpressionStmt.m_pFirstToken = pOperatorExpr.m_pFirstToken;
				pExpressionStmt.m_pExpression = pOperatorExpr;
				{
					NumbatLogic.OperatorExpr __304301329 = pOperatorExpr;
					pOperatorExpr = null;
					pExpressionStmt.AddChild(__304301329);
				}
				{
					NumbatLogic.ExpressionStmt __817911874 = pExpressionStmt;
					pExpressionStmt = null;
					pDisownedScope.AddChild(__817911874);
				}
			}
			{
				NumbatLogic.InternalString __1040485554 = sTempName;
				sTempName = null;
				m_sTempVarName = __1040485554;
			}
			{
				NumbatLogic.AST __3676823010 = pOwnedParentStatement;
				pOwnedParentStatement = null;
				pDisownedScope.AddChild(__3676823010);
			}
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

