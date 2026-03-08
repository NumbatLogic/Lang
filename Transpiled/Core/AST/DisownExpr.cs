#line 0 "../../../Source/Core/AST/DisownExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/DisownExpr.nll"
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
				Assert.Plz(false);
				return null;
			}
			DisownExpr pDisownExpr = new DisownExpr();
			pDisownExpr.m_pFirstToken = pDisownToken;
			pDisownExpr.m_pExpression = pExpression;
			NumbatLogic.AST __1929399913 = pExpression;
			pExpression = null;
			pDisownExpr.AddChild(__1929399913);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.DisownExpr __1970191169 = pDisownExpr;
			pDisownExpr = null;
			return __1970191169;
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
			OutputBuilder outTemp = new OutputBuilder();
			m_pExpression.Stringify(AST.Language.CPP, AST.OutputFile.SOURCE, 0, outTemp);
			sTempName.Append(outTemp.m_sOut.GetExternalString());
			sTempName.AppendInt(pParentStatement.m_pFirstToken.m_nLine);
			uint nHash = ExternalString.GetChecksum(sTempName.GetExternalString());
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
				NumbatLogic.Token __2859238226 = pNameToken;
				pNameToken = null;
				pTempVarDecl.m_pOwnedNameToken = __2859238226;
				pTempVarDecl.m_pAssignment = pAssignment;
				NumbatLogic.TypeRef __967647721 = pTypeRef;
				pTypeRef = null;
				pTempVarDecl.AddChild(__967647721);
				NumbatLogic.AST __183884758 = pAssignment;
				pAssignment = null;
				pTempVarDecl.AddChild(__183884758);
				AST pInjectedVarDecl = pTempVarDecl;
				NumbatLogic.VarDecl __3774795561 = pTempVarDecl;
				pTempVarDecl = null;
				pParentParent.AddChildBefore(__3774795561, pParentStatement);
				pValidator.ValidateSubtree(pInjectedVarDecl);
			}
			{
				AST pLeft = m_pExpression.BaseClone();
				NullExpr pRight = new NullExpr();
				Token pOperatorToken = new Token();
				pOperatorToken.m_eType = Token.Type.TOKEN_EQUALS;
				NumbatLogic.AST __3919013152 = pLeft;
				pLeft = null;
				NumbatLogic.NullExpr __534132299 = pRight;
				pRight = null;
				OperatorExpr pOperatorExpr = OperatorExpr.Create(OperatorExpr.OperatorType.ASSIGNMENT, pOperatorToken, __3919013152, __534132299);
				NumbatLogic.Token __3603785160 = pOperatorToken;
				pOperatorToken = null;
				pOperatorExpr.m_pOwnedOperatorToken = __3603785160;
				ExpressionStmt pExpressionStmt = new ExpressionStmt();
				pExpressionStmt.m_pFirstToken = pOperatorExpr.m_pFirstToken;
				pExpressionStmt.m_pExpression = pOperatorExpr;
				NumbatLogic.OperatorExpr __2365778377 = pOperatorExpr;
				pOperatorExpr = null;
				pExpressionStmt.AddChild(__2365778377);
				AST pInjectedStmt = pExpressionStmt;
				NumbatLogic.ExpressionStmt __1415267173 = pExpressionStmt;
				pExpressionStmt = null;
				pParentParent.AddChildBefore(__1415267173, pParentStatement);
				pValidator.ValidateSubtree(pInjectedStmt);
			}
			NumbatLogic.InternalString __3313827548 = sTempName;
			sTempName = null;
			m_sTempVarName = __3313827548;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder out)
		{
			if (m_sTempVarName != null)
			{
				out.m_sOut.Append(m_sTempVarName.GetExternalString());
				return;
			}
			if (eLanguage == AST.Language.NLL)
			{
				out.m_sOut.Append("disown ");
			}
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, out);
		}

		~DisownExpr()
		{
		}

	}
}

