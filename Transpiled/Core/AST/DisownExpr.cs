#line 1 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
namespace NumbatLogic
{
	class DisownExpr : AST
	{
		public AST m_pExpression;
		public InternalString m_sTempVarName;
#line 8 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
		public DisownExpr()
		{
			m_eType = AST.Type.AST_DISOWN_EXP;
		}

		public static DisownExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			Token pDisownToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_DISOWN);
			if (pDisownToken == null)
			{
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				return null;
			}
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			if (pExpression == null)
			{
				Console.Log("expected expresssion");
				Assert.Plz(false);
				return null;
			}
#line 30 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			DisownExpr pDisownExpr = new DisownExpr();
#line 32 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			pDisownExpr.m_pFirstToken = pDisownToken;
			pDisownExpr.m_pExpression = pExpression;
			NumbatLogic.AST __1929399913 = pExpression;
#line 34 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			pExpression = null;
#line 34 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			pDisownExpr.AddChild(__1929399913);
#line 36 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.DisownExpr __1970191169 = pDisownExpr;
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			pDisownExpr = null;
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			return __1970191169;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
#line 44 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			if (m_pExpression.m_pValueType == null)
			{
				pValidator.AddError("No valuetype for expression???", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
				return;
			}
#line 50 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			if (m_pExpression.m_pValueType.m_eType != ValueType.Type.CLASS_DECL_VALUE && m_pExpression.m_pValueType.m_eType != ValueType.Type.GENERIC_TYPE_DECL_VALUE)
			{
				pValidator.AddError("Expected right side of Disown to be a CLASS_DECL_VALUE or GENERIC_TYPE_DECL_VALUE", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
				return;
			}
#line 56 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			if (m_pExpression.m_pValueType.m_ePointerType != TypeRef.PointerType.OWNED)
			{
				pValidator.AddError("Expected right side of Disown to be a OWNED type", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
				return;
			}
#line 62 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			m_pValueType = m_pExpression.m_pValueType.Clone();
			m_pValueType.m_ePointerType = TypeRef.PointerType.TRANSITON;
#line 66 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			if (m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
			{
				if (m_pValueType.m_pClassDecl == null)
				{
					pValidator.AddError("Can't disown unbeknownst thing (ClassDecl)", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
					return;
				}
			}
			else
#line 74 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				if (m_pValueType.m_eType == ValueType.Type.GENERIC_TYPE_DECL_VALUE)
				{
					if (m_pValueType.m_pGenericTypeDecl == null)
					{
						pValidator.AddError("Can't disown unbeknownst thing (GenericTypeDecl)", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
						return;
					}
				}
#line 83 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			AST pParentStatement = GetParentStatement();
			if (pParentStatement == null)
			{
				pValidator.AddError("Can'd find disown parent???", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
				return;
			}
#line 90 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			InternalString sTempName = new InternalString("");
			OutputBuilder outTemp = new OutputBuilder();
			m_pExpression.Stringify(AST.Language.CPP, AST.OutputFile.SOURCE, 0, outTemp);
#line 94 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			sTempName.Append(outTemp.m_sOut.GetExternalString());
#line 96 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			sTempName.AppendInt(pParentStatement.m_pFirstToken.m_nLine);
			uint nHash = ExternalString.GetChecksum(sTempName.GetExternalString());
#line 99 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			sTempName.Set("__");
			sTempName.AppendUint32(nHash);
#line 105 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			AST pParentParent = pParentStatement.m_pParent;
			{
#line 108 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				TypeRef pTypeRef = m_pValueType.CreateTypeRef();
				Token pNameToken = new Token();
				pNameToken.m_eType = Token.Type.TOKEN_IDENTIFIER;
				pNameToken.m_sValue = new InternalString(sTempName.GetExternalString());
#line 115 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				AST pAssignment = m_pExpression.BaseClone();
#line 117 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				VarDecl pTempVarDecl = new VarDecl();
				pTempVarDecl.m_pFirstToken = pTypeRef.m_pFirstToken;
				pTempVarDecl.m_pTypeRef = pTypeRef;
				pTempVarDecl.m_pNameToken = pNameToken;
				NumbatLogic.Token __2859238226 = pNameToken;
#line 121 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				pNameToken = null;
#line 121 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				pTempVarDecl.m_pOwnedNameToken = __2859238226;
				pTempVarDecl.m_pAssignment = pAssignment;
				NumbatLogic.TypeRef __967647721 = pTypeRef;
#line 123 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				pTypeRef = null;
#line 123 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				pTempVarDecl.AddChild(__967647721);
				NumbatLogic.AST __183884758 = pAssignment;
#line 124 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				pAssignment = null;
#line 124 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				pTempVarDecl.AddChild(__183884758);
#line 126 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				AST pInjectedVarDecl = pTempVarDecl;
				NumbatLogic.VarDecl __3774795561 = pTempVarDecl;
#line 127 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				pTempVarDecl = null;
#line 127 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				pParentParent.AddChildBefore(__3774795561, pParentStatement);
				pValidator.ValidateSubtree(pInjectedVarDecl);
			}
			{
#line 132 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				AST pLeft = m_pExpression.BaseClone();
#line 134 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				NullExpr pRight = new NullExpr();
#line 136 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				Token pOperatorToken = new Token();
				pOperatorToken.m_eType = Token.Type.TOKEN_EQUALS;
				NumbatLogic.AST __3919013152 = pLeft;
				pLeft = null;
				NumbatLogic.NullExpr __534132299 = pRight;
#line 139 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				pRight = null;
#line 139 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				OperatorExpr pOperatorExpr = OperatorExpr.Create(OperatorExpr.OperatorType.ASSIGNMENT, pOperatorToken, __3919013152, __534132299);
				NumbatLogic.Token __3603785160 = pOperatorToken;
#line 140 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				pOperatorToken = null;
#line 140 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				pOperatorExpr.m_pOwnedOperatorToken = __3603785160;
#line 142 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				ExpressionStmt pExpressionStmt = new ExpressionStmt();
				pExpressionStmt.m_pFirstToken = pOperatorExpr.m_pFirstToken;
				pExpressionStmt.m_pExpression = pOperatorExpr;
				NumbatLogic.OperatorExpr __2365778377 = pOperatorExpr;
#line 145 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				pOperatorExpr = null;
#line 145 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				pExpressionStmt.AddChild(__2365778377);
#line 147 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				AST pInjectedStmt = pExpressionStmt;
				NumbatLogic.ExpressionStmt __1415267173 = pExpressionStmt;
#line 148 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				pExpressionStmt = null;
#line 148 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
				pParentParent.AddChildBefore(__1415267173, pParentStatement);
				pValidator.ValidateSubtree(pInjectedStmt);
			}
			NumbatLogic.InternalString __3313827548 = sTempName;
			sTempName = null;
#line 152 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			m_sTempVarName = __3313827548;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			if (m_sTempVarName != null)
			{
				pOutputBuilder.m_sOut.Append(m_sTempVarName.GetExternalString());
				return;
			}
#line 163 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			if (eLanguage == AST.Language.NLL)
			{
				pOutputBuilder.m_sOut.Append("disown ");
			}
#line 168 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/DisownExpr.nll"
		~DisownExpr()
		{
		}

	}
}

