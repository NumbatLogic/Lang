#line 1 "../../../Source/Core/AST/TTHashExpr.nll"
namespace NumbatLogic
{
#line 3 "../../../Source/Core/AST/TTHashExpr.nll"
	class TTHashExpr : AST
	{
#line 5 "../../../Source/Core/AST/TTHashExpr.nll"
		protected StringExpr m_pStringExpr;
#line 7 "../../../Source/Core/AST/TTHashExpr.nll"
		public TTHashExpr()
		{
#line 9 "../../../Source/Core/AST/TTHashExpr.nll"
			m_eType = AST.Type.AST_TTHASH_EXP;
		}

#line 12 "../../../Source/Core/AST/TTHashExpr.nll"
		public static TTHashExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
#line 14 "../../../Source/Core/AST/TTHashExpr.nll"
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 16 "../../../Source/Core/AST/TTHashExpr.nll"
			Token pTTHashToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_TTHASH);
#line 17 "../../../Source/Core/AST/TTHashExpr.nll"
			if (pTTHashToken == null)
			{
#line 18 "../../../Source/Core/AST/TTHashExpr.nll"
				return null;
			}
#line 19 "../../../Source/Core/AST/TTHashExpr.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 21 "../../../Source/Core/AST/TTHashExpr.nll"
			Token pOpenToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT);
#line 22 "../../../Source/Core/AST/TTHashExpr.nll"
			if (pOpenToken == null)
			{
#line 24 "../../../Source/Core/AST/TTHashExpr.nll"
				Console.Log("expected '(' ");
#line 25 "../../../Source/Core/AST/TTHashExpr.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 26 "../../../Source/Core/AST/TTHashExpr.nll"
				NumbatLogic.Assert.Plz(false);
#line 27 "../../../Source/Core/AST/TTHashExpr.nll"
				return null;
			}
#line 29 "../../../Source/Core/AST/TTHashExpr.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 31 "../../../Source/Core/AST/TTHashExpr.nll"
			StringExpr pStringExpr = StringExpr.TryCreate(pTokenContainer, pTempOffset);
#line 32 "../../../Source/Core/AST/TTHashExpr.nll"
			if (pStringExpr == null)
			{
#line 34 "../../../Source/Core/AST/TTHashExpr.nll"
				Console.Log("expected a string to tthash");
#line 35 "../../../Source/Core/AST/TTHashExpr.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 36 "../../../Source/Core/AST/TTHashExpr.nll"
				NumbatLogic.Assert.Plz(false);
#line 37 "../../../Source/Core/AST/TTHashExpr.nll"
				return null;
			}
#line 40 "../../../Source/Core/AST/TTHashExpr.nll"
			Token pCloseToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT);
#line 41 "../../../Source/Core/AST/TTHashExpr.nll"
			if (pCloseToken == null)
			{
#line 43 "../../../Source/Core/AST/TTHashExpr.nll"
				Console.Log("expected ')' ");
#line 44 "../../../Source/Core/AST/TTHashExpr.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 45 "../../../Source/Core/AST/TTHashExpr.nll"
				NumbatLogic.Assert.Plz(false);
#line 46 "../../../Source/Core/AST/TTHashExpr.nll"
				return null;
			}
#line 48 "../../../Source/Core/AST/TTHashExpr.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 51 "../../../Source/Core/AST/TTHashExpr.nll"
			TTHashExpr pTTHashExpr = new TTHashExpr();
#line 52 "../../../Source/Core/AST/TTHashExpr.nll"
			pTTHashExpr.m_pFirstToken = pTTHashToken;
#line 53 "../../../Source/Core/AST/TTHashExpr.nll"
			pTTHashExpr.m_pStringExpr = pStringExpr;
			NumbatLogic.StringExpr __1742876149 = pStringExpr;
#line 54 "../../../Source/Core/AST/TTHashExpr.nll"
			pStringExpr = null;
#line 54 "../../../Source/Core/AST/TTHashExpr.nll"
			pTTHashExpr.AddChild(__1742876149);
#line 56 "../../../Source/Core/AST/TTHashExpr.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.TTHashExpr __4133333365 = pTTHashExpr;
#line 57 "../../../Source/Core/AST/TTHashExpr.nll"
			pTTHashExpr = null;
#line 57 "../../../Source/Core/AST/TTHashExpr.nll"
			return __4133333365;
		}

#line 60 "../../../Source/Core/AST/TTHashExpr.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 62 "../../../Source/Core/AST/TTHashExpr.nll"
			m_pValueType = new ValueType(ValueType.Type.INT);
		}

#line 65 "../../../Source/Core/AST/TTHashExpr.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 67 "../../../Source/Core/AST/TTHashExpr.nll"
			if (eLanguage == AST.Language.NLL || eLanguage == AST.Language.NLL_DEF)
			{
#line 69 "../../../Source/Core/AST/TTHashExpr.nll"
				pOutputBuilder.m_sOut.Append("tthash(");
#line 70 "../../../Source/Core/AST/TTHashExpr.nll"
				m_pStringExpr.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 71 "../../../Source/Core/AST/TTHashExpr.nll"
				pOutputBuilder.m_sOut.AppendChar(')');
			}
			else
			{
#line 75 "../../../Source/Core/AST/TTHashExpr.nll"
				InternalString sTemp = new InternalString(m_pStringExpr.m_pFirstToken.m_sValue.GetExternalString());
#line 76 "../../../Source/Core/AST/TTHashExpr.nll"
				sTemp.Crop(1, sTemp.GetLength() - 2);
#line 77 "../../../Source/Core/AST/TTHashExpr.nll"
				pOutputBuilder.m_sOut.AppendUint32(ExternalString.GetChecksum(sTemp.GetExternalString()));
			}
		}

	}
}

