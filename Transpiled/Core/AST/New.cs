namespace NumbatLogic
{
	class New : AST
	{
		public TypeRef m_pTypeRef;
		public ParamCall m_pParamCall;
		public static New TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			Token pNewToken = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_NEW);
			if (pNewToken == null)
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
				Console.Log("expected ParamCall ");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			New pNew = new New();
			pNew.m_eType = AST.Type.AST_NEW_EXP;
			pNew.m_pFirstToken = pNewToken;
			pNew.m_pTypeRef = pTypeRef;
			pNew.m_pParamCall = pParamCall;
			NumbatLogic.TypeRef __335701768 = pTypeRef;
			pTypeRef = null;
			pNew.AddChild(__335701768);
			NumbatLogic.ParamCall __1084719244 = pParamCall;
			pParamCall = null;
			pNew.AddChild(__1084719244);
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.New __3155456856 = pNew;
			pNew = null;
			return __3155456856;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			m_pValueType = m_pTypeRef.CreateValueType();
			if (m_pValueType == null)
			{
				pValidator.AddError("Unable to compute value type from new", m_pFirstToken.m_sFileName, m_pFirstToken.m_nLine, m_pFirstToken.m_nColumn);
				return;
			}
			if (m_pParamCall.m_pFirstChild != null)
			{
				if (m_pValueType.m_eType != ValueType.Type.CLASS_DECL_VALUE)
				{
					InternalString sTemp = new InternalString("expected to be newing a CLASS_DECL_VALUE, got ");
					m_pValueType.StringifyType(sTemp);
					sTemp.AppendString(" \"");
					sTemp.AppendString(m_pTypeRef.m_pFirstToken.m_sValue.GetExternalString());
					sTemp.AppendString("\"");
					pValidator.AddError(sTemp.GetExternalString(), m_pParamCall.m_pFirstToken.m_sFileName, m_pParamCall.m_pFirstToken.m_nLine, m_pParamCall.m_pFirstToken.m_nColumn);
					return;
				}
				ClassDecl pClassDecl = m_pValueType.m_pClassDecl;
				AST pMember = pClassDecl.m_pFirstChild;
				while (pMember != null)
				{
					if (pMember.m_eType == AST.Type.AST_TOR_DECL)
					{
						TorDecl pTorDecl = (TorDecl)(pMember);
						if (pTorDecl.m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_CONSTRUCT)
						{
							if (pTorDecl.m_pParamDecl.ValidateParamCall(m_pParamCall, null))
							{
								break;
							}
						}
					}
					pMember = pMember.m_pNextSibling;
				}
				if (pMember == null)
				{
					pValidator.AddError("could not find a matching constructor", m_pParamCall.m_pFirstToken.m_sFileName, m_pParamCall.m_pFirstToken.m_nLine, m_pParamCall.m_pFirstToken.m_nColumn);
					return;
				}
			}
			m_pValueType.m_ePointerType = TypeRef.PointerType.TRANSITON;
			AddClassDeclReference(m_pValueType.m_pClassDecl, AST.OutputFile.SOURCE, false);
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			sOut.Append("new ");
			m_pTypeRef.Stringify(eLanguage, eOutputFile, 0, sOut);
			m_pParamCall.Stringify(eLanguage, eOutputFile, 0, sOut);
		}

		public New()
		{
		}

	}
}

