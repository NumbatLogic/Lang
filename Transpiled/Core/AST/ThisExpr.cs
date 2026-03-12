#line 1 "../../../Source/Core/AST/ThisExpr.nll"
namespace NumbatLogic
{
	class ThisExpr : AST
	{
		public static ThisExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 9 "../../../Source/Core/AST/ThisExpr.nll"
			Token pThisToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_THIS);
			if (pThisToken == null)
			{
#line 11 "../../../Source/Core/AST/ThisExpr.nll"
				return null;
			}
#line 12 "../../../Source/Core/AST/ThisExpr.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 14 "../../../Source/Core/AST/ThisExpr.nll"
			ThisExpr pThisExpr = new ThisExpr();
#line 16 "../../../Source/Core/AST/ThisExpr.nll"
			pThisExpr.m_eType = AST.Type.THIS_EXPR;
			pThisExpr.m_pFirstToken = pThisToken;
#line 19 "../../../Source/Core/AST/ThisExpr.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.ThisExpr __1365567169 = pThisExpr;
#line 20 "../../../Source/Core/AST/ThisExpr.nll"
			pThisExpr = null;
#line 20 "../../../Source/Core/AST/ThisExpr.nll"
			return __1365567169;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			m_pValueType = new ValueType(ValueType.Type.CLASS_DECL_VALUE);
#line 27 "../../../Source/Core/AST/ThisExpr.nll"
			AST pTestParent = m_pParent;
			while (true)
			{
				if (pTestParent == null)
				{
					pValidator.AddError("this is not the child of a ClassDec???", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
					return;
				}
#line 36 "../../../Source/Core/AST/ThisExpr.nll"
				if (pTestParent.m_eType == AST.Type.AST_CLASS_DECL)
					break;
#line 39 "../../../Source/Core/AST/ThisExpr.nll"
				pTestParent = pTestParent.m_pParent;
			}
#line 42 "../../../Source/Core/AST/ThisExpr.nll"
			m_pValueType.m_pClassDecl = (ClassDecl)(pTestParent);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			pOutputBuilder.m_sOut.Append("this");
		}

	}
}

