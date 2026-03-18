#line 1 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
namespace NumbatLogic
{
	class TTHashExpr : AST
	{
		protected StringExpr m_pStringExpr;
#line 7 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
		public TTHashExpr()
		{
			m_eType = AST.Type.AST_TTHASH_EXP;
		}

		public static TTHashExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
			Token pTTHashToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_TTHASH);
			if (pTTHashToken == null)
			{
#line 18 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
				return null;
			}
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 21 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
			Token pOpenToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_LEFT);
			if (pOpenToken == null)
			{
				Console.Log("expected '(' ");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 31 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
			StringExpr pStringExpr = StringExpr.TryCreate(pTokenContainer, pTempOffset);
			if (pStringExpr == null)
			{
				Console.Log("expected a string to tthash");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
#line 40 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
			Token pCloseToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_PARENTHESIS_RIGHT);
			if (pCloseToken == null)
			{
				Console.Log("expected ')' ");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 51 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
			TTHashExpr pTTHashExpr = new TTHashExpr();
			pTTHashExpr.m_pFirstToken = pTTHashToken;
			pTTHashExpr.m_pStringExpr = pStringExpr;
			NumbatLogic.StringExpr __1742876149 = pStringExpr;
#line 54 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
			pStringExpr = null;
#line 54 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
			pTTHashExpr.AddChild(__1742876149);
#line 56 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.TTHashExpr __4133333365 = pTTHashExpr;
#line 57 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
			pTTHashExpr = null;
#line 57 "/home/cliffya/git/Lang/Source/Core/AST/TTHashExpr.nll"
			return __4133333365;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			m_pValueType = new ValueType(ValueType.Type.INT);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			if (eLanguage == AST.Language.NLL || eLanguage == AST.Language.NLL_DEF)
			{
				pOutputBuilder.m_sOut.Append("tthash(");
				m_pStringExpr.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				pOutputBuilder.m_sOut.AppendChar(')');
			}
			else
			{
				InternalString sTemp = new InternalString(m_pStringExpr.m_pFirstToken.m_sValue.GetExternalString());
				sTemp.Crop(1, sTemp.GetLength() - 2);
				pOutputBuilder.m_sOut.AppendUint32(ExternalString.GetChecksum(sTemp.GetExternalString()));
			}
		}

	}
}

