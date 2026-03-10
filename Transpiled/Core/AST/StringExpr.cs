#line 1 "../../../Source/Core/AST/StringExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/StringExpr.nll"
	class StringExpr : AST
	{
#line 5 "../../../Source/Core/AST/StringExpr.nll"
		public static StringExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 7 "../../../Source/Core/AST/StringExpr.nll"
			Token pToken = pTokenContainer.PeekExpect(pOffsetDatum, Token.Type.TOKEN_STRING);
#line 8 "../../../Source/Core/AST/StringExpr.nll"
			if (pToken == null)
#line 9 "../../../Source/Core/AST/StringExpr.nll"
				return null;
#line 10 "../../../Source/Core/AST/StringExpr.nll"
			pOffsetDatum.m_nOffset = pOffsetDatum.m_nOffset + 1;
#line 12 "../../../Source/Core/AST/StringExpr.nll"
			StringExpr pStringExpr = new StringExpr();
#line 13 "../../../Source/Core/AST/StringExpr.nll"
			pStringExpr.m_eType = AST.Type.AST_STRING;
#line 14 "../../../Source/Core/AST/StringExpr.nll"
			pStringExpr.m_pFirstToken = pToken;
			NumbatLogic.StringExpr __1742613754 = pStringExpr;
#line 15 "../../../Source/Core/AST/StringExpr.nll"
			pStringExpr = null;
#line 15 "../../../Source/Core/AST/StringExpr.nll"
			return __1742613754;
		}

#line 18 "../../../Source/Core/AST/StringExpr.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 20 "../../../Source/Core/AST/StringExpr.nll"
			m_pValueType = new ValueType(ValueType.Type.STRING);
		}

#line 23 "../../../Source/Core/AST/StringExpr.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 25 "../../../Source/Core/AST/StringExpr.nll"
			m_pFirstToken.Stringify(pOutputBuilder.m_sOut);
		}

	}
}

