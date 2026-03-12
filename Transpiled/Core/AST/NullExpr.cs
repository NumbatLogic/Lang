#line 1 "../../../Source/Core/AST/NullExpr.nll"
namespace NumbatLogic
{
	class NullExpr : AST
	{
		public NullExpr()
		{
			m_eType = AST.Type.NULL_EXPR;
		}

		public static NullExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 14 "../../../Source/Core/AST/NullExpr.nll"
			Token pNullToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_NULL);
			if (pNullToken == null)
			{
#line 16 "../../../Source/Core/AST/NullExpr.nll"
				return null;
			}
#line 17 "../../../Source/Core/AST/NullExpr.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 19 "../../../Source/Core/AST/NullExpr.nll"
			NullExpr pNullExpr = new NullExpr();
			pNullExpr.m_pFirstToken = pNullToken;
#line 22 "../../../Source/Core/AST/NullExpr.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.NullExpr __4021522189 = pNullExpr;
#line 23 "../../../Source/Core/AST/NullExpr.nll"
			pNullExpr = null;
#line 23 "../../../Source/Core/AST/NullExpr.nll"
			return __4021522189;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			m_pValueType = new ValueType(ValueType.Type.NULL_VALUE);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			if (eLanguage == AST.Language.CPP)
				pOutputBuilder.m_sOut.Append("0");
			else
				pOutputBuilder.m_sOut.Append("null");
		}

	}
}

