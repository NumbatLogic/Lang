#line 1 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
namespace NumbatLogic
{
	class DecoratorCall : AST
	{
		public enum DecoratorType
		{
			UNKNOWN,
			DUMMY,
			ENTRY_POINT,
		}

		public DecoratorType m_eDecoratorType;
		public Token m_pDecoratorNameToken;
		public ParamCall m_pParamCall;
#line 16 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
		public static DecoratorCall TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 20 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
			Token pDecoratorToken = pTokenContainer.Peek(pTempOffset);
			if (pDecoratorToken == null)
			{
#line 22 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
				return null;
			}
			if (pDecoratorToken.m_eType != Token.Type.TOKEN_IDENTIFIER)
			{
#line 25 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
				return null;
			}
			InternalString sDecoratorName = new InternalString(pDecoratorToken.GetString());
			if (!sDecoratorName.StartsWith("@"))
			{
#line 29 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
				return null;
			}
#line 30 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 33 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
			ParamCall pParamCall = ParamCall.TryCreate(pTokenContainer, pTempOffset);
			if (pParamCall == null)
			{
#line 35 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
				return null;
			}
			DecoratorCall pDecoratorCall = new DecoratorCall();
			pDecoratorCall.m_eType = AST.Type.AST_DECORATOR_CALL;
			pDecoratorCall.m_pFirstToken = pDecoratorToken;
			pDecoratorCall.m_pDecoratorNameToken = pDecoratorToken;
			pDecoratorCall.m_pParamCall = pParamCall;
#line 43 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
			pDecoratorCall.m_eDecoratorType = DecoratorType.UNKNOWN;
			if (sDecoratorName.IsEqual("@Dummy"))
				pDecoratorCall.m_eDecoratorType = DecoratorType.DUMMY;
			else
#line 46 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
				if (sDecoratorName.IsEqual("@EntryPoint"))
					pDecoratorCall.m_eDecoratorType = DecoratorType.ENTRY_POINT;
			NumbatLogic.ParamCall __1502782304 = pParamCall;
			pParamCall = null;
#line 49 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
			pDecoratorCall.AddChild(__1502782304);
#line 51 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.DecoratorCall __1592970758 = pDecoratorCall;
#line 52 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
			pDecoratorCall = null;
#line 52 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
			return __1592970758;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			if (m_eDecoratorType == DecoratorType.UNKNOWN)
			{
				InternalString sError = new InternalString("Unknown decorator: ");
				sError.Append(m_pDecoratorNameToken.GetString());
				pValidator.AddError(sError.GetExternalString(), m_pDecoratorNameToken.m_sFileName, m_pDecoratorNameToken.m_nLine, m_pDecoratorNameToken.m_nColumn);
			}
#line 64 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
			if (m_eDecoratorType == DecoratorType.ENTRY_POINT)
			{
				if (m_pParent == null || m_pParent.m_eType != AST.Type.AST_FUNCTION_DECL)
				{
					InternalString sError = new InternalString("Decorator ");
					sError.Append(m_pDecoratorNameToken.GetString());
					sError.Append(" must be attached to a function");
					pValidator.AddError(sError.GetExternalString(), m_pDecoratorNameToken.m_sFileName, m_pDecoratorNameToken.m_nLine, m_pDecoratorNameToken.m_nColumn);
				}
			}
#line 75 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
			base.Validate(pValidator, pParent);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			if (eLanguage != AST.Language.NLL)
				return;
#line 83 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
			if (nDepth > 0 && m_pFirstToken != null)
				pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 86 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
			m_pDecoratorNameToken.Stringify(pOutputBuilder.m_sOut);
			m_pParamCall.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
		public DecoratorCall()
		{
		}

	}
}

