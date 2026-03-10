#line 1 "../../../Source/Core/AST/EnumDeclValue.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/EnumDeclValue.nll"
	class EnumDeclValue : AST
	{
#line 5 "../../../Source/Core/AST/EnumDeclValue.nll"
		public AST m_pForceValue;
#line 7 "../../../Source/Core/AST/EnumDeclValue.nll"
		public EnumDeclValue(Token pFirstToken)
		{
#line 9 "../../../Source/Core/AST/EnumDeclValue.nll"
			m_eType = AST.Type.ENUM_DECL_VALUE;
#line 10 "../../../Source/Core/AST/EnumDeclValue.nll"
			m_pFirstToken = pFirstToken;
		}

#line 13 "../../../Source/Core/AST/EnumDeclValue.nll"
		public static EnumDeclValue TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 15 "../../../Source/Core/AST/EnumDeclValue.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 17 "../../../Source/Core/AST/EnumDeclValue.nll"
			Token pToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
#line 18 "../../../Source/Core/AST/EnumDeclValue.nll"
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
#line 26 "../../../Source/Core/AST/EnumDeclValue.nll"
			if (pEqualsToken != null)
			{
#line 28 "../../../Source/Core/AST/EnumDeclValue.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 30 "../../../Source/Core/AST/EnumDeclValue.nll"
				pEnumDeclValue.m_pForceValue = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 31 "../../../Source/Core/AST/EnumDeclValue.nll"
				if (pEnumDeclValue.m_pForceValue == null)
				{
#line 33 "../../../Source/Core/AST/EnumDeclValue.nll"
					Console.Log("expected to parse something...");
#line 34 "../../../Source/Core/AST/EnumDeclValue.nll"
					Assert.Plz(false);
#line 35 "../../../Source/Core/AST/EnumDeclValue.nll"
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

#line 43 "../../../Source/Core/AST/EnumDeclValue.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 45 "../../../Source/Core/AST/EnumDeclValue.nll"
			m_pFirstToken.Stringify(pOutputBuilder.m_sOut);
#line 46 "../../../Source/Core/AST/EnumDeclValue.nll"
			if (m_pForceValue != null)
			{
#line 48 "../../../Source/Core/AST/EnumDeclValue.nll"
				pOutputBuilder.m_sOut.AppendString(" = ");
#line 49 "../../../Source/Core/AST/EnumDeclValue.nll"
				m_pForceValue.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
		}

#line 3 "../../../Source/Core/AST/EnumDeclValue.nll"
		~EnumDeclValue()
		{
		}

	}
}

