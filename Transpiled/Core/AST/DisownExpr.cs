#line 1 "../../../Source/Core/AST/DisownExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/DisownExpr.nll"
	class DisownExpr : AST
	{
#line 5 "../../../Source/Core/AST/DisownExpr.nll"
		public AST m_pExpression;
#line 6 "../../../Source/Core/AST/DisownExpr.nll"
		public InternalString m_sTempVarName;
#line 8 "../../../Source/Core/AST/DisownExpr.nll"
		public DisownExpr()
		{
#line 10 "../../../Source/Core/AST/DisownExpr.nll"
			m_eType = AST.Type.AST_DISOWN_EXP;
		}

#line 13 "../../../Source/Core/AST/DisownExpr.nll"
		public static DisownExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 15 "../../../Source/Core/AST/DisownExpr.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 17 "../../../Source/Core/AST/DisownExpr.nll"
			Token pDisownToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_DISOWN);
#line 18 "../../../Source/Core/AST/DisownExpr.nll"
			if (pDisownToken == null)
			{
#line 19 "../../../Source/Core/AST/DisownExpr.nll"
				return null;
			}
#line 20 "../../../Source/Core/AST/DisownExpr.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 22 "../../../Source/Core/AST/DisownExpr.nll"
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 23 "../../../Source/Core/AST/DisownExpr.nll"
			if (pExpression == null)
			{
#line 25 "../../../Source/Core/AST/DisownExpr.nll"
				Console.Log("expected expresssion");
#line 26 "../../../Source/Core/AST/DisownExpr.nll"
				Assert.Plz(false);
#line 27 "../../../Source/Core/AST/DisownExpr.nll"
				return null;
			}
#line 30 "../../../Source/Core/AST/DisownExpr.nll"
			DisownExpr pDisownExpr = new DisownExpr();
#line 32 "../../../Source/Core/AST/DisownExpr.nll"
			pDisownExpr.m_pFirstToken = pDisownToken;
#line 33 "../../../Source/Core/AST/DisownExpr.nll"
			pDisownExpr.m_pExpression = pExpression;
			NumbatLogic.AST __1929399913 = pExpression;
#line 34 "../../../Source/Core/AST/DisownExpr.nll"
			pExpression = null;
#line 34 "../../../Source/Core/AST/DisownExpr.nll"
			pDisownExpr.AddChild(__1929399913);
#line 36 "../../../Source/Core/AST/DisownExpr.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.DisownExpr __1970191169 = pDisownExpr;
#line 37 "../../../Source/Core/AST/DisownExpr.nll"
			pDisownExpr = null;
#line 37 "../../../Source/Core/AST/DisownExpr.nll"
			return __1970191169;
		}

#line 40 "../../../Source/Core/AST/DisownExpr.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 42 "../../../Source/Core/AST/DisownExpr.nll"
			base.Validate(pValidator, pParent);
