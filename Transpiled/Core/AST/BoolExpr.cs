#line 1 "../../../Source/Core/AST/BoolExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/BoolExpr.nll"
	class BoolExpr : AST
	{
#line 5 "../../../Source/Core/AST/BoolExpr.nll"
		public static BoolExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 7 "../../../Source/Core/AST/BoolExpr.nll"
			Token pToken = pTokenContainer.Peek(pOffsetDatum);
#line 8 "../../../Source/Core/AST/BoolExpr.nll"
			if (pToken == null || (pToken.m_eType != Token.Type.TOKEN_KEYWORD_TRUE && pToken.m_eType != Token.Type.TOKEN_KEYWORD_FALSE))
#line 9 "../../../Source/Core/AST/BoolExpr.nll"
				return null;
#line 11 "../../../Source/Core/AST/BoolExpr.nll"
			pOffsetDatum.m_nOffset = pOffsetDatum.m_nOffset + 1;
#line 13 "../../../Source/Core/AST/BoolExpr.nll"
			BoolExpr pBoolExpr = new BoolExpr();
#line 14 "../../../Source/Core/AST/BoolExpr.nll"
			pBoolExpr.m_eType = AST.Type.AST_BOOL_EXPR;
#line 15 "../../../Source/Core/AST/BoolExpr.nll"
			pBoolExpr.m_pFirstToken = pToken;
			NumbatLogic.BoolExpr __2520519956 = pBoolExpr;
#line 16 "../../../Source/Core/AST/BoolExpr.nll"
			pBoolExpr = null;
#line 16 "../../../Source/Core/AST/BoolExpr.nll"
			return __2520519956;
		}

#line 19 "../../../Source/Core/AST/BoolExpr.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 21 "../../../Source/Core/AST/BoolExpr.nll"
			m_pValueType = new ValueType(ValueType.Type.BOOL);
		}

#line 24 "../../../Source/Core/AST/BoolExpr.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 26 "../../../Source/Core/AST/BoolExpr.nll"
			m_pFirstToken.Stringify(pOutputBuilder.m_sOut);
		}

	}
}

