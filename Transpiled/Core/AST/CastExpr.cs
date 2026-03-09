#line 1 "../../../Source/Core/AST/CastExpr.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/CastExpr.nll"
	class CastExpr : AST
	{
#line 6 "../../../Source/Core/AST/CastExpr.nll"
		public TypeRef m_pTypeRef;
#line 7 "../../../Source/Core/AST/CastExpr.nll"
		public ParamCall m_pParamCall;
#line 9 "../../../Source/Core/AST/CastExpr.nll"
		public CastExpr()
		{
#line 11 "../../../Source/Core/AST/CastExpr.nll"
			m_eType = AST.Type.AST_CAST_EXP;
		}

#line 14 "../../../Source/Core/AST/CastExpr.nll"
		public static CastExpr TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pCastToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_CAST);
#line 19 "../../../Source/Core/AST/CastExpr.nll"
			if (pCastToken == null)
			{
#line 20 "../../../Source/Core/AST/CastExpr.nll"
				return null;
			}
#line 21 "../../../Source/Core/AST/CastExpr.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			TypeRef pTypeRef = TypeRef.TryCreate(pTokenContainer, pTempOffset);
#line 24 "../../../Source/Core/AST/CastExpr.nll"
			if (pTypeRef == null)
			{
#line 26 "../../../Source/Core/AST/CastExpr.nll"
				Console.Log("expected TypeRef...");
#line 27 "../../../Source/Core/AST/CastExpr.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 28 "../../../Source/Core/AST/CastExpr.nll"
				Assert.Plz(false);
#line 29 "../../../Source/Core/AST/CastExpr.nll"
				return null;
			}
			ParamCall pParamCall = ParamCall.TryCreate(pTokenContainer, pTempOffset);
#line 33 "../../../Source/Core/AST/CastExpr.nll"
			if (pParamCall == null)
			{
#line 35 "../../../Source/Core/AST/CastExpr.nll"
				Console.Log("expected ParamCall");
#line 36 "../../../Source/Core/AST/CastExpr.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 37 "../../../Source/Core/AST/CastExpr.nll"
				Assert.Plz(false);
#line 38 "../../../Source/Core/AST/CastExpr.nll"
				return null;
			}
			CastExpr pCastExpr = new CastExpr();
#line 42 "../../../Source/Core/AST/CastExpr.nll"
			pCastExpr.m_pFirstToken = pCastToken;
#line 43 "../../../Source/Core/AST/CastExpr.nll"
			pCastExpr.m_pTypeRef = pTypeRef;
#line 44 "../../../Source/Core/AST/CastExpr.nll"
			pCastExpr.m_pParamCall = pParamCall;
			NumbatLogic.TypeRef __2942570890 = pTypeRef;
#line 46 "../../../Source/Core/AST/CastExpr.nll"
			pTypeRef = null;
#line 46 "../../../Source/Core/AST/CastExpr.nll"
			pCastExpr.AddChild(__2942570890);
			NumbatLogic.ParamCall __1502782301 = pParamCall;
#line 47 "../../../Source/Core/AST/CastExpr.nll"
			pParamCall = null;
#line 47 "../../../Source/Core/AST/CastExpr.nll"
			pCastExpr.AddChild(__1502782301);
#line 49 "../../../Source/Core/AST/CastExpr.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.CastExpr __4190875401 = pCastExpr;
#line 50 "../../../Source/Core/AST/CastExpr.nll"
			pCastExpr = null;
#line 50 "../../../Source/Core/AST/CastExpr.nll"
			return __4190875401;
		}

#line 53 "../../../Source/Core/AST/CastExpr.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 55 "../../../Source/Core/AST/CastExpr.nll"
			base.Validate(pValidator, pParent);
#line 56 "../../../Source/Core/AST/CastExpr.nll"
			m_pValueType = m_pTypeRef.CreateValueType(pValidator.m_pResolver);
