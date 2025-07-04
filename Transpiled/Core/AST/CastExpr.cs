namespace NumbatLogic
{
	class CastExpr : AST
	{
		public TypeRef m_pTypeRef;
		public ParamCall m_pParamCall;
		public CastExpr()
		{
			m_eType = AST.Type.AST_CAST_EXP;
		}

		public static CastExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pCastToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_CAST);
			if (pCastToken == null)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			TypeRef pTypeRef = TypeRef.TryCreate(pTokenContainer, pTempOffset);
			if (pTypeRef == null)
			{
				Console.Log("expected TypeRef...");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			ParamCall pParamCall = ParamCall.TryCreate(pTokenContainer, pTempOffset);
			if (pParamCall == null)
			{
				Console.Log("expected ParamCall");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			CastExpr pCastExpr = new CastExpr();
			pCastExpr.m_pFirstToken = pCastToken;
			pCastExpr.m_pTypeRef = pTypeRef;
			pCastExpr.m_pParamCall = pParamCall;
			NumbatLogic.TypeRef __2831758689 = pTypeRef;
			pTypeRef = null;
			pCastExpr.AddChild(__2831758689);
			NumbatLogic.ParamCall __1229252168 = pParamCall;
			pParamCall = null;
			pCastExpr.AddChild(__1229252168);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.CastExpr __2271758890 = pCastExpr;
			pCastExpr = null;
			return __2271758890;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			m_pValueType = m_pTypeRef.CreateValueType();
			if (m_pValueType == null)
			{
				pValidator.AddError("unable to determine what to cast TO", m_pTypeRef.m_pFirstToken.m_sFileName, m_pTypeRef.m_pFirstToken.m_nLine, m_pTypeRef.m_pFirstToken.m_nColumn);
				return;
			}
			AST pFirstChild = m_pParamCall.m_pFirstChild;
			if (pFirstChild == null)
			{
				pValidator.AddError("no FROM param?", m_pParamCall.m_pFirstToken.m_sFileName, m_pParamCall.m_pFirstToken.m_nLine, m_pParamCall.m_pFirstToken.m_nColumn);
				return;
			}
			if (pFirstChild.m_pNextSibling != null)
			{
				pValidator.AddError("too many no FROM params?", pFirstChild.m_pFirstToken.m_sFileName, pFirstChild.m_pFirstToken.m_nLine, pFirstChild.m_pFirstToken.m_nColumn);
				return;
			}
			if (pFirstChild.m_pValueType == null)
			{
				pValidator.AddError("unable to determine what to cast FROM", m_pParamCall.m_pFirstToken.m_sFileName, m_pParamCall.m_pFirstToken.m_nLine, m_pParamCall.m_pFirstToken.m_nColumn);
				return;
			}
			if (m_pValueType.m_ePointerType == TypeRef.PointerType.OWNED)
			{
				pValidator.AddError("cannot cast to an owned pointer", m_pTypeRef.m_pFirstToken.m_sFileName, m_pTypeRef.m_pFirstToken.m_nLine, m_pTypeRef.m_pFirstToken.m_nColumn);
				return;
			}
			if (pFirstChild.m_pValueType.m_ePointerType != m_pValueType.m_ePointerType && m_pValueType.m_ePointerType != TypeRef.PointerType.SHARED)
			{
				pValidator.AddError("must cast to/from the same pointer type (or to shared)", m_pTypeRef.m_pFirstToken.m_sFileName, m_pTypeRef.m_pFirstToken.m_nLine, m_pTypeRef.m_pFirstToken.m_nColumn);
				return;
			}
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			if (eLanguage == AST.Language.NLL_DEF)
			{
				sOut.Append("cast ");
				m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, sOut);
				m_pParamCall.Stringify(eLanguage, eOutputFile, 0, sOut);
			}
			else
			{
				sOut.AppendChar('(');
				m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, sOut);
				sOut.AppendChar(')');
				m_pParamCall.Stringify(eLanguage, eOutputFile, 0, sOut);
			}
		}

	}
}

