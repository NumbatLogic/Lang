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
				else
				{
					FunctionDecl pFunctionDecl = (FunctionDecl)(m_pParent);
					if (pFunctionDecl.m_pParent == null || pFunctionDecl.m_pParent.m_eType != AST.Type.AST_MEMBER_FUNCTION_DECL || !((MemberFunctionDecl)(pFunctionDecl.m_pParent)).m_bStatic)
						pValidator.AddError("@EntryPoint must be on a static member function", m_pDecoratorNameToken.m_sFileName, m_pDecoratorNameToken.m_nLine, m_pDecoratorNameToken.m_nColumn);
#line 79 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
					if (pFunctionDecl.m_pParamDecl == null || pFunctionDecl.m_pParamDecl.m_pParamVector.GetSize() != 1)
					{
						pValidator.AddError("@EntryPoint function must have exactly 1 parameter: Vector<string>", m_pDecoratorNameToken.m_sFileName, m_pDecoratorNameToken.m_nLine, m_pDecoratorNameToken.m_nColumn);
					}
					else
					{
						VarDecl pParam = pFunctionDecl.m_pParamDecl.m_pParamVector.Get(0);
						TypeRef pTypeRef = pParam.m_pTypeRef;
						bool bValidType = pTypeRef != null && pTypeRef.m_pTypeToken != null && pTypeRef.m_pTypeToken.m_eType == Token.Type.TOKEN_IDENTIFIER && ExternalString.Equal("Vector", pTypeRef.m_pTypeToken.GetString()) && pTypeRef.m_pGenericTypeRefVector.GetSize() == 1;
#line 93 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
						if (bValidType)
						{
							TypeRef pInnerTypeRef = pTypeRef.m_pGenericTypeRefVector.Get(0);
							bValidType = pInnerTypeRef != null && pInnerTypeRef.m_pTypeToken != null && pInnerTypeRef.m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_STRING;
						}
#line 101 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
						if (!bValidType)
							pValidator.AddError("@EntryPoint function parameter must be Vector<string>", pParam.m_pFirstToken.m_sFileName, pParam.m_pFirstToken.m_nLine, pParam.m_pFirstToken.m_nColumn);
					}
				}
			}
#line 107 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
			base.Validate(pValidator, pParent);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			if (eLanguage != AST.Language.NLL)
				return;
#line 115 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
			if (nDepth > 0 && m_pFirstToken != null)
				pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
#line 118 "/home/cliffya/git/Lang/Source/Core/AST/DecoratorCall.nll"
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

