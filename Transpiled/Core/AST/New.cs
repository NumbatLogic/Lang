#line 1 "../../../Source/Core/AST/New.nll"
namespace NumbatLogic
{
#line 4 "../../../Source/Core/AST/New.nll"
	class New : AST
	{
#line 6 "../../../Source/Core/AST/New.nll"
		public TypeRef m_pTypeRef;
#line 7 "../../../Source/Core/AST/New.nll"
		public ParamCall m_pParamCall;
#line 9 "../../../Source/Core/AST/New.nll"
		public static New TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pNewToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_NEW);
#line 14 "../../../Source/Core/AST/New.nll"
			if (pNewToken == null)
			{
#line 15 "../../../Source/Core/AST/New.nll"
				return null;
			}
#line 16 "../../../Source/Core/AST/New.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			TypeRef pTypeRef = TypeRef.TryCreate(pTokenContainer, pTempOffset);
#line 19 "../../../Source/Core/AST/New.nll"
			if (pTypeRef == null)
			{
#line 21 "../../../Source/Core/AST/New.nll"
				Console.Log("expected TypeRef...");
#line 22 "../../../Source/Core/AST/New.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 23 "../../../Source/Core/AST/New.nll"
				Assert.Plz(false);
#line 24 "../../../Source/Core/AST/New.nll"
				return null;
			}
			ParamCall pParamCall = ParamCall.TryCreate(pTokenContainer, pTempOffset);
#line 28 "../../../Source/Core/AST/New.nll"
			if (pParamCall == null)
			{
#line 30 "../../../Source/Core/AST/New.nll"
				Console.Log("expected ParamCall ");
#line 31 "../../../Source/Core/AST/New.nll"
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
#line 32 "../../../Source/Core/AST/New.nll"
				Assert.Plz(false);
#line 33 "../../../Source/Core/AST/New.nll"
				return null;
			}
			New pNew = new New();
#line 38 "../../../Source/Core/AST/New.nll"
			pNew.m_eType = AST.Type.AST_NEW_EXP;
#line 39 "../../../Source/Core/AST/New.nll"
			pNew.m_pFirstToken = pNewToken;
#line 40 "../../../Source/Core/AST/New.nll"
			pNew.m_pTypeRef = pTypeRef;
#line 41 "../../../Source/Core/AST/New.nll"
			pNew.m_pParamCall = pParamCall;
			NumbatLogic.TypeRef __2942570887 = pTypeRef;
#line 43 "../../../Source/Core/AST/New.nll"
			pTypeRef = null;
#line 43 "../../../Source/Core/AST/New.nll"
			pNew.AddChild(__2942570887);
			NumbatLogic.ParamCall __1502782298 = pParamCall;
#line 44 "../../../Source/Core/AST/New.nll"
			pParamCall = null;
#line 44 "../../../Source/Core/AST/New.nll"
			pNew.AddChild(__1502782298);
#line 46 "../../../Source/Core/AST/New.nll"
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.New __4218231602 = pNew;
#line 47 "../../../Source/Core/AST/New.nll"
			pNew = null;
#line 47 "../../../Source/Core/AST/New.nll"
			return __4218231602;
		}

#line 50 "../../../Source/Core/AST/New.nll"
		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
#line 52 "../../../Source/Core/AST/New.nll"
			base.Validate(pValidator, pParent);
#line 53 "../../../Source/Core/AST/New.nll"
			m_pValueType = m_pTypeRef.CreateValueType(pValidator.m_pResolver);
#line 54 "../../../Source/Core/AST/New.nll"
			if (m_pValueType == null)
			{
#line 56 "../../../Source/Core/AST/New.nll"
				pValidator.AddError("Unable to compute value type from new", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
#line 57 "../../../Source/Core/AST/New.nll"
				return;
			}
#line 61 "../../../Source/Core/AST/New.nll"
			if (m_pParamCall.m_pFirstChild != null)
			{
#line 65 "../../../Source/Core/AST/New.nll"
				if (m_pValueType.m_eType != ValueType.Type.CLASS_DECL_VALUE)
				{
					InternalString sTemp = new InternalString("expected to be newing a CLASS_DECL_VALUE, got ");
#line 68 "../../../Source/Core/AST/New.nll"
					m_pValueType.StringifyType(sTemp);
#line 69 "../../../Source/Core/AST/New.nll"
					sTemp.AppendString(" \"");
#line 70 "../../../Source/Core/AST/New.nll"
					sTemp.AppendString(m_pTypeRef.m_pFirstToken.m_sValue.GetExternalString());
#line 71 "../../../Source/Core/AST/New.nll"
					sTemp.AppendString("\"");
#line 73 "../../../Source/Core/AST/New.nll"
					pValidator.AddError(sTemp.GetExternalString(), m_pParamCall.m_pFirstToken.m_sFileName, m_pParamCall.m_pFirstToken.m_nLine, m_pParamCall.m_pFirstToken.m_nColumn);
#line 74 "../../../Source/Core/AST/New.nll"
					return;
				}
				ClassDecl pClassDecl = m_pValueType.m_pClassDecl;
				AST pMember = pClassDecl.m_pFirstChild;
#line 79 "../../../Source/Core/AST/New.nll"
				while (pMember != null)
				{
#line 81 "../../../Source/Core/AST/New.nll"
					if (pMember.m_eType == AST.Type.AST_TOR_DECL)
					{
						TorDecl pTorDecl = (TorDecl)(pMember);
#line 84 "../../../Source/Core/AST/New.nll"
						if (pTorDecl.m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_CONSTRUCT)
						{
#line 86 "../../../Source/Core/AST/New.nll"
							if (pTorDecl.m_pParamDecl.ValidateParamCall(m_pParamCall, pValidator, false))
							{
#line 88 "../../../Source/Core/AST/New.nll"
								break;
							}
						}
					}
#line 92 "../../../Source/Core/AST/New.nll"
					pMember = pMember.m_pNextSibling;
				}
#line 95 "../../../Source/Core/AST/New.nll"
				if (pMember == null)
				{
#line 97 "../../../Source/Core/AST/New.nll"
					pValidator.AddError("could not find a matching constructor", m_pParamCall.m_pFirstToken.m_sFileName, m_pParamCall.m_pFirstToken.m_nLine, m_pParamCall.m_pFirstToken.m_nColumn);
#line 98 "../../../Source/Core/AST/New.nll"
					return;
				}
			}
#line 103 "../../../Source/Core/AST/New.nll"
			m_pValueType.m_ePointerType = TypeRef.PointerType.TRANSITON;
#line 105 "../../../Source/Core/AST/New.nll"
			AddClassDeclReference(m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
		}

#line 108 "../../../Source/Core/AST/New.nll"
		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
#line 110 "../../../Source/Core/AST/New.nll"
			pOutputBuilder.m_sOut.Append("new ");
#line 111 "../../../Source/Core/AST/New.nll"
			m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 112 "../../../Source/Core/AST/New.nll"
			m_pParamCall.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
		}

#line 4 "../../../Source/Core/AST/New.nll"
		public New()
		{
		}

	}
}

