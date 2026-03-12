#line 1 "../../../Source/Core/AST/BoolExpr.nll"
namespace NumbatLogic
{
	class BoolExpr : AST
	{
		public static BoolExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			Token pToken = pTokenContainer.Peek(pOffsetDatum);
			if (pToken == null || (pToken.m_eType != Token.Type.TOKEN_KEYWORD_TRUE && pToken.m_eType != Token.Type.TOKEN_KEYWORD_FALSE))
				return null;
#line 11 "../../../Source/Core/AST/BoolExpr.nll"
			pOffsetDatum.m_nOffset = pOffsetDatum.m_nOffset + 1;
#line 13 "../../../Source/Core/AST/BoolExpr.nll"
			BoolExpr pBoolExpr = new BoolExpr();
			pBoolExpr.m_eType = AST.Type.AST_BOOL_EXPR;
			pBoolExpr.m_pFirstToken = pToken;
			NumbatLogic.BoolExpr __2520519956 = pBoolExpr;
#line 16 "../../../Source/Core/AST/BoolExpr.nll"
			pBoolExpr = null;
#line 16 "../../../Source/Core/AST/BoolExpr.nll"
			return __2520519956;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			m_pValueType = new ValueType(ValueType.Type.BOOL);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			m_pFirstToken.Stringify(pOutputBuilder.m_sOut);
		}

	}
}

