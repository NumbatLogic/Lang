#line 0 "../../../Source/Core/AST/EnumDeclValue.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/EnumDeclValue.nll"
	class EnumDeclValue : AST
	{
		public AST m_pForceValue;
		public EnumDeclValue(Token pFirstToken)
		{
			m_eType = AST.Type.ENUM_DECL_VALUE;
			m_pFirstToken = pFirstToken;
		}

		public static EnumDeclValue TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
			if (pToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			EnumDeclValue pEnumDeclValue = new EnumDeclValue(pToken);
			Token pEqualsToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_EQUALS);
			if (pEqualsToken != null)
			{
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
				pEnumDeclValue.m_pForceValue = AST.TryCreateExpression(pTokenContainer, pTempOffset);
				if (pEnumDeclValue.m_pForceValue == null)
				{
					Console.Log("expected to parse something...");
					Assert.Plz(false);
					return null;
				}
			}
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.EnumDeclValue __478499602 = pEnumDeclValue;
			pEnumDeclValue = null;
			return __478499602;
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder out)
		{
			m_pFirstToken.Stringify(out.m_sOut);
			if (m_pForceValue != null)
			{
				out.m_sOut.AppendString(" = ");
				m_pForceValue.Stringify(eLanguage, eOutputFile, 0, out);
			}
		}

		~EnumDeclValue()
		{
		}

	}
}

