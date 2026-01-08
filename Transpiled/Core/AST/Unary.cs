namespace NumbatLogic
{
	class Unary : AST
	{
		public AST m_pExpression;
		public static Unary TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pToken = pTokenContainer.Peek(pTempOffset);
			if (pToken == null || pToken.m_eType != Token.Type.TOKEN_MINUS && pToken.m_eType != Token.Type.TOKEN_BANG && pToken.m_eType != Token.Type.TOKEN_PLUS_PLUS && pToken.m_eType != Token.Type.TOKEN_MINUS_MINUS && pToken.m_eType != Token.Type.TOKEN_TILDE)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			Unary pUnary = new Unary();
			pUnary.m_eType = AST.Type.AST_UNARY;
			pUnary.m_pFirstToken = pToken;
			pUnary.m_pExpression = pExpression;
			NumbatLogic.AST __1929334314 = pExpression;
			pExpression = null;
			pUnary.AddChild(__1929334314);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.Unary __2876314212 = pUnary;
			pUnary = null;
			return __2876314212;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			if (m_pExpression.m_pValueType == null)
			{
				InternalString sTemp = new InternalString("expression did not validate?? ");
				m_pExpression.StringifyType(sTemp);
				pValidator.AddError(sTemp.GetExternalString(), m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
				return;
			}
			m_pValueType = m_pExpression.m_pValueType.Clone();
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			m_pFirstToken.Stringify(sOut);
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, sOut);
		}

		public Unary()
		{
		}

	}
}

