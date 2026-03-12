#line 1 "../../../Source/Core/AST/StringExpr.nll"
namespace NumbatLogic
{
	class StringExpr : AST
	{
		public static StringExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			Token pToken = pTokenContainer.PeekExpect(pOffsetDatum, Token.Type.TOKEN_STRING);
			if (pToken == null)
				return null;
			pOffsetDatum.m_nOffset = pOffsetDatum.m_nOffset + 1;
#line 12 "../../../Source/Core/AST/StringExpr.nll"
			StringExpr pStringExpr = new StringExpr();
			pStringExpr.m_eType = AST.Type.AST_STRING;
			pStringExpr.m_pFirstToken = pToken;
			NumbatLogic.StringExpr __1742613754 = pStringExpr;
#line 15 "../../../Source/Core/AST/StringExpr.nll"
			pStringExpr = null;
#line 15 "../../../Source/Core/AST/StringExpr.nll"
			return __1742613754;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			m_pValueType = new ValueType(ValueType.Type.STRING);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			m_pFirstToken.Stringify(pOutputBuilder.m_sOut);
		}

	}
}

