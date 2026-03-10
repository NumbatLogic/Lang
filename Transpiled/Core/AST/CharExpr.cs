#line 1 "../../../Source/Core/AST/CharExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/CharExpr.nll"
	class CharExpr : AST
	{
#line 5 "../../../Source/Core/AST/CharExpr.nll"
		public static CharExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 7 "../../../Source/Core/AST/CharExpr.nll"
			Token pToken = pTokenContainer.PeekExpect(pOffsetDatum, Token.Type.TOKEN_CHAR);
#line 8 "../../../Source/Core/AST/CharExpr.nll"
			if (pToken == null)
#line 9 "../../../Source/Core/AST/CharExpr.nll"
				return null;
#line 10 "../../../Source/Core/AST/CharExpr.nll"
			pOffsetDatum.m_nOffset = pOffsetDatum.m_nOffset + 1;
#line 12 "../../../Source/Core/AST/CharExpr.nll"
			CharExpr pCharExpr = new CharExpr();
#line 13 "../../../Source/Core/AST/CharExpr.nll"
			pCharExpr.m_eType = AST.Type.AST_CHAR;
#line 14 "../../../Source/Core/AST/CharExpr.nll"
			pCharExpr.m_pFirstToken = pToken;
			NumbatLogic.CharExpr __2615706591 = pCharExpr;
#line 15 "../../../Source/Core/AST/CharExpr.nll"
			pCharExpr = null;
#line 15 "../../../Source/Core/AST/CharExpr.nll"
			return __2615706591;
		}

#line 18 "../../../Source/Core/AST/CharExpr.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 20 "../../../Source/Core/AST/CharExpr.nll"
			m_pValueType = new ValueType(ValueType.Type.CHAR);
		}

#line 23 "../../../Source/Core/AST/CharExpr.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 25 "../../../Source/Core/AST/CharExpr.nll"
			m_pFirstToken.Stringify(pOutputBuilder.m_sOut);
		}

	}
}

