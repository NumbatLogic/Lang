#line 1 "../../../Source/Core/AST/StringExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/StringExpr.nll"
	class StringExpr : AST
	{
#line 6 "../../../Source/Core/AST/StringExpr.nll"
		public static StringExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			Token pToken = pTokenContainer.PeekExpect(pOffsetDatum, Token.Type.TOKEN_STRING);
#line 9 "../../../Source/Core/AST/StringExpr.nll"
			if (pToken == null)
#line 10 "../../../Source/Core/AST/StringExpr.nll"
				return null;
#line 11 "../../../Source/Core/AST/StringExpr.nll"
			pOffsetDatum.m_nOffset = pOffsetDatum.m_nOffset + 1;
			StringExpr pStringExpr = new StringExpr();
#line 14 "../../../Source/Core/AST/StringExpr.nll"
			pStringExpr.m_eType = AST.Type.AST_STRING;
#line 15 "../../../Source/Core/AST/StringExpr.nll"
			pStringExpr.m_pFirstToken = pToken;
			NumbatLogic.StringExpr __1742613754 = pStringExpr;
#line 16 "../../../Source/Core/AST/StringExpr.nll"
			pStringExpr = null;
#line 16 "../../../Source/Core/AST/StringExpr.nll"
			return __1742613754;
		}

#line 19 "../../../Source/Core/AST/StringExpr.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 21 "../../../Source/Core/AST/StringExpr.nll"
			m_pValueType = new ValueType(ValueType.Type.STRING);
		}

#line 24 "../../../Source/Core/AST/StringExpr.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 26 "../../../Source/Core/AST/StringExpr.nll"
			m_pFirstToken.Stringify(pOutputBuilder.m_sOut);
		}

	}
}

