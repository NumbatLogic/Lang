namespace NumbatLogic
{
	class TorDecl : AST
	{
		public ClassDecl m_pParentClassDecl;
		public AccessLevel m_pAccessLevel;
		public Token m_pTypeToken;
		public ParamDecl m_pParamDecl;
		public ParamCall m_pBaseParamCall;
		public Scope m_pScope;
		public string m_sDisambiguate;
		public static TorDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, ClassDecl pParentClassDecl)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
			AccessLevel pAccessLevel = AccessLevel.TryCreate(pTokenContainer, pTempOffset);
			if (pAccessLevel == null)
			{
				return null;
			}
			Token pTypeToken = pTokenContainer.Peek(pTempOffset);
			if (pTypeToken == null || pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_CONSTRUCT && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_DESTRUCT)
			{
				return null;
			}
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			ParamDecl pParamDecl = ParamDecl.TryCreate(pTokenContainer, pTempOffset);
			if (pParamDecl == null)
			{
				Console.Log("expected ParamDecl");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				NumbatLogic.Assert.Plz(false);
				return null;
			}
			TorDecl pTorDecl = new TorDecl();
			Scope pScope = null;
			Token pSemicolon = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_SEMICOLON);
			if (pSemicolon != null)
				pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
			else
			{
				Token pColon = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_COLON);
				if (pColon != null)
				{
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					Token pBase = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_BASE);
					if (pBase == null)
					{
						Console.Log("expected base!");
						Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
						NumbatLogic.Assert.Plz(false);
						return null;
					}
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
					ParamCall pParamCall = ParamCall.TryCreate(pTokenContainer, pTempOffset);
					if (pParamCall == null)
					{
						InternalString sTemp = new InternalString("expected ParamCall ");
						sTemp.Append(pTokenContainer.StringifyOffset(pTempOffset));
						Console.Log(sTemp.GetExternalString());
						NumbatLogic.Assert.Plz(false);
						return null;
					}
					pTorDecl.m_pBaseParamCall = pParamCall;
					NumbatLogic.ParamCall __3594827602 = pParamCall;
					pParamCall = null;
					pTorDecl.AddChild(__3594827602);
				}
				pScope = Scope.TryCreate(pTokenContainer, pTempOffset, false);
				if (pScope == null)
				{
					Console.Log("expected scope");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					NumbatLogic.Assert.Plz(false);
				}
			}
			pTorDecl.m_eType = AST.Type.AST_TOR_DECL;
			pTorDecl.m_pParent = pParentClassDecl;
			pTorDecl.m_pParentClassDecl = pParentClassDecl;
			pTorDecl.m_pFirstToken = pTypeToken;
			pTorDecl.m_pAccessLevel = pAccessLevel;
			pTorDecl.m_pTypeToken = pTypeToken;
			pTorDecl.m_pParamDecl = pParamDecl;
			pTorDecl.m_pScope = pScope;
			pTorDecl.m_sDisambiguate = "";
			NumbatLogic.AccessLevel __223710120 = pAccessLevel;
			pAccessLevel = null;
			pTorDecl.AddChild(__223710120);
			NumbatLogic.ParamDecl __2571153082 = pParamDecl;
			pParamDecl = null;
			pTorDecl.AddChild(__2571153082);
			if (pScope != null)
			{
				NumbatLogic.Scope __2972552052 = pScope;
				pScope = null;
				pTorDecl.AddChild(__2972552052);
			}
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.TorDecl __2869605135 = pTorDecl;
			pTorDecl = null;
			return __2869605135;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
			if (m_pParentClassDecl != null && m_pBaseParamCall != null)
			{
				ClassDecl pBaseClass = m_pParentClassDecl.GetBaseClassDecl();
				if (pBaseClass == null)
				{
					pValidator.AddError("no base class??", m_pBaseParamCall.m_pFirstToken.m_sFileName, m_pBaseParamCall.m_pFirstToken.m_nLine, m_pBaseParamCall.m_pFirstToken.m_nColumn);
					return;
				}
				AST pMember = pBaseClass.m_pFirstChild;
				while (pMember != null)
				{
					if (pMember.m_eType == AST.Type.AST_TOR_DECL)
					{
						TorDecl pTorDecl = (TorDecl)(pMember);
						if (pTorDecl.m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_CONSTRUCT)
						{
							if (pTorDecl.m_pParamDecl.ValidateParamCall(m_pBaseParamCall, null))
							{
								break;
							}
						}
					}
					pMember = pMember.m_pNextSibling;
				}
				if (pMember == null)
				{
					InternalString sTemp = new InternalString("could not find a matching BASE constructor in ");
					sTemp.AppendString(pBaseClass.m_pNameToken.GetString());
					pValidator.AddError(sTemp.GetExternalString(), m_pBaseParamCall.m_pFirstToken.m_sFileName, m_pBaseParamCall.m_pFirstToken.m_nLine, m_pBaseParamCall.m_pFirstToken.m_nColumn);
					return;
				}
			}
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, InternalString sOut)
		{
			bool bGeneric = m_pParentClassDecl != null && m_pParentClassDecl.m_pGenericTypeDeclVector.GetSize() > 0;
			if (bGeneric && eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
				return;
			Util.Pad(nDepth, sOut);
			if (!(eLanguage == AST.Language.CS && m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_DESTRUCT))
				if (!(eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE))
				{
					m_pAccessLevel.Stringify(eLanguage, eOutputFile, 0, sOut);
					if (eLanguage == AST.Language.CPP)
						sOut.AppendChar(':');
					sOut.AppendChar(' ');
				}
			if (eLanguage == AST.Language.NLL_DEF)
			{
				if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_DESTRUCT)
					sOut.Append("destruct");
				else
					sOut.Append("construct");
			}
			else
			{
				if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
				{
					m_pParentClassDecl.m_pNameToken.Stringify(sOut);
					sOut.Append("::");
				}
				if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_DESTRUCT)
				{
					if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.HEADER)
						sOut.Append("virtual ");
					sOut.Append("~");
				}
				m_pParentClassDecl.m_pNameToken.Stringify(sOut);
			}
			sOut.Append(m_sDisambiguate);
			m_pParamDecl.Stringify(eLanguage, eOutputFile, 0, sOut);
			if ((!bGeneric && eOutputFile == AST.OutputFile.HEADER) || eLanguage == AST.Language.NLL_DEF)
			{
				sOut.Append(";\n");
				return;
			}
			if (m_pScope == null)
			{
				sOut.AppendString(";\n");
			}
			else
			{
				if (m_pBaseParamCall != null)
				{
					sOut.Append(" : ");
					if (eLanguage == AST.Language.CPP)
						m_pParentClassDecl.m_pBaseToken.Stringify(sOut);
					else
						sOut.Append("base");
					m_pBaseParamCall.Stringify(eLanguage, eOutputFile, 0, sOut);
				}
				sOut.AppendChar('\n');
				m_pScope.Stringify(eLanguage, eOutputFile, nDepth, sOut);
				sOut.AppendChar('\n');
			}
		}

		public TorDecl()
		{
		}

	}
}