#line 58 "../../../Source/Core/AST/CastExpr.nll"
			if (m_pValueType == null)
			{
#line 60 "../../../Source/Core/AST/CastExpr.nll"
				pValidator.AddError("unable to determine what to cast TO", m_pTypeRef.m_pFirstToken.m_sFileName, m_pTypeRef.m_pFirstToken.m_nLine, m_pTypeRef.m_pFirstToken.m_nColumn);
#line 61 "../../../Source/Core/AST/CastExpr.nll"
				return;
			}
			AST pFirstChild = m_pParamCall.m_pFirstChild;
#line 65 "../../../Source/Core/AST/CastExpr.nll"
			if (pFirstChild == null)
			{
#line 67 "../../../Source/Core/AST/CastExpr.nll"
				pValidator.AddError("no FROM param?", m_pParamCall.m_pFirstToken.m_sFileName, m_pParamCall.m_pFirstToken.m_nLine, m_pParamCall.m_pFirstToken.m_nColumn);
#line 68 "../../../Source/Core/AST/CastExpr.nll"
				return;
			}
#line 71 "../../../Source/Core/AST/CastExpr.nll"
			if (pFirstChild.m_pNextSibling != null)
			{
#line 73 "../../../Source/Core/AST/CastExpr.nll"
				pValidator.AddError("too many no FROM params?", pFirstChild.m_pFirstToken.m_sFileName, pFirstChild.m_pFirstToken.m_nLine, pFirstChild.m_pFirstToken.m_nColumn);
#line 74 "../../../Source/Core/AST/CastExpr.nll"
				return;
			}
#line 77 "../../../Source/Core/AST/CastExpr.nll"
			if (pFirstChild.m_pValueType == null)
			{
#line 79 "../../../Source/Core/AST/CastExpr.nll"
				pValidator.AddError("unable to determine what to cast FROM", m_pParamCall.m_pFirstToken.m_sFileName, m_pParamCall.m_pFirstToken.m_nLine, m_pParamCall.m_pFirstToken.m_nColumn);
#line 80 "../../../Source/Core/AST/CastExpr.nll"
				return;
			}
#line 83 "../../../Source/Core/AST/CastExpr.nll"
			if (m_pValueType.m_ePointerType == TypeRef.PointerType.OWNED)
			{
#line 85 "../../../Source/Core/AST/CastExpr.nll"
				pValidator.AddError("cannot cast to an owned pointer", m_pTypeRef.m_pFirstToken.m_sFileName, m_pTypeRef.m_pFirstToken.m_nLine, m_pTypeRef.m_pFirstToken.m_nColumn);
#line 86 "../../../Source/Core/AST/CastExpr.nll"
				return;
			}
#line 89 "../../../Source/Core/AST/CastExpr.nll"
			if (pFirstChild.m_pValueType.m_ePointerType != m_pValueType.m_ePointerType && m_pValueType.m_ePointerType != TypeRef.PointerType.SHARED)
			{
#line 91 "../../../Source/Core/AST/CastExpr.nll"
				pValidator.AddError("must cast to/from the same pointer type (or to shared)", m_pTypeRef.m_pFirstToken.m_sFileName, m_pTypeRef.m_pFirstToken.m_nLine, m_pTypeRef.m_pFirstToken.m_nColumn);
#line 92 "../../../Source/Core/AST/CastExpr.nll"
				return;
			}
		}

#line 98 "../../../Source/Core/AST/CastExpr.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 100 "../../../Source/Core/AST/CastExpr.nll"
			if (eLanguage == AST.Language.NLL_DEF)
			{
#line 102 "../../../Source/Core/AST/CastExpr.nll"
				pOutputBuilder.m_sOut.Append("cast ");
#line 103 "../../../Source/Core/AST/CastExpr.nll"
				m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 104 "../../../Source/Core/AST/CastExpr.nll"
				m_pParamCall.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
			else
			{
#line 108 "../../../Source/Core/AST/CastExpr.nll"
				pOutputBuilder.m_sOut.AppendChar('(');
#line 109 "../../../Source/Core/AST/CastExpr.nll"
				m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 110 "../../../Source/Core/AST/CastExpr.nll"
				pOutputBuilder.m_sOut.AppendChar(')');
#line 111 "../../../Source/Core/AST/CastExpr.nll"
				m_pParamCall.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			}
		}

	}
}

