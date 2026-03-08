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
			Token pNullToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_NULL);
			if (pNullToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			NullExpr pNullExpr = new NullExpr();
			pNullExpr.m_pFirstToken = pNullToken;
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.NullExpr __4021522189 = pNullExpr;
			pNullExpr = null;
			return __4021522189;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			m_pValueType = new ValueType(ValueType.Type.NULL_VALUE);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder out)
		{
			if (eLanguage == AST.Language.CPP)
				out.m_sOut.Append("0");
			else
				out.m_sOut.Append("null");
		}

	}
}

