#line 1 "../../../Source/Core/AST/EnumDeclValue.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/EnumDeclValue.nll"
	class EnumDeclValue : AST
	{
#line 6 "../../../Source/Core/AST/EnumDeclValue.nll"
		public AST m_pForceValue;
#line 8 "../../../Source/Core/AST/EnumDeclValue.nll"
		public EnumDeclValue(Token pFirstToken)
		{
#line 10 "../../../Source/Core/AST/EnumDeclValue.nll"
			m_eType = AST.Type.ENUM_DECL_VALUE;
#line 11 "../../../Source/Core/AST/EnumDeclValue.nll"
			m_pFirstToken = pFirstToken;
		}

#line 14 "../../../Source/Core/AST/EnumDeclValue.nll"
		public static EnumDeclValue TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_IDENTIFIER);
#line 19 "../../../Source/Core/AST/EnumDeclValue.nll"
			if (pToken == null)
			{
#line 20 "../../../Source/Core/AST/EnumDeclValue.nll"
				return null;
			}
#line 21 "../../../Source/Core/AST/EnumDeclValue.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			EnumDeclValue pEnumDeclValue = new EnumDeclValue(pToken);
			Token pEqualsToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_EQUALS);
#line 27 "../../../Source/Core/AST/EnumDeclValue.nll"
			if (pEqualsToken != null)
			{
#line 29 "../../../Source/Core/AST/EnumDeclValue.nll"
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 31 "../../../Source/Core/AST/EnumDeclValue.nll"
				pEnumDeclValue.m_pForceValue = AST.TryCreateExpression(pTokenContainer, pTempOffset);
#line 32 "../../../Source/Core/AST/EnumDeclValue.nll"
				if (pEnumDeclValue.m_pForceValue == null)
				{
#line 34 "../../../Source/Core/AST/EnumDeclValue.nll"
					Console.Log("expected to parse something...");
#line 35 "../../../Source/Core/AST/EnumDeclValue.nll"
					Assert.Plz(false);
#line 36 "../../../Source/Core/AST/EnumDeclValue.nll"
					return null;
				}
			}
#line 40 "../../../Source/Core/AST/EnumDeclValue.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.EnumDeclValue __478499602 = pEnumDeclValue;
#line 41 "../../../Source/Core/AST/EnumDeclValue.nll"
			pEnumDeclValue = null;
#line 41 "../../../Source/Core/AST/EnumDeclValue.nll"
			return __478499602;
		}

#line 44 "../../../Source/Core/AST/EnumDeclValue.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 46 "../../../Source/Core/AST/EnumDeclValue.nll"
			m_pFirstToken.Stringify(pOutputBuilder.m_sOut);
#line 47 "../../../Source/Core/AST/EnumDeclValue.nll"
			if (m_pForceValue != null)
			{
#line 49 "../../../Source/Core/AST/EnumDeclValue.nll"
				pOutputBuilder.m_sOut.AppendString(" = ");
#line 50 "../../../Source/Core/AST/EnumDeclValue.nll"
				m_pForceValue.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
		}

#line 4 "../../../Source/Core/AST/EnumDeclValue.nll"
		~EnumDeclValue()
		{
		}

	}
}

