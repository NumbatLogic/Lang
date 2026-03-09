#line 1 "../../../Source/Core/AST/BoolExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/BoolExpr.nll"
	class BoolExpr : AST
	{
#line 6 "../../../Source/Core/AST/BoolExpr.nll"
		public static BoolExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			Token pToken = pTokenContainer.Peek(pOffsetDatum);
#line 9 "../../../Source/Core/AST/BoolExpr.nll"
			if (pToken == null || (pToken.m_eType != Token.Type.TOKEN_KEYWORD_TRUE && pToken.m_eType != Token.Type.TOKEN_KEYWORD_FALSE))
#line 10 "../../../Source/Core/AST/BoolExpr.nll"
				return null;
#line 12 "../../../Source/Core/AST/BoolExpr.nll"
			pOffsetDatum.m_nOffset = pOffsetDatum.m_nOffset + 1;
			BoolExpr pBoolExpr = new BoolExpr();
#line 15 "../../../Source/Core/AST/BoolExpr.nll"
			pBoolExpr.m_eType = AST.Type.AST_BOOL_EXPR;
#line 16 "../../../Source/Core/AST/BoolExpr.nll"
			pBoolExpr.m_pFirstToken = pToken;
			NumbatLogic.BoolExpr __2520519956 = pBoolExpr;
#line 17 "../../../Source/Core/AST/BoolExpr.nll"
			pBoolExpr = null;
#line 17 "../../../Source/Core/AST/BoolExpr.nll"
			return __2520519956;
		}

#line 20 "../../../Source/Core/AST/BoolExpr.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 22 "../../../Source/Core/AST/BoolExpr.nll"
			m_pValueType = new ValueType(ValueType.Type.BOOL);
		}

#line 25 "../../../Source/Core/AST/BoolExpr.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 27 "../../../Source/Core/AST/BoolExpr.nll"
			m_pFirstToken.Stringify(pOutputBuilder.m_sOut);
		}

	}
}

