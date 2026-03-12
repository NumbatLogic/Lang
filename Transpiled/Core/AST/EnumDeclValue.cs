#line 1 "../../../Source/Core/AST/EnumDeclValue.nll"
namespace NumbatLogic
{
	class EnumDeclValue : AST
	{
		public AST m_pForceValue;
#line 7 "../../../Source/Core/AST/EnumDeclValue.nll"
		public EnumDeclValue(Token pFirstToken)
		{
			m_eType = AST.Type.ENUM_DECL_VALUE;
			m_pFirstToken = pFirstToken;
		}

		public static EnumDeclValue TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 17 "../../../Source/Core/AST/EnumDeclValue.nll"
			Token pToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
			if (pToken == null)
			{
#line 19 "../../../Source/Core/AST/EnumDeclValue.nll"
				return null;
			}
#line 20 "../../../Source/Core/AST/EnumDeclValue.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 22 "../../../Source/Core/AST/EnumDeclValue.nll"
			EnumDeclValue pEnumDeclValue = new EnumDeclValue(pToken);
#line 25 "../../../Source/Core/AST/EnumDeclValue.nll"
			Token pEqualsToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_EQUALS);
			if (pEqualsToken != null)
			{
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 30 "../../../Source/Core/AST/EnumDeclValue.nll"
				pEnumDeclValue.m_pForceValue = AST.TryCreateExpression(pTokenContainer, pTempOffset);
				if (pEnumDeclValue.m_pForceValue == null)
				{
					Console.Log("expected to parse something...");
					Assert.Plz(false);
					return null;
				}
			}
#line 39 "../../../Source/Core/AST/EnumDeclValue.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.EnumDeclValue __478499602 = pEnumDeclValue;
#line 40 "../../../Source/Core/AST/EnumDeclValue.nll"
			pEnumDeclValue = null;
#line 40 "../../../Source/Core/AST/EnumDeclValue.nll"
			return __478499602;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			m_pFirstToken.Stringify(pOutputBuilder.m_sOut);
			if (m_pForceValue != null)
			{
				pOutputBuilder.m_sOut.AppendString(" = ");
				m_pForceValue.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
		}

#line 3 "../../../Source/Core/AST/EnumDeclValue.nll"
		~EnumDeclValue()
		{
		}

	}
}