#line 44 "../../../Source/Core/AST/DisownExpr.nll"
			if (m_pExpression.m_pValueType == null)
			{
#line 46 "../../../Source/Core/AST/DisownExpr.nll"
				pValidator.AddError("No valuetype for expression???", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
#line 47 "../../../Source/Core/AST/DisownExpr.nll"
				return;
			}
#line 50 "../../../Source/Core/AST/DisownExpr.nll"
			if (m_pExpression.m_pValueType.m_eType != ValueType.Type.CLASS_DECL_VALUE && m_pExpression.m_pValueType.m_eType != ValueType.Type.GENERIC_TYPE_DECL_VALUE)
			{
#line 52 "../../../Source/Core/AST/DisownExpr.nll"
				pValidator.AddError("Expected right side of Disown to be a CLASS_DECL_VALUE or GENERIC_TYPE_DECL_VALUE", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
#line 53 "../../../Source/Core/AST/DisownExpr.nll"
				return;
			}
#line 56 "../../../Source/Core/AST/DisownExpr.nll"
			if (m_pExpression.m_pValueType.m_ePointerType != TypeRef.PointerType.OWNED)
			{
#line 58 "../../../Source/Core/AST/DisownExpr.nll"
				pValidator.AddError("Expected right side of Disown to be a OWNED type", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
#line 59 "../../../Source/Core/AST/DisownExpr.nll"
				return;
			}
#line 62 "../../../Source/Core/AST/DisownExpr.nll"
			m_pValueType = m_pExpression.m_pValueType.Clone();
#line 63 "../../../Source/Core/AST/DisownExpr.nll"
			m_pValueType.m_ePointerType = TypeRef.PointerType.TRANSITON;
#line 66 "../../../Source/Core/AST/DisownExpr.nll"
			if (m_pValueType.m_eType == ValueType.Type.CLASS_DECL_VALUE)
			{
#line 68 "../../../Source/Core/AST/DisownExpr.nll"
				if (m_pValueType.m_pClassDecl == null)
				{
#line 70 "../../../Source/Core/AST/DisownExpr.nll"
					pValidator.AddError("Can't disown unbeknownst thing (ClassDecl)", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
#line 71 "../../../Source/Core/AST/DisownExpr.nll"
					return;
				}
			}
			else
#line 74 "../../../Source/Core/AST/DisownExpr.nll"
				if (m_pValueType.m_eType == ValueType.Type.GENERIC_TYPE_DECL_VALUE)
				{
#line 76 "../../../Source/Core/AST/DisownExpr.nll"
					if (m_pValueType.m_pGenericTypeDecl == null)
					{
#line 78 "../../../Source/Core/AST/DisownExpr.nll"
						pValidator.AddError("Can't disown unbeknownst thing (GenericTypeDecl)", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
#line 79 "../../../Source/Core/AST/DisownExpr.nll"
						return;
					}
				}
#line 83 "../../../Source/Core/AST/DisownExpr.nll"
			AST pParentStatement = GetParentStatement();
#line 84 "../../../Source/Core/AST/DisownExpr.nll"
			if (pParentStatement == null)
			{
#line 86 "../../../Source/Core/AST/DisownExpr.nll"
				pValidator.AddError("Can'd find disown parent???", m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
#line 87 "../../../Source/Core/AST/DisownExpr.nll"
				return;
			}
#line 90 "../../../Source/Core/AST/DisownExpr.nll"
			InternalString sTempName = new InternalString("");
#line 91 "../../../Source/Core/AST/DisownExpr.nll"
			OutputBuilder outTemp = new OutputBuilder();
#line 92 "../../../Source/Core/AST/DisownExpr.nll"
			m_pExpression.Stringify(AST.Language.CPP, AST.OutputFile.SOURCE, 0, outTemp);
#line 94 "../../../Source/Core/AST/DisownExpr.nll"
			sTempName.Append(outTemp.m_sOut.GetExternalString());
#line 96 "../../../Source/Core/AST/DisownExpr.nll"
			sTempName.AppendInt(pParentStatement.m_pFirstToken.m_nLine);
#line 97 "../../../Source/Core/AST/DisownExpr.nll"
			uint nHash = ExternalString.GetChecksum(sTempName.GetExternalString());
#line 99 "../../../Source/Core/AST/DisownExpr.nll"
			sTempName.Set("__");
#line 100 "../../../Source/Core/AST/DisownExpr.nll"
			sTempName.AppendUint32(nHash);
#line 105 "../../../Source/Core/AST/DisownExpr.nll"
			AST pParentParent = pParentStatement.m_pParent;
			{
#line 108 "../../../Source/Core/AST/DisownExpr.nll"
				TypeRef pTypeRef = m_pValueType.CreateTypeRef();
#line 109 "../../../Source/Core/AST/DisownExpr.nll"
				Token pNameToken = new Token();
#line 110 "../../../Source/Core/AST/DisownExpr.nll"
				pNameToken.m_eType = Token.Type.TOKEN_IDENTIFIER;
#line 111 "../../../Source/Core/AST/DisownExpr.nll"
				pNameToken.m_sValue = new InternalString(sTempName.GetExternalString());
#line 115 "../../../Source/Core/AST/DisownExpr.nll"
				AST pAssignment = m_pExpression.BaseClone();
#line 117 "../../../Source/Core/AST/DisownExpr.nll"
				VarDecl pTempVarDecl = new VarDecl();
#line 118 "../../../Source/Core/AST/DisownExpr.nll"
				pTempVarDecl.m_pFirstToken = pTypeRef.m_pFirstToken;
#line 119 "../../../Source/Core/AST/DisownExpr.nll"
				pTempVarDecl.m_pTypeRef = pTypeRef;
#line 120 "../../../Source/Core/AST/DisownExpr.nll"
				pTempVarDecl.m_pNameToken = pNameToken;
				NumbatLogic.Token __2859238226 = pNameToken;
#line 121 "../../../Source/Core/AST/DisownExpr.nll"
				pNameToken = null;
#line 121 "../../../Source/Core/AST/DisownExpr.nll"
				pTempVarDecl.m_pOwnedNameToken = __2859238226;
#line 122 "../../../Source/Core/AST/DisownExpr.nll"
				pTempVarDecl.m_pAssignment = pAssignment;
				NumbatLogic.TypeRef __967647721 = pTypeRef;
#line 123 "../../../Source/Core/AST/DisownExpr.nll"
				pTypeRef = null;
#line 123 "../../../Source/Core/AST/DisownExpr.nll"
				pTempVarDecl.AddChild(__967647721);
				NumbatLogic.AST __183884758 = pAssignment;
#line 124 "../../../Source/Core/AST/DisownExpr.nll"
				pAssignment = null;
#line 124 "../../../Source/Core/AST/DisownExpr.nll"
				pTempVarDecl.AddChild(__183884758);
#line 126 "../../../Source/Core/AST/DisownExpr.nll"
				AST pInjectedVarDecl = pTempVarDecl;
				NumbatLogic.VarDecl __3774795561 = pTempVarDecl;
#line 127 "../../../Source/Core/AST/DisownExpr.nll"
				pTempVarDecl = null;
#line 127 "../../../Source/Core/AST/DisownExpr.nll"
				pParentParent.AddChildBefore(__3774795561, pParentStatement);
#line 128 "../../../Source/Core/AST/DisownExpr.nll"
				pValidator.ValidateSubtree(pInjectedVarDecl);
			}
			{
#line 132 "../../../Source/Core/AST/DisownExpr.nll"
				AST pLeft = m_pExpression.BaseClone();
#line 134 "../../../Source/Core/AST/DisownExpr.nll"
				NullExpr pRight = new NullExpr();
#line 136 "../../../Source/Core/AST/DisownExpr.nll"
				Token pOperatorToken = new Token();
#line 137 "../../../Source/Core/AST/DisownExpr.nll"
				pOperatorToken.m_eType = Token.Type.TOKEN_EQUALS;
				NumbatLogic.AST __3919013152 = pLeft;
#line 139 "../../../Source/Core/AST/DisownExpr.nll"
				pLeft = null;
				NumbatLogic.NullExpr __534132299 = pRight;
#line 139 "../../../Source/Core/AST/DisownExpr.nll"
				pRight = null;
#line 139 "../../../Source/Core/AST/DisownExpr.nll"
				OperatorExpr pOperatorExpr = OperatorExpr.Create(OperatorExpr.OperatorType.ASSIGNMENT, pOperatorToken, __3919013152, __534132299);
				NumbatLogic.Token __3603785160 = pOperatorToken;
#line 140 "../../../Source/Core/AST/DisownExpr.nll"
				pOperatorToken = null;
#line 140 "../../../Source/Core/AST/DisownExpr.nll"
				pOperatorExpr.m_pOwnedOperatorToken = __3603785160;
#line 142 "../../../Source/Core/AST/DisownExpr.nll"
				ExpressionStmt pExpressionStmt = new ExpressionStmt();
#line 143 "../../../Source/Core/AST/DisownExpr.nll"
				pExpressionStmt.m_pFirstToken = pOperatorExpr.m_pFirstToken;
#line 144 "../../../Source/Core/AST/DisownExpr.nll"
				pExpressionStmt.m_pExpression = pOperatorExpr;
				NumbatLogic.OperatorExpr __2365778377 = pOperatorExpr;
#line 145 "../../../Source/Core/AST/DisownExpr.nll"
				pOperatorExpr = null;
#line 145 "../../../Source/Core/AST/DisownExpr.nll"
				pExpressionStmt.AddChild(__2365778377);
#line 147 "../../../Source/Core/AST/DisownExpr.nll"
				AST pInjectedStmt = pExpressionStmt;
				NumbatLogic.ExpressionStmt __1415267173 = pExpressionStmt;
#line 148 "../../../Source/Core/AST/DisownExpr.nll"
				pExpressionStmt = null;
#line 148 "../../../Source/Core/AST/DisownExpr.nll"
				pParentParent.AddChildBefore(__1415267173, pParentStatement);
#line 149 "../../../Source/Core/AST/DisownExpr.nll"
				pValidator.ValidateSubtree(pInjectedStmt);
			}
			NumbatLogic.InternalString __3313827548 = sTempName;
#line 152 "../../../Source/Core/AST/DisownExpr.nll"
			sTempName = null;
#line 152 "../../../Source/Core/AST/DisownExpr.nll"
			m_sTempVarName = __3313827548;
		}

#line 155 "../../../Source/Core/AST/DisownExpr.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 157 "../../../Source/Core/AST/DisownExpr.nll"
			if (m_sTempVarName != null)
			{
#line 159 "../../../Source/Core/AST/DisownExpr.nll"
				pOutputBuilder.m_sOut.Append(m_sTempVarName.GetExternalString());
#line 160 "../../../Source/Core/AST/DisownExpr.nll"
				return;
			}
#line 163 "../../../Source/Core/AST/DisownExpr.nll"
			if (eLanguage == AST.Language.NLL)
			{
#line 165 "../../../Source/Core/AST/DisownExpr.nll"
				pOutputBuilder.m_sOut.Append("disown ");
			}
#line 168 "../../../Source/Core/AST/DisownExpr.nll"
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}

#line 3 "../../../Source/Core/AST/DisownExpr.nll"
		~DisownExpr()
		{
		}

	}
}

