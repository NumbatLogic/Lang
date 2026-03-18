#line 1 "/home/cliffya/git/Lang/Source/Core/AST/CharExpr.nll"
namespace NumbatLogic
{
	class CharExpr : AST
	{
		public static CharExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			Token pToken = pTokenContainer.PeekExpect(pOffsetDatum, Token.Type.TOKEN_CHAR);
			if (pToken == null)
				return null;
			pOffsetDatum.m_nOffset = pOffsetDatum.m_nOffset + 1;
#line 12 "/home/cliffya/git/Lang/Source/Core/AST/CharExpr.nll"
			CharExpr pCharExpr = new CharExpr();
			pCharExpr.m_eType = AST.Type.AST_CHAR;
			pCharExpr.m_pFirstToken = pToken;
			NumbatLogic.CharExpr __2615706591 = pCharExpr;
#line 15 "/home/cliffya/git/Lang/Source/Core/AST/CharExpr.nll"
			pCharExpr = null;
#line 15 "/home/cliffya/git/Lang/Source/Core/AST/CharExpr.nll"
			return __2615706591;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			m_pValueType = new ValueType(ValueType.Type.CHAR);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			m_pFirstToken.Stringify(pOutputBuilder.m_sOut);
		}

	}
}

