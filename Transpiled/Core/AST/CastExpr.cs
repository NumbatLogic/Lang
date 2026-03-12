#line 1 "../../../Source/Core/AST/CastExpr.nll"
namespace NumbatLogic
{
	class CastExpr : AST
	{
		public TypeRef m_pTypeRef;
		public ParamCall m_pParamCall;
#line 8 "../../../Source/Core/AST/CastExpr.nll"
		public CastExpr()
		{
			m_eType = AST.Type.AST_CAST_EXP;
		}

		public static CastExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 17 "../../../Source/Core/AST/CastExpr.nll"
			Token pCastToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_CAST);
			if (pCastToken == null)
			{
#line 19 "../../../Source/Core/AST/CastExpr.nll"
				return null;
			}
#line 20 "../../../Source/Core/AST/CastExpr.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 22 "../../../Source/Core/AST/CastExpr.nll"
			TypeRef pTypeRef = TypeRef.TryCreate(pTokenContainer, pTempOffset);
			if (pTypeRef == null)
			{
				Console.Log("expected TypeRef...");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				Assert.Plz(false);
				return null;
			}
#line 31 "../../../Source/Core/AST/CastExpr.nll"
			ParamCall pParamCall = ParamCall.TryCreate(pTokenContainer, pTempOffset);
			if (pParamCall == null)
			{
				Console.Log("expected ParamCall");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				Assert.Plz(false);
				return null;
			}
#line 40 "../../../Source/Core/AST/CastExpr.nll"
			CastExpr pCastExpr = new CastExpr();
			pCastExpr.m_pFirstToken = pCastToken;
			pCastExpr.m_pTypeRef = pTypeRef;
			pCastExpr.m_pParamCall = pParamCall;
			NumbatLogic.TypeRef __2942570890 = pTypeRef;
			pTypeRef = null;
#line 45 "../../../Source/Core/AST/CastExpr.nll"
			pCastExpr.AddChild(__2942570890);
			NumbatLogic.ParamCall __1502782301 = pParamCall;
#line 46 "../../../Source/Core/AST/CastExpr.nll"
			pParamCall = null;
#line 46 "../../../Source/Core/AST/CastExpr.nll"
			pCastExpr.AddChild(__1502782301);
#line 48 "../../../Source/Core/AST/CastExpr.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.CastExpr __4190875401 = pCastExpr;
#line 49 "../../../Source/Core/AST/CastExpr.nll"
			pCastExpr = null;
#line 49 "../../../Source/Core/AST/CastExpr.nll"
			return __4190875401;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			m_pValueType = m_pTypeRef.CreateValueType(pValidator.m_pResolver);
#line 57 "../../../Source/Core/AST/CastExpr.nll"
			if (m_pValueType == null)
			{
				pValidator.AddError("unable to determine what to cast TO", m_pTypeRef.m_pFirstToken.m_sFileName, m_pTypeRef.m_pFirstToken.m_nLine, m_pTypeRef.m_pFirstToken.m_nColumn);
				return;
			}
#line 63 "../../../Source/Core/AST/CastExpr.nll"
			AST pFirstChild = m_pParamCall.m_pFirstChild;
			if (pFirstChild == null)
			{
				pValidator.AddError("no FROM param?", m_pParamCall.m_pFirstToken.m_sFileName, m_pParamCall.m_pFirstToken.m_nLine, m_pParamCall.m_pFirstToken.m_nColumn);
				return;
			}
#line 70 "../../../Source/Core/AST/CastExpr.nll"
			if (pFirstChild.m_pNextSibling != null)
			{
				pValidator.AddError("too many no FROM params?", pFirstChild.m_pFirstToken.m_sFileName, pFirstChild.m_pFirstToken.m_nLine, pFirstChild.m_pFirstToken.m_nColumn);
				return;
			}
#line 76 "../../../Source/Core/AST/CastExpr.nll"
			if (pFirstChild.m_pValueType == null)
			{
				pValidator.AddError("unable to determine what to cast FROM", m_pParamCall.m_pFirstToken.m_sFileName, m_pParamCall.m_pFirstToken.m_nLine, m_pParamCall.m_pFirstToken.m_nColumn);
				return;
			}
#line 82 "../../../Source/Core/AST/CastExpr.nll"
			if (m_pValueType.m_ePointerType == TypeRef.PointerType.OWNED)
			{
				pValidator.AddError("cannot cast to an owned pointer", m_pTypeRef.m_pFirstToken.m_sFileName, m_pTypeRef.m_pFirstToken.m_nLine, m_pTypeRef.m_pFirstToken.m_nColumn);
				return;
			}
#line 88 "../../../Source/Core/AST/CastExpr.nll"
			if (pFirstChild.m_pValueType.m_ePointerType != m_pValueType.m_ePointerType && m_pValueType.m_ePointerType != TypeRef.PointerType.SHARED)
			{
				pValidator.AddError("must cast to/from the same pointer type (or to shared)", m_pTypeRef.m_pFirstToken.m_sFileName, m_pTypeRef.m_pFirstToken.m_nLine, m_pTypeRef.m_pFirstToken.m_nColumn);
				return;
			}
		}

#line 97 "../../../Source/Core/AST/CastExpr.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			if (eLanguage == AST.Language.NLL_DEF)
			{
				pOutputBuilder.m_sOut.Append("cast ");
				m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				m_pParamCall.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
			else
			{
				pOutputBuilder.m_sOut.AppendChar('(');
				m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				pOutputBuilder.m_sOut.AppendChar(')');
				m_pParamCall.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
		}

	}
}

