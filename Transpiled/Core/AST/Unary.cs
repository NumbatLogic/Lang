#line 1 "../../../Source/Core/AST/Unary.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/Unary.nll"
	class Unary : AST
	{
#line 5 "../../../Source/Core/AST/Unary.nll"
		public AST m_pExpression;
#line 7 "../../../Source/Core/AST/Unary.nll"
		public static Unary TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 9 "../../../Source/Core/AST/Unary.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 11 "../../../Source/Core/AST/Unary.nll"
			Token pToken = pTokenContainer.Peek(pTempOffset);
#line 12 "../../../Source/Core/AST/Unary.nll"
			if (pToken == null || pToken.m_eType != Token.Type.TOKEN_MINUS && pToken.m_eType != Token.Type.TOKEN_BANG && pToken.m_eType != Token.Type.TOKEN_PLUS_PLUS && pToken.m_eType != Token.Type.TOKEN_MINUS_MINUS && pToken.m_eType != Token.Type.TOKEN_TILDE)
			{
#line 13 "../../../Source/Core/AST/Unary.nll"
				return null;
			}
#line 14 "../../../Source/Core/AST/Unary.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 16 "../../../Source/Core/AST/Unary.nll"
			AST pExpression = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 18 "../../../Source/Core/AST/Unary.nll"
			Unary pUnary = new Unary();
#line 20 "../../../Source/Core/AST/Unary.nll"
			pUnary.m_eType = AST.Type.AST_UNARY;
#line 21 "../../../Source/Core/AST/Unary.nll"
			pUnary.m_pFirstToken = pToken;
#line 22 "../../../Source/Core/AST/Unary.nll"
			pUnary.m_pExpression = pExpression;
			NumbatLogic.AST __1929334314 = pExpression;
#line 24 "../../../Source/Core/AST/Unary.nll"
			pExpression = null;
#line 24 "../../../Source/Core/AST/Unary.nll"
			pUnary.AddChild(__1929334314);
#line 26 "../../../Source/Core/AST/Unary.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.Unary __2876314212 = pUnary;
#line 27 "../../../Source/Core/AST/Unary.nll"
			pUnary = null;
#line 27 "../../../Source/Core/AST/Unary.nll"
			return __2876314212;
		}

#line 30 "../../../Source/Core/AST/Unary.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 33 "../../../Source/Core/AST/Unary.nll"
			base.Validate(pValidator, pParent);
#line 35 "../../../Source/Core/AST/Unary.nll"
			if (m_pExpression.m_pValueType == null)
			{
#line 37 "../../../Source/Core/AST/Unary.nll"
				InternalString sTemp = new InternalString("expression did not validate?? ");
#line 38 "../../../Source/Core/AST/Unary.nll"
				m_pExpression.StringifyType(sTemp);
#line 39 "../../../Source/Core/AST/Unary.nll"
				pValidator.AddError(sTemp.GetExternalString(), m_pExpression.m_pFirstToken.m_sFileName, m_pExpression.m_pFirstToken.m_nLine, m_pExpression.m_pFirstToken.m_nColumn);
#line 40 "../../../Source/Core/AST/Unary.nll"
				return;
			}
#line 43 "../../../Source/Core/AST/Unary.nll"
			m_pValueType = m_pExpression.m_pValueType.Clone();
		}

#line 47 "../../../Source/Core/AST/Unary.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 49 "../../../Source/Core/AST/Unary.nll"
			m_pFirstToken.Stringify(pOutputBuilder.m_sOut);
#line 50 "../../../Source/Core/AST/Unary.nll"
			m_pExpression.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}

#line 3 "../../../Source/Core/AST/Unary.nll"
		public Unary()
		{
		}

	}
}

