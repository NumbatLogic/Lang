#line 1 "../../../Source/Core/AST/New.nll"
namespace NumbatLogic
{
	class New : AST
	{
		public TypeRef m_pTypeRef;
		public ParamCall m_pParamCall;
#line 8 "../../../Source/Core/AST/New.nll"
		public static New TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 12 "../../../Source/Core/AST/New.nll"
			Token pNewToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_NEW);
			if (pNewToken == null)
			{
#line 14 "../../../Source/Core/AST/New.nll"
				return null;
			}
#line 15 "../../../Source/Core/AST/New.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 17 "../../../Source/Core/AST/New.nll"
			TypeRef pTypeRef = TypeRef.TryCreate(pTokenContainer, pTempOffset);
			if (pTypeRef == null)
			{
				Console.Log("expected TypeRef...");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				Assert.Plz(false);
				return null;
			}
#line 26 "../../../Source/Core/AST/New.nll"
			ParamCall pParamCall = ParamCall.TryCreate(pTokenContainer, pTempOffset);
			if (pParamCall == null)
			{
				Console.Log("expected ParamCall ");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				Assert.Plz(false);
				return null;
			}
#line 35 "../../../Source/Core/AST/New.nll"
			New pNew = new New();
#line 37 "../../../Source/Core/AST/New.nll"
			pNew.m_eType = AST.Type.AST_NEW_EXP;
			pNew.m_pFirstToken = pNewToken;
			pNew.m_pTypeRef = pTypeRef;
			pNew.m_pParamCall = pParamCall;
			NumbatLogic.TypeRef __2942570887 = pTypeRef;
			pTypeRef = null;
#line 42 "../../../Source/Core/AST/New.nll"
			pNew.AddChild(__2942570887);
			NumbatLogic.ParamCall __1502782298 = pParamCall;
#line 43 "../../../Source/Core/AST/New.nll"
			pParamCall = null;
#line 43 "../../../Source/Core/AST/New.nll"
			pNew.AddChild(__1502782298);
#line 45 "../../../Source/Core/AST/New.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.New __4218231602 = pNew;
#line 46 "../../../Source/Core/AST/New.nll"
			pNew = null;
#line 46 "../../../Source/Core/AST/New.nll"
			return __4218231602;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			m_pValueType = m_pTypeRef.CreateValueType(pValidator.m_pResolver);
			if (m_pValueType == null)
			{
				pValidator.AddError("Unable to compute value type from new", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				return;
			}
#line 60 "../../../Source/Core/AST/New.nll"
			if (m_pParamCall.m_pFirstChild != null)
			{
#line 64 "../../../Source/Core/AST/New.nll"
				if (m_pValueType.m_eType != ValueType.Type.CLASS_DECL_VALUE)
				{
					InternalString sTemp = new InternalString("expected to be newing a CLASS_DECL_VALUE, got ");
					m_pValueType.StringifyType(sTemp);
					sTemp.AppendString(" \"");
					sTemp.AppendString(m_pTypeRef.m_pFirstToken.m_sValue.GetExternalString());
					sTemp.AppendString("\"");
#line 72 "../../../Source/Core/AST/New.nll"
					pValidator.AddError(sTemp.GetExternalString(), m_pParamCall.m_pFirstToken.m_sFileName, m_pParamCall.m_pFirstToken.m_nLine, m_pParamCall.m_pFirstToken.m_nColumn);
					return;
				}
#line 76 "../../../Source/Core/AST/New.nll"
				ClassDecl pClassDecl = m_pValueType.m_pClassDecl;
				AST pMember = pClassDecl.m_pFirstChild;
				while (pMember != null)
				{
					if (pMember.m_eType == AST.Type.AST_TOR_DECL)
					{
						TorDecl pTorDecl = (TorDecl)(pMember);
						if (pTorDecl.m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_CONSTRUCT)
						{
							if (pTorDecl.m_pParamDecl.ValidateParamCall(m_pParamCall, pValidator, false))
							{
								break;
							}
						}
					}
					pMember = pMember.m_pNextSibling;
				}
#line 94 "../../../Source/Core/AST/New.nll"
				if (pMember == null)
				{
					pValidator.AddError("could not find a matching constructor", m_pParamCall.m_pFirstToken.m_sFileName, m_pParamCall.m_pFirstToken.m_nLine, m_pParamCall.m_pFirstToken.m_nColumn);
					return;
				}
			}
#line 102 "../../../Source/Core/AST/New.nll"
			m_pValueType.m_ePointerType = TypeRef.PointerType.TRANSITON;
#line 104 "../../../Source/Core/AST/New.nll"
			AddClassDeclReference(m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			pOutputBuilder.m_sOut.Append("new ");
			m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
			m_pParamCall.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}

#line 3 "../../../Source/Core/AST/New.nll"
		public New()
		{
		}

	}
}

