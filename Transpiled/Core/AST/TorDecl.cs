#line 1 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
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
#line 13 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
		public static TorDecl TryCreate(TokenContainer pTokenContainer, OffsetDatum pOffsetDatum, ClassDecl pParentClassDecl)
		{
			OffsetDatum pTempOffset = OffsetDatum.Create(pOffsetDatum);
#line 17 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			AccessLevel pAccessLevel = AccessLevel.TryCreate(pTokenContainer, pTempOffset);
			if (pAccessLevel == null)
			{
#line 19 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
				return null;
			}
			Token pTypeToken = pTokenContainer.Peek(pTempOffset);
			if (pTypeToken == null || pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_CONSTRUCT && pTypeToken.m_eType != Token.Type.TOKEN_KEYWORD_DESTRUCT)
			{
#line 23 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
				return null;
			}
#line 24 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 26 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			ParamDecl pParamDecl = ParamDecl.TryCreate(pTokenContainer, pTempOffset);
			if (pParamDecl == null)
			{
				Console.Log("expected ParamDecl");
				Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
				Assert.Plz(false);
				return null;
			}
#line 35 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			TorDecl pTorDecl = new TorDecl();
#line 37 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
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
#line 48 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
					Token pBase = pTokenContainer.PeekExpect(pTempOffset, Token.Type.TOKEN_KEYWORD_BASE);
					if (pBase == null)
					{
						Console.Log("expected base!");
						Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
						Assert.Plz(false);
						return null;
					}
					pTempOffset.m_nOffset = pTempOffset.m_nOffset + 1;
#line 58 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
					ParamCall pParamCall = ParamCall.TryCreate(pTokenContainer, pTempOffset);
					if (pParamCall == null)
					{
						InternalString sTemp = new InternalString("expected ParamCall ");
						sTemp.Append(pTokenContainer.StringifyOffset(pTempOffset));
						Console.Log(sTemp.GetExternalString());
						Assert.Plz(false);
						return null;
					}
#line 68 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
					pTorDecl.m_pBaseParamCall = pParamCall;
					NumbatLogic.ParamCall __1502913502 = pParamCall;
#line 69 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
					pParamCall = null;
#line 69 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
					pTorDecl.AddChild(__1502913502);
				}
#line 72 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
				pScope = Scope.TryCreate(pTokenContainer, pTempOffset, false);
				if (pScope == null)
				{
					Console.Log("expected scope");
					Console.Log(pTokenContainer.StringifyOffset(pTempOffset));
					Assert.Plz(false);
				}
			}
#line 81 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			pTorDecl.m_eType = AST.Type.AST_TOR_DECL;
			pTorDecl.m_pParent = pParentClassDecl;
			pTorDecl.m_pParentClassDecl = pParentClassDecl;
			pTorDecl.m_pFirstToken = pTypeToken;
			pTorDecl.m_pAccessLevel = pAccessLevel;
			pTorDecl.m_pTypeToken = pTypeToken;
			pTorDecl.m_pParamDecl = pParamDecl;
			pTorDecl.m_pScope = pScope;
			pTorDecl.m_sDisambiguate = "";
			NumbatLogic.AccessLevel __99271240 = pAccessLevel;
			pAccessLevel = null;
#line 91 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			pTorDecl.AddChild(__99271240);
			NumbatLogic.ParamDecl __3703057184 = pParamDecl;
#line 92 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			pParamDecl = null;
#line 92 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			pTorDecl.AddChild(__3703057184);
			if (pScope != null)
			{
				NumbatLogic.Scope __1530946527 = pScope;
#line 94 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
				pScope = null;
#line 94 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
				pTorDecl.AddChild(__1530946527);
			}
			pOffsetDatum.Set(pTempOffset);
			NumbatLogic.TorDecl __3519495631 = pTorDecl;
