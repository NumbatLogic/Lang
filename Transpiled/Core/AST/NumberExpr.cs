#line 1 "../../../Source/Core/AST/NumberExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/NumberExpr.nll"
	class NumberExpr : AST
	{
#line 6 "../../../Source/Core/AST/NumberExpr.nll"
		public NumberExpr(Token pFirstToken)
		{
#line 8 "../../../Source/Core/AST/NumberExpr.nll"
			m_eType = AST.Type.AST_NUMBER;
#line 9 "../../../Source/Core/AST/NumberExpr.nll"
			m_pFirstToken = pFirstToken;
		}

#line 12 "../../../Source/Core/AST/NumberExpr.nll"
		public static NumberExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			Token pToken = pTokenContainer.PeekExpect(pOffsetDatum, Token.Type.TOKEN_NUMBER);
#line 15 "../../../Source/Core/AST/NumberExpr.nll"
			if (pToken == null)
#line 16 "../../../Source/Core/AST/NumberExpr.nll"
				return null;
#line 17 "../../../Source/Core/AST/NumberExpr.nll"
			pOffsetDatum.m_nOffset = pOffsetDatum.m_nOffset + 1;
			NumberExpr pNumberExpr = new NumberExpr(pToken);
			NumbatLogic.NumberExpr __3368034133 = pNumberExpr;
#line 19 "../../../Source/Core/AST/NumberExpr.nll"
			pNumberExpr = null;
#line 19 "../../../Source/Core/AST/NumberExpr.nll"
			return __3368034133;
		}

#line 22 "../../../Source/Core/AST/NumberExpr.nll"
		public override AST BaseClone()
		{
			NumberExpr pNumberExpr = new NumberExpr(m_pFirstToken);
			NumbatLogic.NumberExpr __3368099729 = pNumberExpr;
#line 26 "../../../Source/Core/AST/NumberExpr.nll"
			pNumberExpr = null;
#line 26 "../../../Source/Core/AST/NumberExpr.nll"
			return __3368099729;
		}

#line 29 "../../../Source/Core/AST/NumberExpr.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 31 "../../../Source/Core/AST/NumberExpr.nll"
			m_pValueType = new ValueType(ValueType.Type.INT);
		}

#line 34 "../../../Source/Core/AST/NumberExpr.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 36 "../../../Source/Core/AST/NumberExpr.nll"
			m_pFirstToken.Stringify(pOutputBuilder.m_sOut);
		}

	}
}

