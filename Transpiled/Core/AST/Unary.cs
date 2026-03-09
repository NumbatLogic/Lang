#line 1 "../../../Source/Core/AST/Unary.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/Unary.nll"
	class Unary : AST
	{
#line 6 "../../../Source/Core/AST/Unary.nll"
		public AST m_pExpression;
#line 8 "../../../Source/Core/AST/Unary.nll"
		public static Unary TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pToken = pTokenContainer.Peek(pTempOffset);
#line 13 "../../../Source/Core/AST/Unary.nll"
			if (pToken == null || pToken.m_eType != Token.Type.TOKEN_MINUS && pToken.m_eType != Token.Type.TOKEN_BANG && pToken.m_eType != Token.Type.TOKEN_PLUS_PLUS && pToken.m_eType != Token.Type.TOKEN_MINUS_MINUS && pToken.m_eType != Token.Type.TOKEN_TILDE)
			{
#line 14 "../../../Source/Core/AST/Unary.nll"
				return null;
			}
#line 15 "../../../Source/Core/AST/Unary.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
			Unary pUnary = new Unary();
#line 21 "../../../Source/Core/AST/Unary.nll"
			pUnary.m_eType = AST.Type.AST_UNARY;
#line 22 "../../../Source/Core/AST/Unary.nll"
			pUnary.m_pFirstToken = pToken;
#line 23 "../../../Source/Core/AST/Unary.nll"
			pUnary.m_pExpression = pExpression;
			NumbatLogic.AST __1929334314 = pExpression;
#line 25 "../../../Source/Core/AST/Unary.nll"
			pExpression = null;
#line 25 "../../../Source/Core/AST/Unary.nll"
			pUnary.AddChild(__1929334314);
#line 27 "../../../Source/Core/AST/Unary.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.Unary __2876314212 = pUnary;
#line 28 "../../../Source/Core/AST/Unary.nll"
			pUnary = null;
#line 28 "../../../Source/Core/AST/Unary.nll"
			return __2876314212;
		}

#line 31 "../../../Source/Core/AST/Unary.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 34 "../../../Source/Core/AST/Unary.nll"
			base.Validate(pValidator, pParent);
#line 36 "../../../Source/Core/AST/Unary.nll"
			if (m_pExpression.m_pValueType == null)
			{
				InternalString sTemp = new InternalString("expression did not validate?? ");
#line 39 "../../../Source/Core/AST/Unary.nll"
				m_pExpression.StringifyType(sTemp);
#line 40 "../../../Source/Core/AST/Unary.nll"
				pValidator.AddError(sTemp.GetExternalString(), m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
#line 41 "../../../Source/Core/AST/Unary.nll"
				return;
			}
#line 44 "../../../Source/Core/AST/Unary.nll"
			m_pValueType = m_pExpression.m_pValueType.Clone();
		}

#line 48 "../../../Source/Core/AST/Unary.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 50 "../../../Source/Core/AST/Unary.nll"
			m_pFirstToken.Stringify(pOutputBuilder.m_sOut);
#line 51 "../../../Source/Core/AST/Unary.nll"
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}

#line 4 "../../../Source/Core/AST/Unary.nll"
		public Unary()
		{
		}

	}
}