#line 97 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			pTorDecl = null;
#line 97 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			return __3519495631;
		}

		public override void Validate(Validator pValidator, OperatorExpr pParent)
		{
			base.Validate(pValidator, pParent);
#line 106 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			if (m_pParentClassDecl != null && m_pBaseParamCall != null)
			{
#line 109 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
				ClassDecl pBaseClass = m_pParentClassDecl.GetBaseClassDecl(pValidator);
#line 111 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
				if (pBaseClass == null)
				{
					pValidator.AddError("no base class??", m_pBaseParamCall.m_pFirstToken.m_sFileName, m_pBaseParamCall.m_pFirstToken.m_nLine, m_pBaseParamCall.m_pFirstToken.m_nColumn);
					return;
				}
#line 117 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
				AST pMember = pBaseClass.m_pFirstChild;
				while (pMember != null)
				{
					if (pMember.m_eType == AST.Type.AST_TOR_DECL)
					{
						TorDecl pTorDecl = (TorDecl)(pMember);
						if (pTorDecl.m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_CONSTRUCT)
						{
							if (pTorDecl.m_pParamDecl.ValidateParamCall(m_pBaseParamCall, pValidator, false))
							{
								break;
							}
						}
					}
					pMember = pMember.m_pNextSibling;
				}
#line 134 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
				if (pMember == null)
				{
					InternalString sTemp = new InternalString("could not find a matching BASE constructor in ");
					sTemp.AppendString(pBaseClass.m_pNameToken.GetString());
					pValidator.AddError(sTemp.GetExternalString(), m_pBaseParamCall.m_pFirstToken.m_sFileName, m_pBaseParamCall.m_pFirstToken.m_nLine, m_pBaseParamCall.m_pFirstToken.m_nColumn);
					return;
				}
			}
		}

		public override void Stringify(Language eLanguage, OutputFile eOutputFile, int nDepth, OutputBuilder pOutputBuilder)
		{
			bool bGeneric = m_pParentClassDecl != null && m_pParentClassDecl.m_pGenericTypeDeclVector.GetSize() > 0;
#line 148 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			if (bGeneric && eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
				return;
#line 152 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			if (eLanguage == AST.Language.CS)
			{
				if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_DESTRUCT)
				{
					if (m_pParentClassDecl.m_bDisposable)
					{
						Util.Pad(nDepth, pOutputBuilder.m_sOut);
						pOutputBuilder.m_sOut.AppendChar('~');
						m_pParentClassDecl.m_pNameToken.Stringify(pOutputBuilder.m_sOut);
						pOutputBuilder.m_sOut.Append(m_sDisambiguate);
						m_pParamDecl.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
						pOutputBuilder.m_sOut.AppendChar('\n');
						Util.Pad(nDepth, pOutputBuilder.m_sOut);
						pOutputBuilder.m_sOut.Append("{\n");
						Util.Pad(nDepth + 1, pOutputBuilder.m_sOut);
						pOutputBuilder.m_sOut.Append("Dispose();\n");
						Util.Pad(nDepth, pOutputBuilder.m_sOut);
						pOutputBuilder.m_sOut.Append("}\n");
						pOutputBuilder.m_sOut.AppendChar('\n');
#line 172 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
						Util.Pad(nDepth, pOutputBuilder.m_sOut);
						pOutputBuilder.m_sOut.Append("public void Dispose()\n");
						Util.Pad(nDepth, pOutputBuilder.m_sOut);
						pOutputBuilder.m_sOut.Append("{\n");
#line 177 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
						nDepth++;
						m_pScope.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
						Util.Pad(nDepth, pOutputBuilder.m_sOut);
						pOutputBuilder.m_sOut.Append("System.GC.SuppressFinalize(this);\n");
#line 182 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
						nDepth--;
#line 184 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
						Util.Pad(nDepth, pOutputBuilder.m_sOut);
						pOutputBuilder.m_sOut.Append("}\n");
						pOutputBuilder.m_sOut.AppendChar('\n');
#line 188 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
						return;
					}
				}
			}
#line 193 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			pOutputBuilder.UpdateSourceLocation(eLanguage, m_pFirstToken);
			Util.Pad(nDepth, pOutputBuilder.m_sOut);
#line 196 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			if (!(eLanguage == AST.Language.CS && m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_DESTRUCT))
				if (!(eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE))
				{
					m_pAccessLevel.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
					if (eLanguage == AST.Language.CPP)
						pOutputBuilder.m_sOut.AppendChar(':');
					pOutputBuilder.m_sOut.AppendChar(' ');
				}
#line 205 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			if (eLanguage == AST.Language.NLL_DEF)
			{
				if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_DESTRUCT)
					pOutputBuilder.m_sOut.Append("destruct");
				else
					pOutputBuilder.m_sOut.Append("construct");
			}
			else
			{
				if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.SOURCE)
				{
					m_pParentClassDecl.m_pNameToken.Stringify(pOutputBuilder.m_sOut);
					pOutputBuilder.m_sOut.Append("::");
				}
#line 220 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
				if (m_pTypeToken.m_eType == Token.Type.TOKEN_KEYWORD_DESTRUCT)
				{
					if (eLanguage == AST.Language.CPP && eOutputFile == AST.OutputFile.HEADER)
						pOutputBuilder.m_sOut.Append("virtual ");
#line 225 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
					pOutputBuilder.m_sOut.Append("~");
				}
#line 228 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
				m_pParentClassDecl.m_pNameToken.Stringify(pOutputBuilder.m_sOut);
			}
			pOutputBuilder.m_sOut.Append(m_sDisambiguate);
			m_pParamDecl.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
#line 235 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			if ((!bGeneric && eOutputFile == AST.OutputFile.HEADER) || eLanguage == AST.Language.NLL_DEF)
			{
				pOutputBuilder.m_sOut.Append(";\n");
				return;
			}
#line 241 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
			if (m_pScope == null)
			{
				pOutputBuilder.m_sOut.AppendString(";\n");
			}
			else
			{
				if (m_pBaseParamCall != null)
				{
					pOutputBuilder.m_sOut.Append(" : ");
					if (eLanguage == AST.Language.CPP)
						m_pParentClassDecl.m_pBaseTypeRef.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
					else
						pOutputBuilder.m_sOut.Append("base");
					m_pBaseParamCall.Stringify(eLanguage, eOutputFile, 0, pOutputBuilder);
				}
				pOutputBuilder.m_sOut.AppendChar('\n');
				m_pScope.Stringify(eLanguage, eOutputFile, nDepth, pOutputBuilder);
				pOutputBuilder.m_sOut.AppendChar('\n');
			}
		}

#line 3 "/home/cliffya/git/Lang/Source/Core/AST/TorDecl.nll"
		public TorDecl()
		{
		}

	}
}

